# Práctica 3
Los objetivos de esta práctica son: Familiarizarse con Phyton como lenguaje de programación, gestionar datos procedentes de comunicaciones serie, trabajar con estos datos en formato csv y json para almacenarlos en ficheros y redireccionarlos vía internet y operar con los datos y representarlos gráficamente.

En esta práctica hay 3 puntos a desarrollar, partiendo de la anterior práctica en la que se conecta un sensor inercial por I2C (o SPI), muestrea la aceleración y manda los datos vía UART cada 50 ms al PC. Cada uno se encuentra guardado en la carpeta "P3_X", donde X indica el punto correspondiente. 

P3_1: Se trata de creat un programa en Phyton que acceda al puerto serie y muestre por pantalla los datos en tiempo real(igual que el terminal).

P3_2: Se trata de modificar el programa para que almacene los datos en fichero .txt separando cada vaiable con ";" y con retorno de carro al final de cada muestra para abrirlo desde excel.

P3_3: Se trata de modificar el programa para que acumule los datos durante 5s, calculo el promedio y desviación estandar y los represente en tiempo real. 