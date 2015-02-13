import socket
from time import sleep
from random import randint

#UDP_IP = "192.168.1.128"
UDP_IP = "0.0.0.0"
UDP_PORT = 3333
MESSAGE = "<S:%s:%s:%s>"

print "UDP target IP:", UDP_IP
print "UDP target port:", UDP_PORT
print "message:", MESSAGE

sock = socket.socket(socket.AF_INET,  # Internet
                     socket.SOCK_DGRAM)  # UDP


def randval():
    return randint(10, 100)

while (True):
    new_message = MESSAGE % (randval(), randval(), randval())
    for port in range(3000, 4000):
        sock.sendto(new_message, (UDP_IP, port))
        print port

    print "sent " + new_message
    sleep(5)
