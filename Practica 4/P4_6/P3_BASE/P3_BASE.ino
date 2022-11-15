#include <MPU9250_asukiaaa.h>
#include <Wire.h>
#include "WiFi.h"

// Definimos los pines del I2C
#ifdef _ESP32_HAL_I2C_H_
#define SDA_PIN 21
#define SCL_PIN 22
#endif

//Variables para las aceleraciones de los 3 ejes y una de tipo sensor
MPU9250_asukiaaa mySensor;
float aX, aY, aZ, aSqrt;
 
char sX[10];
char sY[10];
char sZ[10];
char sSqrt[10];

const char* ssid       = "RSense"; //Nombre de la Red WIFI
const char* password   = "";      // Contraseña de la Red WIFI

const IPAddress serverIP(192,168,0,180); // La dirección que desea visitar
uint16_t serverPort = 456;         // Número de puerto del servidor

WiFiClient client; // Declarar un objeto cliente para conectarse al servidor


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  
#ifdef _ESP32_HAL_I2C_H_
  Wire.begin(SDA_PIN, SCL_PIN); //Inicializar la comunicación en los puertos
  mySensor.setWire(&Wire); //Asociamos el sensor a I2C
#endif
  mySensor.beginAccel();//Arrancamos las medidas de aceleración
  
  //connect to WiFi
  Serial.printf("Conectando a %s ", ssid);
  Serial.println("");
  WiFi.begin(ssid, password); //Intento conectarme indicando el usuario y la contraseña
  while (WiFi.status() != WL_CONNECTED) { //Mientras se está conectando
    delay(1000);
    Serial.println("Conectando a WiFi...");
  }
  
  Serial.println("Conectado a la red"); //Conectado
 
  
}

void loop() {
  // put your main code here, to run repeatedly:
  client.connect(serverIP, serverPort); //Me conecto al servidor mediante la IP y el puerto definido
  
  while(client.connected()){ //Mientras el cliente esté conectado
    leerDato(); //Leo datos
    sprintf(sX,"%f",aX);
    sprintf(sY,"%f",aY);
    sprintf(sZ,"%f",aZ);
    sprintf(sSqrt,"%f",aSqrt);
    client.write(sX); //Mando al servidor
    client.write(", ");
    client.write(sY);
    client.write(", ");
    client.write(sZ);
    client.write(", ");
    client.write(sSqrt);
    client.write(", ");
 }
}

void leerDato(){
  uint8_t sensorId;
  int result;
  result = mySensor.readId(&sensorId);//Compruebo que puedo leer del sensor
  if (result != 0) {   
    Serial.println("Cannot read sensorId " + String(result));
  }
  result = mySensor.accelUpdate();
  if (result == 0) {
    //Leo las aceleraciones de los 3 ejes del sensor y la media
    aX = mySensor.accelX();
    aY = mySensor.accelY();
    aZ = mySensor.accelZ();
    aSqrt = mySensor.accelSqrt();
      } else {
    Serial.println("Cannod read accel values " + String(result));
  }
}
