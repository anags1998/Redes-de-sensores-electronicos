import os
import matplotlib.pyplot as plt
import numpy as geek
import pandas as pd 
import numpy as np
import statistics as stats

directorio = 'C:/Users/anags/OneDrive/Desktop/UNI/cuatri 3/Redes de sensores electronicos/Practicas/Trabajo/Analisis/Datos_en_crudo'
# Loop through matching files and download each one individually
contenido = os.listdir(directorio)

def obtener_mediana(arreglo):
    # Primero lo ordenamos. Puedes hacerlo manualmente o con métodos del lenguaje:
    # https://parzibyte.me/blog/2020/09/25/ordenar-listas-python/
    arreglo.sort()
    # Obtener longitud
    longitud = len(arreglo)
    mitad = int(longitud / 2)
    # Si la longitud es par, promediar elementos centrales
    if longitud % 2 == 0:
        mediana = (arreglo[mitad - 1]+arreglo[mitad]) / 2
    else:
        # Si no, es la del centro
        mediana = arreglo[mitad]
    return mediana


def obtener_media(arreglo):
    # La media es básicamente el promedio
    sumatoria = 0
    for valor in arreglo:
        sumatoria += valor
    longitud = len(arreglo)
    return sumatoria / longitud


def main():
    datos = []
    ax = []
    ay = []
    az = []
    gx = []
    gy = []
    gz = []
    cont= 0;
    for fichero in contenido:
        cont = cont +1
        print("Getting " + fichero)
        with open(fichero) as fname:
        	lineas = fname.readlines()
        	for linea in lineas:
        		datos.append(linea.strip('\n'))
        
        for dato in datos:
            indice = dato.index(":")
            dato = dato [indice+2:]
            indice2 = dato.index(";")
            ax.append(float(dato[:indice2]))
            dato = dato [indice2+1:] 
            indice3 = dato.index(";")
            ay.append(float(dato[:indice3]))
            dato = dato [indice3+1:] 
            indice4= dato.index(";")
            az.append(float(dato[:indice4]))
            dato = dato [indice4+1:] 
            indice5= dato.index(";")
            gx.append(float(dato[:indice5]))
            dato = dato [indice5+1:] 
            indice6= dato.index(";")
            gy.append(float(dato[:indice6]))
            dato = dato [indice6+1:] 
            gz.append(float(dato))
            
        tamaño  = 30*geek.size(ax)/1500;
        tiempo = geek.linspace(0,tamaño,geek.size(ax)) # Creo eje de tiempos para plotear frente a los 
                
        plt.figure(figsize =(16,12)) #Pongo tamaño a la figura
        plt.subplot(3,2,1) #Creación de primera figura
        plt.plot(tiempo, ax,'r--') #r-- indica que pinto en rojo y a rayas
        plt.title("Aceleración eje X") #Pongo titulo a la grafica
        plt.subplot(3,2,2) #Creación segunda figura
        plt.plot(tiempo, ay,'b--') #b-- indica que pinto en azul y a rayas
        plt.title("Aceleración eje Y") #Pongo titulo a la grafica
        plt.subplot(3,2,3) #Creacion tercera figura
        plt.plot(tiempo, az,'g--') #g-- indica que pinto en verde y a rayas
        plt.title("Aceleración eje Z") #Pongo titulo a la grafica
        
        plt.subplot(3,2,4) #Creación de primera figura
        plt.plot(tiempo, gx,'y--') #r-- indica que pinto en rojo y a rayas
        plt.title("Velocidad angular eje X") #Pongo titulo a la grafica
        plt.subplot(3,2,5) #Creación segunda figura
        plt.plot(tiempo, gy,'m--') #b-- indica que pinto en azul y a rayas
        plt.title("Velocidad angular eje Y") #Pongo titulo a la grafica
        plt.subplot(3,2,6) #Creacion tercera figura
        plt.plot(tiempo, gz,'c--') #g-- indica que pinto en verde y a rayas
        plt.title("Velocidad angular eje Z") #Pongo titulo a la grafica
        
        nombre = fichero[:-4] + "_señales.jpg"
        plt.savefig(nombre) #Me lo guardo en un fichero para poder verlo
        plt.show() #La muestro
        
        axmedia = obtener_media(ax)
        aymedia = obtener_media(ay)
        azmedia = obtener_media(az)
        gxmedia = obtener_media(gx)
        gymedia = obtener_media(gy)
        gzmedia = obtener_media(gz)
        
        axmediana = obtener_mediana(ax)
        aymediana = obtener_mediana(ay)
        azmediana = obtener_mediana(az)
        gxmediana = obtener_mediana(gx)
        gymediana = obtener_mediana(gy)
        gzmediana = obtener_mediana(gz)
        
        axvarianza = stats.pvariance(ax)
        ayvarianza = stats.pvariance(ay)
        azvarianza = stats.pvariance(az)
        gxvarianza = stats.pvariance(gx)
        gyvarianza = stats.pvariance(gy)
        gzvarianza = stats.pvariance(gz)
        
        axdesv = stats.pstdev(ax)
        aydesv = stats.pstdev(ay)
        azdesv = stats.pstdev(az)
        gxdesv = stats.pstdev(gx)
        gydesv = stats.pstdev(gy)
        gzdesv = stats.pstdev(gz)
        
        datosmedia = [axmedia,aymedia,azmedia,gxmedia,gymedia,gzmedia]
        
        datosmediana = [axmediana,aymediana,azmediana,gxmediana,gymediana,gzmediana]
        
        datosvarianza = [axvarianza,ayvarianza,azvarianza,gxvarianza,gyvarianza,gzvarianza]
        
        datosdesv = [axdesv,aydesv,azdesv,gxdesv,gydesv,gzdesv]
        
        with open ("datos.txt","a") as f:
           f.write(fichero[:-4] + '\n')
           f.write("Media: " + str(datosmedia)+'\n')
           f.write("Mediana: " + str(datosmediana)+'\n')
           f.write("Varianza: " + str(datosvarianza)+'\n')
           f.write("Desviacion: " + str(datosdesv)+'\n')
        f.close()
        
        dataa = pd.DataFrame({'Media' : [axmedia, aymedia, azmedia],
                     'Mediana': [axmediana, aymediana, azmediana],
                     'Varianza': [axvarianza, ayvarianza, azvarianza],
                     'Desviacion': [axdesv, aydesv, azdesv]},
                    index=('ax', 'ay', 'az'))
        
        datag = pd.DataFrame({'Media' : [ gxmedia, gymedia, gzmedia],
                     'Mediana': [ gxmediana, gymediana, gzmediana],
                     'Varianza': [gxvarianza, gyvarianza, gzvarianza],
                     'Desviacion': [axdesv, aydesv, azdesv]},
                    index=('gx', 'gy', 'gz'))
        
        n = len(dataa.index)
        x = np.arange(n)
        width = 0.25
        
        plt.figure(figsize =(16,12)) #Pongo tamaño a la figura
        plt.subplot(3,2,1)
        plt.bar(x - width, dataa.Media, width=width, label='Media',color = 'pink')
        plt.bar(x, dataa.Mediana, width=width, label='Mediana',color = 'aquamarine')
        plt.xticks(x, dataa.index)
        plt.legend(loc='best')
        plt.title("Aceleracion") #Pongo titulo a la grafica
       
        plt.subplot(3,2,2)
        plt.bar(x - width, datag.Media, width=width, label='Media',color = 'pink')
        plt.bar(x, datag.Mediana, width=width, label='Mediana',color = 'aquamarine')
        plt.xticks(x, datag.index)
        plt.legend(loc='best')
        plt.title("Velocidad angular") #Pongo titulo a la grafica
        
        plt.subplot(3,2,3)
        plt.bar(x - width, dataa.Desviacion, width=width, label='Desviacion',color = 'plum')
        plt.bar(x, dataa.Varianza, width=width, label='Varianza',color = 'salmon')
        plt.xticks(x, dataa.index)
        plt.legend(loc='best')
        plt.title("Aceleracion") #Pongo titulo a la grafica
       
        plt.subplot(3,2,4)
        plt.bar(x, datag.Varianza, width=width, label='Varianza',color = 'salmon')
        plt.xticks(x, datag.index)
        plt.legend(loc='best')
        plt.title("Velocidad angular") #Pongo titulo a la grafica
       
        plt.subplot(3,2,6)
        plt.bar(x, datag.Desviacion, width=width, label='Desviacion',color = 'plum')
        plt.xticks(x, datag.index)
        plt.legend(loc='best')
        plt.title("Velocidad angular") #Pongo titulo a la grafica
        
        nombre = fichero[:-4] + "_calculos_estadiscticos.jpg"
        plt.savefig(nombre) #Me lo guardo en un fichero para poder verlo
        plt.show()
        
        datos = []
        ax = []
        ay = []
        az = []
        gx = []
        gy = []
        gz = [] 
        fname.close()
        
if __name__ == '__main__':
	main()
    