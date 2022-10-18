import serial
  
def main():
    
    print("Comienza el programa")
    try:
        ser = serial.Serial("COM7", 115200) #Abro el puerto serie
        while True: 
            ser.flushInput() #Limpio el buffer, sobre todo para cuando escribamos en fichero
            try:
                acel = ser.readline().decode('ascii') #Leo una linea completa y decodifico para que se muestre el string
                print(acel) #Muestro por pantalla los datos leidos
            except serial.SerialException: #En caso de no poder acceder a leer los datos del puerto seria saltará una excepción
                print("No se pueden leer los datos")     
                ser.close()#Cerraremos el puerto serie
    except serial.SerialException:#Si no se puede acceder al puerto seria saltará una excepción
        print("No está conectado el puerto")
    
        
if __name__ == '__main__':
	main()
