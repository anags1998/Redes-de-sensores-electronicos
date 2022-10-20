import serial
import matplotlib.pyplot as plt


a = []
x = []
y = []
z = []
sqrt = []

def main():
    
    print("Comienza el programa")
    try:
        ser = serial.Serial("COM7", 115200) #Abro el puerto serie
        cont = 0
        while True: 
            ser.flushInput() #Limpio el buffer, sobre todo para cuando escribamos en fichero
            try:
                if cont < 101: #para conseguir cada 5 segundos
                    acel = ser.readline().decode('ascii') #Leo una linea completa y decodifico para poder quitar los saltos de linea
                    acel = acel.replace("\n","") #quito salto de linea
                    acel = acel.replace("\r","") #reemplazo retorno de carro 
                    with open ("datos.txt","a") as f:
                        f.write(acel)
                    a.append(acel)
                    cont = cont + 1
                else: 
                    
                    cont = 0
                    for i in range(25): #Serapo las aceleraciones de todos los ejes
                        j = 4*i
                        x.append(a[j+1]) 
                        y.append(a[j+2])
                        z.append(a[j+3])
                        sqrt.append(a[j+4])
                    plt.figure(figsize =(16,12)) #Pongo tamaño a la figura
                    plt.subplot(2,2,1) #Creación de primera figura
                    plt.plot(x,'ro--') #ro-- indica que pinto en rojo con puntos y a rayas
                    plt.title("Aceleración eje X") #Pongo titulo a la grafica
                    plt.subplot(2,2,2) #Creación segunda figura
                    plt.plot(y,'bo--') #bo-- indica que pinto en azul con puntos y a rayas
                    plt.title("Aceleración eje Y") #Pongo titulo a la grafica
                    plt.subplot(2,2,3) #Creacion tercera figura
                    plt.plot(z,'go--') #go-- indica que pinto en verde con puntos y a rayas
                    plt.title("Aceleración eje Z") #Pongo titulo a la grafica
                    plt.subplot(2,2,4) #Creación cuarta figura
                    plt.plot(sqrt,'yo--') #yo-- indica que pinto en amarillo con puntos y a rayas
                    plt.title("Aceleración SQRT") #Pongo titulo a la grafica
                    
                    plt.savefig("Aceleración.jpg") #Me lo guardo en un fichero para poder verlo
                    plt.show() #La muestro
                        
            except serial.SerialException: #En caso de no poder acceder a leer los datos del puerto seria saltará una excepción
                print("No se pueden leer los datos")     
                ser.close()#Cerraremos el puerto serie
    except serial.SerialException:#Si no se puede acceder al puerto seria saltará una excepción
        print("No está conectado el puerto")
    
        
if __name__ == '__main__':
	main()
    