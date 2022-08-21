window.initMap = () => {
    
    const map = new google.maps.Map(document.getElementById('map'), {
        center: {lat: 51.5, lng: -0.00},
        zoom: 12,
        mapId: "41eff541116738e7"
       

    });
    const overlay = new GoogleMapsOverlay({
        layers: [
            scatterplot(),
            heatmap(),
            hexagon()
            //Scene()
        ],
    });

    
    overlay.setMap(map);
}

import { GoogleMapsOverlay } from '@deck.gl/google-maps';
import { HexagonLayer } from '@deck.gl/aggregation-layers';
import { ScatterplotLayer } from '@deck.gl/layers';
import { HeatmapLayer } from '@deck.gl/aggregation-layers';
//import {ScenegraphLayer} from '@deck.gl/mesh-layers';


const sourceData = './lora.json';

const COLOR_RANGE = [
    [5,48,97],
    [33,102,172],
    [67,147,195],
    //[146,197,222],
    //[209,229,240],
    //[247,247,247],
    //[253,219,199],
    //[244,165,130],
   // [214,96,77],
    //[178,24,43],
    //[103,0,31],
];

const scatterplot = () => new ScatterplotLayer({
    id: 'scatter',
    data: sourceData,
    opacity: 1,
    filled: true,
    radiusMinPixels: 10,
    radiusMaxPixels: 20,
    getPosition: d => [d.lng, d.lat],
    getFillColor: d => d.Rssi > 0 ? [200, 0, 40, 150] : [255, 140, 0, 100],
    pickable: true,
    onHover: ({object, x, y}) => {
        const el = document.getElementById('tooltip');
        if (object) {
          const { lat, lng, Rssi } = object;
          el.innerHTML = (`<h1>Rssi ${Rssi}</h1>
             <p class='title'> lat: ${lat}&nbsp;&nbsp;lng: ${lng}</p>`);
          el.style.display = 'block';
          el.style.fontSize = 10 ;
          el.style.opacity = 0.9;
          el.style.left = x + 'px';
          el.style.top = y + 'px';
        } else {
          el.style.opacity = 0.0;
        }
    },

    

});
const heatmap = () => new HeatmapLayer({
    id: 'heat',
    data: sourceData,
    getPosition: d => [d.lng, d.lat],
    getWeight: d => d.Rssi + 120,
    radiusPixels: 60,
});



const hexagon = () => new HexagonLayer({
    id: 'hex',
    data: sourceData,
    filled: true,
    //colorRange: colorScale(d.Rssi),
    
    getPosition: d => [d.lng, d.lat],
    //getElevationWeight: d => d.Rssi/1000,
    
    //elevationScale: 20,
    extruded: true,
    //colorRange: COLOR_RANGE,
    elevationRange: [0, 360],
    elevationScale: 120,
    getElevationWeight: d => (d.Rssi+120)/100,
    
    //getFillColor:  [255, 255, 255, 40],
    //getLineColor: [255, 255, 255],
    //getElevation: d=>(d.Rssi+120),
    //getLineWidth: 30,
    //getFillColor: [255, 165, 0],
    //getColor: d => colorScale(d.Rssi),
    //getFillColor: d => colorScale(d.properties.Rssi),
    //getFillColor: colorScale(d => d.Rssi)  ,
    radius: 10,         
    opacity: 0.6,        
    coverage: 0.88,
    lowerPercentile: 50
});

/*
const Scene = () => new ScenegraphLayer({
    id: 'scenegraph-layer',
    data,
    pickable: true,
    scenegraph: './resource/antenna/scene.gltf',
    getPosition: d => [51.5381174,-0.010979],
    //getPosition: d => d.coordinates,
    getOrientation: d => [0, Math.random() * 180, 90],
    sizeScale: 500,
    _lighting: 'pbr'
  });
  */
  const COLOR_SCALE = [
    [1, 152, 189],
    [73, 227, 206],
    [216, 254, 181],
    [254, 237, 177],
    [254, 173, 84],
    [209, 55, 78]
  ];

 
  function colorScale(x) {
    
    if (-80 <= x <= -60) {
      return COLOR_SCALE[0] 
    }
    else if(-90 <= x < -80) {
        return COLOR_SCALE[1];
    }
    else if(-100 <= x < -90) {
        return COLOR_SCALE[2];
    }
    else {
        return COLOR_SCALE[3];
    }
  }
 