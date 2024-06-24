#import socket module
from socket import *
serverSocket = socket(AF_INET, SOCK_STREAM)
#Prepare a sever socket
serverPort = 12000
serverSocket.bind(('',serverPort))
serverSocket.listen(1)
while True:
    #Establish the connection
    print('Ready to serve...')
    connectionSocket, addr = serverSocket.accept()
    try:
        message = connectionSocket.recv(1024).decode()
        filename = message.split()[1]
        f = open(filename[1:])
        outputdata = f.read()
        #Send one HTTP header line into socket
        headers = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n"
        headers += "Content-Length: %d\r\n" % len(outputdata)
        headers += "\r\n"
        connectionSocket.send(headers.encode())
        #Send the content of the requested file to the client
        for i in range(0, len(outputdata)):
            connectionSocket.send(outputdata[i].encode())
        connectionSocket.send("\r\n".encode())
        connectionSocket.close()
    except IOError:
        #Send response message for file not found
        errorMessage_header = "HTTP/1.1 404 Not Found\r\n"
        errorMessage_header += "Content-Type: text/html; charset=UTF-8\r\n"
        errorMessage_header += "\r\n"
        errorMessage_body = "<html><body><hl>404 Not Found</h1></body></html>"
        connectionSocket.send((errorMessage_header + errorMessage_body).encode())
        #Close client socket
        connectionSocket.close()
serverSocket.close()
sys.exit()#Terminate the program after sending the corresponding data