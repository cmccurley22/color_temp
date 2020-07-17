#include <Adafruit_NeoPixel.h>
#include "DHT.h"

#define LED_COUNT 10
#define LED_PIN 6
#define DHT_PIN 2

//#define temp 68

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);
DHT dht(DHT_PIN, DHT11);


int red;
int green;
int blue;

void setup()
{
  Serial.begin(9600);
  Serial.println("lET's GO!");

  strip.begin();
  strip.show();
  strip.setBrightness(5);
  dht.begin();
}

void loop()
{
  delay(2000);

  float temp = dht.readTemperature(true);

  //check if we failed because that would be sad
  if (isnan(temp)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  //DEFAULT - COLD
  red = 0;
  green = 0;
  blue = 255;
  
  if (temp > 85) //HOT
  {
    red = 255;
    blue = 0;
  }

  else if (temp > 65) //COMFY HOT
  {
    red = map(temp, 45, 85, 0, 255);
    green = map(temp, 45, 85, 255, 0);
    blue = 0;
  }
  
  else if (temp > 45) //COMFY COLD
  {
    blue = map(temp, 45, 65, 255, 0);
    green = map(temp, 45, 65, 0, 255);
  }

  for (int i = 0; i < LED_COUNT; i++)
  {
    strip.setPixelColor(i, strip.Color(red, green, blue));
  }

  Serial.print("Temp: ");
  Serial.println(temp);

  strip.show();
}
