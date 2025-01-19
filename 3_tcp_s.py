import socket

# same as 1_udp_s
server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server_ip = ''
server_port = 12345
server.bind((server_ip, server_port))
# get ready to accept clients, up to 5.
server.listen(5)

# loop to keep the server up
while True:
    # server accepts client
    client_socket, client_address = server.accept()
    # print who connected
    print('Connection from: ', client_address)
    # get data
    data = client_socket.recv(1024)
    # while data not empty string keep printing input
    while not data.decode('utf-8') == '':
        print('Received: ', data.decode('utf-8'))
        # turn to upper
        client_socket.send(data.upper())
        # input to data
        data = client_socket.recv(1024)

    print('Client disconnected')
    client_socket.close()