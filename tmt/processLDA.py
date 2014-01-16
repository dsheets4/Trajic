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

# Adapted from resultGenerator.py originally authored by Eric Chu


# -----------------------------------------------------------------------------
from optparse import OptionParser
import time
import os
import subprocess
import sys
import shutil
import gzip


# -----------------------------------------------------------------------------
# Configure you system here
sTemplateScalaFileName = "taxi.in.scala"  # Input scala file used to generate specific ones


# -----------------------------------------------------------------------------
# This function updates the scala file used as input to the TMT LDA algorithm
# so that it's possible to batch process several files with a varying number
# of topics.
def generateScalaFile( sInDir, sDataFile, nTopics, sOutDir ):

   # Create the new file name for this run.
   sScalaFileName = sOutDir + "/taxi.scala"
   sLdaOutDir     = "%s/lda-output" % (sOutDir)

   # Open the template file and the target file
   fileTemplate = open(sTemplateScalaFileName, 'r')
   fileScala    = open(sScalaFileName, 'w')

   # Let the user know not to edit the auto-generated files.
   fileScala.write( "// ----------------------------------------------------\n" )
   fileScala.write( "// This file was auto-generated from the template %s.\n" % (sTemplateScalaFileName) )
   fileScala.write( "// Changes made to the file will be lost!\n" )
   fileScala.write( "// Modify the template instead.\n" )
   fileScala.write( "// ----------------------------------------------------\n" )
   fileScala.write( "\n" )
   fileScala.write( "\n" )

   # Iterate through the template file and write the target file based on the 
   # template with the necessary modifications.
   for line in fileTemplate:
      
      # Find the target lines to replace.
      posDataSource  = line.find("DataSourceDirective")
      posModelParams = line.find("LDAModelParamsDirective")
      posOutputDir   = line.find("OutputDirective")

      # If the file is on the a line requiring modification, write the new line
      # content.  Otherwise just write the template line verbatim to the target.
      if posDataSource != -1:
         fileScala.write("val source = CSVFile(\"%s/%s\");\n" % (sInDir,sDataFile))
      elif posModelParams != -1:
         fileScala.write("val params = LDAModelParams(numTopics = %d,\n" % nTopics)
      elif posOutputDir != -1:
         fileScala.write(\
               "val modelPath = file(\"%s\");\n" % (sLdaOutDir) )
      else:
         fileScala.write(line)

   # Close the template and output scala files
   fileTemplate.close
   fileScala.close

   # Return the name of the newly generated scala file
   return (sScalaFileName,sLdaOutDir)


# -----------------------------------------------------------------------------
# Parse out the command line options for the script.
parser = OptionParser()
parser.add_option("-i", "--in-dir", dest="inputDir",
      help="Input directory, will process each file found", metavar="DIR")
parser.add_option("-o", "--out-dir", dest="outputDir",
      help="Output directory to place the results, one per input file", metavar="DIR")
parser.add_option("-n", "--num-topics", dest="numTopics", default=8,
      help="Number of topics to generate with the input data", metavar="float")

(options, args) = parser.parse_args()

# Read in the previous settings file.
fileSettings = open( "%s/settings.txt" % (options.inputDir), 'r' )
line = fileSettings.readline()
timeIncrement = float(line)
fileSettings.close()

# Translate the arguments to proper types
nTopics = int(options.numTopics)
sParentOutDir = "%s" % (options.outputDir)
print( "Writing LDA results to %s" % (sParentOutDir) )


# -----------------------------------------------------------------------------
# Main() start here
# Copy the CSV source file to the lda folder

# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
# Make sure the output directory exists
if not os.path.isdir( sParentOutDir ):
   os.makedirs( sParentOutDir )

# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
# Get the input list of files from the input directory.
inFiles = os.listdir( options.inputDir )
inFiles.sort()

# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
for corpus in inFiles:

   # Ignore the file unless it's a csv file
   if not corpus.endswith(".csv"):
      continue

   # Print status on which file is being processed.
   print( "Input File: %s" % (corpus) )
   
   # DEPENDENCY: This depends on the previous step creating files with 
   #             timestamps in the format below.
   # Parse the timestamp from the file name
   try:
      timeData = time.strptime( corpus, "%Y-%m-%dT%H-%M-%S.csv")
      sTime = time.strftime( "%Y-%m-%dT%H-%M-%S", timeData )
   except ValueError:
      print( "Exception when processing %s!" % (corpus) )

   # Generate an output directory for each input file.  Since we aren't saving 
   # state in the LDA output we must manually remove any old results.
   sOutDir = "%s/%s" % (sParentOutDir,sTime)
   shutil.rmtree( sOutDir, True )
   if not os.path.isdir( sOutDir):
      os.makedirs( sOutDir )

   # Generate a scala file to execute the LDA process.
   scalaData = generateScalaFile(\
         options.inputDir,\
         corpus,\
         nTopics,\
         sOutDir )

   # Run the LDA process with the newly create scala file
   subprocess.call("java -jar " + "tmt-0.4.0.jar " + scalaData[0], shell=True)

   # Note: This isn't working but the csv filter on the files prevents 
   #       subsequent iterations from failing so I'm leaving this as is for now
   # Clean up after TMT, not sure why it insists on writing these files to the
   # input directory instead of the output but they are in the input...
   #print( "rm %s/*term-counts.cache*" % (options.inputDir) )
   #subprocess.call( "rm %s/*term-counts.cache*" % (options.inputDir) )


   # Extract the needed data from the compressed archive that LDA leaves
   # in the output directory. This prepares for subsequent scripts.
   # DEPENDENCY
   # TODO: At this point the script here and the scala file have a dependency
   #       where the scala file indicates how many iterations to run but the
   #       number is also hard-coded here.
   sFinalIterationDir = scalaData[1] + "/01000"
   sDistFileName = "%s/topic-term-distributions.csv" % (sFinalIterationDir)
   distFile = open(sDistFileName, 'wb')
   with gzip.open("%s.gz" % (sDistFileName), 'rb') as f:
      content = f.read()
      distFile.write(content)
   


# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
# Save the settings in the output directory for later use
# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -


# Write out the settings file for this output
sSettingsFile = "%s/settings.txt" % (sParentOutDir)
fileSettings = open(sSettingsFile, 'w')
fileSettings.write("%d\n" % (timeIncrement))
fileSettings.write("%d\n" % (nTopics))
fileSettings.close()

