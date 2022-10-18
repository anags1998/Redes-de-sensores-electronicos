import serial

import matplotlib.pyplot as plt

import array as ar

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
                if cont < 100:
                    acel = ser.readline().decode('ascii') #Leo una linea completa y decodifico para poder quitar los saltos de linea
                    acel = acel.replace("\n","") #quito salto de linea
                    acel = acel.replace("\r","") #reemplazo retorno de carro por ; y retono de carro   
                    a.append(acel)
                    cont = cont + 1
                else: 
                    #cont = 0
                    for i in range(24):
                        j = 4*i
                        x.append(a[j+1])
                        y.append(a[j+2])
                        z.append(a[j+3])
                        sqrt.append(a[j+4])
                    plt.plot(x)
                        
                        
            except serial.SerialException: #En caso de no poder acceder a leer los datos del puerto seria saltará una excepción
                print("No se pueden leer los datos")     
                ser.close()#Cerraremos el puerto serie
    except serial.SerialException:#Si no se puede acceder al puerto seria saltará una excepción
        print("No está conectado el puerto")
    
        
if __name__ == '__main__':
	main()
    