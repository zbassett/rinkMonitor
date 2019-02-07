FROM frankwolf/rpi-python3

RUN apt-get update
RUN apt-get install -y make
RUN apt-get install -y gcc
RUN apt-get install -y libxslt-dev libxml2-dev
RUN apt-get install -y wget git-core

RUN apt-get install python-setuptools 

# RUN wget http://tmrh20.github.io/RF24Installer/RPi/install.sh
# RUN chmod +x install.sh 
# RUN ./install.sh 

RUN apt-get install python-dev libboost-python-dev 
RUN ln -s /usr/lib/arm-linux-gnueabihf/libboost_python-py34.so /usr/lib/arm-linux-gnueabihf/libboost_python3.so

RUN git clone https://github.com/nRF24/RF24.git

WORKDIR ./RF24

RUN echo $(ls .)

RUN make
RUN make install

# RUN cd ./pyRF24 && make
# run cd ./pyRF24 && make install

# RUN cd pyRF24 && python ./setup.py build
# RUN make install

RUN cd ./pyRF24 && python setup.py build
RUN cd ./pyRF24 && python setup.py install

RUN cd ./pyRF24/pyRF24Network && python setup.py install

RUN cd ./pyRF24/pyRF24Mesh && python setup.py install