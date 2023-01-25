#include "Arduino.h"
#include <WiFi.h>
#include <WiFiClient.h> 
#include <ESP32_FTPClient.h>
#include "octocat.h"
#include <Wire.h>
#include <MPU9250_asukiaaa.h>
#include <Statistics.h>
#include "QuickMedianLib.h"
#include "ESPAsyncWebServer.h"
#include "SPIFFS.h"

//Inicializamos para poder realizar calculos estadisticos
Statistics st = Statistics();

//Defino boton para inicio
#define BUTTON_PIN 36

// Variables para el cambio de estado de boton
int lastState = HIGH; // el estado anterior
int currentState;     // estado actual
int i;

// Definimos los pines del I2C
#ifdef _ESP32_HAL_I2C_H_
#define SDA_PIN 21
#define SCL_PIN 22
#endif

//Definimos los parametros de la red WiFi
const char* ssid       = "MIWIFI_2G_HunM"; //Nombre de la Red WIFI
const char* password   = "mJseX7mv";      // Contraseña de la Red WIFI

WiFiClient client; // Declarar un objeto cliente para conectarse al servidor

//Variables para las aceleraciones de los 3 ejes y una de tipo sensor
MPU9250_asukiaaa mySensor;
const int tam = 500;
String aX, aY, aZ, gX, gY, gZ;
float datosaX[500];
float datosaY[500];
float datosaZ[500];
float datosgX[500];
float datosgY[500];
float datosgZ[500];

float statsaX[4];
float statsaY[4];
float statsaZ[4];
float statsgX[4];
float statsgY[4];
float statsgZ[4];

uint8_t sensorId;
int result;

//Parametro para mandar a la pagina web
String paso = "";

// Objeto AsyncWebServer para crear el servidor
AsyncWebServer server(80);

// Reemplaza el marcador del valor del paso por el actual 
String processor(const String& var){
  if(var == "PASO"){
    return paso; //Reemplazamos por este valor
  }
  return String();
}

void setup() {
  Serial.begin(115200);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  
#ifdef _ESP32_HAL_I2C_H_
  Wire.begin(SDA_PIN, SCL_PIN); //Inicializar la comunicación en los puertos
  mySensor.setWire(&Wire); //Asociamos el sensor a I2C
#endif

  mySensor.beginAccel();//Arrancamos las medidas de aceleración
  
  mySensor.beginGyro();//Arrancamos las medidas del giroscopio

  // Inicializo SPIFFS que es un sistema de archivos diseñado para funcionar en memorias flash conectadas
  //por SPI en dispositivos embebidos y con poca cantidad de RAM.
  if(!SPIFFS.begin(true)){
    Serial.println("An Error has occurred while mounting SPIFFS");
    return;
  }
  
  //Me conecto al WiFi
  Serial.printf("Conectando a %s ", ssid);
  Serial.println("");
  WiFi.begin(ssid, password); //Intento conectarme indicando el usuario y la contraseña
  while (WiFi.status() != WL_CONNECTED) { //Mientras se está conectando
    delay(1000);
    Serial.println("Conectando a WiFi...");
  }
  
  Serial.println("Conectado a la red"); //Conectado
  // Printeo la direacción IP local del ESP32 
  Serial.println(WiFi.localIP());
  
  // Ruta para la pagina web
  //Cuando el servidor recibe solicitud en la URL raíz "/" enviará el archivo index.html al cliente y 
  //sustituira el valor del marcador por el paso actual dado que llamamos a la funcion processor
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/index.html", String(), false, processor);
  });
  
  // Ruta para cargar el archivo style.css 
  //Como se hace referencia al archivo .css en el .html el cliente realiza petición para el archivo
  //y el servidor envía el archivo style.css cuando eso sucede  
  server.on("/style.css", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/style.css", "text/css");
  });
  // Ruta para actualizar el paso
  //Cuando el servidor recibe solicitud en la URL "/paso" enviará el archivo index.html al cliente y 
  //sustituira el valor del marcador por el apso actual dado que llamamos a la funcion processor
  server.on("/paso", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/index.html", String(), false, processor);
  });
  
  // Arrancamos servidor para que escuche a los clientes
  server.begin();
}

void loop() {
  //Leemos el estado actual del boton
  currentState = digitalRead(BUTTON_PIN);
  
  if(lastState == LOW && currentState == HIGH){
    Serial.println("The state changed from LOW to HIGH");
    for( i = 0; i <tam ; i++){
      leerDatosSensor(); //Leemos datos del sensor con una frecuencia de muestreo de 50Hz
      
    }
    for( int j = 0; j <tam ; j++){
      st.add(datosaX[j]);
    }
    float valueslen = sizeof(datosaX) /sizeof(float);
    statsaX[0] = st.mean();
    statsaX[1] = QuickMedian<float>::GetMedian(datosaX, valueslen);
    statsaX[2] = st.var();
    statsaX[3] = st.std();
    
    st.reset();
    for( int j = 0; j <tam ; j++){
      st.add(datosaY[j]);
    }
    statsaY[0] = st.mean();
    statsaY[1] = QuickMedian<float>::GetMedian(datosaY, valueslen);
    statsaY[2] = st.var();
    statsaY[3] = st.std();
    
    st.reset();
    for( int j = 0; j <tam ; j++){
      st.add(datosaZ[j]);
    }
    statsaZ[0] = st.mean();
    statsaZ[1] = QuickMedian<float>::GetMedian(datosaZ, valueslen);
    statsaZ[2] = st.var();
    statsaZ[3] = st.std();

    st.reset();
    for( int j = 0; j <tam ; j++){
      st.add(datosgX[j]);
    }
    statsgX[0] = st.mean();
    statsgX[1] = QuickMedian<float>::GetMedian(datosgX, valueslen);
    statsgX[2] = st.var();
    statsgX[3] = st.std();

    st.reset();
    for( int j = 0; j <tam ; j++){
      st.add(datosgY[j]);
    }
    statsgY[0] = st.mean();
    statsgY[1] = QuickMedian<float>::GetMedian(datosgY, valueslen);
    statsgY[2] = st.var();
    statsgY[3] = st.std();
    
    st.reset();
    for( int j = 0; j <tam ; j++){
      st.add(datosgZ[j]);
    }
    statsgZ[0] = st.mean();
    statsgZ[1] = QuickMedian<float>::GetMedian(datosgZ, valueslen);
    statsgZ[2] = st.var();
    statsgZ[3] = st.std();
    for(int k = 2; k <4; k++){
      Serial.println(statsgX[k]);
      Serial.println(statsgY[k]);
      Serial.println(statsgZ[k]);
    }
    determinarPaso();
  }
 
  st.reset();
  lastState = currentState;
}

//Funcion para determinar el paso realizado en funcion de los parametros estadisticos calculados
void determinarPaso(){
  if((statsgX[2]<25.00)&(statsgY[2]<75.00)&(statsgZ[2]<25.00)&(statsgX[3]<5.00)&(statsgY[3]<7.00)&(statsgZ[3]<5.00)){
    Serial.println("Demi-Plie");
    paso = "Demi-Plie";
  }else if((150.00<statsgX[2])&(statsgX[2]<500.00)&(200.00<statsgY[2])&(statsgY[2]<600.00)&(100.00<statsgZ[2])&(statsgZ[2]<500.00)&(14.00<statsgX[3])&(statsgX[3]<25.00)&(14.00<statsgY[3])&(statsgY[3]<25.00)&(12.00<statsgZ[3])&(statsgZ[3]<25.00)){
    Serial.println("Saute");
    paso = "Saute";
  }else if((20.00<statsgX[2])&(statsgX[2]<150.00)&(75.00<statsgY[2])&(statsgY[2]<250.00)&(15.00<statsgZ[2])&(statsgZ[2]<80.00)&(6.00<statsgX[3])&(statsgX[3]<11.00)&(9.00<statsgY[3])&(statsgY[3]<16.00)&(4.00<statsgZ[3])&(statsgZ[3]<15.00)){
    Serial.println("Releve");
    paso = "Releve";
  }else if((100.00<statsgX[2])&(statsgX[2]<400.00)&(140.00<statsgY[2])&(statsgY[2]<300.00)&(500.00<statsgZ[2])&(statsgZ[2]<1100.00)&(12.00<statsgX[3])&(statsgX[3]<20.00)&(12.00<statsgY[3])&(statsgY[3]<17.00)&(20.00<statsgZ[3])&(statsgZ[3]<35.00)){
    Serial.println("Arabesque");
    paso = "Arabesque";
  }else{
    Serial.println("Indeterminado");
    paso = "Indeterminado";
  }
  
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
 
  datosaX[i] = aX.toFloat();
  datosaY[i] = aY.toFloat();
  datosaZ[i] = aZ.toFloat();
  datosgX[i] = gX.toFloat();
  datosgY[i] = gY.toFloat();
  datosgZ[i] = gZ.toFloat();
  
  delay(17);
  
}
