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
import sys
import math

# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
def Sum( total, count, newValue ):
   return total + newValue


# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
class Value(object):
   # --------------------------------------------------------------------------
   def __init__(self):
      self.nId       = -1
      self.nTopicId  = -1
      self.fValue    = 0
      self.sLabel    = ""

   # --------------------------------------------------------------------------
   def __repr__(self):
      return "(%d,%f)" % (self.nId,self.fValue)

   # --------------------------------------------------------------------------
   def setId(self, nId):
      self.nId = nId

   def getId(self):
      return self.nId
   
   # --------------------------------------------------------------------------
   def setTopicId(self, nTopicId):
      self.nTopicId = nTopicId

   def getTopicId(self):
      return self.nTopicId
      
   # --------------------------------------------------------------------------
   def setValue(self, fValue):
      self.fValue = fValue

   def getValue(self):
      return self.fValue

   # --------------------------------------------------------------------------
   def setLabel(self, sLabel):
      self.sLabel = sLabel

   def getLabel(self):
      return self.sLabel

   # --------------------------------------------------------------------------
   def add(self, value):
      # No children list is created until there is at least one child.  This 
      # separates a circular dependency in the relationship between Value and
      # ValueContainer.
      try:
         self.children.append(value)
      except NameError:
         self.children  = ValueContainer()
         self.children.append(value)

   def get(self, nId):
      for value in self.children:
         if value.getId() == nId:
            return value

      raise LookupError

# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
class ValueContainer(Value):
   # --------------------------------------------------------------------------
   def __init__(self):
      Value.__init__(self)
      self.fTotal    = 0   # Sum of values stored in this container
      self.lstValues = []
      self.sLabel    = ""
      self.fnAgg     = Sum # Aggregate function for child values.

      self.fMax      = sys.float_info.min # Minimum value observed
      self.fMin      = sys.float_info.max # Maximum value observed

   # --------------------------------------------------------------------------
   def __repr__(self):
      sStr = ""
      for topic in self.lstValues:
         sStr += topic.__repr__()

      return sStr

   # --------------------------------------------------------------------------
   # Set total sum of children Values is done by adding topics
   #def setTotal(self, fTotal):
   #   self.fTotal = fTotal

   def getTotal(self):
      return self.fTotal

   # --------------------------------------------------------------------------
   def setLabel(self, sLabel):
      self.sLabel = sLabel

   def getLabel(self):
      return self.sLabel

   # --------------------------------------------------------------------------
   def min(self):
      return self.fMin

   def min(self):
      return self.fMin

   # --------------------------------------------------------------------------
   def add(self, topic):
      self.lstValues.append(topic)
      self.fTotal = self.fnAgg( self.fTotal, len(self.lstValues), topic.getValue() )

      if topic.getValue() > self.fMax:
         self.fMax = topic.getValue()

      if topic.getValue() < self.fMin:
         self.fMin = topic.getValue()

   def num(self):
      return len(self.lstValues)

   def get(self, iTopic):
      return self.lstValues[iTopic]

   def getList(self):
      return self.lstValues

   def getEntropy(self):
      fEntropy = 0

      if self.fTotal > 0:
         for val in self.lstValues:
            fProb = val.getValue()/self.fTotal
            fEntropy += fProb * math.log(fProb)

      return -fEntropy


# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
class Document(ValueContainer):
   # --------------------------------------------------------------------------
   def __init__(self):
      ValueContainer.__init__(self)

   # --------------------------------------------------------------------------
   def __repr__(self):
      sStr = "Document: "
      sStr += ValueContainer.__repr__(self)

      return sStr


# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
class Term(ValueContainer):
   # --------------------------------------------------------------------------
   def __init__(self):
      ValueContainer.__init__(self)

      self.sRoadFile  = ""

   # --------------------------------------------------------------------------
   def __repr__(self):
      sStr = "Term: "
      sStr += ValueContainer.__repr__(self)

      return sStr

   # --------------------------------------------------------------------------
   def setRoadFile(self, sRoadFile):
      self.sRoadFile = sRoadFile

   def getRoadFile(self):
      return self.sRoadFile
      

# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
class TopicTerm(ValueContainer):
   # --------------------------------------------------------------------------
   def __init__(self):
      ValueContainer.__init__(self)


# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
class TopicDoc(ValueContainer):
   # --------------------------------------------------------------------------
   def __init__(self):
      ValueContainer.__init__(self)


# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
class TopicCombiner(Value):
   # --------------------------------------------------------------------------
   def __init__(self):
      Value.__init__(self)

      self.docs    = TopicDoc()  # Documents that are part of this topic
      self.terms   = TopicTerm() # Terms that are part of this topic

      self.nTopicNum  = -1 # Topic number of this topic.

   # --------------------------------------------------------------------------
   def setId(self, nId):
      Value.setId(self, nId)
      self.docs.setId(nId)
      self.terms.setId(nId)
  
   # --------------------------------------------------------------------------
   def setTopicNum(self, nTopicNum):
     self.nTopicNum = nTopicNum

   def getTopicNum(self):
     return self.nTopicNum

  # --------------------------------------------------------------------------
   def docs(self):
      return self.docs
   
   # --------------------------------------------------------------------------
   def terms(self):
      return self.terms


# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
class LdaResults(object):
   # --------------------------------------------------------------------------
   def __init__(self):
      self.sLabel     = "" # The time this set of LDA topics exists.
      self.lstDocs    = [] # List of documents
      self.lstTerms   = [] # List of terms
      self.lstTopics  = [] # List of topic combiners containing docs and terms

   # --------------------------------------------------------------------------
   def setLabel(self, sLabel):
      self.sLabel = sLabel
   
   # --------------------------------------------------------------------------
   def addDocument(self, doc):
      self.lstDocs.append(doc)
      
      for iTopic in range(doc.num()):
         d = doc.get(iTopic)
         if type(d) == TopicDoc:
            if (len(self.lstTopics)-1) < iTopic:
               topic = TopicCombiner()
               topic.setId( d.getId() )
               topic.setTopicId( d.getTopicId() )
               self.lstTopics.append( topic )
            self.lstTopics[iTopic].docs.add(d)
         else:
            print( "Uh-oh, adding a non-TopicDoc to the Document." )

   def getDocument(self, nDocNum):
      return self.lstDocs[nDocNum]

   def numDocuments(self):
      return len(self.lstDocs)
   
   # --------------------------------------------------------------------------
   def addTerm(self, term):
      self.lstTerms.append(term)
      
   def addTopicTerms(self):
      print( "   Number of topics = %d" % (len(self.lstTopics)) )
      print( "   Number of terms  = %d" % (len(self.lstTerms)) )
      for term in self.lstTerms:
         iTopic = -1
         for topic in term.getList():
            iTopic += 1
            combiner = self.lstTopics[iTopic]
            t = term.getList()[iTopic]
            t.setTopicId( topic.getTopicId() )
            combiner.terms.add( t )

   def getTerm(self, iTerm):
      return self.lstTerms[iTerm]

   def numTerms(self):
      return len(self.lstTerms)

   def getTermList(self):
      return self.lstTerms

   # --------------------------------------------------------------------------
   def addTopic(self, topic):
      self.lstTopics.append(topic)

   def numTopics(self):
      return len(self.lstTopics)

   def getTopicList(self):
      return self.lstTopics
