# ANALISIS DE DATOS
Para el analisis de datos como ya se mencionó, se han recopilado los datos de cuatro personas distintas. Esto se encuentra almacenado en la carpeta "Datos_en_crudo".

Posteriormente se ha creado un programa que permite obtener las señales de aceleracion y velocidad angular de los tres ejes (x, y, z) de cada uno de los archivos, ademas de la media, mediana, varianza y desviacion de cada una de ellas. Estos ultimos calculos estadisticos se almacenan despues en un fichero "datos.txt" para poder analizarlo, ademas de graficarse tambien. Todo esto se encuentra almacenado en la carpeta "Analisis_datos".

De todos los datos obtenidos y de los algoritmos probados, se ha determinado que la diferenciacion de los nueve pasos propuestos necesita algoritmos mucho mas robustos. Por lo tanto, se han decidido determinar cuatro pasos (Demi-Plie, Saute, Releve y Arabesque). Se han elegido estos, ya que son los que se obtienen parametros estadisticos mas dispares y por lo tanto facilita el uso de un algoritmo menos robusto. 

Se ha concluido que de todos ellos los parametros que mas informacion nos dan son la varianza y la desviacion de cada señal obtenida. En consecuencia, se han realizado pruebas más concretas con el codigo final del trabajo para poder determinar el rango exacto de cada uno de los parametros para la diferenciacion de los pasos.

A continuacion se muestran un par de graficas obtenidas por cada tipo de dato, la primera muentra las señales de cada uno de los ejes de la aceleracion y la velocidad angular, y la segunda muestra los parametros estadisticos calculados. Se puede observar en estas graficas como otra manera de diferenciar el paso realizado seria mirar directamente las graficas, pero se ha descartado dicha opcion por necesidad del usuario de conocer las graficas resultantes.

1. Demi-Plie
![Monday,January_23_2023_09_15_48_señales](https://user-images.githubusercontent.com/113996288/214261668-2ef25bf1-cc7f-4666-90b1-0171b014ece0.jpg)
![Monday,January_23_2023_09_15_48_calculos_estadiscticos](https://user-images.githubusercontent.com/113996288/214261680-7b0871a8-7175-4b50-89c7-a89237a863d0.jpg)
2. Grand-Plie
![Monday,January_23_2023_09_16_30_señales](https://user-images.githubusercontent.com/113996288/214261714-dd4d9dfa-a4b3-4246-aae0-4e20577332eb.jpg)
![Monday,January_23_2023_09_16_30_calculos_estadiscticos](https://user-images.githubusercontent.com/113996288/214261733-3d97d6b7-48b3-451a-af3d-5ce7e9c0476e.jpg)
3. Saute
![Monday,January_23_2023_09_18_19_señales](https://user-images.githubusercontent.com/113996288/214261788-367295fa-a1f1-4229-a97e-583e14e7c70d.jpg)
![Monday,January_23_2023_09_18_19_calculos_estadiscticos](https://user-images.githubusercontent.com/113996288/214261802-e53bc191-170b-4027-bdeb-400d11572553.jpg)
4. Releve
![Monday,January_23_2023_09_39_02_señales](https://user-images.githubusercontent.com/113996288/214261859-54cd11bc-3ebc-476a-901f-e1e7af77efd1.jpg)
![Monday,January_23_2023_09_39_02_calculos_estadiscticos](https://user-images.githubusercontent.com/113996288/214261877-ae61869a-727c-4711-93bd-9f05cab6c860.jpg)
5. Penche
![Monday,January_23_2023_09_43_10_señales](https://user-images.githubusercontent.com/113996288/214262107-cc035470-0b4c-4c08-a691-b0d995c918aa.jpg)
![Monday,January_23_2023_09_43_10_calculos_estadiscticos](https://user-images.githubusercontent.com/113996288/214262116-9f0ed548-3b50-4ff5-bb6b-cb80897416b8.jpg)
6. Arabesque
![Monday,January_23_2023_09_45_22_señales](https://user-images.githubusercontent.com/113996288/214262176-2404e4c0-c263-43fc-a42b-0c51ff88cb41.jpg)
![Monday,January_23_2023_09_45_22_calculos_estadiscticos](https://user-images.githubusercontent.com/113996288/214262187-0ab57df4-08ec-4bd6-85d2-27be56389cb2.jpg)
7. Tendu
![Monday,January_23_2023_09_48_06_señales](https://user-images.githubusercontent.com/113996288/214262223-4af86759-7e1e-4f6c-a505-16e0de6b896c.jpg)
![Monday,January_23_2023_09_48_06_calculos_estadiscticos](https://user-images.githubusercontent.com/113996288/214262234-182e8944-a63e-44c1-ba85-79582ee8bc0e.jpg)
8. Developpe
![Monday,January_23_2023_09_49_40_señales](https://user-images.githubusercontent.com/113996288/214262254-46281d2d-a33a-4a3d-b031-8cbd7275a3a7.jpg)
![Monday,January_23_2023_09_49_40_calculos_estadiscticos](https://user-images.githubusercontent.com/113996288/214262275-f957b845-57c2-4b2b-9399-9f7046c8962a.jpg)
9. Pirouette
![Monday,January_23_2023_09_59_33_señales](https://user-images.githubusercontent.com/113996288/214262306-b4eeb70f-caa2-42cd-bd04-29dda031d0b2.jpg)
![Monday,January_23_2023_09_59_33_calculos_estadiscticos](https://user-images.githubusercontent.com/113996288/214262322-880a0f1a-d938-4272-98ed-c4dcdbca6f83.jpg)
