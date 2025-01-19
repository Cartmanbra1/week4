import socket

# Create a socket
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
# Add IP and Port to connect to
dest_ip = '127.0.0.1'
dest_port = 12345
s.connect((dest_ip, dest_port))

# message to the server
msg = input("Message to send: ")
# loop to talk to the server until input 'quit'
while not msg == 'quit':
    # send to server
    s.send(bytes(msg, 'utf-8'))
    # receive data from server
    data = s.recv(4096)
    # print the dataS
    print("Server sent: ", data.decode('utf-8'))
    msg = input("Message to send: ")

s.close()