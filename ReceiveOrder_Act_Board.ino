#include <Wire.h>
#include <UnoWiFiDevEd.h>
#include <Servo.h>

#define CONNECTOR         "rest"
#define SERVER_ADDR       "158.108.165.223"

#define READ_DOOR         "/data/workshop/5"
#define READ_AIR          "/data/workshop/2"
#define READ_LIGHT        "/data/workshop/1"

#define SERVO_PIN         3
#define LED_AIR_PIN       4
#define LED_FRONT_PIN     5

#define SERVO_DOOR_CLOSE  135
#define SERVO_DOOR_OPEN   45

#define ON                "on"
#define OFF               "off"

#define DELAY_TIME        2000

CiaoData data;
Servo door_servo;

void doorOpen(){
  door_servo.write(SERVO_DOOR_OPEN);
}

void doorClose(){
  door_servo.write(SERVO_DOOR_CLOSE);
}

void airOn(){
  digitalWrite(LED_AIR_PIN, HIGH);
}

void airOff(){
  digitalWrite(LED_AIR_PIN, LOW);
}

void frontLightOn(){
  digitalWrite(LED_FRONT_PIN, HIGH);
}

void frontLightOff(){
  digitalWrite(LED_FRONT_PIN, LOW);
}

void door()
{
  data = Ciao.read(CONNECTOR, SERVER_ADDR, READ_DOOR);
  if(!data.isEmpty()){
    Serial.println(String(data.get(2)));
    if(String(data.get(2)) == ON){
      Serial.println(F("Door Open"));
      doorOpen();
    }
    else{
      Serial.println(F("Door Close"));
      doorClose();
    }
  }
  else{
    Serial.println(F("Door Read Failed"));
  }
}

void air()
{
  data = Ciao.read(CONNECTOR, SERVER_ADDR, READ_AIR);
  if(!data.isEmpty()){
    Serial.println(String(data.get(2)));
    if(String(data.get(2)) == ON){
      Serial.println(F("Air Open"));
      airOn();
    }
    else{
      Serial.println(F("Air Close"));
      airOff();
    }
  }
  else{
    Serial.println(F("Air Read Failed"));
  }
}

void light()
{
  data = Ciao.read(CONNECTOR, SERVER_ADDR, READ_LIGHT);
  if(!data.isEmpty()){
    Serial.println(String(data.get(2)));
    if(String(data.get(2)) == ON){
      Serial.println(F("Light Open"));
      frontLightOn();
    }
    else{
      Serial.println(F("Light Close"));
      frontLightOff();
    }
  }
  else{
    Serial.println(F("Light Read Failed"));
  }
}

void setup() {
  Serial.begin(9600);
  Ciao.begin();
  
  door_servo.attach(SERVO_PIN);
  pinMode(LED_AIR_PIN, OUTPUT);
  pinMode(LED_FRONT_PIN, OUTPUT);
}

void loop() {
  door();
  air();
  light();
  delay(DELAY_TIME);
}
