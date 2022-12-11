#include <Arduino.h>
#include <DHT.h>
#include <ServerHeader.h>
// #include <ESP8266LLMNR.h>
// #include <ESP8266mDNS.h>
#include <FastLED.h>
#include <macrosses.h>


#define LED_PIN     D5
#define NUM_LEDS    20
#define BRIGHTNESS  70
#define SATURATION  255
#define LED_TYPE    WS2812B
#define COLOR_ORDER GRB
CRGB leds[NUM_LEDS];
int fade_iterator = 0;
int min_value = 2000;
int max_value = 0;
int medium_value = 850;
int hysteresis = 30;
bool rising_flag = false;

#define DHTPIN D1     // Digital pin connected to the DHT sensor
#define DHTTYPE    DHT11
DHT dht(DHTPIN, DHTTYPE);

volatile int flow_frequency; 
float l_sec;
#define flowsensor  D2
unsigned long currentTime;
unsigned long cloopTime;

bool is_active = false;
unsigned long last_pulse_time = 0;
// unsigned long first_pulse_time = 0;
unsigned long finish_threshold = 400;
bool needToNotify = true;

#define transition_time 10000

#define users_count 3
struct User {
  float volume = 0;
  unsigned long total_duration = 0;
  String name = "";
} users[users_count];
const String user_names[] = {"Dan", "Marin", "Laura"};
const int last_three_day_consumption[] = {90, 85, 2987};
struct Result {
  float volume = 0;
  unsigned long duration = 0;
  unsigned long first_pulse_time = 0;
} last_result;

struct Data {
  float temperature = 0;
  float humidity = 0;
  float total_volume = 10;
  unsigned long total_duration = 200;
} data;

void enableDevice(){
  last_pulse_time = millis();
  if (!is_active) {
    last_result.first_pulse_time = millis();
    last_result.duration = 0;
    last_result.volume = 0;
    is_active = true;
    Serial.println("Device enabled.");
  }
  needToNotify = true;
}

IRAM_ATTR void flowInterrupt(){
  //Serial.println("Pulse");
  flow_frequency++;
  enableDevice();
}

String stringifyUsers(){
  String res = "\"users\":[";

  for (User user : users){
    res = res + "{\"total_duration\":" + user.total_duration
        + ",\"total_volume\":"  + user.volume
        + ",\"name\":\"" + user.name + "\""
        + "},";
  }
                   
  res = res.substring(0, res.length()-1);                             
  res += "]";
  //Serial.println(res);
  return res;
}

String stringifyConsumption(){
  String res = "\"consumption\":[";

  for (int val : last_three_day_consumption){
    res = res
        + val
        + ",";
  }
                   
  res = res.substring(0, res.length()-1);                             
  res += "]";
  //Serial.println(res);
  return res;
}

String getStateMessage(){
  // int targetPos100 = map(stepper.targetPosition(), 0, homePosition, 0, 100);

  String message = "{\"device\":{\"state\":" + String(is_active) 
                    + ",\"temperature\":"+ data.temperature 
                    + ",\"humidity\":" + data.humidity
                    + ",\"total_volume\":" + data.total_volume
                    + ",\"total_duration\":" + data.total_duration

                    + "," + stringifyUsers()
                    + "," + stringifyConsumption()
                    + "}}";

  return message;
}

void notifyClients() {
  String message = getStateMessage();
  ws.textAll(message);
}

void handleWebSocketMessage(void *arg, uint8_t *data, size_t len) {
  String message = (char*)data;
  AwsFrameInfo *info = (AwsFrameInfo*)arg;
  if (info->final && info->index == 0 && info->len == len && info->opcode == WS_TEXT) {
    data[len] = 0;
    if (strcmp((char*)data, "goUp") == 0) {
      // handleButtonUp();
    }

    if (strcmp((char*)data, "goDown") == 0) {
      // handleButtonDown();
    }

    if (strcmp((char*)data, "stop") == 0) {
      // handleButtonSet();
    }
    needToNotify = true;


    if (message.indexOf("1s") >= 0) {
      int messageInt = message.substring(2).toInt();
      // if (homePosition){
      //   long targetPosition = map(messageInt, 0, 100, 0, homePosition);
      //   handleMoveTo(targetPosition);

      //   Serial.printf("Target position from slider: %d, mapped: %ld.\n", messageInt, targetPosition);
      // } else {
      //   Serial.println("Please set homeposition first!");
      // }
    }
  }
}

void onEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len) {
    switch (type) {
      case WS_EVT_CONNECT:
        Serial.printf("WebSocket client #%u connected from %s\n", client->id(), client->remoteIP().toString().c_str());
        ws.text(client->id(), getStateMessage());
        break;
      case WS_EVT_DISCONNECT:
        Serial.printf("WebSocket client #%u disconnected\n", client->id());
        break;
      case WS_EVT_DATA:
        handleWebSocketMessage(arg, data, len);
        break;
      case WS_EVT_PONG:
      case WS_EVT_ERROR:
        break;
  }
}



void setup()
{

  delay(500);
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.setBrightness(  BRIGHTNESS );

  for (int i = 0; i < users_count; i++){
    users[i].name = user_names[i];
  }

  pinMode(flowsensor, INPUT);
  dht.begin();
  Serial.begin(115200);
  // attachInterrupt(digitalPinToInterrupt(flowsensor), flowInterrupt, RISING); // Setup Interrupt
  currentTime = millis();



  // if (!MDNS.begin("esp8266")) {             // Start the mDNS responder for esp8266.local
  //   Serial.println("Error setting up MDNS responder!");
  // }
  // Serial.println("mDNS responder started");


  // LLMNR.begin("aquargb");
  // Serial.println("LLMNR responder started");

  WiFi.mode(WIFI_AP_STA);
  WiFi.hostname(newHostname.c_str());
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println();
  // Print ESP Local IP Address
  Serial.println(WiFi.localIP());

  ws.onEvent(onEvent);
  server.addHandler(&ws);

  // Route for root / web page
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    // request->send_P(200, "text/html", index_html, processor);
    request->send_P(200, "text/html", index_html);
  });
  // Start server
  server.begin();

  //fill_solid(leds, NUM_LEDS, CRGB::Green);

}

CRGB getColor(){
  int r, g;
  unsigned long duration = millis() - last_result.first_pulse_time;
  if (duration < transition_time/2){
    g = 255;
    r = map(duration, 0, transition_time/2, 0, 255);
  } else {
    if (duration > transition_time) {
      g = 0;
      if ((duration - transition_time)/250 % 2){
        r = 255;
      } else {
        r = 0;
      }
    }
    else
    {
      r = 255;
      g = 255 - map(duration, transition_time/2, transition_time, 0, 255);
    }
  }


  return CRGB(r,g,0);
}

void calcFlowRate(){
  currentTime = millis();
  if(currentTime >= (cloopTime + 250))
  {
    
    float temporary_temp = dht.readTemperature();
    float temporary_humidity = dht.readHumidity();

    if (temporary_temp != data.temperature && data.humidity!= temporary_humidity) {
      needToNotify = true;
    }

    data.temperature = temporary_temp;
    data.humidity = temporary_humidity;

    cloopTime = currentTime; 
    if(flow_frequency != 0){
      l_sec = (flow_frequency / 7.5 /4)/60; 
      data.total_volume += l_sec;
      last_result.volume += l_sec;
      
      flow_frequency = 0; // Reset Counter
      //Serial.printf("flow rate = %f L/Sec     |    temp: %f(°C) | hum: %f \n", l_sec, temperature, humidity);

      // fill_solid(leds, NUM_LEDS, getColor());
    }
    else {
      // fill_solid(leds, NUM_LEDS, CRGB::Black);
    }
  }
}

void disableDevice(){
  is_active = false;
  Serial.println("Device disabled.");
  last_result.duration = millis() - last_result.first_pulse_time;
  data.total_duration += last_result.duration;
  Serial.printf("Last result: volume = %f | duration = %ld  || Total: duration = %ld | volume = %f \n", last_result.volume, last_result.duration, data.total_duration, data.total_volume);
  needToNotify = true;                          
}


void loop ()
{
  FastLED.show();
  ws.cleanupClients();
  calcFlowRate();
  
  if (millis() - last_pulse_time > finish_threshold && is_active){
    disableDevice();
  }


  EVERY_MS(300){
    // updateCurrentState();
    // compareStates();
    if (needToNotify){
      if (ws.count() > 0){
        notifyClients();
        needToNotify = false;

        // updatePreviousState();
      }
    }
  }



  EVERY_MSS(25){
    if (is_active){
    fill_solid(leds, NUM_LEDS, getColor());
    }
    else {
      //fill_solid(leds, NUM_LEDS, CRGB::Black);
    if (fade_iterator < 255) {
      fade_iterator++;
    } else {
      fade_iterator = 0;
    }
    for (int i = 0; i < NUM_LEDS; i++) {
      leds[i] = CHSV(i - (fade_iterator * 2), SATURATION, BRIGHTNESS); /* The higher the value 4 the less fade there is and vice versa */ 
      }
    }
    
  }
  int value = analogRead(A0);

  if (value >= medium_value + hysteresis ) {
    if (!rising_flag) {
      rising_flag = true;
      flow_frequency++;
      enableDevice();
    }
  } else{
    if (value <= medium_value - hysteresis) {
      rising_flag = false;
    }
  }



  // if (value > max_value) max_value = value;
  // if (value < min_value) min_value = value;
  // Serial.printf("%d    %d\n", min_value, max_value);
}