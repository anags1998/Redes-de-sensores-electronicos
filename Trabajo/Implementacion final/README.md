# IMPLEMENTACION FINAL
En cuanto a la implementacion final del trabajo, se ha optado por un sistema activado por la pulsacion de un boton del ESP-32. 

Una vez pulsado el boton se lee los datos del sensor durante 10s, para poder dar tiempo a realizar el paso correctamente. 

Con los datos almacenados en diferentes variables se realizan calculos de cuatro parametros estadisticos de todas las señales para despues realizar la identificacion del paso realizado en funcion de estos.

Finalmente, obtenida la determinacion del paso se envia dicho dato a un servidor web creado en la ESP-32, donde veremos el paso realizado.

A continuacion, se muestra el diagrama del sistema y unas capturas de la web detectando los diferentes tipos de pasos.
![final drawio (2)](https://user-images.githubusercontent.com/113996288/214508842-822cb156-8736-40be-8540-bdec69f7f7a4.png)
1. Pagina web al inicio:
![web_inicio](https://user-images.githubusercontent.com/113996288/214518364-8a719c57-f069-457c-9c6f-dbd6326af6e4.png)
2. Pagina web detectando Demi-Plie:
![web_dp](https://user-images.githubusercontent.com/113996288/214518472-5d1ce6a6-a2ac-4d94-96cb-4912c467da86.png)
3. Pagina web detectando Releve:
![web_r](https://user-images.githubusercontent.com/113996288/214518551-b86b7f75-9a2d-4aac-bd37-1046c6448fe2.png)
4. Pagina web detectando Saute:
![web_s](https://user-images.githubusercontent.com/113996288/214518868-9cc2d6b0-f000-4d85-a6f6-841c6b2b2d06.png)
5. Pagina web detectando Arabesque:
![web_a](https://user-images.githubusercontent.com/113996288/214518921-fff7286c-8546-4fdb-8b60-a7731726d1a7.png)
6. Pagina web con paso indeterminado:
![web_inder](https://user-images.githubusercontent.com/113996288/214518958-3bf82564-ed88-4a70-b2a2-391de6040b34.png)
