from socket import socket, AF_INET, SOCK_DGRAM
# Create socket
s = socket(AF_INET, SOCK_DGRAM)

# binds the socket to available network interfaces on system
src_ip = ''
src_port = 12345
s.bind((src_ip, src_port))

while True:
    data, sender_info = s.recvfrom(2048)
    # Prints data received from client
    print(data.decode('utf-8'))
    # Prints the message sent from client
    print(sender_info)

    # Sends respone to Client
    s.sendto(data.upper(), sender_info)