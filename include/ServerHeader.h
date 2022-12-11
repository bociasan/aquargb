#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <SiteHeader.h>

// const char* ssid = "Anonymus";
// const char* password = "camera18";
const char* ssid = "NES Team";
const char* password = "qwerty123";

// const char* ssid = "Alexandru's Galaxy S21+ 5G";
// const char* password = "btyo7331";

String newHostname = "AquaRGB";
AsyncWebServer server(80);
AsyncWebSocket ws("/ws");