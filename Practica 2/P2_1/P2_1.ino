#include <Arduino.h>

//Definimos el pin del LED
#define LED 5

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(LED, OUTPUT);//Inicializamos el LED a encender
  digitalWrite(LED, HIGH);    // Apago LED

  //Creación de ambas tareas. xTaskCreate(param1,param2,param3,param4,param5,param6)
  //param1 = puntero de la funcion que implementa la tarea.
  //param2 = un nombre descriptivo de la tarea. Sólo sirver para debug. 
  //param3 = cada tarea tiene una pila de programa propia en el kernel, este parámetro determina 
    //el tamaño de la pila (en words). El tamaño de la pila para la tareas en reposo se 
    //define mediante al constante de configMINIMAL_STACK_SIZE.
  //param4 = los parametros que necesita la tarea. Si no hay NULL.
  //param5 = define la prioridad de la tarea.
  //param6 = argumentos de la tarea. Si no hay NULL.
  xTaskCreate(Tarea1,"Tarea1",10000,NULL,1,NULL);
  xTaskCreate(Tarea2,"Tarea2",10000,NULL,1,NULL);
}

void loop() {
  //delay(1000);
}


//Descripción de las dos tareas. Las tareas tienen que devolver un void y tener como argumento de entrada
//un puntero void

void Tarea1( void * parameter ){
  for( ;; ){                  //Bucle infinito
    digitalWrite(LED, LOW);   // Enciendo LED
    delay(200);                //Espero 200ms
    digitalWrite(LED, HIGH);    // Apago LED
    delay(1000);               //Pongo un delay de 1s para poder verlo, sino no se aprecia
  }
  Serial.println("Finalizando tarea 1");//Por aquí no puede pasar nunca debido al bucle infinito y 
                                        //en caso de que lo haga me muestra que se finaliza la tarea
                                        //y se elimina la función
  vTaskDelete( NULL ); //No se puede salir de un Task mediante un return, sino hay que eliminar el Task.

}

void Tarea2( void * parameter){
  for( ;; ){                      //Bucle infinito
    Serial.println("Hola mundo"); //Mando Hola mundo por la UART
    delay(1000);                  //Delay de 1s
  }
  Serial.println("Finalizando tarea 2");//Por aquí no puede pasar nunca debido al bucle infinito y 
                                        //en caso de que lo haga me muestra que se finaliza la tarea
                                        //y se elimina la función
  vTaskDelete( NULL );//No se puede salir de un Task mediante un return, sino hay que eliminar el Task.
}
