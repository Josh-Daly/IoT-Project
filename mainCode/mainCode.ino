// LIBRARIES
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
#define SOUND_INPUT 34
#define HEART_INPUT 13
#define LIGHT_INPUT 14
#define GLED 27
#define YLED 26
#define RLED 32
//LCD YEL 22, WHITE 21 

// FUNCTIONS
String getTemp() {
  DHT.read(HEAT_INPUT);
  String temp =(String) DHT.temperature;
  temp += " C";
  return temp;
}

// SETUP CODE
void setup() {
  // LEDS
  pinMode(GLED,OUTPUT);
  pinMode(YLED,OUTPUT);
  pinMode(RLED,OUTPUT);
  // SERIAL FOR TESTING
  Serial.begin(115200);
  // LCD
  lcd.begin(16,2);
  lcd.print("All Peripherals Test");
  Serial.println("LCD TOP SCR: All Peripherals Test");
  delay(1000);
}

// MAIN CODE
void loop() {
  // VARIABLES
  int validValue = 60;
  int t=0;

  // START
  digitalWrite(GLED,HIGH);
  digitalWrite(YLED,HIGH);
  digitalWrite(RLED,HIGH);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Peripheral testing");
  Serial.println("LCD TOP SCR: Peripheral testing");
  delay(100);
  lcd.setCursor(0,1);
  lcd.print("With LCD Screen");
  Serial.println("LCD BOTTOM SCR: With LCD Screen");
  delay(2000);

  // HEAT READING
  digitalWrite(GLED,LOW);
  digitalWrite(YLED,LOW);
  digitalWrite(RLED,LOW);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Heat Sensor");
  Serial.println("LCD TOP SCR: Heat Sensor");
  String heat = getTemp();
  delay(300);
  lcd.setCursor(0,1);
  lcd.print(heat);
  Serial.println("LCD BOTTOM SCR: " + heat);
  delay(2000);

  
  // LIGHT READING
  digitalWrite(GLED,HIGH);
  digitalWrite(YLED,HIGH);
  digitalWrite(RLED,HIGH);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Light Sensor");
  Serial.println("LCD TOP SCR: Light Sensor");
  int light = analogRead(LIGHT_INPUT);
  delay(300);
  lcd.setCursor(0,1);
  lcd.print(light);
  Serial.println("LCD BOTTOM SCR: " + light);
  delay(2000);

  
  // HEART READING
  digitalWrite(GLED,LOW);
  digitalWrite(YLED,LOW);
  digitalWrite(RLED,LOW);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Heartrate Sensor");
  Serial.println("LCD TOP SCR: Heartrate Sensor");
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
  Serial.println("LCD BOTTOM SCR: " + validValue);
  delay(2000);
  /*
  // SOUND READING (ugh)
  lcd.clear();
  lcd.setCursor(0,1);
  lcd.print("Peripheral testing");
  Serial.println("LCD TOP SCR: Peripheral testing");
  delay(100);
  lcd.setCursor(0,2);
  lcd.print("With LCD Screen");
  Serial.println("LCD BOTTOM SCR: With LCD Screen");
  delay(500);


  */
}