FROM frankwolf/rpi-python3

RUN apt-get update
# RUN apt-get upgrade
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

# RUN git clone https://github.com/intel-iot-devkit/mraa.git && \
#     cd mraa && \
#     mkdir build && \
#     cd build && \
#     cmake .. -DBUILDSWIGNODE=OFF && \
#     make install

RUN git clone https://github.com/nRF24/RF24.git
WORKDIR ./RF24

# RUN /bin/sh -c ls

RUN /bin/sh -c make
RUN /bin/sh -c make install -B

# RUN /bin/sh -c cd ./pyRF24 && make
# run /bin/sh -c cd ./pyRF24 && make install

# RUN cd pyRF24 && python ./setup.py build
# RUN make install

RUN /bin/sh -c cd ./pyRF24/pyRF24
RUN /bin/sh -c python setup.py build
RUN /bin/sh -c python setup.py install

RUN /bin/sh -c cd ../pyRF24Network
RUN /bin/sh -c python setup.py build
RUN /bin/sh -c python setup.py install

RUN /bin/sh -c cd ../pyRF24Mesh
RUN /bin/sh -c python setup.py build
RUN /bin/sh -c python setup.py install

RUN mkdir -p /app
WORKDIR /app

COPY requirements.txt .
RUN pip install --upgrade pip
RUN pip install -r requirements.txt

# RUN cd ./pyRF24/pyRF24Network && python setup.py build && python setup.py install

# RUN cd ./pyRF24/pyRF24Mesh && python setup.py build && python setup.py install