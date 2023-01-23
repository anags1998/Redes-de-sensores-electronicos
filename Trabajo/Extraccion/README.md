# EXTRACCION DE DATOS
Para la extraccion de datos, se ha optado por la creación de ficheros en un servidor FTP, donde cada fichero se identfica con el nombre de la fecha en la cual ha sido creado, y los datos que contiene son los captados por el sensor durante 30 segundos, es decir, 4 repeticiones del paso correspondiente.

Cada dato capturado por el sensor es escrito en el fichero con el instante temporal de ejecucion al inicio de la linea. Se captan, tanto los datos del acelerometro como los del giroscopio de los tres ejes (X, Y y Z). Estos datos se escriben en el fichero separados por ";" para despues poder leerlos desde excel.

La imagen muestra el diagrama que sigue el codigo creado para la extraccion de los datos. Cabe mencionar que se recopilan datos cada 20ms, es decir, se muestrea a 50 Hz. Y como se observa en el diagrama, se recopilan datos durante 30s, por lo tanto se obtienen un total de 1500 muestras por cada fichero.

Se ha decidido que cada individuo por paso realizado cree dos ficheros en el servidor, es decir, en total se realizaran 8 repeticiones de cada paso y por cada uno de los cuatro sujetos que forman la base de datos. Por lo tanto, en la base de datos dispondremos de 8 ficheros por paso y un total de 72 ficheros para todos los pasos que se quieren reconocer.
![extraccion drawio (1)](https://user-images.githubusercontent.com/113996288/212017354-ff5faca5-46cc-46e0-921e-405ba425d3da.png)
