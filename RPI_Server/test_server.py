#!/usr/bin/env python3
#Author - Jon

import os
from PI_Server import *

HOST = 'xxx.xxx.xxx.xxx'
PORT = 10000

srvr = PI_Server(HOST,PORT)

while True:
        msg = srvr.Get_Keyboard_Input()
        if ("quit" in msg.lower()):
            os._exit(0)
        else:
            srvr.Send_All(msg)
