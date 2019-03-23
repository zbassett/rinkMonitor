FROM arm32v7/python:3.7-stretch

RUN apt-get update
# RUN apt-get upgrade
RUN apt-get install -y make cmake gcc
RUN apt-get install -y libxslt-dev libxml2-dev
RUN apt-get install -y wget git-core

RUN apt-get install -y python-setuptools 
#libncurses5-dev

# RUN wget http://tmrh20.github.io/RF24Installer/RPi/install.sh
# RUN chmod +x install.sh 
# RUN ./install.sh 

WORKDIR /tmp

#install BCM2835 library
# RUN wget http://www.airspayce.com/mikem/bcm2835/bcm2835-1.58.tar.gz
# RUN tar zxvf bcm2835-1.58.tar.gz
# WORKDIR ./bcm2835-1.58
# RUN ./configure && make && make check && make install

RUN apt-get install -y python-dev libboost-python-dev gcc mono-mcs g++
RUN ln -s /usr/lib/arm-linux-gnueabihf/libboost_python-py35.so /usr/lib/arm-linux-gnueabihf/libboost_python3.so

RUN git clone https://github.com/intel-iot-devkit/mraa.git && \
    cd mraa && \
    mkdir build && \
    cd build && \
    cmake .. -DBUILDSWIGNODE=OFF && \
    make install
    
WORKDIR /tmp
    
COPY install.sh /tmp
RUN chmod +x /tmp/install.sh
RUN /tmp/install.sh

# install RF24 Python libraries
RUN cd /tmp/rf24libs/RF24/pyRF24 && python setup.py build && python setup.py install
RUN cd /tmp/rf24libs/RF24/pyRF24/pyRF24Network && python setup.py build && python setup.py install
RUN cd /tmp/rf24libs/RF24/pyRF24/pyRF24Mesh && python setup.py build && python setup.py install

COPY requirements.txt .
RUN pip install --upgrade pip
RUN pip install -r requirements.txt

RUN mkdir -p /rf24-app
WORKDIR /rf24-app

# RUN /bin/sh -c pwd

CMD '/bin/bash'