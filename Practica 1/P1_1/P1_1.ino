// Potenciometro conectado a  GPIO 34 (Analog ADC1_CH6) 
const int potPin = 34;

// variable para almacenar valor de potenciometro
float potVal = 0;
float potValor = 0;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  analogSetPinAttenuation(potPin,ADC_11db);// Establece la atenuación de entrada para el pin especificado.Es la atenuación correspondiente para un rango de 3.3V
}

void loop() {
  // put your main code here, to run repeatedly:
  potVal = analogRead(potPin); //Leo el puerto analógico del potenciómetro
  potValor = potVal * (3.3/4095); // Conversión referente al ADC (4095 porque cogemos todo el rango al tener la attenuación de 11dB)
  Serial.println(potValor);//Muestro el valor por el monitor serie
  delay(1000); //Para leer con una diferencia de 1s
}
