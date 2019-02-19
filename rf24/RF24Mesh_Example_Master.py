#!/usr/bin/env python3

from RF24 import *
from RF24Network import *
from RF24Mesh import *

from struct import unpack
import requests


# radio setup for RPi B Rev2: CS0=Pin 24
radio = RF24(17,0)
network = RF24Network(radio)
mesh = RF24Mesh(radio, network)

mesh.setNodeID(0)
mesh.begin()
radio.setPALevel(RF24_PA_MAX) # Power Amplifier
radio.printDetails()


def post_to_openhab(data_dict):
    for key in data_dict:
        url = 'http://localhost:8080/rest/items/%s/state' %key
        data = data_dict[key]
        headers = {"Content-Type": "text/plain"}
        
        r = requests.put(url, headers=headers, data = data)
        print(r.status_code)
        

while 1:
    mesh.update()
    mesh.DHCP()

    while network.available():
        receivedMessage = []
        header, payload = network.read(500)
        # print(payload)
        if chr(header.type) == 'M':
            print("Rcv {} from 0{:o}".format(unpack("L",payload)[0], header.from_node))
            
        elif chr(header.type) == 'I':
            # print("Received: " + str(payload))
            data_list = str(payload).split('|')
            # print(data_list)
            data_dict = {}
            for itm in data_list:
                itm_lst = itm.split(":")
                data_dict[itm_lst[0]] = itm_lst[1]
                
            print(data_dict)
            post_to_openhab(data_dict)
            
        else:
            print("Rcv bad type {} from 0{:o}".format(header.type,header.from_node));
