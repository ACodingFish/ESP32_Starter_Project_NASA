#Author - Jon
import sys
import os

import socket
import threading

#repeater server

class PI_Server:
    def __init__(self, IP="127.0.0.1", PORT=10000):
        self.tcp_ip = IP
        self.tcp_port = PORT
        self.server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.server.bind((IP,PORT))
        self.client_list = []
        self.MAX_CONN = 20 # max clients
        self.MAX_MSG_SZ = 2048
        self.server.listen(self.MAX_CONN)

        #start listening
        thr = threading.Thread(target=self.Listen_Thread,args=())
        thr.start();

    def Get_Keyboard_Input(self):
        return sys.stdin.readline()
        

    def Listen_Thread(self):
        print("Now Listening on ", self.tcp_ip, " port ", self.tcp_port, ".")
        while True:
            client, addr = self.server.accept()
            self.client_list.append(client)
            #start client thread
            thr = threading.Thread(target=self.Client_Thread,args=(client,addr))
            thr.start();

    def Client_Thread(self, client, addr):
        print("New Connection: ",addr," on port ",self.tcp_port,".")
        connected = True
        while connected:
            try:
                msg = client.recv(self.MAX_MSG_SZ)
                if msg: #if client is still connected
                    msg = msg.decode().strip("\n") + "\n" # this makes sure that there is always one "\n" at the end
                    self.Sent_All_Exclusive(client, msg)
                    print(addr,",",self.tcp_port,":",msg)
                else: #remove client
                    connected = self.Remove_Client(client, addr)
            except ConnectionResetError: #remove client
                connected = self.Remove_Client(client, addr)
                
    def Remove_Client(self, client, addr):
        self.client_list.remove(client)
        print("Client",addr," has disconnected")
        return False
        
    def Send_Msg(self, client, msg):
        if (type(msg) == str):
            msg = msg.encode()
        client.send(msg) #sendall can be used to send entire buffer
        
    def Sent_All_Exclusive(self, source_client, msg): # send to everyone but source
        for client in self.client_list:
            if (client != source_client):
                self.Send_Msg(client, msg)

    def Send_All(self, msg):
        for client in self.client_list:
            self.Send_Msg(client, msg)

if __name__ == '__main__':
    srvr = PI_Server('127.0.0.1', 10000)
    while True:
        msg = srvr.Get_Keyboard_Input()
        if (msg == "quit"):
            os._exit(0)
        else:
            srvr.Send_All(msg)
