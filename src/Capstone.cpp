/* 
 * Project Tread Lightly
 * Author: Joeseph Arnoux
 * Date: 11/27/24
 * For comprehensive documentation and examples, please visit:
 * https://docs.particle.io/firmware/best-practices/firmware-template/
 */

#include "Particle.h"
#include "IoTClassroom_CNM.h"
#include "Button.h"
#include "colors.h"
#include <math.h>
#include <neopixel.h>
#include <credentials.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT/Adafruit_MQTT_SPARK.h" 
#include "Adafruit_MQTT/Adafruit_MQTT.h"
 
unsigned int last, lastTime;
float buttonOnOff;
float pirsensorValue;
const int PIXELCOUNT = 113;
const int PIR_SENSOR_OUTPUT_PIN = D4;
int some_long_process_within_loop;
const float amplitude = 127.5;
const float offset = 127.5;
float frequency = .2;
float t;
float brightness;

// TCPClient TheClient;
// Adafruit_MQTT_SPARK mqtt(&TheClient,AIO_SERVER,AIO_SERVERPORT,AIO_USERNAME,AIO_KEY);
// Adafruit_MQTT_Subscribe buttonOnOffFeed = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/buttonOnOff");
// Adafruit_MQTT_Publish pirsensorFeed = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/pirsensor"); 

Adafruit_NeoPixel pixel (PIXELCOUNT,SPI1,WS2812B);
void PixelFill(int startPixel, int endPixel, int color);

ApplicationWatchdog *wd;
void watchdogHandler() {
   System.reset(RESET_NO_WAIT);
}

// void MQTT_connect();
// bool MQTT_ping();
// void WebPublish();

SYSTEM_MODE(SEMI_AUTOMATIC);


void setup() {
pinMode (PIXELCOUNT,OUTPUT);
pinMode(PIR_SENSOR_OUTPUT_PIN, INPUT);
Serial.begin(9600);
waitFor(Serial.isConnected,10000);

pixel.begin();
pixel.setBrightness(255);
pixel.show();

// WiFi.on();
// WiFi.clearCredentials();
// WiFi.setCredentials("IoTNetwork");
// WiFi.connect();
// mqtt.subscribe(&buttonOnOffFeed);

wd = new ApplicationWatchdog(60000, watchdogHandler, 1536);

}


void loop() {

int sensor_output;
sensor_output = digitalRead(PIR_SENSOR_OUTPUT_PIN);

// MQTT_connect();
// MQTT_ping();

// Adafruit_MQTT_Subscribe *subscription;
//   while ((subscription = mqtt.readSubscription(100))) {
//     if (subscription == &buttonOnOffFeed) {
//       buttonOnOff = atof((char *)buttonOnOffFeed.lastread);
//     }
//   }

// if((millis()-lastTime > 6000)) {
//     if(mqtt.Update()) {
      
//       pirsensorFeed.publish(pirsensorValue);
//       // Serial.printf("Publishing = %f \n",pirsensorValue);
//       } 
//     lastTime = millis();
//   }

if(sensor_output == HIGH) {
   PixelFill(0,113,red);
   delay(2000);
   Serial.printf("ON %i\n",sensor_output);
      PixelFill(0,113,orange);
      delay(2000);
       PixelFill(0,113,yellow);
       delay(2000);
         PixelFill(0,113,green);
         delay(2000);
          PixelFill(0,113,blue);
          delay(2000);
            PixelFill(0,113,indigo);
            delay(2000);
               PixelFill(0,113,violet);
               delay(2000);

// t = millis()/1000.0;  
// brightness = amplitude*sin(2*M_PI*frequency*t)+offset;
// analogWrite (PIXELCOUNT,brightness);
}
pixel.show();

if(sensor_output == LOW) {
   PixelFill(0,113,black);
      Serial.printf("OFF %i\n",sensor_output);
}
pixel.show();

while (some_long_process_within_loop) {
   ApplicationWatchdog::checkin();
  }

//  WebPublish();

}

//END

void PixelFill(int startPixel, int endPixel, int color) {
    int litPixel;;

   for(litPixel=startPixel;litPixel<=endPixel;litPixel++) {
      pixel.setPixelColor(litPixel,color);
   }
   pixel.show();
   delay(100);

}


// void WebPublish() {
//   static int PIRSensorTimer;
// }

// if((millis()-PIRSensorTimer>5000)) {
//     if (mqtt.Update()) {
//       pirensorFeed.publish(pirsensorValue);
//       }

//   PIRSensorTimer = millis();
//   }


// void MQTT_connect() {
//   int8_t ret;
 
//   if (mqtt.connected()) {
//     return;
//   }
 
//   while ((ret = mqtt.connect()) != 0) { 
//        Serial.printf("Error Code %s\n",mqtt.connectErrorString(ret));
//        Serial.printf("Retrying MQTT connection in 5 seconds...\n");
//        mqtt.disconnect();
//        delay(5000);  // wait 5 seconds and try again
//   }
//   Serial.printf("MQTT Connected!\n");
// }

// bool MQTT_ping() {
//   static unsigned int last;
//   bool pingStatus;

//   if ((millis()-last)>120000) {
//       Serial.printf("Pinging MQTT \n");
//       pingStatus = mqtt.ping();
//       if(!pingStatus) {
//         Serial.printf("Disconnecting \n");
//         mqtt.disconnect();
//       }
//       last = millis();
//   }
//   return pingStatus;
// }

