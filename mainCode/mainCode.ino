// LIBRARIES
#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <ESPmDNS.h>
#include "homepage.h"
#include <Wire.h>
#include "rgb_lcd.h"
#include <DFRobot_DHT11.h>
#include "DFRobot_Heartrate.h"

// PERIPHERAL INITS
rgb_lcd lcd;
DFRobot_DHT11 DHT;
DFRobot_Heartrate heartrate(DIGITAL_MODE);

// PINS
#define HEAT_INPUT 19
#define SOUND_INPUT 34 //SOUND SENSOR NON-FUNCTIONING RN
#define HEART_INPUT 13
#define LIGHT_INPUT 25 //ACTUAL: 14, TEST: 25
#define GLED 27
#define YLED 26
#define RLED 32
//LCD YEL 22, WHITE 21 

// CONSTANTS
const char* ssid = "PaulHotspot";
const char* password = "12345678";
const int B_DELAY = 1000;
const int S_DELAY = 100;


WebServer server(80);

// FUNCTIONS
String getTemp() {
  DHT.read(HEAT_INPUT);
  String tempRead =(String) DHT.temperature;
  tempRead += " C";
  return tempRead;
}

String getLight(){
  String lightRead = (String) analogRead(LIGHT_INPUT);
  return lightRead;
}

String serverHeartbeat(){
  return (String) 60;
}


void handleRoot() {
  String message = homePagePart1 + getTemp() + homePagePart2 + getLight() + homePagePart3 + serverHeartbeat() + homePagePart4;
  server.send(200, "text/html", message);
}

void handleNotFound() {
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++) {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
}

// SETUP CODE
void setup(void) {
  Serial.begin(115200);
  // LEDS
  pinMode(GLED,OUTPUT);
  pinMode(YLED,OUTPUT);
  pinMode(RLED,OUTPUT);
  // LCD
  lcd.begin(16,2);
  lcd.print("Peripherals +");
  lcd.setCursor(0,1);
  lcd.print("WebServer Test");
  Serial.println("LCD SCR: Peripherals +\nWebServer Test");
  delay(B_DELAY);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  if (MDNS.begin("esp32")) {
    Serial.println("MDNS responder started");
  }

  server.on("/", handleRoot);
  server.on("/inline", []() {
    server.send(200, "text/plain", "this works as well");
  });
  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("HTTP server started");
}

void loop(void) {
  // VARIABLES
  int validValue = 60; //NONFUNC
  int t=0; //NONFUNC

  // SERVER
  server.handleClient();
  delay(2);//allow the cpu to switch to other tasks

  // START
  digitalWrite(GLED,HIGH);
  digitalWrite(YLED,HIGH);
  digitalWrite(RLED,HIGH);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Project Demo");
  delay(S_DELAY);
  lcd.setCursor(0,1);
  lcd.print("Sensors/Website");
  delay(B_DELAY);
  delay(B_DELAY);
  
  // HEAT READING
  digitalWrite(GLED,LOW);
  digitalWrite(YLED,LOW);
  digitalWrite(RLED,LOW);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Heat Sensor");
  String heat = getTemp();
  delay(S_DELAY);
  lcd.setCursor(0,1);
  lcd.print(heat);
  delay(B_DELAY);
  
  // LIGHT READING
  digitalWrite(GLED,HIGH);
  digitalWrite(YLED,HIGH);
  digitalWrite(RLED,HIGH);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Light Sensor");
  int light = analogRead(LIGHT_INPUT);
  Serial.println(light);
  delay(S_DELAY);
  lcd.setCursor(0,1);
  lcd.print(light);
  delay(B_DELAY);

  // HEART READING
  digitalWrite(GLED,LOW);
  digitalWrite(YLED,LOW);
  digitalWrite(RLED,LOW);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Heartrate Sensor");
  delay(S_DELAY);
  int rateValue;
  heartrate.getValue(HEART_INPUT);
  rateValue = heartrate.getRate();
  if(rateValue){
    Serial.println(rateValue);
  }
  if (rateValue < 130){
    if (rateValue > 55){
      validValue = rateValue;
      //t = 0;
    }
  }
  lcd.setCursor(0,1);
  lcd.print(validValue);
  delay(B_DELAY);

  /*
  // SOUND READING
  lcd.clear();
  lcd.setCursor(0,1);
  lcd.print("Peripheral testing");
  delay(100);
  lcd.setCursor(0,2);
  lcd.print("With LCD Screen");
  delay(500);
  */
}
