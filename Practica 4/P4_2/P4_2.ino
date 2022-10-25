#include <WiFi.h>
#include <ESP32Ping.h>

const char* ssid       = "RSense"; //Nombre de la Red WIFI
const char* password   = "";      // Contraseña de la Red WIFI

const char* ntpServer = "pool.ntp.org"; //Servidor NTP
const long  gmtOffset_sec = 3600; //UTC +1.00 : 1 * 60 * 60 : 3600
const int   daylightOffset_sec = 3600; //Desplazamiento en segundos para el horario de verano

void printLocalTime()
{
  struct tm timeinfo; //Estructura que contiene los detalles sobre el tiempo (minutos, segundos, horas...)
  if(!getLocalTime(&timeinfo)){ //Obtengo datos de fecha y hora y los guardo en timeinfo
    Serial.println("Failed to obtain time");
    return;
  }
  Serial.println(&timeinfo, "%A, %B %d %Y %H:%M:%S"); // Escribo, lo obtenido:
                                                      // A: día de la semana
                                                      // B: mes
                                                      // d: día del mes
                                                      // Y: año
                                                      // H: hora formato 24h
                                                      // M: minutos
                                                      // S: segundos
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  
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
  printLocalTime(); //Llamo a la funcion para mostrar la hora local

  
  //Desconecto el WIFI porque ya no es necesario
  WiFi.disconnect(true);
  WiFi.mode(WIFI_OFF);
}

void loop() {
  // put your main code here, to run repeatedly:

  delay(1000);
  printLocalTime();//Con un delay de un segundo printeo la hora local

}
