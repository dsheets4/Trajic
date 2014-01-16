
Contents
--------

===============================================================================
Compiling
---------
mkdir build
cd build
cmake ../
make

-------------------------------------------------------------------------------
Starting the web server
-----------------------
A web server is required due to the D3 implementation of Parallel Coordinates
reading a csv file.  Python offers a simple server that satisfies this need.

python2 -m SimpleHTTPServer 8888 &
python3 -m http.server 8888 &


-------------------------------------------------------------------------------
Debug Builds (on Linux)
----------------------
cmake -DCMAKE_BUILD_TYPE=Debug ../


===============================================================================
Parsing the taxi data
------------------------------

(Windows)
TaxiDataParser C:\Users\Dingbat\Ph.D\doctorate\Research\2011-3-Trajectory\TaxiAnalysis\data\SmallData .\output


===============================================================================
Creating the user and database
------------------------------
mysql> create user 'taxi'@'localhost' identified by 'taxi';
mysql> create database taxi2;
mysql> grant all privileges on taxi2.* to taxi@localhost;
mysql> flush privileges;

Make a backup of the database
-----------------------------
$> 

Load the database from a backup
-------------------------------
$> mysql -u taxi -p taxi_info < taxi_tables.sql
$> mysql -u taxi -p taxi_info < taxi_info_geography_info.sql


===============================================================================
Data Set
--------
$PHD_DATA/TaxiDataSet/tar_201004_1/data4/TRACK
There are 81925 files in the data set as counted by the command below.

[dingbat@memor TRACK]$ cd $PHD_DATA/TaxiDataSet/tar_201004_1/data4/TRACK
[dingbat@memor TRACK]$ ls -lR | grep "^-" | wc
  81925  737334 5233243

End parsing: 2012-03-01T22:22:42.410
Parsing completed in 28753 seconds.
Processed a total of 132044296 number of points.

select count(*) AS "Num Taxis" from Taxi;select count(*) AS "Num Files" from Files; select count(*) AS "Num GPS Pts" from TaxiPoint;select count(*) AS "Valid GPS Pts" from TaxiPoint where Error=0;

-------------------------------------------------------------------------------
mysql> select count(*) AS "Num Taxis" from Taxi;
+-----------+
| Num Taxis |
+-----------+
|     27905 |
+-----------+
1 row in set (0.12 sec)

mysql> select count(*) AS "Num Files" from Files;
+-----------+
| Num Files |
+-----------+
|     81900 |
+-----------+
1 row in set (0.11 sec)

-------------------------------------------------------------------------------
mysql> select count(*) AS "Num GPS Pts" from TaxiPoint;
+-------------+
| Num GPS Pts |
+-------------+
|   132044296 |
+-------------+
1 row in set (2 min 21.06 sec)

-------------------------------------------------------------------------------
mysql> select count(*) AS "Valid GPS Pts" from TaxiPoint where Error=0;
+----------------+
| Valid GPS Pts  |
+----------------+
|      126392046 |
+----------------+
1 row in set (3 min 7.92 sec)

-------------------------------------------------------------------------------
mysql> select count(*) AS "Loaded GPS Pts" from TaxiPoint where Error=0 AND Loaded=1;
+----------------+
| Loaded GPS Pts |
+----------------+
|       33927805 |
+----------------+
1 row in set (3 min 21.93 sec)

mysql> create index IdxTaxiPointTimestamp on TaxiPoint(Timestamp);
Query OK, 0 rows affected (32 min 43.49 sec)
Records: 0  Duplicates: 0  Warnings: 0

mysql> create index IdxTaxiPointTaxiID on TaxiPoint(Taxi_ID);
Query OK, 0 rows affected (27 min 20.50 sec)
Records: 0  Duplicates: 0  Warnings: 0

-------------------------------------------------------------------------------
mysql> select min(Timestamp) from TaxiPoint;
+----------------+
| min(Timestamp) |
+----------------+
|  1270051200000 | 2010-03-31T16:00:00.000Z
+----------------+
1 row in set (0.08 sec)

mysql> select max(Timestamp) from TaxiPoint;
+----------------+
| max(Timestamp) |
+----------------+
|  1270310399994 | 2010-04-03T15:59:59.994Z
+----------------+
1 row in set (0.02 sec)
`


===============================================================================
Running the Taxi Data Parser
----------------------------
$> ./src/TaxiDataParser/TaxiParser $PHD_DATA/TaxiDataSet/tar_201004_1/data4/TRACK ../output > full-run-output.log 2>&1 &
$> head -n4 full-run-output.log
$> date; tail -n1 full-run-output.log


Test Data
---------
$> ./src/TaxiParser ../data/SmallData ../output/Empty


Windows Visual Studio Command Line
----------------------------------
..\..\data\TaxiDataSet\tar_201004_1\data4\TRACK ..\..\output\FullData


Performance
-----------
If you are creating a database from scratch it's beneficial to postpone the 
creation of an index until after the date has been read in.  Just speeds 
things up although creating it later takes some time it's still quite faster
to create the index post load.  Note that there is an index created on the 
Taxi(Plate) column during DB loading since the act of populating the database
requires a lookup of the Plate to correlate taxi data.  Having this index
does improve the speed of the load.


===============================================================================
Creating KML Files
------------------
$> ./src/ReverseGeocoder/ReverseGeocoder 2010-04-01T07:00:00+08 2010-04-01T07:30:00+08 /var/www/html/maps/kml/lines.kml
$> ./src/ReverseGeocoder/ReverseGeocoder 2010-04-01T07:00:00+08 2010-04-01T07:30:00+08 /var/www/html/maps/kml/points.kml Point


===============================================================================
Creating a grid
---------------

Create a grid between 22.5,113.42 and 23.5,114.2 with a grid spacing of
0.045 in latitude and 0.050 in longitude and save the grid definition as 
level 10.

$> ./src/GridGen/GridGen --lat 22.5 23.0 --lon 113.5 114.2 --grid 0.045 0.050 --level 10


The tables are defined by a table of latitude and longitude lines that create a 
grid at various levels.  Each point is then cached into a level by a separate
table.

LatGridLines/LonGridLines
-------------------------
Lat_ID/Lon_ID
Lat/Lon
Level

GridCache[Level]
----------------
Point_ID  FOREIGN KEY REFERENCES TaxiPoint(Point_ID)
Lat_ID    FOREIGN KEY REFERENCES LatGridLines(Lat_ID)
Lon_ID    FOREIGN KEY REFERENCES LonGridLines(Lon_ID)
Cell Label

===============================================================================
Other data collection
---------------------

-------------------------------------------------------------------------------
Reverse GeoCoding
-----------------

Geocoding is the process of finding the GPS coordinates of an address.  Reverse
geocoding, then, is the process of finding an address from GPS coordinates.
Since the data has an abundance of GPS coordinates and no associated 
information it is necessary to reverse geocode for the sematics of the GPS 
point.  OpenStreetMap provides an API to request the reverse geocoding, as 
does Google.

Lookup closest road segment
---------------------------
http://210.75.252.45:81/itsservice/itsdata.ashx?action=getroadinfobylatlng&lat=22.54483223&lng=114.1250534

This will return a road id for the segment.


Lookup points for the road segment
----------------------------------
http://210.75.252.45:81/itsservice/itsdata.ashx?action=getroadbyid&roadid=11817

This will return the lon,lat points separated by a semi-colon of the points in the road segment.


OpenStreetMap - Nominatim
-------------------------
http://nominatim.openstreetmap.org/reverse?format=json&lat=52.5487429714954&lon=-1.81602098644987&zoom=18&addressdetails=1

format=[xml|json]
   Output format
osm_type=[N|W|R]
osm_id=<value>
   A specific osm node / way / relation to return an address for
   Please use this in preference to lat/lon where possible 
   Note: Using a osm_type of W seems required to get the address details.
email=<valid email address>
   If you are making large numbers of request please include a valid email address
   or alternatively include your email address as part of the User-Agent string.
   This information will be kept confidential and only used to contact you in the
   event of a problem, see Usage Policy for more details.


===============================================================================
Time Calculations
-----------------
Time from the data files was assumed as China Standard Time (CST) and converted
to Greenwich Mean Time (GMT).  The offset is +8 hours.  That means that
midnight GMT is 8AM CST.  Each hour has 3600 seconds and 3600000 milliseconds.

April 1, 2010 7AM CST since Jan 1, 1970: 1270076400000 ms = 21167940 min
April 1, 2010 8AM CST since Jan 1, 1970: 1270080000000 ms = 21168000 min
April 1, 2010 9AM CST since Jan 1, 1970: 1270083600000 ms = 21168060 min


===============================================================================
Useful Queries
--------------

* Find all Points between a certain time
select * from TaxiPoint where Time_min>=21168600 AND Time_min<21168660 order by Time_min, Time_ms;
select * from TaxiPoint where Timestamp>=1270076400000 AND Timestamp<1270080000000;

* Find all valid points between a time where the taxi has a customer.
select * from TaxiPoint where Time_min>21167940 AND Time_min<21168000 AND Error=0 AND Loaded=1;


===============================================================================
Reverse GeoCoding
-----------------

OpenStreetMap
-------------
http://wiki.openstreetmap.org/wiki/Nominatim
http://nominatim.openstreetmap.org/reverse?format=xml&zoom=18&addressdetails=1&lat=22.5581&lon=114.091

Google
------
http://code.google.com/apis/maps/documentation/geocoding/#ReverseGeocoding
http://maps.googleapis.com/maps/api/geocode/xml?latlng=22.55809784,114.0910645&sensor=false

geoPlugin
---------
http://www.geoplugin.com/webservices/extras
http://www.geoplugin.net/extras/location.gp?lat=22.5581&long=114.091&format=xml


===============================================================================
Deploying the web-site
----------------------
$> cd <taximap-svn>/www
$> svn export --force ./ /var/www/html/maps


