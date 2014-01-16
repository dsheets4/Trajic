// To run, type the following at the prompt:
//     run("test.js")
// 
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
print("This is the Heat Map test script file.");

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Zoom in on the airport
var settings_map = new JsSettingsMap();
settings_map.setZoomLevel(16);
settings_map.setCenterLon(  114.111864 );
settings_map.setCenterLat(   22.538024 );
image_name = "mapdefaultall00-ZoomAirport.png"
//run("s10800/t8/P0.004000p0.000750/all/default/2012-06-27T00-00-00/map.js");

run("s10800/t8/P0.004000p0.000750/loaded/default_filter/2012-06-27T12-00-00/heat.js");
settings_map = undefined
image_name = undefined
