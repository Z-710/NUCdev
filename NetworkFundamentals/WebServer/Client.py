from socket import *
serverName = '172.20.160.1'
serverPort = 12000
clientSocket = socket(AF_INET, SOCK_STREAM)
clientSocket.connect((serverName, serverPort))
sentence = input('Input filename:')
clientSocket.send(sentence.encode())
while True:
    serverOutput = clientSocket.recv(1024)
    if not serverOutput:
        break
    print(serverOutput.decode())
clientSocket.close()