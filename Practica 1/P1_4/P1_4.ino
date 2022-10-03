#include <HardwareSerial.h>


// Potenciometro conectado a GPIO 34 (Analog ADC1_CH6) 
const int potPin = 34;

// variable para almacenar valor de potenciometro
float potVal = 0;
float potValor = 0;
char dato[];

void setup() {
  Serial.begin(115200);
  
  SerialPort.begin(115200,SERIAL_8N1,3,1);//Inicializamos puertos UART
  
  analogSetPinAttenuation(potPin,ADC_11db);// Es la atenuación correspondiente para una entrada de 3.3V
}

void loop(){
  if (SerialPort.available()){
    dato = SerialPort.read();
    
  }
  potVal = analogRead(potPin); //Leo el puerto analógico del potenciómetro
  potValor = potVal * (3.3/4095); // Conversión referente al ADC (4095 porque cogemos todo el rango al tener la attenuación de 11dB)
  
  //Serial.println(potValor);//Muestro el valor por el monitor serie
  
}
