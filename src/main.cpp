#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266httpUpdate.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <Wire.h>
#include <PCF8574.h>
#include <TimeLib.h>
#include <WidgetRTC.h>


//defines
#define BLYNK_PRINT terminal
//#define BLYNK_DEBUG
#define ONEWIRE_BUS 12
#define TEMPERATURE_PRECISION 10 // 12 9 or other ds18b20 resolution
#define TEMPERATURE_START_PIN V100
#define SDA_PIN 4
#define SCL_PIN 5
#define EXPANDER_ADR 0x3c
#define LAMP_PIN 16
#define LAMP_SAVER_TIMER 1000*60*5
#define CASE_FAN_PIN 13
#define HEATER_FAN_PIN 14
#define DEBUG terminal.println

//var
#include "setting.h"
//led
int brightness = 1023;
int fadeAmount = 5;
unsigned long previousMillis = 0;
unsigned long interval = 10;

float temperatures[11];
String otaURL;

struct{
  int pin = 0; // 1 lamp; 2 heat relay; 3-10 gpio expander relay
  int mode = 0; // 1 time range; 2 heater; 3 cooler; 4 periodic;
  int automatic = 0;
  float low_temp = 0,high_temp = 0;
  int temperature_sensor_index = -1;
  long int startTime = 0,stopTime = 0;
  long int run_time = 0,pause_time = 0;
}worker[11];

//class
OneWire oneWire(ONEWIRE_BUS);
DallasTemperature sensors(&oneWire);
DeviceAddress tempDeviceAddress;
BlynkTimer timer;
PCF8574 gpio(EXPANDER_ADR);
WidgetRTC rtc;
WidgetTerminal terminal(V0);

//func proto
void sensorsInit(void);
int time_check(long int start, long int stop);
void worker_run(void);
void pin_write(int pin, int value);
void led_run(void);

void setup()
{
  Serial.begin(115200);
  Serial.println("start");
  Blynk.begin(auth, ssid, pass, address, port);
  sensorsInit();
  Wire.begin(SDA_PIN, SCL_PIN);
  setSyncInterval(10 * 60); //10 minute period RTC sync
  timer.setInterval(500,worker_run);
  timer.setInterval(10,led_run);
  Serial.println("started");
  pinMode(LAMP_PIN,OUTPUT);
  pinMode(CASE_FAN_PIN,OUTPUT);
  pinMode(HEATER_FAN_PIN,OUTPUT);
  digitalWrite(CASE_FAN_PIN,LOW);
  digitalWrite(HEATER_FAN_PIN,LOW);
}
void loop()
{
  Blynk.run();
  timer.run();
}

void sensorsRun(void){
  float temperature = 0.0;
  int sensorsNum = sensors.getDeviceCount();
  for (int i = 0; i < sensorsNum; i++){
    temperature = sensors.getTempCByIndex(i);
    if (temperature != 0.0 && temperature != -127){
      temperatures[i+1] = temperature;
      Blynk.virtualWrite( (TEMPERATURE_START_PIN + i) ,temperature);
    }
  }
  sensors.requestTemperatures();
}
void sensorsSetResolution(void){
  DeviceAddress tempDeviceAddress;
  int sensorsNum = sensors.getDeviceCount();
  for (int i = 0; i < sensorsNum; i++)
  {
    sensors.getAddress(tempDeviceAddress, i);
    sensors.setResolution(tempDeviceAddress, TEMPERATURE_PRECISION);
  }
}
void sensorsInit(void){
  sensors.begin();
  sensors.setWaitForConversion(false);
  sensorsSetResolution();
  sensors.requestTemperatures();
  timer.setInterval(750 / (1 << (12 - TEMPERATURE_PRECISION)), sensorsRun);
}
int time_check(long int start, long int stop){
  int nowtime = hour()*60*60 + minute()*60 + second();
  if (start < stop){
    if (start < nowtime && nowtime < stop){
      return 1;
    }else{
      return 0;
    }
  }
  if (start > stop){
    if (stop < nowtime && nowtime < start){
      return 0;
    }else{
      return 1;
    }
  }
  return 0;
}
void worker_run(void){
  for (int i = 0; i < 10; i++){
    if (worker[i].automatic != 0 && worker[i].pin != 0){
      switch (worker[i].mode) // 1 time range; 2 heater; 3 cooler; 4 periodic;
      {
        case 1: //time range
          if (worker[i].startTime > 0 && worker[i].stopTime > 0 ){
            pin_write(worker[i].pin, time_check(worker[i].startTime, worker[i].stopTime));
          }
          break;
        case 2: // heater
          if (worker[i].temperature_sensor_index < 0) break;
          //if (worker[i].low_temp == 0) break;
          //if (worker[i].high_temp == 0) break;
          //if (temperatures[i] == 0.0) break;
          if (temperatures[worker[i].temperature_sensor_index] < worker[i].low_temp ){
            pin_write(worker[i].pin, 1);
          }else if (temperatures[worker[i].temperature_sensor_index] > worker[i].high_temp){
            pin_write(worker[i].pin, 0);
          }else{
            pin_write(worker[i].pin, 0);
          }
          break;
        case 3: //cooler
          if (worker[i].temperature_sensor_index < 0) break;
          //if (worker[i].low_temp != 0) break;
          //if (worker[i].high_temp != 0 ) break;
          if (temperatures[worker[i].temperature_sensor_index] < worker[i].low_temp ){
            pin_write(worker[i].pin, 0);
          }else if (temperatures[worker[i].temperature_sensor_index] > worker[i].high_temp){
            pin_write(worker[i].pin, 1);
          }else{
            pin_write(worker[i].pin, 0);
          }
          break;
        case 4:{ //periodic
          if (worker[i].run_time == 0) break;
          if (worker[i].pause_time == 0) break;
          long int all_times = worker[i].run_time + worker[i].pause_time;
          int nowtimes = hour()*60*60 + minute()*60 + second();
          if ((nowtimes % all_times) > worker[i].run_time){
            pin_write(worker[i].pin, 0);
          }else{
            pin_write(worker[i].pin, 1);
          }
          break;
          }
        default :
          break;
      }
    }
  }
}
void pin_write(int pin, int value){
  switch (pin){
  case 9:
    if (millis() < LAMP_SAVER_TIMER){
      break;
    }
    digitalWrite(LAMP_PIN, value);
    Blynk.virtualWrite(V9,value);
    break;
  case 10:
    digitalWrite(HEATER_FAN_PIN, value);
    Blynk.virtualWrite(V10,value);
    break;
  case 11:
    digitalWrite(CASE_FAN_PIN, value);
    Blynk.virtualWrite(V11,value);
    break;
  case 1:
    gpio.write(0, ~value);
    Blynk.virtualWrite(V1,value);
    break;
  case 2:
    gpio.write(1, ~value);
    Blynk.virtualWrite(V2,value);
    break;
  case 3:
    gpio.write(2, ~value);
    Blynk.virtualWrite(V3,value);
    break;
  case 4:
    gpio.write(3, ~value);
    Blynk.virtualWrite(V4,value);
    break;
  case 5:
    gpio.write(4, ~value);
    Blynk.virtualWrite(V5,value);
    break;
  case 6:
    gpio.write(5, ~value);
    Blynk.virtualWrite(V6,value);
    break;
  case 7:
    gpio.write(6, ~value);
    Blynk.virtualWrite(V7,value);
    break;
  case 8:
    gpio.write(7, ~value);
    Blynk.virtualWrite(V8,value);
    break;
  default:
    break;
  }
}
int pin_read(int pin){
  switch (pin){
  case 9:
    return digitalRead(LAMP_PIN);
  case 10:
    return digitalRead(HEATER_FAN_PIN);
  case 11:
    return digitalRead(CASE_FAN_PIN);
  case 1:
    return ~gpio.read(0);
  case 2:
    return ~gpio.read(1);
  case 3:
    return ~gpio.read(2);
  case 4:
    return ~gpio.read(3);
  case 5:
    return ~gpio.read(4);
  case 6:
    return ~gpio.read(5);
  case 7:
    return ~gpio.read(6);
  case 8:
    return ~gpio.read(7);
  default:
    break;
  }
}
void led_run(void){
  if (millis() - previousMillis >= interval){
    if (brightness <= 0 ){ // reverse the direction of the fading at the ends of the fade:
      brightness = 0;
      fadeAmount = -fadeAmount;
    }
    if (brightness >=1024 ){ // reverse the direction of the fading at the ends of the fade:
      brightness = 1024;
      fadeAmount = -fadeAmount;
    }
    brightness = brightness + fadeAmount;
    analogWrite(2, brightness);
    previousMillis = millis();
  }
}
#include "blynk_pin.h"
