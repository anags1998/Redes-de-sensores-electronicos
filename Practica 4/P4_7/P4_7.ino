// Import required libraries
#include "WiFi.h"
#include "ESPAsyncWebServer.h"
#include "SPIFFS.h"

const char* ntpServer = "pool.ntp.org"; //Servidor NTP
const long  gmtOffset_sec = 3600; //UTC +1.00 : 1 * 60 * 60 : 3600
const int   daylightOffset_sec = 3600; //Desplazamiento en segundos para el horario de verano

const char* ssid = "MIWIFI_5G_HunM";//Nombre de la red WIFI
const char* password = "mJseX7mv";//Contraseña de la red WIFI

//Para escribir la hora en el servidor
String hora;

// Objeto AsyncWebServer para crear el servidor
AsyncWebServer server(80);

//Variables necesarias para mandar datos al servidor
char hour[3];
char minute[3];

// Reemplaza el marcador del valor de la hora por la actual 
String processor(const String& var){
  Serial.println(var);
  if(var == "HOUR"){
    printLocalTime(); //Obtenemos la hora actual del servidor ntp
    hora = String(hour) + ":" + String(minute); 
    Serial.print(hora);
    return hora; //Reemplazamos por este valor
  }
  return String();
}

// Reemplaza el marcador del valor de la hora por 00:00 
String processor2(const String& var){
  Serial.println(var);
  if(var == "HOUR"){ //Comprueba que eciste el marcador de posicion
    hora = "00:00";
    Serial.print(hora);
    return hora; //Reemplazamos por este valor
  }
  return String();
}

void printLocalTime()
{
  struct tm timeinfo; //Estructura que contiene los detalles sobre el tiempo (minutos, segundos, horas...)
  if(!getLocalTime(&timeinfo)){ //Obtengo datos de fecha y hora y los guardo en timeinfo
    Serial.println("Failed to obtain time");
    return;
  }
  // Guardo en distintas variables lo obtenido. A: día de la semana, B: mes, d: día del mes, Y: año, 
  //H: hora formato 24h, M: minutos, S: segundos
  strftime(hour,3,"%H",&timeinfo);
  strftime(minute,3,"%M",&timeinfo);
} 
void setup(){
  // Serial port
  Serial.begin(115200);

  // Inicializo SPIFFS que es un sistema de archivos diseñado para funcionar en memorias flash conectadas
  //por SPI en dispositivos embebidos y con poca cantidad de RAM.
  if(!SPIFFS.begin(true)){
    Serial.println("An Error has occurred while mounting SPIFFS");
    return;
  }

  // Me conecto al wifi mediante ssid y password
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }

  // Printeo la direacción IP local del ESP32 
  Serial.println(WiFi.localIP());
  
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer); //Configuro la hora con los parametros definidos
  
  // Rota para la pagina web
  //Cuando el servidor recibe solicitud en la URL raíz "/" enviará el archivo index.html al cliente y 
  //sustituira el valor del marcador por la hora actual dado que llamamos a la funcion processor
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/index.html", String(), false, processor);
  });
  
  // Rota para cargar el archivo style.css 
  //Como se hace referencia al archivo .css en el .html el cliente realiza petición para el archivo
  //y el servidor envía el archivo style.css cuando eso sucede  
  server.on("/style.css", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/style.css", "text/css");
  });
  // Ruta para resetear la hora
   //Cuando el servidor recibe solicitud en la URL "/reset" enviará el archivo index.html al cliente y 
  //sustituira el valor del marcador por 00:00 dado que llamamos a la funcion processor2
    server.on("/reset", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/index.html", String(), false, processor2);
  });
  // Ruta para actualizar la hora
  //Cuando el servidor recibe solicitud en la URL "/actual" enviará el archivo index.html al cliente y 
  //sustituira el valor del marcador por la hora actual dado que llamamos a la funcion processor
  server.on("/actual", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/index.html", String(), false, processor);
  });
  
  // Arrancamos servidor para que escuche a los clientes
  server.begin();
}
 
void loop(){
  
}
