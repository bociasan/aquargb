#include <tinyNeoPixel.h>

#define PIN            7
#define NUMPIXELS      1

tinyNeoPixel pixels = tinyNeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

int delayval = 100; // delay for half a second

const int analogInPin = A2;
int sensorValue = 0;

void setup() {
  // declare pin  to be an output:

   pixels.begin(); // This initializes the NeoPixel library
  Serial.begin(9600);
}

// the loop routine runs over and over again forever:
void loop() {
  sensorValue = analogRead(analogInPin);
  Serial.print("sensor = ");
  Serial.print(sensorValue);
  Serial.print("\n");
  delay(2);
  if((sensorValue>=100)&&(sensorValue<=800)){
   for (int i = 0; i < NUMPIXELS; i++) {

    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    pixels.setPixelColor(i, pixels.Color(0, 150, 0)); // Moderately bright green color.

    pixels.show(); // This sends the updated pixel color to the hardware.

    delay(delayval); // Delay for a period of time (in milliseconds).

  }
    
    }
  
  else{
    pixels.Color(255, 0, 0);
    pixels.show();
    delay(delayval);
    }
}
