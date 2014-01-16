
// tells Scala where to find the TMT classes
import scalanlp.io._;
import scalanlp.stage._;
import scalanlp.stage.text._;
import scalanlp.text.tokenize._;
import scalanlp.pipes.Pipes.global._;

import edu.stanford.nlp.tmt.stage._;
import edu.stanford.nlp.tmt.model.SymmetricDirichletParams;
import edu.stanford.nlp.tmt.model.lda._;
import edu.stanford.nlp.tmt.model.llda._;

val source = ${DataSourceDirective}

val tokenizer = {
//  SimpleEnglishTokenizer() ~>            // tokenize on space and punctuation
  SimpleEnglishTokenizer()             // tokenize on space and punctuation
//  CaseFolder() ~>                        // lowercase everything
//  CaseFolder() ~>                        // lowercase everything
//  WordsAndNumbersOnlyFilter()            // ignore non-words and non-numbers
//  MinimumLengthFilter(3)                 // take terms with >=3 characters
}

val text = {
  source ~>                              // read from the source file
  Columns(2) ~>                   // select column containing text
  Join(" ") ~>
  TokenizeWith(tokenizer) ~>             // tokenize with tokenizer above
  TermCounter()                        // collect counts (needed below)
//  TermMinimumDocumentCountFilter(4) ~>   // filter terms in <4 docs
//  TermDynamicStopListFilter(10)       // filter out 10 most common terms
//  TermStopListFilter(List("Longgang", "Futian", "Bao'an", "Luohu", "Nanshan", "Yantian")) 
//  TermStopListFilter(List("rd", "ave", "2nd", "east", "west", "5th", "expy", "bao'an", "side", "highway", "road", "avenue", "exit", "of", "1st", "3rd", "7th", "8th", "no.2", "4th", "middle", "107", "north", "east-west", "south", "st", "motorway", "1st", "park", "alley", "9th", "pedestrian", "interchange", "11th", "s", "high-speed", "e", "national", "ring", "n", "entrance", "eastern", "6th", "hwy")) 
//  DocumentMinimumLengthFilter(5)         // take only docs with >=5 terms
}

// turn the text into a dataset ready to be used with LDA
val dataset = LDADataset(text);

// define the model parameters
val params = ${LDAModelParamsDirective},
  dataset = dataset,
  topicSmoothing = SymmetricDirichletParams(0.01),
  termSmoothing = SymmetricDirichletParams(0.01)
);

// Name of the output model folder to generate
val modelPath = ${OutputDirective}

// Trains the model: the model (and intermediate models) are written to the
// output folder.  If a partially trained model with the same dataset and
// parameters exists in that folder, training will be resumed.
TrainCVB0LDA(params, dataset, output=modelPath, maxIterations=1000);

// To use the Gibbs sampler for inference, instead use
//TrainGibbsLDA(params, dataset, output=modelPath, maxIterations=1500);
