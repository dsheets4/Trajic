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
import tempfile
import os
import shutil
import chardet
import codecs

import Utils



# -----------------------------------------------------------------------------
# Main() start here

# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
# Parse out the command line options for the script.
parser = OptionParser()
parser.add_option(
      "-i", "--input", 
      dest="inputFile",
      help="CSV format taxi input file",
      metavar="FILE")
parser.add_option(
      "-o", "--out-dir",
      dest="outputDir",
      help="Output directory containing the split files",
      metavar="DIR")
parser.add_option(
      "-d", "--duration",
      dest="duration",
      default=3600,
      help="Duration in seconds for each division")

(options, args) = parser.parse_args()


# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
# Process some of the command line inputs
rawdata = open(options.inputFile, 'rb').readline()
result  = chardet.detect(rawdata)
charenc = result['encoding']

inFile  = codecs.open(options.inputFile, 'r', encoding=charenc)
timeIncrement = int(options.duration)
sOutDir = "%s" % (options.outputDir)
if not os.path.isdir( sOutDir ):
   os.makedirs( sOutDir )
print( "Processing file with time duration of %s seconds" % (timeIncrement) )
print( "Output directory is: %s" % (sOutDir) )


# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
nRecProcessed = 0     # Total number of records in the input file
data          = {}    # Dictionary mapping time segment to taxi


# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
# Read the input file line by line
for line in inFile:

   # Track the number of records that were processed from the file
   nRecProcessed += 1

   # Strip the whitespace from either side of the line
   line = line.strip()

   # Split the input CSV into individual fields
   csv = line.split(',')

   # Get a comparable time value
   fTime = calendar.timegm(time.strptime(csv[Utils.iTime], Utils.sTimeFormatIn))
   
   # Determine if the output file has been created yet and, if not, create it.
   # One file is created to store all the valid points for a given time 
   # duration
   timeStart = int(fTime / timeIncrement)
   if not timeStart in data:
      sTime = time.strftime( Utils.sTimeFormatOut, time.gmtime(timeStart*timeIncrement) )
      data[timeStart] = open( "%s/%s" % (options.outputDir,sTime), 'w')
      print( "Starting new time slot: %s" % sTime )

   # Append the new point to the end of the taxis list
   data[timeStart].write( "%s,%s,%s,%s,%s,%s,%s,%s,%s\n" % (\
         csv[Utils.iPlate],\
         csv[Utils.iTime], \
         csv[Utils.iLoad], \
         csv[Utils.iSpd],  \
         csv[Utils.iHdg],  \
         csv[Utils.iLat],  \
         csv[Utils.iLon],  \
         csv[Utils.iRoad], \
         csv[Utils.iRId]   \
         ) )


# Close all the individual output files
for tmpKey, tmpFile in data.items():
   tmpFile.close()


# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
# Print some status
print( "Records processed : %d" % (nRecProcessed) )
print( "Finished reading input file.  Processing output" )

