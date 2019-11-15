/* gpio

*/
BLYNK_CONNECTED() {
  rtc.begin();// Synchronize time on connection
  Blynk.syncAll();
}

BLYNK_WRITE(V127) {
  if (param.asInt() == 0) return;
  Blynk.virtualWrite(V127,0);
  WiFiClient client;
  ESPhttpUpdate.setLedPin(2, LOW);
	Blynk.disconnect();
	delay(500);
  Serial.println("Update started");
	ESPhttpUpdate.update(client,String("http://192.168.1.200:8888/firmware.bin"));
}
int select = 0;
BLYNK_WRITE(V110){
    select = param.asInt();
    Blynk.virtualWrite(V111,worker[select].pin);
    Blynk.virtualWrite(V112,pin_read(worker[select].pin));
    Blynk.virtualWrite(V113,worker[select].automatic);
    Blynk.virtualWrite(V114,worker[select].temperature_sensor_index);
    Blynk.virtualWrite(V115,temperatures[worker[select].temperature_sensor_index]);
    Blynk.virtualWrite(V116,worker[select].low_temp);
    Blynk.virtualWrite(V117,worker[select].high_temp);
    Blynk.virtualWrite(V118,worker[select].startTime,worker[select].stopTime);
    Blynk.virtualWrite(V119,worker[select].run_time,worker[select].pause_time);
    Blynk.virtualWrite(V120,worker[select].mode);
}
BLYNK_WRITE(V111){
    worker[select].pin = param.asInt();
}
BLYNK_WRITE(V112){
    pin_write(worker[select].pin,param.asInt());
}
BLYNK_WRITE(V113){
    worker[select].automatic = param.asInt();
}
BLYNK_WRITE(V114){
    worker[select].temperature_sensor_index = param.asInt();
}
BLYNK_WRITE(V116){
    worker[select].low_temp = param.asInt();
}
BLYNK_WRITE(V117){
    worker[select].high_temp = param.asInt();
}
BLYNK_WRITE(V118){
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
BLYNK_WRITE(V119){
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
BLYNK_WRITE(V120){
    worker[select].mode = param.asInt();
}

