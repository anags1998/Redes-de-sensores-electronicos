#include <WiFi.h>
#include <ESP32Ping.h>

const char* ssid       = "RSense"; //Nombre de la Red WIFI
const char* password   = "";      // Contraseña de la Red WIFI

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
  Serial.print("IP: ");
  Serial.println(WiFi.localIP()); //Obtengo la IP que me ha asignado 
  bool correcto = Ping.ping("www.google.com"); //Compruebo conectividad con google.com mediante un ping
  if( !correcto){
    Serial.println("Fallo en el Ping");
    return;
  }
  Serial.println("Acceso a www.google.com correcto");
}

void loop() {
  // put your main code here, to run repeatedly:

}
