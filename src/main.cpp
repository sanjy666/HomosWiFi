#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <BlynkSimpleEsp8266.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266httpUpdate.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <Wire.h>
#include <PCF8574.h>
#include <TimeLib.h>
#include <WidgetRTC.h>
#include <WidgetTerminal.h>
#include <ArduinoOTA.h>
#include <MQTTClient.h>

//#include <ArduinoJson.h>

// Blynk
#define BLYNK_DEBUG
#define BLYNK_PRINT Serial
//#define BLYNK_PRINT terminal

#define ONEWIRE_BUS 12
#define TEMPERATURE_PRECISION 12 // 12 9 or other ds18b20 resolution
#define TEMPERATURE_START_PIN V100
#define SDA_PIN 4
#define SCL_PIN 5
#define EXPANDER_ADR 0x3c
#define SRELAY_PIN 16
#define SRELAY_SAVER_TIMER 1000
#define CASE_FAN_PIN 13
#define HEATER_FAN_PIN 14

//var
#include "setting.h"
//led
int brightness = 1023;
int fadeAmount = 5;
unsigned long previousMillis = 0;
unsigned long interval = 10;

float temperatures[11];
String otaURL;

u_long mqttlastMillis = 0;
struct
{
  int pin = 0;
  int mode = 0; // 1 time range; 2 heater; 3 cooler; 4 periodic;
  int automatic = 0;
  float low_temp = 0, high_temp = 0;
  int temperature_sensor_index = -1;
  long int startTime = 0, stopTime = 0;
  long int run_time = 0, pause_time = 0;
} worker[11];

//class
MQTTClient mqttClient;
WiFiClient WiFiclient;
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
void mqttSend();
void mqttConnect(void);

//void i2c_scaner(void);

void setup()
{
  Serial.begin(115200);
  Serial.println("start");
  Blynk.begin(auth, ssid, pass, address, port);
  sensorsInit();
  Wire.begin(SDA_PIN, SCL_PIN);
  setSyncInterval(10 * 60); //10 minute period RTC sync
  timer.setInterval(200, worker_run);
  timer.setInterval(10, led_run);
  timer.setInterval(1000, mqttSend);
  // timer.setInterval(5000,i2c_scaner);
  Serial.println("started");
  pinMode(SRELAY_PIN, OUTPUT);
  pinMode(CASE_FAN_PIN, OUTPUT);
  pinMode(HEATER_FAN_PIN, OUTPUT);
  digitalWrite(CASE_FAN_PIN, LOW);
  digitalWrite(HEATER_FAN_PIN, LOW);
#include "ota.h"
  ArduinoOTA.begin();
  mqttClient.begin(mqserver, mqport, WiFiclient);
  //mqttClient.connect("nodemcu", "testusername", "testpass");
}
void loop()
{
  ArduinoOTA.handle();
  Blynk.run();
  timer.run();
  mqttClient.loop();
}

void sensorsRun(void)
{
  float temperature = 0.0;
  int sensorsNum = sensors.getDeviceCount();
  for (int i = 0; i < sensorsNum; i++)
  {
    temperature = sensors.getTempCByIndex(i);
    if (temperature != 0.0) // && temperature != -127)
    {
      temperatures[i + 1] = temperature;
      if (temperature != -127)
      {
        Blynk.virtualWrite((TEMPERATURE_START_PIN + i), temperature);
        mqttClient.publish("nodemcu/temp", (String)temperature);
        //terminal.print(temperature);
      }
    }
  }
  terminal.println();
  sensors.requestTemperatures();
}

void sensorsSetResolution(void)
{
  DeviceAddress tempDeviceAddress;
  int sensorsNum = sensors.getDeviceCount();
  for (int i = 0; i < sensorsNum; i++)
  {
    sensors.getAddress(tempDeviceAddress, i);
    sensors.setResolution(tempDeviceAddress, TEMPERATURE_PRECISION);
  }
}

void sensorsInit(void)
{
  sensors.begin();
  sensors.setWaitForConversion(false);
  sensorsSetResolution();
  sensors.requestTemperatures();
  timer.setInterval(1000 / (1 << (12 - TEMPERATURE_PRECISION)), sensorsRun);
}

int time_check(long int start, long int stop)
{
  int nowtime = hour() * 60 * 60 + minute() * 60 + second();
  if (start < stop)
  {
    if (start < nowtime && nowtime < stop)
    {
      return 1;
    }
    else
    {
      return 0;
    }
  }
  if (start > stop)
  {
    if (stop < nowtime && nowtime < start)
    {
      return 0;
    }
    else
    {
      return 1;
    }
  }
  return 0;
}

void worker_run(void)
{
  for (int i = 0; i < 10; i++)
  {
    if (worker[i].automatic != 0 && worker[i].pin != 0)
    {
      switch (worker[i].mode) // 1 time range; 2 heater; 3 cooler; 4 periodic;
      {
      case 1: //time range
        if (worker[i].startTime > 0 && worker[i].stopTime > 0)
        {
          pin_write(worker[i].pin, time_check(worker[i].startTime, worker[i].stopTime));
        }
        break;
      case 2: // heater
        if (worker[i].temperature_sensor_index < 0)
          break;
        //if (worker[i].low_temp == 0) break;
        //if (worker[i].high_temp == 0) break;

        if (temperatures[i] == -127)
        {
          pin_write(worker[i].pin, 0);
          break;
        }

        if (temperatures[worker[i].temperature_sensor_index] < worker[i].low_temp)
        {
          pin_write(worker[i].pin, 1);
          break;
        }
        else if (temperatures[worker[i].temperature_sensor_index] > worker[i].high_temp)
        {
          pin_write(worker[i].pin, 0);
          break;
        }
        break;
      case 3: //cooler
        if (worker[i].temperature_sensor_index < 0)
          break;
        //if (worker[i].low_temp != 0) break;
        //if (worker[i].high_temp != 0 ) break;
        if (temperatures[i] == -127)
        {
          pin_write(worker[i].pin, 0);
          break;
        }
        if (temperatures[worker[i].temperature_sensor_index] < worker[i].low_temp)
        {
          pin_write(worker[i].pin, 0);
          break;
        }
        else if (temperatures[worker[i].temperature_sensor_index] > worker[i].high_temp)
        {
          pin_write(worker[i].pin, 1);
        }
        break;
      case 4: //period time
      {
        if (worker[i].run_time == 0)
          break;
        if (worker[i].pause_time == 0)
          break;
        long int all_times = worker[i].run_time + worker[i].pause_time;
        int nowtimes = hour() * 60 * 60 + minute() * 60 + second();
        if ((nowtimes % all_times) > worker[i].run_time)
        {
          pin_write(worker[i].pin, 0);
        }
        else
        {
          pin_write(worker[i].pin, 1);
        }
        break;
      }
      default:
        break;
      }
    }
  }
}
void pin_write(int pin, int value)
{
  switch (pin)
  {
  case 9:
    if (millis() < SRELAY_SAVER_TIMER)
    {
      break;
    }
    digitalWrite(SRELAY_PIN, value);
    break;
  case 10:
    digitalWrite(HEATER_FAN_PIN, value);
    break;
  case 11:
    digitalWrite(CASE_FAN_PIN, value);
    break;
  case 1:
    if (value)
    {
      gpio.write(pin - 1, 0);
    }
    else
    {
      gpio.write(pin - 1, 1);
    }
  case 2:
    if (value)
    {
      gpio.write(pin - 1, 0);
    }
    else
    {
      gpio.write(pin - 1, 1);
    }
  case 3:
    if (value)
    {
      gpio.write(pin - 1, 0);
    }
    else
    {
      gpio.write(pin - 1, 1);
    }
  case 4:
    if (value)
    {
      gpio.write(pin - 1, 0);
    }
    else
    {
      gpio.write(pin - 1, 1);
    }
  case 5:
    if (value)
    {
      gpio.write(pin - 1, 0);
    }
    else
    {
      gpio.write(pin - 1, 1);
    }
  case 6:
    if (value)
    {
      gpio.write(pin - 1, 0);
    }
    else
    {
      gpio.write(pin - 1, 1);
    }
  case 7:
    if (value)
    {
      gpio.write(pin - 1, 0);
    }
    else
    {
      gpio.write(pin - 1, 1);
    }
  case 8:
    if (value)
    {
      gpio.write(pin - 1, 0);
    }
    else
    {
      gpio.write(pin - 1, 1);
    }
  default:
    break;
  }
}
int pin_read(int pin)
{
  switch (pin)
  {
  case 9:
    return digitalRead(SRELAY_PIN);
  case 10:
    return digitalRead(HEATER_FAN_PIN);
  case 11:
    return digitalRead(CASE_FAN_PIN);
  case 1:
    if (gpio.read(pin - 1))
    {
      return 0;
    }
    else
    {
      return 1;
    }
  case 2:
    if (gpio.read(pin - 1))
    {
      return 0;
    }
    else
    {
      return 1;
    }
  case 3:
    if (gpio.read(pin - 1))
    {
      return 0;
    }
    else
    {
      return 1;
    }
  case 4:
    if (gpio.read(pin - 1))
    {
      return 0;
    }
    else
    {
      return 1;
    }
  case 5:
    if (gpio.read(pin - 1))
    {
      return 0;
    }
    else
    {
      return 1;
    }
  case 6:
    if (gpio.read(pin - 1))
    {
      return 0;
    }
    else
    {
      return 1;
    }
  case 7:
    if (gpio.read(pin - 1))
    {
      return 0;
    }
    else
    {
      return 1;
    }
  case 8:
    if (gpio.read(pin - 1))
    {
      return 0;
    }
    else
    {
      return 1;
    }
  default:
    return 0;
  }
}
void led_run(void)
{
  if (millis() - previousMillis >= interval)
  {
    if (brightness <= 0)
    { // reverse the direction of the fading at the ends of the fade:
      brightness = 0;
      fadeAmount = -fadeAmount;
    }
    if (brightness >= 1024)
    { // reverse the direction of the fading at the ends of the fade:
      brightness = 1024;
      fadeAmount = -fadeAmount;
    }
    brightness = brightness + fadeAmount;
    analogWrite(2, brightness);
    previousMillis = millis();
  }
}
void mqttConnect(void)
{
  if (!mqttClient.connected())
  {
    mqttClient.connect("nodemcu");
    Serial.println("\nmqtt connected!");
    mqttClient.subscribe("nodemcu");
  }
}
void mqttSend()
{
  int val = analogRead(A0);
  if (!mqttClient.connected())
  {
    mqttConnect();
  }
  mqttClient.publish("nodemcu/photocell", (String)val);
}
#include "blynk_pin.h"