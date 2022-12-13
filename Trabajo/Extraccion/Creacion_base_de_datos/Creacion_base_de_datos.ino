#include "Arduino.h"
#include <WiFi.h>
#include <WiFiClient.h> 
#include <ESP32_FTPClient.h>
#include "octocat.h"
#include <Wire.h>
#include <MPU9250_asukiaaa.h>

//Defino boton para inicio
#define BUTTON_PIN 36

// Variables will change:
int lastState = HIGH; // the previous state from the input pin
int currentState;     // the current reading from the input pin
int i;

// Definimos los pines del I2C
#ifdef _ESP32_HAL_I2C_H_
#define SDA_PIN 21
#define SCL_PIN 22
#endif

const char* ssid       = "RSense"; //Nombre de la Red WIFI
const char* password   = "";      // Contraseña de la Red WIFI

const char* ntpServer = "pool.ntp.org"; //Servidor NTP
const long  gmtOffset_sec = 3600; //UTC +1.00 : 1 * 60 * 60 : 3600
const int   daylightOffset_sec = 3600; //Desplazamiento en segundos para el horario de verano

WiFiClient client; // Declarar un objeto cliente para conectarse al servidor
char ftp_server[] = "155.210.150.77";//Servidor FTP
char ftp_user[]   = "rsense";//Usuario a servidor FTP
char ftp_pass[]   = "rsense";//Contraseña a servidor FTP

//Crear cliente FTP para subir archivos a servidor FTP
ESP32_FTPClient ftp (ftp_server,ftp_user,ftp_pass, 5000, 2);

//Variables para las aceleraciones de los 3 ejes y una de tipo sensor
MPU9250_asukiaaa mySensor;
String aX, aY, aZ, gX, gY, gZ;
String datos;

const int tam = 2000;
String datosFich[tam];
uint8_t sensorId;
int result;
char datosFichero[500];
//Variables necesarias para mandar datos al servidor
char fecha[50];
String nombre = "";

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  
#ifdef _ESP32_HAL_I2C_H_
  Wire.begin(SDA_PIN, SCL_PIN); //Inicializar la comunicación en los puertos
  mySensor.setWire(&Wire); //Asociamos el sensor a I2C
#endif

  mySensor.beginAccel();//Arrancamos las medidas de aceleración
  
  mySensor.beginGyro();//Arrancamos las medidas del giroscopio

  
  //connect to WiFi
  Serial.printf("Conectando a %s ", ssid);
  Serial.println("");
  WiFi.begin(ssid, password); //Intento conectarme indicando el usuario y la contraseña
  while (WiFi.status() != WL_CONNECTED) { //Mientras se está conectando
    delay(1000);
    Serial.println("Conectando a WiFi...");
  }
  
  Serial.println("Conectado a la red"); //Conectado
  
  
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer); //Configuro la hora con los parametros definidos
  
  //Comenzar conexión con servidor FTP
  ftp.OpenConnection();
  ftp.ChangeWorkDir("/rsense/847048");//Cambiamos directorio en el servidor

}

void loop() {
  // put your main code here, to run repeatedly:
  currentState = digitalRead(BUTTON_PIN);
  
  if(lastState == LOW && currentState == HIGH){
    Serial.println("The state changed from LOW to HIGH");
    for( i = 0; i <tam ; i++){
      //Serial.println(millis());
      leerDatosSensor();
      //Serial.println(millis());
    }
    printLocalTime();
    nombre = fecha;
    nombre.concat(".txt");
    
    
    const char *path = nombre.c_str();
    ftp.InitFile("Type A");//Inicializamos tipo de archivo
    ftp.NewFile(path);//Creamos archivo
    for (int j = 0; j < tam; j++){
      datosFich[j].toCharArray(datosFichero, 500);
      ftp.Write(datosFichero);
    }
    ftp.CloseFile();//Cerramos
    
  }
  //save the last state
  lastState = currentState;
}

//Funcion para obtener la hora
void printLocalTime(){
  struct tm timeinfo; //Estructura que contiene los detalles sobre el tiempo (minutos, segundos, horas...)
  if(!getLocalTime(&timeinfo)){ //Obtengo datos de fecha y hora y los guardo en timeinfo
    Serial.println("Failed to obtain time");
    return;
  }
  strftime(fecha,50, "%A, %B %d %Y %H:%M:%S",&timeinfo); // Escribo, lo obtenido:
                                                      // A: día de la semana
                                                      // B: mes
                                                      // d: día del mes
                                                      // Y: año
                                                      // H: hora formato 24h
                                                      // M: minutos
                                                      // S: segundos
}

//Funcion para leer los datos del sensor, tanto del acelerometro como del giroscopio
void leerDatosSensor(){
  float tiempo = millis();
  result = mySensor.readId(&sensorId);//Compruebo que puedo leer del sensor
  if (result != 0) {   
    Serial.println("Cannot read sensorId " + String(result));
  }
  result = mySensor.accelUpdate();
  if (result == 0) {
    //Leo las aceleraciones de los 3 ejes del sensor y la media
    aX = String(mySensor.accelX());
    aY = String(mySensor.accelY());
    aZ = String(mySensor.accelZ());
  } else {
    Serial.println("Cannod read accel values " + String(result));
  }
  result = mySensor.gyroUpdate();
  if (result == 0) {
    //Leo los 3 ejes del giroscopio
    gX = String(mySensor.gyroX());
    gY = String(mySensor.gyroY());
    gZ = String(mySensor.gyroZ());
  } else {
    Serial.println("Cannot read gyro values " + String(result));
  }
  datos.concat(tiempo);
  datos.concat("ms : ");
  datos.concat(aX);
  datos.concat(";");
  datos.concat(aY);
  datos.concat(";");
  datos.concat(aZ);
  datos.concat(";");
  datos.concat(gX);
  datos.concat(";");
  datos.concat(gY);
  datos.concat(";");
  datos.concat(gZ);
  datos.concat('\n');
  
  datosFich[i] = datos;
  datos = "";
  delay(17);
  
}
