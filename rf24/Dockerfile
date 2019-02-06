FROM frankwolf/rpi-python3

# RUN wget http://tmrh20.github.io/RF24Installer/RPi/install.sh
# RUN chmod +x install.sh 
# RUN ./install.sh 

RUN ln -s /usr/lib/arm-linux-gnueabihf/libboost_python-py34.so /usr/lib/arm-linux-gnueabihf/libboost_python3.so

RUN git clone https://github.com/nRF24/RF24.git

WORKDIR ./nRF24

RUN make
RUN make install

RUN cd ./pyRF24 && python setup.py install

RUN cd ./pyRF24/pyRF24Network && python setup.py install

RUN cd ./pyRF24/pyRF24Mesh && python setup.py install