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
import os
import sys
import subprocess
import shutil


# -----------------------------------------------------------------------------
# Main() start here

# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
# Parse out the command line options for the script.
parser = OptionParser()
parser.add_option( "-i", "--input", 
      dest="inputFile",
      default="../data/2012-06-27.good",
      help="CSV format taxi input file",
      metavar="FILE")
parser.add_option( "-o", "--out-dir", 
      dest="outputDir",
      default="../scripts",
      help="Output directory containing the processed files",
      metavar="DIR")
parser.add_option( "-d", "--duration",
      dest="duration",
      default=10800,
      help="Duration in seconds for each division",
      metavar="int")
parser.add_option ("-r", "--road", 
      dest="sRoadData",
      default="../data/road_text_info",
      help="Folder containing the road geometry",
      metavar="FOLDER")
parser.add_option( "-n", "--numTopics", 
      dest="nTopics",
      default=8,
      help="Number of topics to generate",
      metavar="int")
parser.add_option( "-P", "--threshold-upper", 
      dest="thresholdUpper",
      default=0.004,
      help="Initial threshold used to filter topics",
      metavar="float")
parser.add_option( "-p", "--threshold-lower", 
      dest="thresholdLower",
      default=0.00075,
      help="Second threshold used to filter topics",
      metavar="float")
parser.add_option("-l", "--loaded",
      action="store_true",
      dest="bUseLoaded",
      default=False,
      help="Excludes points when the taxi has a customer.")
parser.add_option("-u", "--unloaded",
      action="store_true",
      dest="bUseUnloaded",
      default=False,
      help="Excludes points when the taxi does not have a customer.")
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

nDuration    = int(options.duration)
nTopics      = int(options.nTopics)
sOutDir      = options.outputDir
sRoadDir     = options.sRoadData
fThreshUpper = float(options.thresholdUpper)
fThreshLower = float(options.thresholdLower)


# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
# Call each of the individual python scripts in the correct order to generate
# the needed output for the visualization.

# Processing the input data file
# ------------------------------
# The input file is now a giant CSV file of records (used to be binary files,
# one per taxi). The input file is roughly ordered by time but must be processed
# to give an exact ordering.  The following command will split the giant input
# file into the input files used for the LDA input.  The duration (-d) argument 
# indicates a duration for subdividing the data.  Duration defaults to 1 hour.

# Whether the non-loaded points are filtered out.
sLoadedExt = ""
sSplitOptions = ""
if (options.bUseLoaded) and (options.bUseUnloaded):
   sSplitOptions = "-l -u"
   sLoadedExt = "all"
elif options.bUseLoaded:
   sSplitOptions = "-l"  # -u because the if checks that it's not -l
   sLoadedExt = "loaded"
elif options.bUseUnloaded:
   sSplitOptions = "-u"  # -l because the if checks that it's not -u
   sLoadedExt = "unloaded"
else:
   # Just assume all by default.
   sSplitOptions = "-l -u"
   sLoadedExt = "all"

# Process the split options.
sModifier = ""
if options.bAugmentSpeed:
   sModifier = "speed"
   sSplitOptions += " -s"
else:
   sModifier += "default"

if options.bFilterRepeats:
   sModifier += "_filter"
   sSplitOptions += " -f"


# Base directory for all the output in the cache.
sBaseDir     = "%s/s%d/%s/%s" % ("./cache",nDuration,sLoadedExt,sModifier)

# Create the output path.
sLdaInputDir = "%s/%s" % (sBaseDir,"split")

# If the data already exists, no need to regenerate, otherwise, proccess.
if os.path.isdir(sLdaInputDir):
   print( "Output already exists, skipping split" )
   print( "  Remove directory to re-process: %s" % (sLdaInputDir) )
else:

   subprocess.call( "python ./Preprocess.py -i %s -o %s -d %d %s" \
         % (options.inputFile,sLdaInputDir, nDuration, sSplitOptions), \
         shell=True )


# Processing Taxi data using LDA
# ------------------------------
# After generating the desired input for the LDA process from the taxi input 
# file, the data can be processed using LDA.  The LDA process script takes in
# an input directory (-i), which is the output directory of the Preprocess step.
# It also takes in the number of topics (-n) that should be generated using the 
# input data.  The LDA output is stored in the output directory (-o)

sScriptInputDir = "%s/%s/t%d/" % (sBaseDir,"lda",nTopics)
if os.path.isdir(sScriptInputDir):
   print( "Output already exists, skipping LDA" )
   print( "  Remove directory to re-process: %s" % (sScriptInputDir) )
else:
   subprocess.call( "python processLDA.py -n %d -i %s -o %s" \
         % (nTopics,sLdaInputDir,sScriptInputDir), \
         shell=True )


# Process the topic similarity
# ----------------------------------------

sSimilarityMatrixFile = "%s/%s" % (sScriptInputDir,"topic_similarity_matrix.csv")
sFinalDir = "%s/s%d/t%d/P%fp%f/%s/%s" % (sOutDir,nDuration,nTopics,fThreshUpper,fThreshLower,sLoadedExt,sModifier)
sTemplDir = "%s/s%d/%s/%s/%s/t%d/%s" % ("./cache",nDuration,"all","default","lda",nTopics,"2012-06-27T00-00-00")
#print( sSimilarityMatrixFile )
if not os.path.isfile(sSimilarityMatrixFile):
   # Safe-guard, delete the scripts if there is no similarity since scripts 
   # depend on similiarity
   if os.path.exists( sFinalDir ):
      shutil.rmtree(sFinalDir)
   subprocess.call(
         "python generateTopicSimilarity.py -i %s -o %s -t %s -n 30 -s .3" % (sScriptInputDir,sSimilarityMatrixFile,sTemplDir),
         shell=True )
   

# Parsing the LDA output to TaxiVis Script
# ----------------------------------------
# Creating the TaxiVis script file for the full LDA result:
sTitle = "%s%s" % (sModifier,sLoadedExt)
if os.path.isdir(sFinalDir):
   print( "Output already exists, skipping Script Gen" )
   print( "  Remove directory to re-process: %s" % (sFinalDir) )
else:
   subprocess.call(
         "python TaxiVisScriptGen-Full.py -i %s -o %s -r %s -P %f -p %f -t \"%s\"" % \
         (sScriptInputDir,sFinalDir,sRoadDir,fThreshUpper,fThreshLower,sTitle),
         shell=True )


