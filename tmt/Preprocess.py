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
import codecs

import Utils



# -----------------------------------------------------------------------------
# Main() start here

# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
# Parse out the command line options for the script.
parser = OptionParser()
parser.add_option("-i", "--input",
      dest="inputFile",
      help="CSV format taxi input file",
      metavar="FILE")
parser.add_option("-o", "--out-dir",
      dest="outputDir",
      help="Output directory containing the split files",
      metavar="DIR")
parser.add_option("-d", "--duration",
      dest="duration",
      default=3600,
      help="Duration in seconds for each division",
      metavar="float")
parser.add_option("-l", "--loaded",
      action="store_true",
      dest="bUseLoaded",
      default=False,
      help="Retain points when the taxi has a customer.")
parser.add_option("-u", "--unloaded",
      action="store_true",
      dest="bUseUnloaded",
      default=False,
      help="Retain points when the taxi does not have a customer.")
parser.add_option("-s", "--speed",
      action="store_true",
      dest="bAugmentSpeed",
      default=False,
      help="If speed is greater than 30 km/hr, introduce additional weight to the points.")
parser.add_option("-f", "--filter-repeats",
      action="store_true",
      dest="bFilterRepeats",
      default=False,
      help="If the same road id is repeated the duplicates are filtered out.")

(options, args) = parser.parse_args()

# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
# Process the command line inputs

# Verify the options are valid.
if (not options.bUseLoaded) and (not options.bUseUnloaded):
   print( " ALL POINTS HAVE BEEN FILTERED!  NO DATA TO PROCESS!" )
   print( " Please specify one or both of the options -u or -l" )
   sys.exit(2) # Command line error

inFile  = codecs.open(options.inputFile, 'r', encoding="utf_8")

timeIncrement = int(options.duration)
sOutDir = "%s" % (options.outputDir)
print( "Processing file with time duration of %s seconds" % (timeIncrement) )
print( "Output directory is: %s" % (sOutDir) )


# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
nProgressInc  = 50000 # number of records to process before print an indication
nRecProcessed = 0     # Total number of records in the input file
nRecKept      = 0     # Total number of records used in the output
data          = {}    # Dictionary mapping time segment to taxi

# Temp directory for intermediate files.
sTmpDir       = tempfile.mkdtemp(".taxivis")


# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
# Read the input file line by line and write out temporary files for furhter 
# processing.
for line in inFile:

   # Track the number of records that were processed from the file
   nRecProcessed += 1

   # Strip the whitespace from either side of the line
   line = line.strip()

   # Split the input CSV into individual fields
   csv = line.split(',')
   
   # Run the pre-process, which returns whether to process the record
   if not Utils.PreProcessData(csv):
      continue

   # Track the number of records that were kept
   nRecKept += 1

   # Determine if the output file has been created yet and, if not, create it.
   # One file is created to store all the valid points for a given time 
   # duration
   timeStart = int(csv[Utils.iTime] / timeIncrement)
   if not timeStart in data:
      sTime = time.strftime( Utils.sTimeFormatOut, time.gmtime(timeStart*timeIncrement) )
      data[timeStart] = open( "%s/%s" % (sTmpDir,sTime), 'w')
      print( "Starting new time slot: %s" % sTime )

   # If the option to only process points for a loaded taxi is set or if
   # the point corresponds to a loaded value then output the value to
   # the output file.
   if (options.bUseLoaded and int(csv[Utils.iLoad]) == 1) \
         or (options.bUseUnloaded and int(csv[Utils.iLoad]) == 0):
      # Append the new point to the end of the taxis list
      data[timeStart].write("%s,%s,%s,%s,%s\n" % \
            (csv[Utils.iPlate],csv[Utils.iTime],csv[Utils.iRId],csv[Utils.iLoad],csv[Utils.iSpd]))

   # DEBUG: Process a subset of the total over all points.  Just makes
   #        it faster to test during development.
   #if nRecProcessed > 500000:
   #   break

# Close all the individual output files
for tmpFile in data.values():
   tmpFile.close()


# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
# Print some status
print( "Records processed : %d" % (nRecProcessed) )
print( "Records kept      : %d" % (nRecKept) )
print( "Finished reading input file.  Processing output" )


# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
# Sort the cached data.  At this point the data has been grouped into its 
# proper time category and now needs to be sorted by the plate ID.  The
# sorted data is also output in the format for the TMT utility.
sTmpFiles = os.listdir( sTmpDir )
sTmpFiles.sort()
for sTmpFile in sTmpFiles:

   # Create a new dictionary for this time segment.
   data = {}

   # Sort the data so that the taxis are sorted by plate.
   # Update: This isn't required.
   #timeVal = sorted( timeVal, key=lambda record: record[Utils.iPlate] )

   # - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
   # Open up the input file from the temporary location.
   inFile = open("%s/%s" % (sTmpDir,sTmpFile), 'r')

   # Parse out the input file
   for line in inFile:

      # Strip the whitespace from either side of the line
      line = line.strip()

      # Split the input CSV into individual fields
      csv = line.split(',')

      # If this is the first time the taxi has been seen, create a list for it
      if not csv[0] in data:
         data[csv[0]] = []
      
      # Add the point onto the end of the taxi's list
      data[csv[0]].append(csv)


   # - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
   # Open up the output file for this time slot.
   nSpdBucketRange = 30
   if not os.path.isdir( sOutDir ):
      os.makedirs( sOutDir )
   outFile = open("%s/%s.csv" % (sOutDir,sTmpFile), 'w')

   # Within each time segment is a dictionary of the taxi's trajectory 
   # keyed by the taxi's plate. 
   nTaxiProcessed = 0
   nRecProcessed  = 0
   for taxiKey, taxiVal in data.items():

      # Print the taxi ID as the identifier for the document.
      outFile.write( "%s," % (taxiKey) )

      # Track the total number of taxis in this time period.
      nTaxiProcessed += 1

      # Iterate over all the taxis and write a list of the taxi's points to
      # the output file.
      lastRoadId = None
      for point in taxiVal:

         # Determine if the duplicate should be filtered.
         if (not options.bFilterRepeats) or (not (point[2] == lastRoadId)):
            lastRoadId = point[2]

            # Write out the Road ID as the content to the document
            outFile.write( "%s " % (point[2]) )

            # If weighting is to occur for faster points, then add the additional
            # points to the output file.
            nSpd = 0
            try:
               nSpd = int(point[4])
            except ValueError:
               nSpd = 0
            if options.bAugmentSpeed and nSpd > nSpdBucketRange:
               nInsertions = int(nSpd / nSpdBucketRange) - 1
               for i in range(nInsertions):
                  outFile.write( "%s " % (point[2]) )
                  #print( "Zoom-Zoom(%d)! %d" % (i,nSpd) )

            # Track how many records are processed in total
            nRecProcessed += 1

      # End the document by moving to the next line.
      outFile.write("\n")

   # Close the output file for this time slot.
   outFile.close()

   # Print some statistics on the processed data
   print( "Time slot: %s" % (sTmpFile) )
   print( "   Total taxis  : %d" % (nTaxiProcessed) )
   print( "   Total points : %d" % (nRecProcessed) )

# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
# Save the settings in the output directory for later use
sSettingsFile = "%s/settings.txt" % (sOutDir)
fileSettings = open(sSettingsFile, 'w')
fileSettings.write("%d" % (timeIncrement))
fileSettings.close()

# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
# Clean up the temp directory
#print( "Temp directory at %s" % (sTmpDir) )
shutil.rmtree( sTmpDir, True )

