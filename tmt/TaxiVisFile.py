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

import sys
import re
import array
import math

import Utils

# -----------------------------------------------------------------------------
# Constants
fProbMultiplier = 100000000 # Multiplier to make log scale stretch the low range

fTransThresholdMin = 0.40  # Minimum value any street can have for transparency
fTransThresholdMax = 0.90  # Maximum value any street can have for transparency

fWeightThresholdMin = 10  # Minimum value any street can have for width
fWeightThresholdMax = 30  # Maximum value any street can have for width


# =============================================================================
#                             Helper Functions
# =============================================================================
# --------------------------------------------------------------------------
def Prob(total, value):
   if total > 0:
      return  value / total
   else:
      return 0

# --------------------------------------------------------------------------
def ProcessLogValue( fValue ):
   if fValue > 0:
      return math.log10( ((fValue*fProbMultiplier)+1) )
   else:
      return 0


# =============================================================================
#                                   Base
# =============================================================================

# -----------------------------------------------------------------------------
# This script defines a base class for writing out the visualization
# scripts that are parsed by the TaxiVis application.
class Base(object):
   # --------------------------------------------------------------------------
   def __init__(self, sFileName, sTitle):
      self.sFileName = sFileName
      self.sTitle    = sTitle
      self.out = open(sFileName, 'w')

   # --------------------------------------------------------------------------
   # --------------------------------------------------------------------------
   def topicColor(self,nTopicNum):
      pass

   # --------------------------------------------------------------------------
   def ProcessLdaResults(self, ldaResults):
      pass
   
   # --------------------------------------------------------------------------
   def __del__(self):
      self.out.close()


# =============================================================================
#                                   BaseScript
# =============================================================================

# -----------------------------------------------------------------------------
# This script defines a base class for writing out the visualization
# scripts that are parsed by the TaxiVis application.
class BaseScript(Base):
   # --------------------------------------------------------------------------
   def __init__(self, sFileName, sTitle):
      Base.__init__(self, sFileName, sTitle)

      self.nTotalTopics = 0
      self.nTotalTerms  = 0
      self.fProbMax     = sys.float_info.min # Minimum probability observed
      self.fProbMin     = sys.float_info.max # Maximum probability observed
      self.fProbSum     = 0
      self.summary      = []
     
      self.scene   = "scene"
      self.view    = "view"

   # --------------------------------------------------------------------------
   def topicColor(self,nTopicNum):
      return "colors[%d]" % (nTopicNum)

   # --------------------------------------------------------------------------
   def writeHeader(self):
      self.out.write("var colors = new Array();\n")
      self.out.write("print(\"Running script %s.\");\n" % (self.sTitle))
      
      # Create the new view for the visualization.
      self.out.write("var %s = new MainScene();\n" % (self.scene)            )
      self.out.write("var %s  = new MainView();\n" % (self.view)             )
      self.out.write("%s.setTitle( \"%s\" )\n"     % (self.view,self.sTitle) )
      self.out.write("app.createWindow(%s,%s);\n"  % (self.scene,self.view)  )

   # --------------------------------------------------------------------------
   def writeTopicColor(self, nTopicNum):
      # Increment the topic count.
      self.nTotalTopics += 1

      # Write out the color for this topic.
      self.out.write("%s = \"%s\";\n" \
            % (self.topicColor(nTopicNum), Utils.stableRandomColor(nTopicNum)))

   # --------------------------------------------------------------------------
   def captureScreenShot( self, sImageName, nMsBeforeCapture ):
      sImgName = sImageName.replace( " ", "_" )

      self.out.write("var ms = %d;\n" % (nMsBeforeCapture))
      self.out.write("ms += new Date().getTime();\n")
      self.out.write("while (new Date() < ms){}\n")

      self.out.write("if( typeof(image_name) == 'undefined' )\n")
      self.out.write("{\n")
      self.out.write("   print( \"Capturing PNG screenshot as %s.png\" )\n" % sImageName)
      self.out.write("   %s.captureScreenShot( \"%s.png\" );\n" % (self.view,sImgName) )
      self.out.write("}\n")
      self.out.write("else\n")
      self.out.write("{\n")
      self.out.write("   print( \"Capturing PNG screenshot as \" + image_name )\n")
      self.out.write("   %s.captureScreenShot( image_name );\n" % (self.view) )
      self.out.write("}\n")

   # --------------------------------------------------------------------------
   def mapSettings(self):
      self.out.write("if( typeof(settings_map) == 'undefined' )\n")
      self.out.write("{\n")
      self.out.write("   var settings_local = new JsSettingsMap();\n")
      self.out.write("   settings_local.setZoomLevel(12);\n")
      self.out.write("   settings_local.setCenterLon( 113.987506 );\n")
      self.out.write("   settings_local.setCenterLat(  22.599686 );\n")
      self.out.write("   %s.setMapSettings( settings_local );\n" % self.mapPage)
      self.out.write("}\n")
      self.out.write("else\n")
      self.out.write("{\n")
      self.out.write("   print( \"*** Using predefined settings_map\" );\n")
      self.out.write("   %s.setMapSettings( settings_map );\n" % self.mapPage)
      self.out.write("}\n")


# =============================================================================
#                         TaxiVisFile.GeoMap
# =============================================================================

# -----------------------------------------------------------------------------
# Defines a class that writes the TaxiVis ring map for a single time slot
class GeoMap(BaseScript):

   # --------------------------------------------------------------------------
   def __init__(self, sFileName, sTitle, fDrawThreshold, fProbThreshold, sRoadData):
      BaseScript.__init__(self, sFileName, sTitle)

      self.mapPage = "mapGeoPage"

      self.fDrawThreshold = fDrawThreshold
      self.fProbThreshold = fProbThreshold
      self.sRoadData      = sRoadData

      self.view  = "topicView"
      self.scene = "topicScene"

   # --------------------------------------------------------------------------
   def ProcessLdaResults(self, ldaResults):
      lstCreatedLayers = {}  # List of already created topic layers

      # Write out the common header information.
      BaseScript.writeHeader(self)
      self.out.write("var %s = new MapPage();\n" % (self.mapPage))
      self.out.write("%s.setMapPage(%s);\n" % (self.scene,self.mapPage))
      self.out.write("\n")
      self.mapSettings();


      # Get the number of topics in these results.
      numTopics = ldaResults.numTopics()
      for combiner in ldaResults.getTopicList():
         sTopicName = "Topic %d" % (combiner.getTopicId())
         self.out.write("\n")
         self.out.write("// -------------------------------------------------\n" );
         self.out.write("// Topic = %s\n" % (combiner.getTopicId()));

         self.writeTopicColor(combiner.getTopicId())

         layer = "layer%d" % (combiner.getTopicId())
         nTopicNum = 0
         if not layer in lstCreatedLayers.keys():
            self.out.write("var %s = new JsLayer();\n" % layer)
            self.out.write("%s.setName(\"%s\");\n" % (layer, sTopicName) )
            lstCreatedLayers[layer] = 0
         else:
            lstCreatedLayers[layer] += 1
            print( "   ** Merged topics in this time window" )

            
         # Get a list of the top N terms.
         sortedTerms = sorted(combiner.terms.getList(), key=lambda t: t.getValue(), reverse=True)
         topNStreets = []
         i = 0
         for term in sortedTerms:
            if i < 30:
               topNStreets.append( term.getId() )
            i += 1

         sStreets = ""
         for nId in topNStreets:
            sStreets = "%s,%d" % (sStreets,nId)
         print( "Top N streets: %s" % (sStreets) )


         # Process the results of the file.
         for term in combiner.terms.getList():
            fProb = Prob(combiner.terms.getTotal(),term.getValue())
            nRoadNum = term.getId()

            if fProb > self.fDrawThreshold:
               try:
                  sRoadFileName = "%s/%d" % (self.sRoadData,nRoadNum)
                  fileRoad = open(sRoadFileName, 'r')

                  route = "layer%d_%d_R%d" \
                           % (combiner.getTopicId(),lstCreatedLayers[layer],nRoadNum)

                  # Look up the entropy for the term but need to look up from the term-topic
                  # perspective whereas this code is looking at it from topic-term.
                  fEntropy = 0
                  for iTerm in range(ldaResults.numTerms()):
                     term2 = ldaResults.getTerm(iTerm)
                     if term2.getId() == term.getId():
                        fEntropy = term2.getEntropy()
                        break


                  fTrans  = 0.9
                  if fProb < self.fProbThreshold:
                     fWeight = 3
                  else:
                     # Calculate line weight for the road.
                     fWeight = (math.log(fProb+1)*25) * fWeightThresholdMax
                     if fWeight < fWeightThresholdMin:
                        fWeight = fWeightThresholdMin
                     if fWeight > fWeightThresholdMax:
                        fWeight = fWeightThresholdMax

                  # Calculate transparency for the road.
                  # TODO: Tweak the transparency slightly according to importance
                  #       in order to see if that helps with the visualization
                  #       and visibility of the individual topics.
                  fTrans = (1 - fEntropy)*fTransThresholdMax
                  if fTrans < fTransThresholdMin:
                     fTrans = fTransThresholdMin
                  if fTrans > fTransThresholdMax:
                     fTrans = fTransThresholdMax

                  # Regular expressions to extract lon,lat from data files.
                  rePoint = re.compile( r'(\d+\.\d*),(\d+\.\d*)' )
                  iLon = 1
                  iLat = 2

                  # Write out the road segment
                  self.out.write("// Road ID = %s with p(%s)\n" % (nRoadNum, fProb));
                  self.out.write("var %s = new JsRoute();\n" % (route));
                  self.out.write("%s.setColor ( %s, %s );\n" 
                        % (route, self.topicColor(combiner.getTopicId()), fTrans) );
                  self.out.write("%s.setWeight( %s );\n" % (route, fWeight) );
                  for point in fileRoad:
                     match = rePoint.match(point)
                     if match:
                        fLon = match.group(iLon)
                        fLat = match.group(iLat)
                        self.out.write("%s.addPoint(0, %s, %s, 0,0);\n" 
                              % (route, fLat, fLon) );

                  # Add the road segment route to the layer
                  self.out.write("%s.addRoute( %s );\n" % (layer, route) );
                  fileRoad.close()
               except IOError:
                  print( "   Error opening road segment: %s" % (sRoadFileName) )

         self.out.write("%s.addLayer( %s );\n" % (self.mapPage,layer))
         self.out.write("print( \"Topic " + str(combiner.getTopicId()) + " added.\");\n")

      self.captureScreenShot( self.sTitle, 15000 )

# =============================================================================
#                         TaxiVisFile.StreetFiles
# =============================================================================
# -----------------------------------------------------------------------------
# Defines a class that writes the TaxiVis ring map for a single time slot
class StreetFiles(BaseScript):

   # --------------------------------------------------------------------------
   def __init__(self, sFileName, sTitle, fDrawThreshold, fProbThreshold, sRoadData):
      BaseScript.__init__(self, sFileName, sTitle)

      self.mapPage = "mapGeoPage"

      self.fDrawThreshold = fDrawThreshold
      self.fProbThreshold = fProbThreshold
      self.sRoadData      = sRoadData

      self.view  = "topicView"
      self.scene = "topicScene"

   # --------------------------------------------------------------------------
   def ProcessLdaResults(self, ldaResults):
      lstCreatedLayers = {}  # List of already created topic layers

      # Write out the common header information.
      BaseScript.writeHeader(self)
      self.out.write("var %s = new MapPage();\n" % (self.mapPage))
      self.out.write("%s.setMapPage(%s);\n" % (self.scene,self.mapPage))
      self.out.write("\n")
      self.mapSettings();


      # Get the number of topics in these results.
      numTopics = ldaResults.numTopics()
      for combiner in ldaResults.getTopicList():
         sTopicName = "Topic %d" % (combiner.getTopicId())
         self.out.write("\n")
         self.out.write("// -------------------------------------------------\n" );
         self.out.write("// Topic = %s\n" % (combiner.getTopicId()));

         self.writeTopicColor(combiner.getTopicId())

         layer = "layer%d" % (combiner.getTopicId())
         nTopicNum = 0
         if not layer in lstCreatedLayers.keys():
            self.out.write("var %s = new JsLayer();\n" % layer)
            self.out.write("%s.setName(\"%s\");\n" % (layer, sTopicName) )
            lstCreatedLayers[layer] = 0
         else:
            lstCreatedLayers[layer] += 1
            print( "   ** Merged topics in this time window" )

         # Process the results of the file.
         for term in combiner.terms.getList():
            fProb = Prob(combiner.terms.getTotal(),term.getValue())
            nRoadNum = term.getId()

            if fProb > self.fDrawThreshold:
               try:
                  sRoadFileName = "%s/%d" % (self.sRoadData,nRoadNum)
                  fileRoad = open(sRoadFileName, 'r')

                  route = "layer%d_%d_R%d" \
                           % (combiner.getTopicId(),lstCreatedLayers[layer],nRoadNum)

                  if fProb < self.fProbThreshold:
                     fTrans  = 0.9
                     fWeight = 2
                  else:
                     # Calculate transparency for the road.
                     fTrans = 1 - ((math.log(fProb+1)*25) * fTransThresholdMax)
                     if fTrans < fTransThresholdMin:
                        fTrans = fTransThresholdMin
                     if fTrans > fTransThresholdMax:
                        fTrans = fTransThresholdMax

                     # Calculate line weight for the road.
                     fWeight = (math.log(fProb+1)*25) * fWeightThresholdMax
                     if fWeight < fWeightThresholdMin:
                        fWeight = fWeightThresholdMin
                     if fWeight > fWeightThresholdMax:
                        fWeight = fWeightThresholdMax

                  # Regular expressions to extract lon,lat from data files.
                  rePoint = re.compile( r'(\d+\.\d*),(\d+\.\d*)' )
                  iLon = 1
                  iLat = 2

                  # Write out the road segment
                  self.out.write("// Road ID = %s with p(%s)\n" % (nRoadNum, fProb));
                  self.out.write("var %s = new JsRoute();\n" % (route));
                  self.out.write("%s.setColor ( %s, %s );\n" 
                        % (route, self.topicColor(combiner.getTopicId()), fTrans) );
                  self.out.write("%s.setWeight( %s );\n" % (route, fWeight) );
                  for point in fileRoad:
                     match = rePoint.match(point)
                     if match:
                        fLon = match.group(iLon)
                        fLat = match.group(iLat)
                        self.out.write("%s.addPoint(0, %s, %s, 0,0);\n" 
                              % (route, fLat, fLon) );

                  # Add the road segment route to the layer
                  self.out.write("%s.addRoute( %s );\n" % (layer, route) );
                  fileRoad.close()
               except IOError:
                  print( "   Error opening road segment: %s" % (sRoadFileName) )

         self.out.write("%s.addLayer( %s );\n" % (self.mapPage,layer))
         self.out.write("print( \"Topic " + str(combiner.getTopicId()) + " added.\");\n")

      self.captureScreenShot( self.sTitle, 20000 )


# =============================================================================
#      D3                 TaxiVisFile.ParallelCoordinates              D3
# =============================================================================

# -----------------------------------------------------------------------------
# Defines a class that writes the TaxiVis heat map file based on the LDA 
# results
class ParallelCoordinatesD3(BaseScript):

   # --------------------------------------------------------------------------
   def __init__(self, sFileName, sTitle, fProbThreshold, sCsvFile):
      BaseScript.__init__(self, sFileName, sTitle)

      self.sCsvFile = sCsvFile

      self.view  = "pcView"
      self.scene = "pcScene"

   # --------------------------------------------------------------------------
   def ProcessLdaResults(self, ldaResults):
      BaseScript.writeHeader(self)

      self.out.write("var colorsPc = new Array();\n")
      self.out.write("var html = new GraphPage();\n")
      self.out.write("html.setCsvFile(\"%s\");\n" % (self.sCsvFile))

      # Iterate over the term topics in the results and grab the second highest 
      # topic from each term and add it to a list.
      lstHighToLowProbabilities = []
      for iTerm in range(ldaResults.numTerms()):
         term = ldaResults.getTerm(iTerm)
         topic = sorted(term.getList(), 
               key=lambda t: Prob(term.getTotal(),t.getValue()),
               reverse=True)[1]
         lstHighToLowProbabilities.append( Prob(term.getTotal(), topic.getValue()) )

      # Sort the list of second highest probabilities for each term in reverse
      # order so that it is possible to extract the probability that can be
      # used to ensure that the visualization displays the highest N terms that
      # match a probability of P for at least T terms.
      lstHighToLowProbabilities.sort( reverse=True )

      # - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
      # Write out the CSV file

      # Nothing to do if there are no terms to process.
      if ldaResults.numTerms() < 1:
         return

      fileCsv = open(self.sCsvFile, 'w')

      # CSV header row - There is at least one term at this point.
      fileCsv.write("RoadID")
      term = ldaResults.getTerm(0)
      for iTopic in range(term.num()):
         topic = term.get(iTopic)
         fileCsv.write(",Topic%d" % (iTopic+1))
         self.writeTopicColor( topic.getTopicId() )
         #self.out.write("colorsPc[%d] = colors[%d];\n" 
         #      % (iTopic, self.topicColor(topic.getTopicId())))
         self.out.write("colorsPc[%d] = \"%s\";\n" 
               % (iTopic,Utils.stableRandomColor(topic.getTopicId())))
      fileCsv.write("\n")

      fThreshValue = lstHighToLowProbabilities[200]
      fThreshValue = ProcessLogValue( fThreshValue )
      self.out.write("html.setValueThresh(%f);\n" % (1*fThreshValue/3))
      self.out.write("html.setTopicThresh(2);\n")
      self.out.write("html.setTopicColors(colorsPc);\n")
      self.out.write("%s.setMapPage(html);\n" % (self.scene))

      self.captureScreenShot( self.sTitle, 15000 )


      # Write out the data values.
      sortedTerms = sorted( ldaResults.getTermList(), key=lambda w: w.getId() )
      for term in sortedTerms:
         nHigherThanThresh = 0
         for topic in term.getList():
            value = Prob(term.getTotal(), topic.getValue())
            value = ProcessLogValue( value )

            #print( "Value(%f)==Thresh(%f)" % (value,fThreshValue) )
            if value > fThreshValue:
               nHigherThanThresh += 1

         if nHigherThanThresh > 1:
            fileCsv.write( "%d" % (term.getId()) )
            for topic in term.getList():
               value = Prob( term.getTotal(), topic.getValue() )
               value = ProcessLogValue(value)
               fileCsv.write(",%f" % (value) )
            fileCsv.write("\n")

      fileCsv.close()

      
# =============================================================================
#                               TaxiVisFile.HeatMap
# =============================================================================

# -----------------------------------------------------------------------------
## Writes the TaxiVis heat map file based on the LDA results.
class HeatMap(BaseScript):
   
   # --------------------------------------------------------------------------
   def __init__(self, sFileName, sTitle, fThreshold, sRoadData):
      BaseScript.__init__(self, sFileName, sTitle)

      self.fWeightThresholdMin = 2  # Minimum value any street can have for width
      self.fWeightThresholdMax = 30 # Maximum value any street can have for width

      self.fThreshold     = 0.075 #fThreshold
      self.sRoadData      = sRoadData
      self.data           = {}
      self.colorMap       = []
      self.fMin           = sys.float_info.max
      self.fMax           = sys.float_info.min
      self.mapPage        = "mapHeatPage"

      self.view  = "heatView"
      self.scene = "heatScene"

      self.colorMap.append("#0000FF")  # Cold color
      self.colorMap.append("#3366FF")
      self.colorMap.append("#33CCFF")
      self.colorMap.append("#33FFFF")
      self.colorMap.append("#FFFFCC")
      self.colorMap.append("#FFFF99")
      self.colorMap.append("#FFFF66")
      self.colorMap.append("#FFFF33")
      self.colorMap.append("#FFFF00")
      self.colorMap.append("#FFCC00")
      self.colorMap.append("#FF9900")
      self.colorMap.append("#FF6600")
      self.colorMap.append("#FF3300")
      self.colorMap.append("#FF0000")  # Hot color

   # --------------------------------------------------------------------------
   def writeHeader(self):
      self.out.write("// Using threshold of %f to filter roads.\n" % (self.fThreshold))

      BaseScript.writeHeader(self)

      self.out.write("var %s = new MapPage();\n" % (self.mapPage))
      self.out.write("%s.setMapPage(%s);\n" % (self.scene,self.mapPage))

   # --------------------------------------------------------------------------
   def ProcessLdaResults(self, ldaResults):
      self.writeHeader()
      
      # Determine a range for the colors by dividing the probability range into
      # the number of segments for which there are colors into the color map.
      # Then group each item into the buckets.
      layer = "layer"
      self.out.write("var %s = new JsLayer();\n" % layer)
      self.out.write("%s.setName(\"Heat Map\");\n" % (layer) )
      self.mapSettings()

      # Find the min and max entropy for scaling.
      fEntropyMin = sys.float_info.max
      fEntropyMax = sys.float_info.min
      for iTerm in range(ldaResults.numTerms()):
         term2 = ldaResults.getTerm(iTerm)
         if fEntropyMin > term2.getEntropy():
            fEntropyMin = term2.getEntropy()
         if fEntropyMax < term2.getEntropy():
            fEntropyMax = term2.getEntropy()

      fEntropyRange = fEntropyMax - fEntropyMin

      # Find the contribution min and max.
      fSumMin = sys.float_info.max
      fSumMax = sys.float_info.min
      dictTermSums = {}
      fTotal = 0
      for term in ldaResults.getTermList():
         if fSumMax < term.getTotal():
            fSumMax = term.getTotal()
         if fSumMin > term.getTotal():
            fSumMin = term.getTotal()

         fTotal += term.getTotal()   

      fSumMin += self.fThreshold # Scale the min up to the threshold to give complete range.
      fRange = fSumMax - fSumMin
      fColorScale = float(self.fWeightThresholdMax)/float(len(self.colorMap)-1)

      if fRange < (0+sys.float_info.min):
         return

      sortedTerms = sorted(ldaResults.getTermList(), key=lambda t: t.getTotal(), reverse=False)
      for term in sortedTerms: #ldaResults.getTermList():
         fRelPercent = ((term.getTotal()-fSumMin)/fRange)
         #print( "%f = (%f-%f)/%f" % (fRelPercent,term.getTotal(),fSumMin,fRange) )
         if fRelPercent > self.fThreshold:
            try:
               fileRoad = open(term.getRoadFile(), 'r')

               route = "layer_R%d" % (term.getId())

               # Look up the entropy for the term but need to look up from the term-topic
               # perspective whereas this code is looking at it from topic-term.
               fEntropy = 0
               for iTerm in range(ldaResults.numTerms()):
                  term2 = ldaResults.getTerm(iTerm)
                  if term2.getId() == term.getId():
                     fEntropy = term2.getEntropy()
                     break

               # Calculate transparency for the road.
               fTrans = fRelPercent*fTransThresholdMax
               fTrans = (1-((fEntropy-fEntropyMin)/fEntropyRange))*fTransThresholdMax
               if fTrans < fTransThresholdMin:
                  fTrans = fTransThresholdMin
               if fTrans > fTransThresholdMax:
                  fTrans = fTransThresholdM

               # Calculate line weight for the road.
               fWeight = int(fRelPercent*self.fWeightThresholdMax)
               nColorIdx = int(fWeight/fColorScale)
               #fWeight = ((fEntropy-fEntropyMin)/fEntropyRange)*fWeightThresholdMax
               if fWeight < self.fWeightThresholdMin:
                  fWeight = self.fWeightThresholdMin
               if fWeight > self.fWeightThresholdMax:
                  fWeight = self.fWeightThresholdMax

               # Regular expressions to extract lon,lat from data files.
               rePoint = re.compile( r'(\d+\.\d*),(\d+\.\d*)' )
               iLon = 1
               iLat = 2

               # Write out the road segment
               self.out.write("// Road ID = %s with p(%s)\n" % (term.getId(),fRelPercent));
               self.out.write("var %s = new JsRoute();\n" % (route));
               self.out.write("%s.setColor ( \"%s\", %f );\n" % (route, self.colorMap[nColorIdx], 0.9) );
               self.out.write("%s.setWeight( %s );\n" % (route, fWeight) );
               for point in fileRoad:
                  match = rePoint.match(point)
                  if match:
                     fLon = match.group(iLon)
                     fLat = match.group(iLat)
                     self.out.write("%s.addPoint(0, %s, %s, 0,0);\n" % (route, fLat, fLon) );
   
               # Add the road segment route to the layer
               self.out.write("%s.addRoute( %s );\n" % (layer, route) );
               fileRoad.close()
            except IOError:
               print( "   Error opening road segment: %s" % (term.getRoadFile()) )

      self.out.write("%s.addLayer( %s );\n" % (self.mapPage,layer))

      self.captureScreenShot( self.sTitle, 10000 )


# =============================================================================
#                           TaxiVisFile.DocumentCluster
# =============================================================================
      
# -----------------------------------------------------------------------------
## Prepares LDA output for clustering.
class DocumentCluster(Base):
   # --------------------------------------------------------------------------
   def __init__(self, sFileName, sTitle):
      Base.__init__(self, sFileName, sTitle)

   # --------------------------------------------------------------------------
   def ProcessLdaResults(self, ldaResults):
      for iDoc in range(ldaResults.numDocuments()):
         doc = ldaResults.getDocument(iDoc)
         for iTopic in range(doc.num()):
            topic = doc.get(iTopic)
            if iTopic < (doc.num()-1):
               self.out.write( "%f " % (topic.getValue()) )
            else:
               self.out.write( "%f" % (topic.getValue()) )

         self.out.write("\n")


# =============================================================================
#                           TaxiVisFile.TopicStats
# =============================================================================
      
# -----------------------------------------------------------------------------
## Calculates statistics regarding the LDA output.
class Stats(Base):
   # --------------------------------------------------------------------------
   def __init__(self, sFileName, sTitle):
      Base.__init__(self, sFileName, sTitle)

   # --------------------------------------------------------------------------
   def ProcessLdaResults(self, ldaResults):

      # Loop over the terms with sublists of all the topics.
      for iTerm in range(ldaResults.numTerms()):
         term = ldaResults.getTerm(iTerm)
         sVals = ""
         for val in term.getList():
            sVals = "%s,%s" % (sVals,val.getValue())
         self.out.write( "%d,%s,%f\n" % (term.getId(),sVals,term.getEntropy()) )
