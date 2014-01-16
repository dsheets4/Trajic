Quick Generation
----------------

   Windows
   -------
   python main.py & python main.py -s & ^
   python main.py -u -s & python main.py -u -f & ^
   python main.py -l -f & python main.py -l -f

   Linux
   -----
   python main.py & python main.py -s & \
   python main.py -u -s & python main.py -u -f & \
   python main.py -l -f & python main.py -l -f


Using the main script
---------------------
The main.py script will sequentially handle processing the necessary scripts
to generate the visualization files.  This script automatically determines
if there are existing results and skips re-running files that have already
been generated.  The command line arguments it takes are a conglomerate of
the arguments described for each of the other scripts below.  If main is run
then no other scripts need to be run separately.  Use python main.py --help
for additional help text or refer to script.

python main.py \
   -i ../data/2012-06-27.good -r ../data/road_text_info \
   -o ../scripts \
   -d 10800 -n 8 \
   -P 0.005 -p 0.001 \
   -l -u

Processing the input data file
------------------------------
The input file is now a giant CSV file of records (used to be binary files,
one per taxi). The input file is roughly ordered by time but must be processed
to give an exact ordering.  The following command will split the giant input
file into the input files used for the LDA input.  The duration (-d) argument 
indicates a duration for subdividing the data.  Duration defaults to 1 hour.
The -l option is optional and causes the script to remove any recorded points
where the taxi does not have a passenger.

python ./InputSplit.py \
   -i ../data/GPS_2012_06_27.txt.new \
   -o ../data/TaxiDataSplit \
   -d 10800 \
   [-l]


Processing Taxi data using LDA
------------------------------
After generating the desired input for the LDA process from the taxi input 
file, the data can be processed using LDA.  The LDA process script takes in
an input directory (-i), which is the output directory of the InputSplit step.
It also takes in the number of topics (-n) that should be generated using the 
input data.  The LDA output is stored in the output directory (-o).  The -l 
option instructs the logic to ignore any taxi points where the taxi does not
have a passenger.

python processLDA.py \
   -n 8 \
   -i ../data/TaxiDataSplit/s10800 \
   -o ../data/TaxiDataLda



Parsing the LDA output to TaxiVis Script
----------------------------------------
Creating the TaxiVis script file for the full LDA result:

python TaxiVisScriptGen-Full.py \
   -i ../data/TaxiDataLda/t8 \
   -o ../scripts \
   -r ../data/road_text_info \
   -P 0.005 -p 0.001


Running TaxiVis to create the visualization
-------------------------------------------
From the build directory (in Linux),
$> cmake ../
$> make
$> ./bin/TaxiVis \
   s10800/t8/P0.001000p0.000500/2012-06-27T06-00-00/map.js \
   s10800/t8/P0.001000p0.000500/2012-06-27T00-00-00/vis.js \
   s10800/t8/P0.001000p0.000500/2012-06-27T03-00-00/vis.js \
   s10800/t8/P0.001000p0.000500/2012-06-27T06-00-00/vis.js \
   s10800/t8/P0.001000p0.000500/2012-06-27T09-00-00/vis.js \
   s10800/t8/P0.001000p0.000500/2012-06-27T12-00-00/vis.js \
   s10800/t8/P0.001000p0.000500/2012-06-27T15-00-00/vis.js \
   s10800/t8/P0.001000p0.000500/2012-06-27T18-00-00/vis.js \
   s10800/t8/P0.001000p0.000500/2012-06-27T21-00-00/vis.js \
   capture.js

The capture.js script simply captures the current screen.  Since the 
application is threaded, it may be better to manually capture the screen so 
that it has time to finish drawing.  In the script prompt a screenshot can 
be taken by executing the following:
TaxiAnalysis> view.captureScreenShot( "TaxiVis.png" );



Statistics on the 2012-06-27 data set
-------------------------------------
Records processed : 59354643
Records kept      : 34477348  (records with null road id are thrown out)

fDrawThreshold = 0.0002 (required probability before point is drawn)

Time slot: 2012-06-27T00-00-00
   Total taxis  : 21076
   Total points : 1324580
   Total routes : 7852
   Total points : 58731
Time slot: 2012-06-27T01-00-00
   Total taxis  : 20975
   Total points : 1368105
   Total routes : 7838
   Total points : 55771
Time slot: 2012-06-27T02-00-00
   Total taxis  : 20796
   Total points : 1294996
   Total routes : 7145
   Total points : 49180
Time slot: 2012-06-27T03-00-00
   Total taxis  : 20552
   Total points : 1202681
   Total routes : 6470
   Total points : 44164
Time slot: 2012-06-27T04-00-00
   Total taxis  : 20352
   Total points : 1129532
   Total routes : 6021
   Total points : 41797
Time slot: 2012-06-27T05-00-00
   Total taxis  : 20378
   Total points : 1129680
   Total routes : 5934
   Total points : 43637
Time slot: 2012-06-27T06-00-00
   Total taxis  : 20797
   Total points : 1248904
   Total routes : 6826
   Total points : 50351
Time slot: 2012-06-27T07-00-00
   Total taxis  : 21117
   Total points : 1386174
   Total routes : 7801
   Total points : 56493
Time slot: 2012-06-27T08-00-00
   Total taxis  : 21177
   Total points : 1534690
   Total routes : 8438
   Total points : 61462
Time slot: 2012-06-27T09-00-00
   Total taxis  : 21185
   Total points : 1523084
   Total routes : 8447
   Total points : 62826
Time slot: 2012-06-27T10-00-00
   Total taxis  : 21179
   Total points : 1513834
   Total routes : 8317
   Total points : 61191
Time slot: 2012-06-27T11-00-00
   Total taxis  : 21177
   Total points : 1552415
   Total routes : 7976
   Total points : 59736
Time slot: 2012-06-27T12-00-00
   Total taxis  : 20854
   Total points : 1506718
   Total routes : 8037
   Total points : 59828
Time slot: 2012-06-27T13-00-00
   Total taxis  : 20837
   Total points : 1539116
   Total routes : 7879
   Total points : 58949
Time slot: 2012-06-27T14-00-00
   Total taxis  : 20831
   Total points : 1570521
   Total routes : 8026
   Total points : 59817
Time slot: 2012-06-27T15-00-00
   Total taxis  : 20826
   Total points : 1505156
   Total routes : 8420
   Total points : 63572
Time slot: 2012-06-27T16-00-00
   Total taxis  : 20853
   Total points : 1510926
   Total routes : 8443
   Total points : 63959   
Time slot: 2012-06-27T17-00-00
   Total taxis  : 20887
   Total points : 1504912
   Total routes : 8585
   Total points : 62855
Time slot: 2012-06-27T18-00-00
   Total taxis  : 20914
   Total points : 1555355
   Total routes : 8359
   Total points : 61804
Time slot: 2012-06-27T19-00-00
   Total taxis  : 20912
   Total points : 1542569
   Total routes : 8503
   Total points : 61036
Time slot: 2012-06-27T20-00-00
   Total taxis  : 20901
   Total points : 1517863
   Total routes : 8351
   Total points : 59929
Time slot: 2012-06-27T21-00-00
   Total taxis  : 20873
   Total points : 1487689
   Total routes : 8610
   Total points : 63270
Time slot: 2012-06-27T22-00-00
   Total taxis  : 20856
   Total points : 1509323
   Total routes : 8738
   Total points : 63771
Time slot: 2012-06-27T23-00-00
   Total taxis  : 20830
   Total points : 1497045
   Total routes : 8172
   Total points : 60375




