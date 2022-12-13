/************************** Configuration ***********************************/
//En el archivo config.h, se especifican los credenciales necesarios para acceder a la cuenta
// de Adafruit IO.
#include "config.h"

int count = 0;

// Se accede al feed que se quiere indicando el nombre dentro de la funcion
AdafruitIO_Feed *counter = io.feed("RSense");

void setup() {

 
  Serial.begin(115200);

  
  while(! Serial);

  Serial.print("Connecting to Adafruit IO");

  //Se conecta a Adafruit
  io.connect();

  
  while(io.status() < AIO_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  //Estará aqui cuando se haya realizado una conexion exitosa
  Serial.println();
  Serial.println(io.statusText());

}

void loop() {

  //io.run();Siempre debe estar presente en la parte superior de su funcion loop
  //Mantiene al cliente conectado a io.adafruit.com y procesa los datos entrantes.
  io.run();
  //Enviamos los datos al feed de Adafruit IO
  Serial.print("sending -> ");
  Serial.println(count);
  counter->save(count);

  // incremento el dato a escribir 
  count++;

  //Adafruit IO tiene una velocidad limitada para la publicación, por lo que se 
  //requiere un retraso entre eventos feed->save. 
  delay(3000);

}
