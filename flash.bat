@copy to server
@scp -i ~/.ssh/id_rsa .pio/build/esp07/firmware.bin sanjy@192.168.1.200:~/www/firmware.bin
@ direct upload OTA from tools
python ..\..\.platformio\packages\framework-arduinoespressif8266\tools\espota.py --progress --ip 192.168.1.203 --auth admin --file .\.pio\build\esp07\firmware.bin
cd HomOsMqttSrv
npm start