# IMPLEMENTACION FINAL
En cuanto a la implementacion final del trabajo, se ha optado por un sistema activado por la pulsacion de un boton del ESP-32. 
Una vez pulsado el boton se lee los datos del sensor durante 10s, para poder dar tiempo a realizar el paso correctamente. 
Con los datos almacenados en diferentes variables se realizan calculos de cuatro parametros estadisticos de todas las señales para despues realizar la identificacion del paso realizado en funcion de estos.
Finalmente, obtenida la determinacion del paso se envia dicho dato a un servidor web creado en la ESP-32, donde veremos el paso realizado.
![final drawio (2)](https://user-images.githubusercontent.com/113996288/214508842-822cb156-8736-40be-8540-bdec69f7f7a4.png)
