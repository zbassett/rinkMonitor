FROM frankwolf/rpi-python3

RUN wget http://tmrh20.github.io/RF24Installer/RPi/install.sh
RUN chmod +x install.sh 
RUN ./install.sh 

RUN git clone https://github.com/haseebehsan/RF24Python

RUN cd ./RF24Python/pyRF24/pyRF24
RUN python setup.py install

RUN cd ../pyRF24Network
RUN python setup.py install

RUN cd ../pyRF24Mesh
RUN python setup.py install