// Potenciometro conectado a GPIO 34 (Analog ADC1_CH6) 
const int potPin = 34;

//Pin del LED para comprobar el correcto funcionamiento del PWM
const int LED = 5;

//Propiedades del PWM
const int frecuencia = 5000;
const int canal = 0; //Canales disponibles del 0 al 15
const int resolucion = 8; //de 8 bits de 0 a 255

// variable para almacenar valor de potenciometro
int potVal = 0;
int potValor = 0;

void setup() {
  Serial.begin(115200);
  ledcSetup(canal, frecuencia, resolucion); //Se configura la funcionalidad PWM
  ledcAttachPin(LED,canal); //Asociamos el canal al puerto del LED
}

void loop(){
  
  potVal = analogRead(potPin); //Leo el puerto analógico del potenciómetro
  
  potValor = map(potVal, 0, 4095, 0, 255); //mapeo el rango 0-4095 a 0-255);
  Serial.println(potVal);
  ledcWrite(canal,potValor);
  delay(2000); //Esperamos dos segundos
  
  //Serial.println(potValor);//Muestro el valor por el monitor serie
  
}
