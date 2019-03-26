#!/usr/bin/env python3

from RF24 import *
from RF24Network import *
from RF24Mesh import *

from struct import unpack
import requests


# radio setup for RPi B Rev2: CS0=Pin 24
radio = RF24(RPI_V2_GPIO_P1_15, RPI_V2_GPIO_P1_24, BCM2835_SPI_SPEED_8MHZ)
network = RF24Network(radio)
mesh = RF24Mesh(radio, network)

mesh.setNodeID(0)
mesh.begin()
radio.setPALevel(RF24_PA_MAX) # Power Amplifier
radio.printDetails()


def post_to_homeassistant(data_dict):
    for key in data_dict:
        url = 'http://flask_app:5555/sensors/%s' %key
        data = data_dict[key]
        headers = {"Content-Type": "text/plain"}
        
        r = requests.put(url, headers=headers, data = data)
        print(r.status_code)
        

while 1:
    mesh.update()
    mesh.DHCP()

    while network.available():
        header, payload = network.read(300)
        if chr(header.type) == 'M':
            print("Rcv {} from 0{:o}".format(unpack("L",payload)[0], header.from_node))
        elif chr(header.type) == 'I':
            try:
                print("Received: " + payload.decode())
                data_list = payload.decode().split('|')
                # print(data_list)
                data_dict = {}
                for itm in data_list:
                    itm_lst = itm.split(":")
                    data_dict[itm_lst[0]] = itm_lst[1]

                print(data_dict)
                try:
                    post_to_homeassistant(data_dict)
                except:
                    print('problem with posting to home assistant.')
            except:
                print('received bad "I" payload')
        else:
            print("Rcv bad type {} from 0{:o}".format(header.type,header.from_node));