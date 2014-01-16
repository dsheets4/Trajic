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

# This script will process the TMT summary.txt ouput file and generate
# a script that can be read in to the TaxiVis application.

import re
import random
import os
import subprocess
import sys
import shutil
import glob
from optparse import OptionParser
import array
import os
import time
import calendar

import Utils
import TaxiVisFile
import LdaObjects


# -----------------------------------------------------------------------------
# Parse out the command line options for the script.
parser = OptionParser()
parser.add_option(
      "-t", "--title",
      dest="sTitle",
      default="",
      help="Title sent to the various files to help identify the data" )
parser.add_option(
      "-i", "--in",
      dest="inputDir",
      help="LDA iteration directory to process",
      metavar="DIR" )
parser.add_option(
      "-o", "--out",
      dest="outputDir",
      help="Output script directory for the visualization",
      metavar="DIR" )
parser.add_option(
      "-r", "--road",
      dest="roadData",
      help="Folder containing the road geometry",
      metavar="FOLDER" )
parser.add_option(
      "-P", "--threshold-upper",
      dest="thresholdUpper",
      default=0.005,
      help="Initial threshold used to filter topics",
      metavar="float" )
parser.add_option(
      "-p", "--threshold-lower",
      dest="thresholdLower",
      default=0.001,
      help="Second threshold used to filter topics",
      metavar="float" )

(options, args) = parser.parse_args()


# -----------------------------------------------------------------------------
# Threshold settings for creating the visualization.
fProbThreshold = float(options.thresholdUpper)
fDrawThreshold = float(options.thresholdLower)

fTransThresholdMin = 0.9  # Minimum value any street can have for transparency
fTransThresholdMax = 0.9  # Maximum value any street can have for transparency

fWeightThresholdMin = 10  # Minimum value any street can have for width
fWeightThresholdMax = 100 # Maximum value any street can have for width

fProbMultiplier = 100000000

mapPage = "mapPage"
scene   = "scene"
view    = "view"
colors  = "colors"


# -----------------------------------------------------------------------------
# -----------------------------------------------------------------------------
def ProcessFiles( \
      sTermIndexFile, sTopicDocFile, sTopicTermFile, sTopicSimilarityFile, \
      sTimeFormat, sTitle,
      fRotation, fSpan, \
      sOutputDir, sRoadData ):

   fileTopicDoc   = open(sTopicDocFile,        'r')
   idxFile        = open(sTermIndexFile,       'r')
   fileTopicTerm  = open(sTopicTermFile,       'r')
   fileSimilarity = open(sTopicSimilarityFile, 'r')

   # Read in the index lookup
   idx = array.array('L')
   for line in idxFile:
      # Remove newline from the read in line.
      line = line.strip()
      nRoadId = int(line)
      idx.append( nRoadId )

   # Read in the topic similarity lookup
   lstTopicLookup = []
   for line in fileSimilarity:
      lstTopicLookup.append(int(line))


   # Regular expressions to extract lon,lat from data files.
   rePoint = re.compile( r'(\d+\.\d*),(\d+\.\d*)' )
   iLon = 1
   iLat = 2


   # - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
   # Tracking variables to print statistics
   nStreetCount  = 0  # Count of the total number of streets in the "bag-of-streets"
   fProbMax      = 0  # Maximum probability observed in the data set.
   fProbMin      = sys.float_info.max # Maximum probability observed in the data set.
   nTopicNum     = 0  # Current topic number being processed
   nTotalStreets = 0  # Total routes in the current topic
   nTotalPoints  = 0  # Total points in the current topic
   stats         = []

   # - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
   # Create the LDA data structure.
   ldaResults = LdaObjects.LdaResults()
   ldaResults.setLabel( sTimeFormat )

   # - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
   # Create the output file objects
   sPcCsvFile = "%s/%s" % (sOutputDir,"pc.csv")
   sTitlePrefix = "%s" % (sTitle)
   mapFile     = TaxiVisFile.GeoMap(
                  sOutputDir + "/map.js",
                  "map" + sTitlePrefix,
                  fDrawThreshold,
                  fProbThreshold,
                  sRoadData)
   heatFile    = TaxiVisFile.HeatMap(
                  sOutputDir + "/heat.js",
                  "heat" + sTitlePrefix,
                  fProbThreshold,
                  sRoadData)
   clusterFile = TaxiVisFile.DocumentCluster(
                  sOutputDir + "/cluster.csv",
                  options.sTitle)
   d3File      = TaxiVisFile.ParallelCoordinatesD3(
                  sOutputDir + "/pcD3.js",
                  "pc" + sTitlePrefix,
                  fProbThreshold,
                  sPcCsvFile)
   statFile    = TaxiVisFile.Stats(
                  sOutputDir + "/stats.txt",
                  sTitlePrefix + " - Stats")

   #outFiles = [mapFile, ringFile, pcFile, heatFile, clusterFile, d3File]
   outFiles = [mapFile, heatFile, clusterFile, d3File, statFile]

   # - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
   # Document Processing (document-topic-distributions.csv)
   #
   # Iterate through each line in the Document distributions file.  Each line 
   # represents a single document. First column is a document number.  
   # Subsequent columns represent the topics in order.
   for line in fileTopicDoc: # 
      # Remove newline from the read in line.
      line = line.rstrip()

      # Split the line into a list of values corresponding to the terms.
      lstTopicDocProbs = line.split(',')

      # Process each row of the document probabilities.
      nTopic = -1
      nDocNum = -1
      for sContr in lstTopicDocProbs:
         if nTopic >= 0:
            # Create the document topic value and store off all the values.
            topic = LdaObjects.TopicDoc()
            topic.setTopicId( lstTopicLookup[nTopic] )
            topic.setValue(float(sContr))
            doc.add(topic)
         else: # First column is the document number
            doc = LdaObjects.Document()
            doc.setId( int(sContr) )
         nTopic += 1

      # Add the document to the LDA results, this will populate the topic view
      ldaResults.addDocument(doc)


   # - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
   # Term Processing (topic-term-distributions.csv)
   # 
   # Iterate through each line in the distributions file.  Each line represents
   # a single topic and the columns are the terms.
   layer = None
   for line in fileTopicTerm:
      # Reset probability
      fProbTotal = 0;

      # Remove newline from the read in line.
      line = line.rstrip()

      # Verify that there is actually data in the LDA output.  If not, return
      # since there is no further data to process.
      if len(line) == 0:
         return stats
      
      # Split the line into a list of values corresponding to the terms.
      lstTopicTermProbs = line.split(',')

      # Iterate over all terms and determine which ones to add to the output.
      iCurrIdx = -1
      nStreetCount = 0
      for sContr in lstTopicTermProbs:
         iCurrIdx += 1

         topic = LdaObjects.TopicTerm()
         topic.setTopicId( lstTopicLookup[nTopicNum] )
         topic.setId( idx[iCurrIdx] )
         topic.setValue( float(sContr) )
         if iCurrIdx > (ldaResults.numTerms()-1):
            # Create a new term in the results structure.
            term = LdaObjects.Term()
            nRoadNum = idx[iCurrIdx]
            term.setLabel( "%d" % (nRoadNum) )
            term.setId( nRoadNum )
            term.setRoadFile( "%s/%d" % (sRoadData,nRoadNum) )
            ldaResults.addTerm(term)
         else:
            # Get the existing term.
            term = ldaResults.getTerm( iCurrIdx )
         term.add(topic)

      nTopicNum += 1

   ldaResults.addTopicTerms()

   # - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
   # All topics and all terms have been written to the file, prepare to
   # close out the file.
   for outFile in outFiles:
      outFile.ProcessLdaResults(ldaResults)

   # Close the input and output files.
   fileTopicDoc.close()
   fileTopicTerm.close()

   # - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
   # Print some statistics about the process
   stats.append(["Count-Streets Total",   nStreetCount])
   stats.append(["Count-Pass Filter",     nTotalStreets])
   stats.append(["Count-Points Total",    nTotalPoints])
   stats.append(["Max Probability",       fProbMax])
   if nTotalStreets > 0:
      stats.append(["Avg Probability",       fProbTotal/nTotalStreets])
   else:
      stats.append(["Avg Probability",       0])
   stats.append(["Min Probability",       fProbMin])


   return stats

# -----------------------------------------------------------------------------
# Main() start here

# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
# Read in the settings from the settings file.
fileSettings = open( "%s/settings.txt" % (options.inputDir), 'r' )
line = fileSettings.readline()
timeIncrement = float(line)
line = fileSettings.readline()
nTopics = int(line)
fileSettings.close()

# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
# Open up a statistics file to allow for numeric comparison.
sStatDir = "%s" % (options.outputDir)
if not os.path.isdir( sStatDir ):
   os.makedirs( sStatDir )
fileStat = open( "%s/stats.csv" % (sStatDir), 'w' )
fileStat.write( "Time Increment,%f\n" % (timeIncrement) )
fileStat.write( "Number of Topics,%d\n" % (nTopics) )
fileStat.write( "Filter Threshold - Upper,%f\n" % (fDrawThreshold) )
fileStat.write( "Filter Threshold - Lower,%f\n" % (fProbThreshold) )
fileStat.write( "\n" )
fileStat.write( "\n" )

# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
# Get a sorted list of input directories
inDirs = os.listdir( options.inputDir )
inDirs.sort()

temp = 0
bStatHeaderWritten = False  # If the header for the statistics file has been written
for sDir in inDirs:

   # Skip non-directories like the settings file.
   if os.path.isfile(sDir):
      continue

   # Extract the time from the directory name
   try:
      sTimeFormat = "%Y-%m-%dT%H-%M-%S"
      timeStruct = time.strptime( sDir, sTimeFormat )
      timeData = calendar.timegm(timeStruct)
      fRotation = (int(timeData) % 86400) * 360.0 / 86400.0
      fSpan     = (int(timeIncrement) % 86400) * 360.0 / 86400.0
   except ValueError:
      continue

   # Create the path to the input LDA results and reference each file
   sDirResults = "%s/%s/%s" % (options.inputDir,sDir,"lda-output")
   sDirResultsIteration = "%s/%s" % (sDirResults,"01000")
   sTopicDocFile        = sDirResults          + "/document-topic-distributions.csv"
   sSummaryFile         = sDirResultsIteration + "/summary.txt"
   sTermIndexFile       = sDirResultsIteration + "/term-index.txt"
   sTopicTermFile       = sDirResultsIteration + "/topic-term-distributions.csv"
   sTopicSimilarityFile = sDirResultsIteration + "/topic-similarity.txt"
   sTitle               = options.sTitle + time.strftime("%H", timeStruct)

   # Calculate the output directory
   sOutputDir = "%s/%s" % (sStatDir,sDir)
   if not os.path.isdir( sOutputDir ):
      os.makedirs( sOutputDir )

   # Process the current file to create the script
   print( "Processing %s" % sDir )
   stats = []
   stats.append( ["Start Time",sDir] )
   stats = stats + ProcessFiles( \
         sTermIndexFile, sTopicDocFile, sTopicTermFile, sTopicSimilarityFile, \
         sDir, sTitle,
         fRotation, fSpan, \
         sOutputDir, \
         options.roadData )

   # Write the statistics to the stat file
   if not bStatHeaderWritten:
      for statVal in stats:
         fileStat.write( "%s," % (statVal[0]) )
      fileStat.write( "\n" )
      bStatHeaderWritten = True

   for statVal in stats:
      fileStat.write( "%s," % (statVal[1]) )
   fileStat.write( "\n" )


# Close the statistics file.
fileStat.close()
