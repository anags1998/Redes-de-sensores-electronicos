#include "BluetoothSerial.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

#if !defined(CONFIG_BT_SPP_ENABLED)
#error Serial Bluetooth not available or not enabled. It is only available for the ESP32 chip.
#endif

//Definimos una instancia Bluetooth
BluetoothSerial SerialBT;

void setup() {
  Serial.begin(115200);
  SerialBT.begin("ESP32test"); //Indicamos el nombre con el que aparecerá el dispositivo para 
                               //emparejarnos con el en el móvil
  Serial.println("El dispositivo está listo para emparejar");
}

void loop() {
  if (Serial.available()) {
    SerialBT.write(Serial.read()); //Si escribimos algo por el Serial lo mandamos por Bluetooth
  }
  if (SerialBT.available()) {
    Serial.write(SerialBT.read());//Si recibimos algo por Bluetooth lo mandamos por el Serial
  }
  delay(20);
}
