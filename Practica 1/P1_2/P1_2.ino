// Potenciometro conectado a  GPIO 34 (Analog ADC1_CH6) 
const int potPin = 34;

//Contador para la interrupción. Se define volatile para evitar la eliminación por parte del compilador 
//al compartirse por dos ciclos
volatile int counter;

// variable para almacenar valor de potenciometro
float potVal = 0;
float potValor = 0;

//Para configurar el temporizador necesario un puntero a este tipo de variable
hw_timer_t * tempo = NULL;

//Para la sincronización entre el bucle principal y el de ISR(interrupt service routine)
portMUX_TYPE tempoMux = portMUX_INITIALIZER_UNLOCKED;
 
void IRAM_ATTR ftemp() {
  // debe tener el atributo IRAM_ATTR para que el compilador coloque el código en la RAM interna
  //Como variable counter compartida con el bucle principal el aumento se hará dentro de una sección crítica
  portENTER_CRITICAL_ISR(&tempoMux);
  counter++; //Indica al bucle principal que ha ocurrido una interrupción
  portEXIT_CRITICAL_ISR(&tempoMux);
 
}
 
void setup() {
  Serial.begin(115200);
  analogSetPinAttenuation(potPin,ADC_11db);// Es la atenuación correspondiente para una entrada de 3.3V
  
  //Correspondiente a la interrupción
  tempo = timerBegin(0, 80, true); //inicialización del temporizador. 
                                   //Primero se mete el número del temporizador a utilizar
                                   //el valor del preescalado. La frecuencia de ESP32 es 80 MHz si ponemos preescaler de 80 
                                   //el contador del temporizador incrementará 1 000 000 veces por segundo. Inviertiendo
                                   //se sabe que el contador se incrementará a cada microsegundo.
                                   //el flag que indica si contar hacia arriba o abajo, true hacia arriba y false hacia abajo
  timerAttachInterrupt(tempo, &ftemp, true);//vinculación del temporizador a una función de manejo
                                            //primero se mete la varibale global
                                            //la dirección de la función de manejo
                                            //true(interrución edge triggered) o false (interrupción de level triggered)
                                            //Edge triggered: El circuito se activa en el flanco negativo o positivo de la señal del reloj.
                                            //Level triggered: El circuito se activará cuando el impulso de reloj o activación esté en un nivel particular.
  timerAlarmWrite(tempo, 10000000, true);//Para indicar la frecuencia de interrupciones
                                         //variable global
                                         //el valor teniendo en cuenta el prescaler
                                         //flag para indiciar si se vuelve a cargar el contardor cuando
                                         //se dispara una interrupción(true) o no(false)
  timerAlarmEnable(tempo);//habilitamos el temporizador pasando la variable como entrada
}
 
void loop() {
 
  if (counter > 0) {
    //Como variable counter compartida con el ISR el decrementar se hará dentro de una sección crítica
    portENTER_CRITICAL(&tempoMux);
    counter--; //Decrementamos para indicar que la interrupción ha sido reconocida y se va a manejar
    portEXIT_CRITICAL(&tempoMux);
    
    //Acciones a realizar cada vez que ocurra la interrupción
    potVal = analogRead(potPin); //Leo el puerto analógico del potenciómetro
    potValor = potVal * (3.3/4095); // Conversión referente al ADC (4095 porque cogemos todo el rango al tener la attenuación de 11dB)
    Serial.println(potValor);//Muestro el valor por el monitor serie
  }
}
