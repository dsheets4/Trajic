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


# -----------------------------------------------------------------------------
# Main() start here

# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
# Parse out the command line options for the script.
parser = OptionParser()
parser.add_option("-i", "--input", dest="inputFile",
      help="CSV format taxi input file", metavar="FILE")
parser.add_option("-o", "--output", dest="outputFile",
      help="CSV format taxi output file", metavar="FILE")
parser.add_option("-n", "--num-lines", dest="nLines",
      help="Numer of lines to write to the test file", metavar="DIR")

(options, args) = parser.parse_args()


# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
# Process some of the command line inputs
nLinesToProcess = int(options.nLines)
inFile  = open(options.inputFile, 'r')
outFile = open(options.outputFile, 'w')
print( "Processing test file to contain %d lines." % (nLinesToProcess) )
print( "Output file is: %s" % (options.outputFile) )


# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
nRecProcessed = 0     # Total number of records in the input file


# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
# Read the input file line by line
for line in inFile:

   # Determine if we can stop processing the file.
   if nRecProcessed >= nLinesToProcess:
      break

   # Track the number of records that were processed from the file
   nRecProcessed += 1

   # Write the line to the output file
   outFile.write("%s" % line)

