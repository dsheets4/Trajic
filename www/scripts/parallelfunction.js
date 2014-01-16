bInitialized = false
gMaxValue = 0;
var arrSelectedTopics = new Array();
var arrSelectedStreet = new Array();
var fOpacityHighlight = 1.0
var fOpacityHighlight2 = 1.0
var fOpacityNormal     = 0.5
var fOpacityBackground = 0.03
var sWidthNormal    = "1px"
var sWidthHighlight = "4px"
var sWidthHighlight2 = "8px"


function resetLineHighlight(d, obj) {

    var fOpacity = fOpacityHighlight;
    var sWidth = sWidthHighlight;

    // Set the selection state on the data element, which seems to be 
    // the only thing that carries state.
    if (d.pcp_select === undefined) {
        d.pcp_select = 0;
    }

    switch (d.pcp_select) {
        case 0:
            fOpacity = fOpacityNormal;
            sWidth = sWidthNormal;
            break;

        case 1:
            fOpacity = fOpacityHighlight;
            sWidth = sWidthHighlight;
            break;

        case 2:
            fOpacity = fOpacityHighlight2;
            sWidth = sWidthHighlight2;
            break;
    }

    console.log("resetLineHighlight:");
    console.log("   select = " + d.pcp_select);
    //console.log("   fOpacityCurr  = " + fOpacityCurr);
    //console.log("   sWidthCurr    = " + sWidthCurr);
    console.log("   fOpacityNew   = " + fOpacity);
    console.log("   sWidthCurrNew = " + sWidth);
    console.log("");

    return d3.select(obj).style("stroke-opacity", fOpacity).attr("stroke-width", sWidth);
}

function incrementLineHighlight(d, obj) {
    // Set the selection state on the data element, which seems to be 
    // the only thing that carries state.
    if (d.pcp_select === undefined) {
        d.pcp_select = 0;
    }
    else {
        d.pcp_select++;
        if (d.pcp_select > 2) {
            d.pcp_select = 0
        }
    }

    return resetLineHighlight(d, obj);
}



function Initial() {

   if( !bInitialized )
   {
      // Set the default values requested by the application framework/script.
      document.getElementById('max').value = GraphPage.getValueThresh();
      document.getElementById('Num').value = GraphPage.getTopicThresh();
      bInitialized = true

      var colorArray = GraphPage.getTopicColors();
      for(i = 0; i < colorArray.length; ++i )
      {
         var style = document.createElement('style');
         sClassName = '.Topic' + (i+1)
         style.type = 'text/css';
         style.innerHTML = sClassName + ' { stroke: ' + colorArray[i] + '; }';
         //console.log( style.innerHTML )
         document.documentElement.appendChild(style);
      }
      
   }


   line = d3.svg.line();
   axis = d3.svg.axis().orient("left");
   svg  = d3.select("body").append("svg")
      .attr("id","svg") 
      .attr("width", width)
      .attr("height", height + margin.top + margin.bottom)  
      .append("g")    
      .attr("transform", "translate(" + margin.left + "," + margin.top + ")");


   d3.csv(GraphPage.getCsvFile(), function (pc) {

       //filter content
       var ct, test, min;
       min = document.getElementById("max").value;
       ct = document.getElementById("Num").value;
       console.log("Max value threshold: " + min);
       console.log("Num topics that must exceed threshold: " + ct);
       ct = 8 - ct;
       filter(pc, min, ct);
       var content = pc.filter(function (d) {
           for (i = 0; i < newpc.length; i++) {
               if (d.RoadID == newpc[i]) {
                   return d.RoadID == newpc[i];
               }
           }
       });

       //Extract the list of dimensions and create a scale for each. 
       x.domain(dimensions = d3.keys(content[0]).filter(
               function (d) {
                   return d != "RoadID" &&
                        (y[d] = d3.scale.linear()
                           .domain([0, gMaxValue])//d3.extent(content, function(p) { return +p[d]; }))
                           .range([height, 0]));
               }
            ));

       //find the bigest Topic is
       bigTopic(content, index, temp);

       //create background lines
       background = svg.append("g")
         .attr("class", "background")
         .selectAll("path")
         .data(content)
         .enter()
         .append("path")
         .attr("d", path);

       //due to the highest probability to color paths
       svg.selectAll("g")
         .selectAll(".background path")
         .data(topicid)
         .attr("class", function (d) { return "Topic" + d; console.log(d); })
         .attr("id", function (d) { return d; });


       //add foreground path
       var classid = -1, idid = -1, strr = "", cr = 0; ;
       foreground = svg.append("g")
         .attr("class", "foreground")
         .selectAll("path")
         .data(content)
         .enter().append("path")
         .attr("d", path)
         .attr("class", function (d) { classid++; return "Topic" + topicid[classid]; })
         .attr("id", function (d) { return d.RoadID; })
         .on("mouseover", function highlight() {
             var roadid = d3.select(this).attr("id");
             var fOpacity = fOpacityHighlight;
             var sWidth = sWidthHighlight;
             return d3.select(this).style("stroke-opacity", fOpacity).attr("stroke-width", sWidth) && getInfo(topict, content, roadid);
         })
         .on("mouseout", function highlight1(d) {
             var deroadid = document.getElementById("info1");
             //console.log(deroadid);
             return resetLineHighlight(d, this) && deroadid.parentNode.removeChild(deroadid);
         })
      .on("click", function (d) {
          //var strr = new String();
          var temp = d3.select(this).attr("id");
          cr++;

          //clear the old stufff
          if (document.getElementById("t2body")) {
              strr = document.getElementById("t2body").rows[0].cells[0].innerHTML;
          }
          strr = strr.concat(temp)
          strr = strr.concat(",");
          if (cr < 30) {
              strr = strr;
          }
          else {
              strr = strr.concat("\n");
              cr = 0;
          }
          console.log(strr);
          //roadfile = roadfile.concat(temp);
          //console.log(roadfile);
          if (!document.getElementById("t2body")) {
              ShowSelecRoad(strr);
          }
          else {
              document.getElementById("t2body").parentNode.removeChild(document.getElementById("t2body"));
              ShowSelecRoad(strr);
          }

          // Set the street as highlighted/unhighlighted depending on previous state.
          if (arrSelectedStreet.indexOf(d) == -1) {
              arrSelectedStreet.push(d);
          }

          // Set the line to the next highlight level.
          incrementLineHighlight(d, this);
      });


       // Add a group element for each dimension.  
       var g = svg.selectAll(".dimension")
         .data(dimensions)
         .enter().append("g")
         .attr("class", "dimension")
         .attr("transform", function (d) { return "translate(" + x(d) + ")"; })
         .on("click", changecolor(fOpacityNormal))
         .on("mouseout", changecolor1(fOpacityNormal));

       // Add an axis and title.  
       g.append("g")
         .attr("class", "axis")
         .each(function (d) { d3.select(this).call(axis.scale(y[d])); })
         .append("text")
         .attr("text-anchor", "middle")
         .attr("y", -9)
         .text(String);

       // Add and store a brush for each axis.  
       g.append("g")
         .attr("class", "brush")
         .each(function (d) { d3.select(this).call(y[d].brush = d3.svg.brush().y(y[d]).on("brush", brush)); })
         .selectAll("rect")
         .attr("x", -8)
         .attr("width", 16);
   });

      //create table
      d3.select("body").append("table").attr("id","t1").attr("align","left");
      d3.select("body").select("#t1").append("thead").append("tr").selectAll("th").data(topict).enter().append("th").text(function(d){return d;});

      ResetPCP();
}

//functions
function filter(pc,max,ct){
   var count;
   for(var j=0;j<pc.length;j++){ 
      count = 0;
      var top= new Array();
      pc[j].Topic1 = parseFloat(pc[j].Topic1);
      pc[j].Topic2 = parseFloat(pc[j].Topic2);
      pc[j].Topic3 = parseFloat(pc[j].Topic3);
      pc[j].Topic4 = parseFloat(pc[j].Topic4);
      pc[j].Topic5 = parseFloat(pc[j].Topic5);
      pc[j].Topic6 = parseFloat(pc[j].Topic6);
      pc[j].Topic7 = parseFloat(pc[j].Topic7);
      pc[j].Topic8 = parseFloat(pc[j].Topic8);
      top[0] = pc[j].Topic1;
      top[1] = pc[j].Topic2;
      top[2] = pc[j].Topic3;
      top[3] = pc[j].Topic4;
      top[4] = pc[j].Topic5;
      top[5] = pc[j].Topic6;
      top[6] = pc[j].Topic7;
      top[7] = pc[j].Topic8;
      //define the threshold
      for(var i=0;i<top.length;i++){
         if(top[i]<max){ count++; }
         if(top[i]>gMaxValue){ gMaxValue = top[i]; }
      }
      if(count <= ct)
      {
         newpc = newpc.concat(pc[j].RoadID);
         //console.log("Passed:        ; " + top);
      }
      else
      {
         //console.log("Failed: Count=" + count + "; " + top);
      }
   }
}
//find the bigest topic
function bigTopic(content,index,temp){
   var topicidf = [];
   for(var i=0;i<content.length;i++){
      var topics= new Array();
      //console.log(content);
      content[i].Topic1 = parseFloat(content[i].Topic1);
      content[i].Topic2 = parseFloat(content[i].Topic2);
      content[i].Topic3 = parseFloat(content[i].Topic3);
      content[i].Topic4 = parseFloat(content[i].Topic4);
      content[i].Topic5 = parseFloat(content[i].Topic5);
      content[i].Topic6 = parseFloat(content[i].Topic6);
      content[i].Topic7 = parseFloat(content[i].Topic7);
      content[i].Topic8 = parseFloat(content[i].Topic8);
      topics[0] = content[i].Topic1;
      topics[1] = content[i].Topic2;
      topics[2] = content[i].Topic3;
      topics[3] = content[i].Topic4;
      topics[4] = content[i].Topic5;
      topics[5] = content[i].Topic6;
      topics[6] = content[i].Topic7;
      topics[7] = content[i].Topic8;
      temp = d3.max(topics);
      index = topics.indexOf(temp);
      index = index +1;
      topicidf = topicidf.concat(index);  
   }
   topicid = topicidf;
}



function ShowSelecRoad(strr){
   var t2 = d3.select("body").select("#t2");
   t2.append("tbody").attr("id","t2body").append("tr").append("td").attr("width","1%").text(strr);

}

function clearSelectedRoads(){
    strr = "";
    document.getElementById("t2body").parentNode.removeChild(document.getElementById("t2body"));
    ShowSelecRoad(" ");
}

function ResetStreetSelections() {

    for (var i = 0; i < arrSelectedStreet.length; i++) {
        console.log("Reset select = " + d3.select(arrSelectedStreet[i]).datum());
    }
    arrSelectedStreet = [];
}

function ResetPCP()
{
   //console.log("Reseting PCP");

   svg.selectAll("g").selectAll(".foreground path").style("stroke-opacity",fOpacityNormal); 
   svg.selectAll("g").selectAll(".background path").style("stroke-opacity",0);

   arrSelectedTopics = [];
   ResetStreetSelections();
}

function changecolor(opacity){
    return function (g, i) {

        var fOpacity = fOpacityBackground;

        if (arrSelectedTopics.length == 0) {
            // Makes all the other lines (almost) disappear.
            svg.selectAll("g").selectAll(".foreground path").transition().style("stroke-opacity", fOpacityBackground);
            arrSelectedStreet = []; // Should we clear the selections or reselect them???
        }

        var idx = arrSelectedTopics.indexOf(g);
        if ( idx == -1) {
            arrSelectedTopics.push(g);
            fOpacity = fOpacityNormal;
        }
        else {
            arrSelectedTopics.splice(idx, 1);
            if (arrSelectedTopics.length == 0) {
                // Makes all the other lines (almost) disappear.
                svg.selectAll("g").selectAll(".foreground path").transition().style("stroke-opacity", fOpacityNormal);
            }
        }

        // Causes the clicked set of lines to appear.
        svg.selectAll("g").selectAll(".background path").filter(
            function (d) {
                //console.log(i);
                //console.log(d);
                return d == i + 1;
            })
        .transition().style("stroke-opacity", fOpacity).style("stroke-width", sWidthNormal);

        //// Makes the non-clicked lines disappear.
        //svg.selectAll("g").selectAll(".background path").filter(function(d){ 
        //   return d!=i+1;
        //})
        //.transition()
        //   .style("stroke-opacity",.03); 
    }

}
function changecolor1(opacity){
   return function(g,i)
   {
      //svg.selectAll("g").selectAll(".foreground path")
      //   .style("stroke-opacity",0.5); 
      //svg.selectAll("g").selectAll(".background path")
      //   .style("stroke-opacity",0); 
   }
}

// Returns the path for a given data point.
function path(d) {  return line(dimensions.map(function(p) { return [x(p), y[p](d[p])]; }));}// Handles a brush event, toggling the display of foreground lines.
function brush() {  var actives = dimensions.filter(function(p) { return !y[p].brush.empty(); }),      
   extents = actives.map(function(p) { return y[p].brush.extent(); });  
   foreground.classed("fade", function(d) {   
      return actives.every(function(p, i) {      
         return extents[i][0] <= d[p] && d[p] <= extents[i][1];    }) ? null : "none";  });}  

   var td = [];
   function getInfo(topict,content,roadid){
      var info = content.filter(function(d){
         return d.RoadID == roadid;});

      td[0]=info[0].RoadID;
      td[1]=parseFloat(info[0].Topic1);
      td[2]=parseFloat(info[0].Topic2);
      td[3]=parseFloat(info[0].Topic3);
      td[4]=parseFloat(info[0].Topic4);
      td[5]=parseFloat(info[0].Topic5);
      td[6]=parseFloat(info[0].Topic6);
      td[7]=parseFloat(info[0].Topic7);
      td[8]=parseFloat(info[0].Topic8);
      var table = d3.select("body").select("#t1");

      table.append("tbody").attr("id","info1").append("tr");
      d3.select("body").select("#t1").select("tbody").selectAll("tr").selectAll("td")
         .data(td).enter().append("td");
      d3.select("body").select("#t1").select("tbody").selectAll("tr").selectAll("td").text(function(d){return d; }).attr("class","RoadID");

   }


function WriteToFile(){
   try{
      var fso = new ActiveXObject("Scripting.FileSystemObject");
      var s = fso.CreateTextFile("C:\\aest.txt",true);
      s.WriteLine("RoadID");
      for(var x = 0; x < roadfile.length; x++){
         s.WriteLine(roadfile[x]);
      }
      console.log("Created File successfully!");
      s.Close();
      window.alert("Created File successfully!");}
      catch(err){
         var strErr = "Error:";
         strErr+=err.description;
         console.log(strErr);
         console.log("R U here!");
      }
}

function buttonLeft(){
   console.log("Did you see me?");
   var left = document.getElementById("max");
   var v = left.value;
   v = parseFloat(v);
   console.log(v);
   if(v-0.1 >= 0){
      left.value = v - 0.1;
   }
   else{
      left.value = 0;
   }
}

function buttonRight(){
   console.log("Did you see me?");
   var right = document.getElementById("max");
   var v = right.value;
   v = parseFloat(v);
   console.log(v);
   if(v+0.1 <= 8.0){
      right.value = v + 0.1;
   }
   else{
      right.value = 8.0;
   }
}

function ReInitial(){
   var s = document.getElementById("svg");
   var s1 = document.getElementById("t1");
   s.parentNode.removeChild(s);
   s1.parentNode.removeChild(s1);
   newpc = [];
   Initial();
}
