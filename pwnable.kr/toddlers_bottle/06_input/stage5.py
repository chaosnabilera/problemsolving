import socket
import sys

sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
sock.connect(('127.0.0.1',int(sys.argv[1])))
sock.sendall("\xde\xad\xbe\xef")
sock.close()