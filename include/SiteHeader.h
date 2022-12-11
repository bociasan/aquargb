#include <Arduino.h>

const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html>
<head>
  
  <title>AquaRGB Plus</title>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <style>
body{

  --bg-range-color: rgba(15, 139, 141,1);
  --bg-value-color: white;
  padding:0px;
  margin:0px;
  justify-content: center;
  align-content: center;
  font-family: Segoe UI;
}
.main{
  display: flex;
  flex-direction: column;
  width:100%;
  height:100%;
  justify-content: center;
  align-items: center;
}

/*---FirstPart---*/
.firstPart{
  display:flex;
  margin-top: 20px;
  width:100%;
}
.curtain-box{
  display:block;
  padding: 5vh;
  margin: auto;
  width: 210px;
  height: 210px;
  
  border-top-left-radius: 50%;
  border-bottom-left-radius: 50%;
  border-bottom-right-radius: 50%;
  

}
.curtain-behind{
  margin: auto;
  width: inherit;
  height: inherit;
  border-radius: 0 0 8px 8px;
  background-color: var(--bg-range-color);
  box-shadow: 2px 2px 12px 1px rgba(140,140,140,.5);
   border-top-left-radius: 50%;
    border-bottom-left-radius: 50%;
    border-bottom-right-radius: 50%;
  overflow:hidden;
  border:solid 1px lightgray;
  transform:rotate(-45deg);
}

.curtain{
  height: 90%;
  width: 200%;
  background-color: var(--bg-value-color);
  transition: height 3s !important;
  transition-timing-function: ease-in;
  transform: rotate(45deg) translate(-60px, 0);
}


/*---SecondPart---*/

.secondPart{
  display:flex;
  flex-direction: row;
  
  width:90%;
  height:150px;
  margin-top:20px;

}
@media screen and (max-width: 920px){
  .secondPart{
    display:flex;
    flex-direction: column;
    
    width:90%;
    height:450px;
    margin-top:20px;
  
  }
  .Card1{
    margin-bottom: 15px;
  }
  .Card2{
    margin-bottom: 15px;
  }
  .subSec1{
    display: flex;
    align-items: center;
    justify-content: center;
  }
}


.Card1{
  display:flex;
  justify-content: center;
  flex-direction: row;
  width:100%;
  height:150px;
  background-color: white;
  margin-right: 10px;
  box-shadow: inset 0 -3em 3em rgba(0, 0, 0, 0.1), 0 0 0 2px rgb(255, 255, 255),
    0.3em 0.3em 1em rgba(0, 0, 0, 0.3);
  
}
.Card2{
  display:flex;
  width:100%;
  height:150px;
  margin-right: 10px;
  background-color: white;
  box-shadow: inset 0 -3em 3em rgba(0, 0, 0, 0.1), 0 0 0 2px rgb(255, 255, 255),
    0.3em 0.3em 1em rgba(0, 0, 0, 0.3);
}
.Card3{
  display:flex;
  width:100%;
  height:150px;
  background-color: white;
  box-shadow: inset 0 -3em 3em rgba(0, 0, 0, 0.1), 0 0 0 2px rgb(255, 255, 255),
    0.3em 0.3em 1em rgba(0, 0, 0, 0.3);
}

/*--SubSections*/
.subSec1{
  display: flex;
  width: 60%;
  height:100%;
  background-color: none;
  justify-content: center;
  align-items: center;
}
.subSec2{
  display: flex;
  width: 70%;
  height:100%;
  justify-content: center;
  align-items: center;
  font-size: x-large;
  font-weight: 600;
}
.subSec3{
  display: flex;
  width: 100%;
  height:100%;
  justify-content: center;
  align-items: center;
}

.subSec3>p{
  font-size: x-large;
  font-weight: 600;
}

/*circleStat*/

@property --p{
  syntax: '<number>';
  inherits: true;
  initial-value: 0;
}






.pie {
  --b:20px;
  --c:rgba(15, 139, 141,1);
  --w:100px;
  
  width:var(--w);
  aspect-ratio:1;
  position:relative;
  display:inline-grid;
  margin:5px;
  place-content:center;
  font-size:25px;
  font-weight:bold;
  font-family:sans-serif;
}
:root{
  --p:0;
}
.pie:before,
.pie:after {
  content:"";
  position:absolute;
  border-radius:50%;
}
.pie:before {
  inset:0;
  background:
    radial-gradient(farthest-side,var(--c) 98%,#0000) top/var(--b) var(--b) no-repeat,
    conic-gradient(var(--c) calc(var(--p)*1%),#0000 0);
  -webkit-mask:radial-gradient(farthest-side,#0000 calc(99% - var(--b)),#000 calc(100% - var(--b)));
          mask:radial-gradient(farthest-side,#0000 calc(99% - var(--b)),#000 calc(100% - var(--b)));
}
.pie:after {
  inset:calc(50% - var(--b)/2);
  background:var(--c);
  transform:rotate(calc(var(--p)*3.6deg)) translateY(calc(50% - var(--w)/2));
}
.animate {
  animation:p 1s .5s both;
}
.no-round:before {
  background-size:0 0,auto;
}
.no-round:after {
  content:none;
}
@keyframes p {
  from{--p:0}
}

body {
  background:#ddd;
}


/*--tHIRDpART*/
.thirdPart{
  display:flex;
  flex-direction: row;
  
  width:90%;
  height:412px;
  margin-top:10px;

}

/*--->Cards for history data<---*/

  .TCard{
    display: flex;
    height:100%;
    width:100%;
    justify-content: center;
    align-items:center;

  }
  @media screen and (min-width: 920px){
    .circle{
      display: flex;
      flex-direction: column;
      justify-content: center;
      align-items: center;
      height:300px;
      width:300px;
      border-radius: 50%;
      background-color: white;
      box-shadow: inset 0 -3em 3em rgba(0, 0, 0, 0.1), 0 0 0 2px rgb(255, 255, 255),
      0.3em 0.3em 1em rgba(0, 0, 0, 0.3);
    }
  }
  .title{
    display:flex;
    width:100%;
    height:30px;
    justify-content: center;
    align-items: center;
  }
  .title>p{
    font-size: x-large;
    font-weight: 700;
  }

  .consumption{
    display:flex;
    width:100%;
    height:30%;
    justify-content: center;
    align-items: center;
  }
  .consumption>p{
    font-size: larger;
    font-weight: 600;
  }


  @media screen and (max-width: 920px){
    .thirdPart{
      display:flex;
      flex-direction: column;
      margin-top: 15px;

    }
    .TCard{
      display:flex;
      height:60px;
      width:100%;
    }
    .circle{
      display: flex;
      flex-direction: row;
      justify-content: center;
      align-items: center;
      height:60px;
      width:100%;
      background-color: white;
      box-shadow: inset 0 -3em 3em rgba(0, 0, 0, 0.1), 0 0 0 2px rgb(255, 255, 255),
      0.3em 0.3em 1em rgba(0, 0, 0, 0.3);
    }
  }

  .boxbox{
  position:absolute;
  width:inherit;
  height: 30px;
  margin-top: 40px;
  justify-content: center;
  align-items: center;
  z-index: 1;
}
.boxbox>p{
  display: flex;
  font-size: x-large;
  justify-content: center;
  align-items: center;
  font-weight:700;
}
</style>
<title>AquaRGB Plus</title>
<meta name="viewport" content="width=device-width, initial-scale=1">
<link rel="icon" href="data:,">
</head>
<body>
  <div class="main">
    <div class="firstPart">
      <div class="curtain-box">
      <div class="boxbox"><p id="DataWDrop"></p></div>
      <div class="curtain-behind">
        <div class="curtain" id="curtain"></div>
      </div>
    </div>
    </div>

    <div class="secondPart">
        <div class="Card1">
            <div class="subSec1">
                <svg xmlns="http://www.w3.org/2000/svg" width="40" height="40" fill="currentColor"
                     class="bi bi-thermometer-high" viewBox="0 0 16 16">
                    <path d="M9.5 12.5a1.5 1.5 0 1 1-2-1.415V2.5a.5.5 0 0 1 1 0v8.585a1.5 1.5 0 0 1 1 1.415z"/>
                    <path d="M5.5 2.5a2.5 2.5 0 0 1 5 0v7.55a3.5 3.5 0 1 1-5 0V2.5zM8 1a1.5 1.5 0 0 0-1.5 1.5v7.987l-.167.15a2.5 2.5 0 1 0 3.333 0l-.166-.15V2.5A1.5 1.5 0 0 0 8 1z"/>
                </svg>
                </i></div>
            <div class="subSec2">Temperature</div>
            <div class="subSec3">
                <p id="temp"></p>
            </div>

        </div>
        <div class="Card2">
            <div class="subSec1"><img
                    src="data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAABgAAAAYCAYAAADgdz34AAAABmJLR0QA/wD/AP+gvaeTAAABaElEQVRIieWUMUsDQRCFPyWFEcRGkaSxkIgkpLYSLMVCRCKChb9Gf4yKqJ2NWFgFjLGwEi1N1EpDMEKUWNxbHJfNJeaw0YHhze6be29usxf4L7EKnAFN5SmwPKhYATgEGsoLoNMlz4EHoAYcAPl+xBsxgr3ypZfJcQJxl0dxBkmmd/lsBYc9g6E49z7jm0bKI6vAgup34ITo9pSBOvAobgrIAvPAIrBktMrdnNeAD6LXvAfmfjB1XgN0NNhKqOmKr3PcNPvTpnZ8iNsyfDVk0DINM9qraJ0JGGRUV7SeNXzTidof+cbU48KGsBgYqOj1jBnuNmSwbaZzH8u1sBAwKHg97pkOsBMy2AdKwCWQ096d0J413p6bNkd09iVp9RUbmmjXTOfeck/1epyA/6H5URNmAlxWWE9i8CScDHATXs9ABi1hOsCNCl9/y2BE+JbEwD0cMkh7PQNFiuimtLW2t6it2v/D/GPxCf1pjJqpy4PVAAAAAElFTkSuQmCC"
                    width="40" height="40"></div>
            <div class="subSec2">Humidity</div>
            <div class="subSec3">
                <div class="pie animate no-round" id="HUM"><p class="class" id="humi"></p></div>

            </div>
        </div>
        <div class="Card3">
            <div class="subSec1">
                <svg xmlns="http://www.w3.org/2000/svg" width="36" height="36" fill="currentColor" class="bi bi-fan"
                     viewBox="0 0 16 16">
                    <path d="M10 3c0 1.313-.304 2.508-.8 3.4a1.991 1.991 0 0 0-1.484-.38c-.28-.982-.91-2.04-1.838-2.969a8.368 8.368 0 0 0-.491-.454A5.976 5.976 0 0 1 8 2c.691 0 1.355.117 1.973.332.018.219.027.442.027.668Zm0 5c0 .073-.004.146-.012.217 1.018-.019 2.2-.353 3.331-1.006a8.39 8.39 0 0 0 .57-.361 6.004 6.004 0 0 0-2.53-3.823 9.02 9.02 0 0 1-.145.64c-.34 1.269-.944 2.346-1.656 3.079.277.343.442.78.442 1.254Zm-.137.728a2.007 2.007 0 0 1-1.07 1.109c.525.87 1.405 1.725 2.535 2.377.2.116.402.222.605.317a5.986 5.986 0 0 0 2.053-4.111c-.208.073-.421.14-.641.199-1.264.339-2.493.356-3.482.11ZM8 10c-.45 0-.866-.149-1.2-.4-.494.89-.796 2.082-.796 3.391 0 .23.01.457.027.678A5.99 5.99 0 0 0 8 14c.94 0 1.83-.216 2.623-.602a8.359 8.359 0 0 1-.497-.458c-.925-.926-1.555-1.981-1.836-2.96-.094.013-.191.02-.29.02ZM6 8c0-.08.005-.16.014-.239-1.02.017-2.205.351-3.34 1.007a8.366 8.366 0 0 0-.568.359 6.003 6.003 0 0 0 2.525 3.839 8.37 8.37 0 0 1 .148-.653c.34-1.267.94-2.342 1.65-3.075A1.988 1.988 0 0 1 6 8Zm-3.347-.632c1.267-.34 2.498-.355 3.488-.107.196-.494.583-.89 1.07-1.1-.524-.874-1.406-1.733-2.541-2.388a8.363 8.363 0 0 0-.594-.312 5.987 5.987 0 0 0-2.06 4.106c.206-.074.418-.14.637-.199ZM8 9a1 1 0 1 0 0-2 1 1 0 0 0 0 2Z"/>
                    <path d="M8 15A7 7 0 1 1 8 1a7 7 0 0 1 0 14Zm0 1A8 8 0 1 0 8 0a8 8 0 0 0 0 16Z"/>
                </svg>
            </div>
            <div class="subSec2">FAN</div>
            <div class="subSec3">
                <p id="fan"></p>

            </div>
        </div>
    </div>
    <div class="thirdPart">

        <div class="TCard">
            <div class="circle">
                <div class="title"><p>Yesterday</p></div>
                <div class="consumption"><p id="DataYest"></p></div>
            </div>
        </div>

        <div class="TCard">
            <div class="circle">
                <div class="title"><p>2d Ago</p></div>
                <div class="consumption"><p id="DataAgo1"></p></div>
            </div>
        </div>

        <div class="TCard">
            <div class="circle">
                <div class="title"><p>Last Month</p></div>
                <div class="consumption"><p id="DataTotal"></p></div>
            </div>
        </div>
    </div>
</div>
<script>
  var gateway = `ws://${window.location.hostname}/ws`;
  var websocket;
  window.addEventListener('load', onLoad);
  function initWebSocket() {
    console.log('Trying to open a WebSocket connection...');
    websocket = new WebSocket(gateway);
    websocket.onopen    = onOpen;
    websocket.onclose   = onClose;
    websocket.onmessage = onMessage; // <-- add this line
  }
  function onOpen(event) {
    console.log('Connection opened');
  }
  function onClose(event) {
    console.log('Connection closed');
    setTimeout(initWebSocket, 2000);
  }

  function onMessage(event) {
    var state;
    //console.log(event.data)
    var device = JSON.parse(event.data).device
    console.log(device);



    // document.getElementById('humidity').innerHTML = device.humidity + ' %';
    // document.getElementById('temperature').innerHTML = device.temperature + '\u2103';
    // document.getElementById('status').innerHTML = device.state ? 'on' : 'off';
    // document.getElementById('total_duration').innerHTML = device.total_duration;
    // document.getElementById('total_volume').innerHTML = device.total_volume;
        
      const volumeInPercent = map_range(device.total_volume, 0, 50, 0, 100);
const a=100-volumeInPercent;
let previousHeight = document.getElementById("curtain").style.height=map_range(a,0,100,0,145)+"%";

document.getElementById('DataWDrop').innerHTML=device.total_volume + " Liter";
console.log(previousHeight);

//Input data section
var Temperature=device.temperature;  //Temperature of air
var humidity=device.humidity;    //Humidity in air
var Fan=humidity >= 50 ? 1 : 0;         //Fan OFF/ON
var DtYester=device.consumption[0]; //consumption yesterday
var DtAgo1=device.consumption[1];   //consumption 2d Ago
var DtMonth=device.consumption[2]; //consumption in last month


//Temperature Part
document.getElementById('temp').innerHTML=Temperature+'\u2103';

//Humidity Part
var root=document.querySelector(':root')
var rootStyles=getComputedStyle(root);
var p=rootStyles.getPropertyValue('--p');
root.style.setProperty('--p',humidity);
document.getElementById('humi').innerHTML=humidity+"%";

//Fan Part
 if(Fan==0){
    document.getElementById('fan').innerHTML="OFF";
 }
 else
 document.getElementById('fan').innerHTML="ON";

 
//Consumtion Part
document.getElementById('DataYest').innerHTML=DtYester+" Liter";
document.getElementById('DataAgo1').innerHTML=DtAgo1+" Liter";
document.getElementById('DataTotal').innerHTML=DtMonth+" Liter";


  }
  function onLoad(event) {
    initWebSocket();
  }



  function map_range(value, low1, high1, low2, high2) {
    return low2 + (high2 - low2) * (value - low1) / (high1 - low1);
  }
</script>
</body>
</html>
)rawliteral";