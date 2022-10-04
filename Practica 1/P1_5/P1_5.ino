#include <MPU9250_asukiaaa.h>
#include <Wire.h>

// Definimos los pines del I2C
#ifdef _ESP32_HAL_I2C_H_
#define SDA_PIN 21
#define SCL_PIN 22
#endif

//Definimos el pin del LED
#define LED 5

//Variable para contar 1s
int cont = 0;

//Variables para las aceleraciones de los 3 ejes y una de tipo sensor
MPU9250_asukiaaa mySensor;
float aX, aY, aZ, aSqrt;

void setup() {
  Serial.begin(115200);
  pinMode(LED, OUTPUT);//Inicializamos el LED a encender
  digitalWrite(LED, HIGH);    // Apago LED
#ifdef _ESP32_HAL_I2C_H_
  Wire.begin(SDA_PIN, SCL_PIN); //Inicializar la comunicación en los puertos
  mySensor.setWire(&Wire); //Asociamos el sensor a I2C
#endif

  mySensor.beginAccel();//Arrancamos las medidas de aceleración
  delay(5000);//Añadimos delay de 5s para observar que en pantalla de comando que el setup se arranca bien 
}

void loop() {
  uint8_t sensorId;
  int result;
  result = mySensor.readId(&sensorId);//Compruebo que puedo leer del sensor
  if (result != 0) {   
    Serial.println("Cannot read sensorId " + String(result));
  }
  if(cont < 10){//Como mido casa 100ms, cuando el contador sea 10 habrá pasado 1s y mostraré valores
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
  }else{
    //Mando por UART cada segundo los valores
    Serial.println("Aceleración eje X: " + String(aX));
    Serial.println("Aceleración eje Y: " + String(aY));
    Serial.println("Aceleración eje Z: " + String(aZ));
    Serial.println("Aceleración eje media: " + String(aSqrt));
    cont = 0;//Reseteo contador para volver a contar 1s
    digitalWrite(LED, LOW);   // Enciendo LED
    delay(200);                //Espero 200ms
    digitalWrite(LED, HIGH);    // Apago LED
  }
  // Delay de 100ms para volver a medir y aumento de contador para llegar a 1s para printear valores
  delay(100);
  cont = cont +1;
}
