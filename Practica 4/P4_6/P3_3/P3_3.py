import socket
import sys
# Creo TCP/IP server
tcp_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
 
# Asocio al servidor la dirección y el puerto
server_address = ("192.168.0.180", 456)
tcp_socket.bind(server_address)
 
def main():
    # Escucho en puerto 456
    tcp_socket.listen(1)
     
    while True:
        print("Waiting for connection")
        connection, client = tcp_socket.accept() #Acepto clientes
     
        try:
            print("Connected to client IP: {}".format(client))
             
            # Receive and print data 32 bytes at a time, as long as the client is sending something
            while True:
                data = connection.recv(32).decode() #Recojo datos de 32 bytes en 32 bytes y printeo
                print(sys.getsizeof(data))
                print(data)
                if not data:
                    break
     
        finally:
            connection.close()


if __name__ == '__main__':
	main()
    