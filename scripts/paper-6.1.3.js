// To run, type the following at the prompt:
//     run("test.js")
// 
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
print("This generates images for section 6.1.3.");

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
run("s10800/t8/P0.004000p0.000750/all/default/2012-06-27T18-00-00/heat.js");
run("s10800/t8/P0.004000p0.000750/all/default/2012-06-27T12-00-00/heat.js");
run("s10800/t8/P0.004000p0.000750/all/default/2012-06-27T03-00-00/heat.js");
run("s10800/t8/P0.004000p0.000750/all/default/2012-06-27T03-00-00/map.js");

// Zoom in on the airport
var settings_map = new JsSettingsMap();
settings_map.setZoomLevel(16);
settings_map.setCenterLon(  113.813789 );
settings_map.setCenterLat(   22.651206 );
image_name = "heatdefaultall18-ZoomAirport.png"
run("s10800/t8/P0.004000p0.000750/all/default/2012-06-27T18-00-00/heat.js");
settings_map = undefined
image_name = undefined

// Zoom in on Fu'tian border crossing
var settings_map = new JsSettingsMap();
settings_map.setZoomLevel(16);
settings_map.setCenterLon(  114.058499 );
settings_map.setCenterLat(   22.519294 );
image_name = "heatdefaultall18-ZoomTraffic.png"
run("s10800/t8/P0.004000p0.000750/all/default/2012-06-27T18-00-00/heat.js");
image_name = "mapdefaultall18-ZoomTraffic.png"
run("s10800/t8/P0.004000p0.000750/all/default/2012-06-27T18-00-00/map.js");
settings_map = undefined
image_name = undefined
