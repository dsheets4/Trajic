# TaxiVis product for analyzing trends in taxi trajectories.
# Copyright (C) 2012  David Sheets (dsheets4@kent.edu)
#
# This is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.

# -----------------------------------------------------------------------------
from optparse import OptionParser
import time
import calendar
import re
import urllib.parse
import urllib.request
import urllib.error
import socket
import chardet
import codecs
import sys

import Utils

def file_len(fname):
    with open(fname) as f:
        for i, l in enumerate(f):
            pass
    return i+1


# -----------------------------------------------------------------------------
# Main() start here

# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
# Parse out the command line options for the script.
parser = OptionParser()
parser.add_option("-i", "--input", dest="inputFile",
      help="CSV format taxi input file", metavar="FILE")
parser.add_option("-d", "--date", dest="sDate",
      help="Date to limit in the overall file")

(options, args) = parser.parse_args()


# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
sUrlGetRoadId = "http://210.75.252.45:81/itsservice/itsdata.ashx?action=getroadinfobylatlng&lat=%f&lng=%f"
def GetRoadId( fLat, fLon ):

   nRetVal = -1
   sUrlReq = ""
   try:
      # Construct the HTTP GET URL and make the request
      req = urllib.request.Request(sUrlGetRoadId % (fLat,fLon), None)
      sUrlReq = req.get_full_url()
      response = urllib.request.urlopen(req)

      # Parse the return value and hand-off to the caller.
      sReturn = "%s" % response.read()
      csv = sReturn.split(',')

      if len(csv) > 1:
         nRetVal = int(csv[1].replace("'",""))
   except socket.error as msg:
      sUrlReq = sUrlReq + ": socket.error : %s" % msg
      pass
   except urllib.error.URLError:
      sUrlReq = sUrlReq + ": urllib.error.URLError Exception caught"
      pass
   except NameError:
      sUrlReq = sUrlReq + "NameError Exception caught"
      pass

   return (nRetVal,sUrlReq)

# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
# Process some of the command line inputs
rawdata = open(options.inputFile, 'rb').readline()
result  = chardet.detect(rawdata)
charenc = result['encoding']
print(result)
inFile  = codecs.open(options.inputFile, 'r', encoding=charenc)

sOutFileName = "%s.good" % options.inputFile
nProcessedLines = file_len( sOutFileName )
print( "Already processed %d lines\n" % nProcessedLines )
outFile = open(sOutFileName, 'a')
fTimeStart = calendar.timegm(time.strptime(options.sDate, "%Y-%m-%d"))
fTimeEnd   = fTimeStart + (86400)
print( "Time filtered output file is: %s" % (sOutFileName) )


# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
nRecTotalIn         = 0     # Total number of records in the input file
nRecTotalGood       = 0     # Total number of records that had good data
nRecTotalOut        = 0     # Total number of records in the output file
nRecTotalBadId      = 0     # Total number of records that had a bad Road Id
nRecTotalPassFilter = 0     # Total number of records that meet time filter
nRecTotalFailed     = 0


# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
# Read the input file line by line
try:
   for line in inFile:

      nRecTotalIn += 1
      if nRecTotalIn <= nProcessedLines:
         continue

      # Clean up and split the input line.
      line = line.strip()
      csv = line.split(',')

      # Perform required data translations from string.
      try:
         # Convert Lat/Lon to float for use in the URL request.
         csv[Utils.iLat] = float(csv[Utils.iLat])
         csv[Utils.iLon] = float(csv[Utils.iLon])

         # Convert time to comparable form. (data form is 2012-06-26 23:59:56)
         nTime = calendar.timegm(time.strptime(csv[Utils.iTime], Utils.sTimeFormatIn))

         try:
            nFileId = int( csv[Utils.iRId] )
         except ValueError:
            nFileId = -1

      except ValueError:
         continue

      # Increment a counter so we can see how many records are failing
      # the check in pre-process.
      nRecTotalGood += 1
   
      # Filter out points that aren't in the requested time frame
      if nTime < fTimeStart or nTime >= fTimeEnd:
         continue

      nRecTotalPassFilter += 1

      # Verify that the road ID is valid since many are incorrect in the input.
      nRoadId = GetRoadId( csv[Utils.iLat], csv[Utils.iLon] )
      sMsg = csv[Utils.iTime] + ": " + nRoadId[1]
      if nRoadId[0] == -1:
         sMsg = sMsg + ": GET fail  %6s" % ("")
         nRecTotalFailed += 1
      else:
         sMsg = sMsg + ": Road ID = %6d" % (nRoadId[0])

      # Detect mismatches between the input file and the web service
      if not nRoadId[0] == nFileId:
         sMsg = sMsg + ": ID mismatch: File(%6s)" % (nFileId)
         nRecTotalBadId += 1

      # Print message to the console.  This provides some progress indication
      # as well as throttling the requests to the web service.
      if len(sMsg) > 0:
         print( "%8d: %s" % (nRecTotalIn,sMsg) )

      sRoadId = "%s" % nRoadId[0]
      if int(nRoadId[0]) < 0:
         sRoadId = "n"


      # Write the line to the output file
      outFile.write( "%s,%s,%s,%s,%s,%s,%s,%s,%s\n" % \
            ( csv[Utils.iPlate],\
            csv[Utils.iTime],   \
            csv[Utils.iLoad],   \
            csv[Utils.iSpd],    \
            csv[Utils.iHdg],    \
            csv[Utils.iLat],    \
            csv[Utils.iLon],    \
            csv[Utils.iRoad],   \
            sRoadId) )
      nRecTotalOut += 1

except:
   print( "Exception terminated processing!: %s" );


print( "%10d Records read in"                % (nRecTotalIn) )
print( "%10d Records with bad data"          % (nRecTotalIn-nRecTotalGood) )
print( "%10d Records filtered by time"       % (nRecTotalGood-nRecTotalPassFilter) )
print( "%10d Records mismatched in file"     % (nRecTotalBadId) )
print( "%10d Records failed to get Road Id"  % (nRecTotalFailed) )
print( "%10d Records written out"            % (nRecTotalOut) )

