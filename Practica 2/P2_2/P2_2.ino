#include <MPU9250_asukiaaa.h>
#include <Wire.h>

// Definimos los pines del I2C
#ifdef _ESP32_HAL_I2C_H_
#define SDA_PIN 21
#define SCL_PIN 22
#endif

//Definimos el pin del LED
#define LED 5

//Definimos pin de muestro para comprobar muestrea datos cada 100ms
#define MUES 17

//Variables para las aceleraciones de los 3 ejes y una de tipo sensor
MPU9250_asukiaaa mySensor;
float aX, aY, aZ, aSqrt;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(LED, OUTPUT);//Inicializamos el LED a encender
  digitalWrite(LED, HIGH);    // Apago LED
  pinMode(MUES, OUTPUT);//Inicializamos el pin de muestreo
  
#ifdef _ESP32_HAL_I2C_H_
  Wire.begin(SDA_PIN, SCL_PIN); //Inicializar la comunicación en los puertos
  mySensor.setWire(&Wire); //Asociamos el sensor a I2C
#endif
  mySensor.beginAccel();//Arrancamos las medidas de aceleración
  delay(5000);//Añadimos delay de 5s para observar que en pantalla de comando que el setup se arranca bien 

  //Creación de ambas tareas. xTaskCreate(param1,param2,param3,param4,param5,param6)
  //param1 = puntero de la funcion que implementa la tarea.
  //param2 = un nombre descriptivo de la tarea. Sólo sirver para debug. 
  //param3 = cada tarea tiene una pila de programa propia en el kernel, este parámetro determina 
    //el tamaño de la pila (en words). El tamaño de la pila para la tareas en reposo se 
    //define mediante al constante de configMINIMAL_STACK_SIZE.
  //param4 = los parametros que necesita la tarea. Si no hay NULL.
  //param5 = define la prioridad de la tarea.
  //param6 = argumentos de la tarea. Si no hay NULL.
  xTaskCreate(Acel,"Acel",10000,NULL,1,NULL);
  xTaskCreate(LedYUart,"LedYUart",10000,NULL,1,NULL);
}

void loop() {
  // put your main code here, to run repeatedly:
}

//Descripción de las dos tareas. Las tareas tienen que devolver un void y tener como argumento de entrada
//un puntero void

void Acel( void * parameter ){
  for( ;; ){                  //Bucle infinito
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
      digitalWrite(MUES, HIGH); //Activamos pin de muestreo 
    } else {
      Serial.println("Cannod read accel values " + String(result));
    }
    delay(100); //Delay para muestrear cada 100ms
    digitalWrite(MUES, LOW);    //Apagamos pin de muestro
  }
  Serial.println("Finalizando tarea lectura aceleración");//Por aquí no puede pasar nunca debido al bucle infinito y 
                                                          //en caso de que lo haga me muestra que se finaliza la tarea
                                                          //y se elimina la función
  vTaskDelete( NULL ); //No se puede salir de un Task mediante un return, sino hay que eliminar el Task.
}



void LedYUart( void * parameter ){
  for( ;; ){                  //Bucle infinito
    //Mando por UART cada segundo los valores
    Serial.println("Aceleración eje X: " + String(aX));
    Serial.println("Aceleración eje Y: " + String(aY));
    Serial.println("Aceleración eje Z: " + String(aZ));
    Serial.println("Aceleración eje media: " + String(aSqrt));
    /*digitalWrite(LED, LOW);   // Enciendo LED
    delay(200);                //Espero 200ms
    digitalWrite(LED, HIGH);    // Apago LED*/
    xTaskCreate(TaskLed,"TaskLed",10000,NULL,1,NULL); //Creamos tarea y matamos cuando se haga para encender y apagar el LED
    delay(1000);
  }
  Serial.println("Finalizando tarea escritura aceleración");//Por aquí no puede pasar nunca debido al bucle infinito y 
                                                            //en caso de que lo haga me muestra que se finaliza la tarea
                                                            //y se elimina la función
  vTaskDelete( NULL ); //No se puede salir de un Task mediante un return, sino hay que eliminar el Task.
}

void TaskLed( void * parameter){
 digitalWrite(LED, LOW);   // Enciendo LED
 delay(200);                //Espero 200ms
 digitalWrite(LED, HIGH);    // Apago LED
 vTaskDelete( NULL ); //Maramos la tarea del LED, para solo crearla cada vez que envíe datos por la UART
}
