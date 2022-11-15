#include <WiFi.h>
#include <ESP32Ping.h>


const char* ssid       = "RSense"; //Nombre de la Red WIFI
const char* password   = "";      // Contraseña de la Red WIFI

const char* ntpServer = "pool.ntp.org"; //Servidor NTP
const long  gmtOffset_sec = 3600; //UTC +1.00 : 1 * 60 * 60 : 3600
const int   daylightOffset_sec = 3600; //Desplazamiento en segundos para el horario de verano

//Variables necesarias para mandar datos al servidor
char weekday[10];
char month[15];
char monthday[3];
char hour[3];
char minute[3];
char seconds[3];
char year[5];

const IPAddress serverIP(192,168,0,180); // La dirección que desea visitar
uint16_t serverPort = 455;         // Número de puerto del servidor

WiFiClient client; // Declarar un objeto cliente para conectarse al servidor


void printLocalTime()
{
  struct tm timeinfo; //Estructura que contiene los detalles sobre el tiempo (minutos, segundos, horas...)
  if(!getLocalTime(&timeinfo)){ //Obtengo datos de fecha y hora y los guardo en timeinfo
    Serial.println("Failed to obtain time");
    return;
  }
  // Guardo en distintas variables lo obtenido. A: día de la semana, B: mes, d: día del mes, Y: año, 
  //H: hora formato 24h, M: minutos, S: segundos
  strftime(weekday,10,"%A",&timeinfo);
  strftime(month,15,"%B",&timeinfo);
  strftime(monthday,3,"%d",&timeinfo);
  strftime(year,5,"%Y",&timeinfo);
  strftime(hour,3,"%H",&timeinfo);
  strftime(minute,3,"%M",&timeinfo);
  strftime(seconds,3,"%S",&timeinfo);

  //Mando al servidor todos los datos de la hora local con el formato que quiero
  client.write(weekday);
  client.write(", ");
  client.write(month);
  client.write(" ");
  client.write(monthday);
  client.write(" ");
  client.write(year);
  client.write(" ");
  client.write(hour);
  client.write(":");
  client.write(minute);
  client.write(":");
  client.write(seconds);
  client.write("\n");
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
  //printLocalTime(); //Llamo a la funcion para mostrar la hora local

  
}

void loop() {
  // put your main code here, to run repeatedly:
  client.connect(serverIP, serverPort); //Me conecto al servidor mediante la IP y el puerto definido
  while(client.connected()){ //Mientras el cliente esté conectado
    printLocalTime();//Con un delay de un segundo printeo la hora local
    delay(1000);
  }
  

}
