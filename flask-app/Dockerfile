FROM frankwolf/rpi-python3

COPY requirements.txt .
RUN pip install --upgrade pip
RUN pip install -r requirements.txt

RUN mkdir -p /flask-app
WORKDIR /flask-app
