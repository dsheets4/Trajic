# Similarity code modified from original provided by Eric Chu
import os
import subprocess
import sys
import shutil
import glob
import math

#import logging

from optparse import OptionParser


##############################################
# Configure you system here
##############################################
# -----------------------------------------------------------------------------
# Parse out the command line options for the script.
parser = OptionParser()
parser.add_option(
      "-i", "--in",
      dest="sInDir",
      help="LDA output to process",
      metavar="DIR" )
parser.add_option(
      "-o", "--out",
      dest="sOutFileName",
      default="",
      help="Similarity output file",
      metavar="FILE" )
parser.add_option(
      "-n", "--num-terms",
      dest="nTermsToTest",
      help="Number of terms to use in the similarity comparison" )
parser.add_option(
      "-s", "--similarity-threshold",
      dest="fSimilarityThreshold",
      default=0.75,
      help="Required percentage of similarity before a topic matches",
      metavar="float" )
parser.add_option(
      "-t", "--template",
      dest="sTemplDir",
      help="Template LDA results to use for assigning the topic numbers",
      metavar="PATH" )
parser.add_option(
      "-r", "--road",
      dest="sRoadData",
      default="../data/road_text_info"
      help="Folder containing the road geometry.",
      metavar="PATH" )
parser.add_option(
      "-t", "--timelevels",
      dest="nTimeLevels",
      help="Number of time slots going back in time to compare the topics.  Default is infinite.",
      metavar="int" )

(options, args) = parser.parse_args()

if len(options.sOutFileName) == 0:
   options.sOutFileName = "%s/%s" % (options.sInDir,"topic_similarity_matrix.csv")


# -----------------------------------------------------------------------------
# Process the command line arguments
totalTopic = 8

# define the parameter for the topic similarity
# determine total number of terms within a topic
MAX_TERM_OF_TOPIC = int(options.nTermsToTest)
MIN_SIMILARITY    = float(options.fSimilarityThreshold)

lda_result_dirs = os.listdir( options.sInDir )
lda_result_dirs.sort() # We want to process these in order.

logFile = options.sInDir + "/similarity.log"
#logging.basicConfig(filename = logFile, level=logging.DEBUG)

similarityMatrixResultFile = options.sOutFileName

        

# -----------------------------------------------------------------------------
# Initialize and prepare to execute the similarity logic.
topic_similarity_matrix = []
topic_similarity_values = []

# Calculate how many time divisions there are so that the matrix size in 
# consistent.
similarity_matrix_column = 0
for dir in lda_result_dirs:
   if os.path.isdir(options.sInDir + "/" + dir):
      similarity_matrix_column += 1
      #print( dir )

# Initialize the similarity matrix.
for i in range(totalTopic):
    tmpMatrix = []
    tmpValues = []
    for j in range(similarity_matrix_column):
        tmpMatrix.append(j)
        tmpValues.append(0)
    topic_similarity_matrix.append(tmpMatrix)
    topic_similarity_values.append(tmpValues)

# Initialize the next topic id to the number of topics+1 since the first
# time slot always gets its own set of IDs.
nNextTopicId = similarity_matrix_column

# end of topic similarity matrix 


# -----------------------------------------------------------------------------
def printSimilarityMatrixResult():
    resultFile = open(similarityMatrixResultFile, 'w')

    for oneRow in topic_similarity_matrix:
        resultFile.write(str(oneRow[0]))
        for element in oneRow[1:]:
            resultFile.write(",%d" % element)
        resultFile.write("\n")

    resultFile.close()

# -----------------------------------------------------------------------------
# Define function to get topic similarity
def getTopicSimilarity(topic1, topic2):
    common = []

    for a in topic1:
        for b in topic2:
            if a == b:
                common.append(a)
                break

    similarity = (float)(len(common))/(float)(len(topic1))
    return similarity

# -----------------------------------------------------------------------------
# Function: generate current top MAX_TERM_OF_TOPIC topic list
# this is a two-dimensional list
def getCurrentTopicList(term_index_file_path, term_distribution_file_path):
    #construct the term index list first
    termSourceFile = open(term_index_file_path, 'r')

    termIndexList = []
    for line in termSourceFile:
        term = line.rstrip('\n')
        termIndexList.append(term)
    termSourceFile.close()

    # start to generate the current topic list
    currentTopicList = []
    for i in range(totalTopic):
        tmp = []
        currentTopicList.append(tmp)

    termDistributionFile = open(term_distribution_file_path, 'r')
    topicNumberIdx = 0
    # here I will use a stupid way to do this sort and find the id for that term
    for line in termDistributionFile:
        words = line.rstrip('\n').split(',')
        originalList = []
        
        # Convert input to float and sort the list so that the highest 
        # probability is at the end of the list.
        for word in words:
            try:
               originalList.append((float)(word))
            except ValueError:
               print( "Error converting value for %s in file %s!" % (word,term_distribution_file_path) )
               originalList.append(-1.0)
        sortedList = sorted(originalList)

        # Then, determine how many items are supposed to be in the list
        # as an index from the end of the sorted list.  Extract the value
        # of the term at this index.
        compareTermIndex = 0
        if len(originalList) > MAX_TERM_OF_TOPIC:
           compareTermIndex = len(originalList) - MAX_TERM_OF_TOPIC
        else:
           compareTermIndex = len(originalList)-1
        compareTerm = sortedList[compareTermIndex]

        # For every term that has a higher probability than the lowest expected
        # value, add it to the list of top n topics.
        for idx in range(len(originalList)):
            if originalList[idx] >= compareTerm:
                currentTopicList[topicNumberIdx].append(termIndexList[idx])

        topicNumberIdx += 1

    return currentTopicList
# end of getCurrentTopicList function

# -----------------------------------------------------------------------------
# Function: getCurrentColorSchemeBySimilarity()
# return a list which contains the new color scheme for the current generated topic
def getCurrentColorSchemeBySimilarity(oldTopicList, newTopicList, oldTimeFileIndex, newTimeFileIndex):

    #logging.debug("old topic list" + str(oldTopicList))
    #logging.debug("new topic list" + str(newTopicList))

    # start to compare the similarity
    new_topic_idx = 0
    for topic in newTopicList:
        old_topic_idx = 0
        
        #print( "[%d][%d]" % (old_topic_idx,oldTimeFileIndex) )
        last_similarity_result = topic_similarity_values[new_topic_idx][newTimeFileIndex]
        for i in range(len(oldTopicList)):
            similarity_result = getTopicSimilarity(topic, oldTopicList[i])
            if similarity_result >= MIN_SIMILARITY and similarity_result > last_similarity_result:
                #logging.debug("XXXXXXXXXXXXXXXXXXXXXX FIND SIMILARITY TOPICS ")
                #logging.debug( "prev[%d][%d](%d) <==> curr[%d][%d](%d): similarity = %f" 
                #      % ( \
                #            old_topic_idx,oldTimeFileIndex, \
                #            topic_similarity_matrix[old_topic_idx][oldTimeFileIndex], \
                #            new_topic_idx,newTimeFileIndex, \
                #            topic_similarity_matrix[new_topic_idx][newTimeFileIndex], \
                #            similarity_result) )
                #logging.debug(str(topic))
                #logging.debug(str(oldTopicList[i]))
                #logging.debug("XXXXXXXXXXXXXXXXXXXXXX END SIMILARITY TOPICS ")

                print( "   prev[%d][%d](%d) <==> curr[%d][%d](%d): similarity = %f" 
                     % ( \
                            old_topic_idx,oldTimeFileIndex, \
                            topic_similarity_matrix[old_topic_idx][oldTimeFileIndex], \
                            new_topic_idx,newTimeFileIndex, \
                            topic_similarity_matrix[new_topic_idx][newTimeFileIndex], \
                            similarity_result) )

                # here record the similarity information into the topic_similarity_matrix file
                if oldTimeFileIndex == newTimeFileIndex:
                   topic_similarity_matrix[new_topic_idx][newTimeFileIndex] = old_topic_idx+1
                else:
                   topic_similarity_matrix[new_topic_idx][newTimeFileIndex] \
                         = topic_similarity_matrix[old_topic_idx][oldTimeFileIndex]

                topic_similarity_values[new_topic_idx][newTimeFileIndex] = similarity_result
                # end of topic_similarity_matrix generation

                last_similarity_result = similarity_result

            old_topic_idx += 1

        new_topic_idx += 1

# end of getCurrentColorChemeBySimilarity


# -----------------------------------------------------------------------------
###############################################
# Main() start here
###############################################
# Copy the CSV source file to the lda folder
if __name__ == "__main__":

    # define the some useful global variables
    iteration_index = 0
    new_topic_list = []
    lstPreviousTopics = []
    nNextTopicId = totalTopic+1
    for sDir in lda_result_dirs:
        sFullPath = "%s/%s" % (options.sInDir,sDir)

        # Skip non-directories like the settings file.
        if os.path.isfile(sFullPath):
            continue

        print( "Processing similarity for: %s" % (sFullPath) )

        lda_sub_folder = "%s/%s" % (sFullPath,"lda-output/01000")

        #logging.debug("=======================================")
        #logging.debug("[" + str(iteration_index) + "]" + "process file [" + lda_sub_folder + ']')

        # Test to see if this folder exist
        if not os.path.exists(options.sInDir):
            os.makedirs(options.sInDir)


        #############
        # According to the LDA result, do the topic similarity analysis and
        # decide the color scheme for the topics first prepare the word 
        # cloud result file
        sTermIndex = "%s/%s" % (lda_sub_folder,"term-index.txt")
        sTermDistr = "%s/%s" % (lda_sub_folder,"topic-term-distributions.csv")
        if iteration_index == 0:
            # First iteration just prime the loop for the next iteration.
            new_topic_list = getCurrentTopicList(sTermIndex,sTermDistr)

            # This is the first iteration.  If there is a template to seed
            # the similarity then grab it and add it to the list of topics
            # that will be checked for similarity.
            try:
               sTermIndex = "%s/%s" % (options.sTemplDir,"lda-output/01000/term-index.txt")
               sTermDistr = "%s/%s" % (options.sTemplDir,"lda-output/01000/topic-term-distributions.csv")
               lstSeedTempl = getCurrentTopicList(sTermIndex,sTermDistr)
               getCurrentColorSchemeBySimilarity(lstSeedTempl, new_topic_list, 0, iteration_index)
               print( "Using a template for similarity correlation: %s" % (options.sTemplDir) )
            except AttributeError:
               print( "Not using a template for similarity correlation" )
        else:
            # otherwise need to determine the color scheme based on the topic similarity result
            lstPreviousTopics.append( new_topic_list )
            new_topic_list = getCurrentTopicList(sTermIndex,sTermDistr)
            
            if options.nTimeLevels <= 1: # Only process one time slot backward
               getCurrentColorSchemeBySimilarity(lstPreviousTopics[iteration_index-1], new_topic_list, iteration_index-1, iteration_index)
            else:
               for i in range(len(lstPreviousTopics)-1,0,-1):
                  getCurrentColorSchemeBySimilarity(lstPreviousTopics[i], new_topic_list, i, iteration_index)

        # Make sure the topic has an ID.
        for i in range(len(topic_similarity_values)):
           if topic_similarity_values[i][iteration_index] == 0:
               #print( "Topic needs Id - Assigning: %d" % (nNextTopicId) )
               topic_similarity_matrix[i][iteration_index] = nNextTopicId
               nNextTopicId += 1

                
        # Write out the overall topic index for the current LDA result set.
        fileTopicSimilarity = open(lda_sub_folder + "/topic-similarity.txt", 'w')
        fileTopicSimilarityColors = open(lda_sub_folder + "/topic-similarity-colors.txt", 'w')
        for i in range(totalTopic):
            fileTopicSimilarity.write( "%s\n" % topic_similarity_matrix[i][iteration_index] )
            fileTopicSimilarityColors.write( "%s\n" % Utils.stableRandomColor(topic_similarity_matrix[i][iteration_index]) )

        # end of the similarity computation
        #######################################

        # increase the iteration index
        iteration_index += 1

    # print out the topic similarity matrix result
    printSimilarityMatrixResult()
# end of main() function
