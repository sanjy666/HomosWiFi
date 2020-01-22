/* gpio

*/
BLYNK_CONNECTED()
{
  rtc.begin(); // Synchronize time on connection
  Blynk.syncVirtual(V81, V82, V83, V84, V85, V86, V87, V88, V89, V90);
}

/* BLYNK_WRITE(V80)
{
  pin_write(1, param.asInt());
  terminal.println("wrire i2c 0 chanell");
  terminal.print("read back = ");
  terminal.println(pin_read(1));
  terminal.print("last error = ");
  terminal.println(gpio.lastError());
  terminal.flush();
} */

BLYNK_WRITE(V81)
{
  worker[1].pin = param[0].asInt();
  worker[1].automatic = param[1].asInt();
  worker[1].temperature_sensor_index = param[2].asInt();
  worker[1].low_temp = param[3].asInt();
  worker[1].high_temp = param[4].asInt();
  worker[1].startTime = param[5].asInt();
  worker[1].stopTime = param[6].asInt();
  worker[1].run_time = param[7].asInt();
  worker[1].pause_time = param[8].asInt();
  worker[1].mode = param[9].asInt();
}
BLYNK_WRITE(V82)
{
  worker[2].pin = param[0].asInt();
  worker[2].automatic = param[1].asInt();
  worker[2].temperature_sensor_index = param[2].asInt();
  worker[2].low_temp = param[3].asInt();
  worker[2].high_temp = param[4].asInt();
  worker[2].startTime = param[5].asInt();
  worker[2].stopTime = param[6].asInt();
  worker[2].run_time = param[7].asInt();
  worker[2].pause_time = param[8].asInt();
  worker[2].mode = param[9].asInt();
}
BLYNK_WRITE(V83)
{
  worker[3].pin = param[0].asInt();
  worker[3].automatic = param[1].asInt();
  worker[3].temperature_sensor_index = param[2].asInt();
  worker[3].low_temp = param[3].asInt();
  worker[3].high_temp = param[4].asInt();
  worker[3].startTime = param[5].asInt();
  worker[3].stopTime = param[6].asInt();
  worker[3].run_time = param[7].asInt();
  worker[3].pause_time = param[8].asInt();
  worker[3].mode = param[9].asInt();
}
BLYNK_WRITE(V84)
{
  worker[4].pin = param[0].asInt();
  worker[4].automatic = param[1].asInt();
  worker[4].temperature_sensor_index = param[2].asInt();
  worker[4].low_temp = param[3].asInt();
  worker[4].high_temp = param[4].asInt();
  worker[4].startTime = param[5].asInt();
  worker[4].stopTime = param[6].asInt();
  worker[4].run_time = param[7].asInt();
  worker[4].pause_time = param[8].asInt();
  worker[4].mode = param[9].asInt();
}
BLYNK_WRITE(V85)
{
  worker[5].pin = param[0].asInt();
  worker[5].automatic = param[1].asInt();
  worker[5].temperature_sensor_index = param[2].asInt();
  worker[5].low_temp = param[3].asInt();
  worker[5].high_temp = param[4].asInt();
  worker[5].startTime = param[5].asInt();
  worker[5].stopTime = param[6].asInt();
  worker[5].run_time = param[7].asInt();
  worker[5].pause_time = param[8].asInt();
  worker[5].mode = param[9].asInt();
}
BLYNK_WRITE(V86)
{
  worker[6].pin = param[0].asInt();
  worker[6].automatic = param[1].asInt();
  worker[6].temperature_sensor_index = param[2].asInt();
  worker[6].low_temp = param[3].asInt();
  worker[6].high_temp = param[4].asInt();
  worker[6].startTime = param[5].asInt();
  worker[6].stopTime = param[6].asInt();
  worker[6].run_time = param[7].asInt();
  worker[6].pause_time = param[8].asInt();
  worker[6].mode = param[9].asInt();
}
BLYNK_WRITE(V87)
{
  worker[7].pin = param[0].asInt();
  worker[7].automatic = param[1].asInt();
  worker[7].temperature_sensor_index = param[2].asInt();
  worker[7].low_temp = param[3].asInt();
  worker[7].high_temp = param[4].asInt();
  worker[7].startTime = param[5].asInt();
  worker[7].stopTime = param[6].asInt();
  worker[7].run_time = param[7].asInt();
  worker[7].pause_time = param[8].asInt();
  worker[7].mode = param[9].asInt();
}
BLYNK_WRITE(V88)
{
  worker[8].pin = param[0].asInt();
  worker[8].automatic = param[1].asInt();
  worker[8].temperature_sensor_index = param[2].asInt();
  worker[8].low_temp = param[3].asInt();
  worker[8].high_temp = param[4].asInt();
  worker[8].startTime = param[5].asInt();
  worker[8].stopTime = param[6].asInt();
  worker[8].run_time = param[7].asInt();
  worker[8].pause_time = param[8].asInt();
  worker[8].mode = param[9].asInt();
}
BLYNK_WRITE(V89)
{
  worker[9].pin = param[0].asInt();
  worker[9].automatic = param[1].asInt();
  worker[9].temperature_sensor_index = param[2].asInt();
  worker[9].low_temp = param[3].asInt();
  worker[9].high_temp = param[4].asInt();
  worker[9].startTime = param[5].asInt();
  worker[9].stopTime = param[6].asInt();
  worker[9].run_time = param[7].asInt();
  worker[9].pause_time = param[8].asInt();
  worker[9].mode = param[9].asInt();
}
BLYNK_WRITE(V90)
{
  worker[10].pin = param[0].asInt();
  worker[10].automatic = param[1].asInt();
  worker[10].temperature_sensor_index = param[2].asInt();
  worker[10].low_temp = param[3].asInt();
  worker[10].high_temp = param[4].asInt();
  worker[10].startTime = param[5].asInt();
  worker[10].stopTime = param[6].asInt();
  worker[10].run_time = param[7].asInt();
  worker[10].pause_time = param[8].asInt();
  worker[10].mode = param[9].asInt();
}
//auto update
BLYNK_WRITE(V127)
{
  if (param.asInt() == 0) return;
  Blynk.virtualWrite(V127, 0);
  WiFiClient client;
  ESPhttpUpdate.setLedPin(2, LOW);
  Blynk.disconnect();
  delay(500);
  Serial.println("Update started");
  ESPhttpUpdate.update(client, String("http://192.168.1.200:8888/firmware.bin"));
}

//menu
int select = 0;

BLYNK_WRITE(V110)//menu selector
{
  select = param.asInt();
  Blynk.virtualWrite(V111, worker[select].pin);
  Blynk.virtualWrite(V112, pin_read(worker[select].pin));
  Blynk.virtualWrite(V113, worker[select].automatic);
  Blynk.virtualWrite(V114, worker[select].temperature_sensor_index);
  //Blynk.virtualWrite(V115,temperatures[worker[select].temperature_sensor_index]);
  Blynk.virtualWrite(V116, worker[select].low_temp);
  Blynk.virtualWrite(V117, worker[select].high_temp);
  Blynk.virtualWrite(V118, worker[select].startTime, worker[select].stopTime);
  Blynk.virtualWrite(V119, worker[select].run_time, worker[select].pause_time);
  Blynk.virtualWrite(V120, worker[select].mode);
  Blynk.virtualWrite(
      (V80 + select),
      worker[select].pin,
      worker[select].automatic,
      worker[select].temperature_sensor_index,
      worker[select].low_temp,
      worker[select].high_temp,
      worker[select].startTime,
      worker[select].stopTime,
      worker[select].run_time,
      worker[select].pause_time,
      worker[select].mode);
}
//change setting
BLYNK_WRITE(V111)
{
  worker[select].pin = param.asInt();
}
BLYNK_WRITE(V112)
{
  pin_write(worker[select].pin, param.asInt());
}
BLYNK_WRITE(V113)
{
  worker[select].automatic = param.asInt();
}
BLYNK_WRITE(V114)
{
  worker[select].temperature_sensor_index = param.asInt();
}
BLYNK_WRITE(V116)
{
  worker[select].low_temp = param.asInt();
}
BLYNK_WRITE(V117)
{
  worker[select].high_temp = param.asInt();
}
BLYNK_WRITE(V118)
{
  TimeInputParam t(param);
  if (t.hasStartTime())
  {
    worker[select].startTime = (t.getStartHour() * 60 * 60) + (t.getStartMinute() * 60) + t.getStartSecond();
  }
  if (t.hasStopTime())
  {
    worker[select].stopTime = (t.getStopHour() * 60 * 60) + (t.getStopMinute() * 60) + t.getStopSecond();
  }
}
BLYNK_WRITE(V119)
{
  TimeInputParam t(param);
  if (t.hasStartTime())
  {
    worker[select].run_time = (t.getStartHour() * 60 * 60) + (t.getStartMinute() * 60) + t.getStartSecond();
  }
  if (t.hasStopTime())
  {
    worker[select].pause_time = (t.getStopHour() * 60 * 60) + (t.getStopMinute() * 60) + t.getStopSecond();
  }
}
BLYNK_WRITE(V120)
{
  worker[select].mode = param.asInt();
}
