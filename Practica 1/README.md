# Práctica 1
Los objetivos de esta práctica son:
	- Familiarizarse con el sistema de desarrollo ESP32
	- Manejar los periféricos típicos de cualquier microcontrolador: ADC, PWM, Timer...
En esta práctica hay 5 puntos a desarrollar, cada uno se encuentra guardado en la carpeta "P1_X", donde X indica el punto correspondiente. 
P1_1: Se trata de leer un valor ADC con una periodicidad de un segundo y mostrarlo por consola.
P1_2: Se trata de leer un valor ADC con una periodicidad de 10 segundos utilizando los timer hardware.
P1_3: Se trata de crear una salida PWM a 5 kHz proporcional a la lectura del ADC.
P1_4: Se trata de comandar por la UART los periféricos mendiante un protocolo tal que si mandas:
	- ADC: Envía lectura ADC
	- ADC(x): Envía lectura ADC cada x segundos mediante timer hardware
	- PWM(x): comanda el duty cycle del módulo PWM con números del 0 al 9
P1_5: Se trata de conectar un sensor por I2C o SPI, mostrar la aceleración cada 100 ms y mandar los datos cada segundo vía UART(cada vez que se encía se enciendo un LED 200ms).
