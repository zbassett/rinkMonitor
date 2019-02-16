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

RUN apt-get install -y python-dev libboost-python-dev 
# RUN ln -s /usr/lib/arm-linux-gnueabihf/libboost_python-py34.so /usr/lib/arm-linux-gnueabihf/libboost_python3.so

RUN git clone https://github.com/intel-iot-devkit/mraa.git && \
    cd mraa && \
    mkdir build && \
    cd build && \
    cmake .. -DBUILDSWIGNODE=OFF && \
    make install
    
WORKDIR /tmp

COPY Makefile.inc .
    
COPY rf24_installer.sh /tmp
RUN chmod +x /tmp/rf24_installer.sh
RUN sh /tmp/rf24_installer.sh


# RUN git clone https://github.com/nRF24/RF24.git
# WORKDIR ./RF24

# COPY Makefile.inc .

# # RUN /bin/sh -c ls

# RUN make
# RUN /bin/sh -c make install -B

# # RUN /bin/sh -c cd ./pyRF24 && make
# # run /bin/sh -c cd ./pyRF24 && make install

# # RUN cd pyRF24 && python ./setup.py build
# # RUN make install

# RUN /bin/sh -c cd ./pyRF24
# RUN /bin/sh -c python setup.py build
# RUN /bin/sh -c python setup.py install

# RUN /bin/sh -c cd ./pyRF24
# RUN /bin/sh -c python setup.py build
# RUN /bin/sh -c python setup.py install

# RUN /bin/sh -c cd ../pyRF24Network
# RUN /bin/sh -c python setup.py build
# RUN /bin/sh -c python setup.py install

# RUN /bin/sh -c cd ../pyRF24Mesh
# RUN /bin/sh -c python setup.py build
# RUN /bin/sh -c python setup.py install

COPY requirements.txt .
RUN pip install --upgrade pip
RUN pip install -r requirements.txt

RUN mkdir -p /rf24-app
WORKDIR /rf24-app

# RUN /bin/sh -c pwd

CMD '/bin/bash'