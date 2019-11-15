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

BLYNK_WRITE(V1){
	pin_write(1,param.asInt());
}
BLYNK_WRITE(V2){
	pin_write(2,param.asInt());
}
BLYNK_WRITE(V3){
  pin_write(3,param.asInt());
}
BLYNK_WRITE(V4){
  pin_write(4,param.asInt());
}
BLYNK_WRITE(V5){
  pin_write(5,param.asInt());
}
BLYNK_WRITE(V6){
  pin_write(6,param.asInt());
}
BLYNK_WRITE(V7){
  pin_write(7,param.asInt());
}
BLYNK_WRITE(V8){
  pin_write(8,param.asInt());
}
BLYNK_WRITE(V9){
  pin_write(9,param.asInt());
}
BLYNK_WRITE(V10){
  pin_write(10,param.asInt());
}
BLYNK_WRITE(V11){
  pin_write(11,param.asInt());
}
// 100+ termo
//pin set
BLYNK_WRITE(V21){
  worker[0].pin = param.asInt();
}
BLYNK_WRITE(V22){
  worker[1].pin = param.asInt();
}
BLYNK_WRITE(V23){
  worker[2].pin = param.asInt();
}
BLYNK_WRITE(V24){
  worker[3].pin = param.asInt();
}
BLYNK_WRITE(V25){
  worker[4].pin = param.asInt();
}
BLYNK_WRITE(V26){
  worker[5].pin = param.asInt();
}
BLYNK_WRITE(V27){
  worker[6].pin = param.asInt();
}
BLYNK_WRITE(V28){
  worker[7].pin = param.asInt();
}
BLYNK_WRITE(V29){
  worker[8].pin = param.asInt();
}
BLYNK_WRITE(V30){
  worker[9].pin = param.asInt();
}
//mode
BLYNK_WRITE(V31){
  worker[0].mode = param.asInt();
}
BLYNK_WRITE(V32){
  worker[1].mode = param.asInt();
}
BLYNK_WRITE(V33){
  worker[2].mode = param.asInt();
}
BLYNK_WRITE(V34){
  worker[3].mode = param.asInt();
}
BLYNK_WRITE(V35){
  worker[4].mode = param.asInt();
}
BLYNK_WRITE(V36){
  worker[5].mode = param.asInt();
}
BLYNK_WRITE(V37){
  worker[6].mode = param.asInt();
}
BLYNK_WRITE(V38){
  worker[7].mode = param.asInt();
}
BLYNK_WRITE(V39){
  worker[8].mode = param.asInt();
}
BLYNK_WRITE(V40){
  worker[9].mode = param.asInt();
}

//automatic
BLYNK_WRITE(V41){
  worker[0].automatic = param.asInt();
}
BLYNK_WRITE(V42){
  worker[1].automatic = param.asInt();
}
BLYNK_WRITE(V43){
  worker[2].automatic = param.asInt();
}
BLYNK_WRITE(V44){
  worker[3].automatic = param.asInt();
}
BLYNK_WRITE(V45){
  worker[4].automatic = param.asInt();
}
BLYNK_WRITE(V46){
  worker[5].automatic = param.asInt();
}
BLYNK_WRITE(V47){
  worker[6].automatic = param.asInt();
}
BLYNK_WRITE(V48){
  worker[7].automatic = param.asInt();
}
BLYNK_WRITE(V49){
  worker[8].automatic = param.asInt();
}
BLYNK_WRITE(V50){
  worker[9].automatic = param.asInt();
}
//low term
BLYNK_WRITE(V51){
  worker[0].low_temp = param.asDouble();
}
BLYNK_WRITE(V52){
  worker[1].low_temp = param.asDouble();
}
BLYNK_WRITE(V53){
  worker[2].low_temp = param.asDouble();
}
BLYNK_WRITE(V54){
  worker[3].low_temp = param.asDouble();
}
BLYNK_WRITE(V55){
  worker[4].low_temp = param.asDouble();
}
BLYNK_WRITE(V56){
  worker[5].low_temp = param.asDouble();
}
BLYNK_WRITE(V57){
  worker[6].low_temp = param.asDouble();
}
BLYNK_WRITE(V58){
  worker[7].low_temp = param.asDouble();
}
BLYNK_WRITE(V59){
  worker[8].low_temp = param.asDouble();
}
BLYNK_WRITE(V60){
  worker[9].low_temp = param.asDouble();
}

//high term
BLYNK_WRITE(V61){
  worker[0].high_temp = param.asDouble();
}
BLYNK_WRITE(V62){
  worker[1].high_temp = param.asDouble();
}
BLYNK_WRITE(V63){
  worker[2].high_temp = param.asDouble();
}
BLYNK_WRITE(V64){
  worker[3].high_temp = param.asDouble();
}
BLYNK_WRITE(V65){
  worker[4].high_temp = param.asDouble();
}
BLYNK_WRITE(V66){
  worker[5].high_temp = param.asDouble();
}
BLYNK_WRITE(V67){
  worker[6].high_temp = param.asDouble();
}
BLYNK_WRITE(V68){
  worker[7].high_temp = param.asDouble();
}
BLYNK_WRITE(V69){
  worker[8].high_temp = param.asDouble();
}
BLYNK_WRITE(V70){
  worker[9].high_temp = param.asDouble();
}

//term sensor index
BLYNK_WRITE(V71){
  worker[0].temperature_sensor_index = param.asInt();
}
BLYNK_WRITE(V72){
  worker[1].temperature_sensor_index = param.asInt();
}
BLYNK_WRITE(V73){
  worker[2].temperature_sensor_index = param.asInt();
}
BLYNK_WRITE(V74){
  worker[3].temperature_sensor_index = param.asInt();
}
BLYNK_WRITE(V75){
  worker[4].temperature_sensor_index = param.asInt();
}
BLYNK_WRITE(V76){
  worker[5].temperature_sensor_index = param.asInt();
}
BLYNK_WRITE(V77){
  worker[6].temperature_sensor_index = param.asInt();
}
BLYNK_WRITE(V78){
  worker[7].temperature_sensor_index = param.asInt();
}
BLYNK_WRITE(V79){
  worker[8].temperature_sensor_index = param.asInt();
}
BLYNK_WRITE(V80){
  worker[9].temperature_sensor_index = param.asInt();
}
//time range set
BLYNK_WRITE(V81) {
  TimeInputParam t(param);
  if (t.hasStartTime())
  {
    worker[0].startTime = (t.getStartHour() * 60 * 60) + (t.getStartMinute() * 60) + t.getStartSecond();
  }
  if (t.hasStopTime())
  {
    worker[0].stopTime = (t.getStopHour() * 60 * 60) + (t.getStopMinute() * 60) + t.getStopSecond();
  }
}
BLYNK_WRITE(V82) {
  TimeInputParam t(param);
  if (t.hasStartTime())
  {
    worker[1].startTime = (t.getStartHour() * 60 * 60) + (t.getStartMinute() * 60) + t.getStartSecond();
  }
  if (t.hasStopTime())
  {
    worker[1].stopTime = (t.getStopHour() * 60 * 60) + (t.getStopMinute() * 60) + t.getStopSecond();
  }
}
BLYNK_WRITE(V83) {
  TimeInputParam t(param);
  if (t.hasStartTime())
  {
    worker[2].startTime = (t.getStartHour() * 60 * 60) + (t.getStartMinute() * 60) + t.getStartSecond();
  }
  if (t.hasStopTime())
  {
    worker[2].stopTime = (t.getStopHour() * 60 * 60) + (t.getStopMinute() * 60) + t.getStopSecond();
  }
}
BLYNK_WRITE(V84) {
  TimeInputParam t(param);
  if (t.hasStartTime())
  {
    worker[3].startTime = (t.getStartHour() * 60 * 60) + (t.getStartMinute() * 60) + t.getStartSecond();
  }
  if (t.hasStopTime())
  {
    worker[3].stopTime = (t.getStopHour() * 60 * 60) + (t.getStopMinute() * 60) + t.getStopSecond();
  }
}
BLYNK_WRITE(V85) {
  TimeInputParam t(param);
  if (t.hasStartTime())
  {
    worker[4].startTime = (t.getStartHour() * 60 * 60) + (t.getStartMinute() * 60) + t.getStartSecond();
  }
  if (t.hasStopTime())
  {
    worker[4].stopTime = (t.getStopHour() * 60 * 60) + (t.getStopMinute() * 60) + t.getStopSecond();
  }
}
BLYNK_WRITE(V86) {
  TimeInputParam t(param);
  if (t.hasStartTime())
  {
    worker[5].startTime = (t.getStartHour() * 60 * 60) + (t.getStartMinute() * 60) + t.getStartSecond();
  }
  if (t.hasStopTime())
  {
    worker[5].stopTime = (t.getStopHour() * 60 * 60) + (t.getStopMinute() * 60) + t.getStopSecond();
  }
}
BLYNK_WRITE(V87) {
  TimeInputParam t(param);
  if (t.hasStartTime())
  {
    worker[6].startTime = (t.getStartHour() * 60 * 60) + (t.getStartMinute() * 60) + t.getStartSecond();
  }
  if (t.hasStopTime())
  {
    worker[6].stopTime = (t.getStopHour() * 60 * 60) + (t.getStopMinute() * 60) + t.getStopSecond();
  }
}
BLYNK_WRITE(V88) {
  TimeInputParam t(param);
  if (t.hasStartTime())
  {
    worker[7].startTime = (t.getStartHour() * 60 * 60) + (t.getStartMinute() * 60) + t.getStartSecond();
  }
  if (t.hasStopTime())
  {
    worker[7].stopTime = (t.getStopHour() * 60 * 60) + (t.getStopMinute() * 60) + t.getStopSecond();
  }
}
BLYNK_WRITE(V89) {
  TimeInputParam t(param);
  if (t.hasStartTime())
  {
    worker[8].startTime = (t.getStartHour() * 60 * 60) + (t.getStartMinute() * 60) + t.getStartSecond();
  }
  if (t.hasStopTime())
  {
    worker[8].stopTime = (t.getStopHour() * 60 * 60) + (t.getStopMinute() * 60) + t.getStopSecond();
  }
}
BLYNK_WRITE(V90) {
  TimeInputParam t(param);
  if (t.hasStartTime())
  {
    worker[9].startTime = (t.getStartHour() * 60 * 60) + (t.getStartMinute() * 60) + t.getStartSecond();
  }
  if (t.hasStopTime())
  {
    worker[9].stopTime = (t.getStopHour() * 60 * 60) + (t.getStopMinute() * 60) + t.getStopSecond();
  }
}
//periodic time
BLYNK_WRITE(V91) {
  TimeInputParam t(param);
  if (t.hasStartTime())
  {
    worker[0].run_time = (t.getStartHour() * 60 * 60) + (t.getStartMinute() * 60) + t.getStartSecond();
  }
  if (t.hasStopTime())
  {
    worker[0].pause_time = (t.getStopHour() * 60 * 60) + (t.getStopMinute() * 60) + t.getStopSecond();
  }
}
BLYNK_WRITE(V92) {
  TimeInputParam t(param);
  if (t.hasStartTime())
  {
    worker[1].run_time = (t.getStartHour() * 60 * 60) + (t.getStartMinute() * 60) + t.getStartSecond();
  }
  if (t.hasStopTime())
  {
    worker[1].pause_time = (t.getStopHour() * 60 * 60) + (t.getStopMinute() * 60) + t.getStopSecond();
  }
}
BLYNK_WRITE(V93) {
  TimeInputParam t(param);
  if (t.hasStartTime())
  {
    worker[2].run_time = (t.getStartHour() * 60 * 60) + (t.getStartMinute() * 60) + t.getStartSecond();
  }
  if (t.hasStopTime())
  {
    worker[2].pause_time = (t.getStopHour() * 60 * 60) + (t.getStopMinute() * 60) + t.getStopSecond();
  }
}
BLYNK_WRITE(V94) {
  TimeInputParam t(param);
  if (t.hasStartTime())
  {
    worker[3].run_time = (t.getStartHour() * 60 * 60) + (t.getStartMinute() * 60) + t.getStartSecond();
  }
  if (t.hasStopTime())
  {
    worker[3].pause_time = (t.getStopHour() * 60 * 60) + (t.getStopMinute() * 60) + t.getStopSecond();
  }
}
BLYNK_WRITE(V95) {
  TimeInputParam t(param);
  if (t.hasStartTime())
  {
    worker[4].run_time = (t.getStartHour() * 60 * 60) + (t.getStartMinute() * 60) + t.getStartSecond();
  }
  if (t.hasStopTime())
  {
    worker[4].pause_time = (t.getStopHour() * 60 * 60) + (t.getStopMinute() * 60) + t.getStopSecond();
  }
}
BLYNK_WRITE(V96) {
  TimeInputParam t(param);
  if (t.hasStartTime())
  {
    worker[5].run_time = (t.getStartHour() * 60 * 60) + (t.getStartMinute() * 60) + t.getStartSecond();
  }
  if (t.hasStopTime())
  {
    worker[5].pause_time = (t.getStopHour() * 60 * 60) + (t.getStopMinute() * 60) + t.getStopSecond();
  }
}
BLYNK_WRITE(V97) {
  TimeInputParam t(param);
  if (t.hasStartTime())
  {
    worker[6].run_time = (t.getStartHour() * 60 * 60) + (t.getStartMinute() * 60) + t.getStartSecond();
  }
  if (t.hasStopTime())
  {
    worker[6].pause_time = (t.getStopHour() * 60 * 60) + (t.getStopMinute() * 60) + t.getStopSecond();
  }
}
BLYNK_WRITE(V98) {
  TimeInputParam t(param);
  if (t.hasStartTime())
  {
    worker[7].run_time = (t.getStartHour() * 60 * 60) + (t.getStartMinute() * 60) + t.getStartSecond();
  }
  if (t.hasStopTime())
  {
    worker[7].pause_time = (t.getStopHour() * 60 * 60) + (t.getStopMinute() * 60) + t.getStopSecond();
  }
}
BLYNK_WRITE(V99) {
  TimeInputParam t(param);
  if (t.hasStartTime())
  {
    worker[8].run_time = (t.getStartHour() * 60 * 60) + (t.getStartMinute() * 60) + t.getStartSecond();
  }
  if (t.hasStopTime())
  {
    worker[8].pause_time = (t.getStopHour() * 60 * 60) + (t.getStopMinute() * 60) + t.getStopSecond();
  }
}
BLYNK_WRITE(V100) {
  TimeInputParam t(param);
  if (t.hasStartTime())
  {
    worker[9].run_time = (t.getStartHour() * 60 * 60) + (t.getStartMinute() * 60) + t.getStartSecond();
  }
  if (t.hasStopTime())
  {
    worker[9].pause_time = (t.getStopHour() * 60 * 60) + (t.getStopMinute() * 60) + t.getStopSecond();
  }
}
