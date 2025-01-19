from socket import socket, AF_INET, SOCK_DGRAM

# Creates a socket
s = socket(AF_INET, SOCK_DGRAM)

# Adds destination ip and destination port
dst_ip = '127.0.0.1'
dst_port = 12345

# Sends hello from the client to the server at specified id and port
s.sendto(b'Hello', (dst_ip,dst_port))

# Receive information back from the server
data, sender_info = s.recvfrom(2048)
# Print the data sent back from the server as well as the socket info.
print(data.decode('utf-8'))
print(sender_info)

# Close the socket
s.close()