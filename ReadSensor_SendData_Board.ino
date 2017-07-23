#include <UnoWiFiDevEd.h>
#include <Wire.h>
#include <dht.h>

#define CONNECTOR         "rest" 
#define SERVER_ADDR       "158.108.165.223"

#define ULTRA_1_TRIG_PIN  13
#define ULTRA_1_ECHO_PIN  12
#define ULTRA_2_TRIG_PIN  11
#define ULTRA_2_ECHO_PIN  10
#define DHT11_PIN         2
#define LDR_PIN           A0

#define DELAY_TIME        1000

dht DHT;

long ultra_duration;
long ultra_distance_1;
long ultra_distance_2;
int light;
int temperature;

String sendStr;

String sendLdr = "/data/workshop/6/set/";
String sendTemp = "/data/workshop/4/set/";
String sendUltra = "/data/workshop/10/set/";

CiaoData data;

void taskValue(){
  //Outdoor Ultrasonic
  digitalWrite(ULTRA_1_TRIG_PIN, LOW);
  delay(2);
  digitalWrite(ULTRA_1_TRIG_PIN, HIGH);
  delay(10);
  digitalWrite(ULTRA_1_TRIG_PIN, LOW);
  ultra_duration = pulseIn(ULTRA_1_ECHO_PIN, HIGH);
  ultra_distance_1 = ultra_duration / 58.2;

  //Indoor Ultrasonic
  digitalWrite(ULTRA_2_TRIG_PIN, LOW);
  delay(2);
  digitalWrite(ULTRA_2_TRIG_PIN, HIGH);
  delay(10);
  digitalWrite(ULTRA_2_TRIG_PIN, LOW);
  ultra_duration = pulseIn(ULTRA_2_ECHO_PIN, HIGH);
  ultra_distance_2 = ultra_duration / 58.2;

  //LDR
  light = analogRead(LDR_PIN);

  //DHT
  DHT.read11(DHT11_PIN);
  temperature =(int) DHT.temperature;
}

void taskSendData(){
  sendStr = sendLdr + String(light);
  writeAndCheck();

  sendStr = sendTemp + String(temperature);
  writeAndCheck();

  sendStr = sendUltra + String(ultra_distance_1) + "," + String(ultra_distance_2);
  writeAndCheck();
}

void writeAndCheck()
{
  //Write to server
  data = Ciao.write(CONNECTOR, SERVER_ADDR, sendStr);
  //Check
  Serial.print(F(" >> "));
  Serial.println(sendStr);
  if(!data.isEmpty()) Serial.println(F("Write Success"));
  else Serial.println(F("Write Failed"));
}

void setup() {
  Serial.begin(9600);
  Ciao.begin();

  pinMode(ULTRA_1_TRIG_PIN, OUTPUT);
  pinMode(ULTRA_1_ECHO_PIN, INPUT);
  pinMode(ULTRA_2_TRIG_PIN, OUTPUT);
  pinMode(ULTRA_2_ECHO_PIN, INPUT);
  pinMode(LDR_PIN, INPUT);
}

void loop() {
  taskValue();
  taskSendData();
  delay(DELAY_TIME);
}

