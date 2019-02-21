#include <DHT.h>
#include <DHT_U.h>

#include <OneWire.h> 
#include <DallasTemperature.h>

#include "RF24.h"
#include "RF24Network.h"
#include "RF24Mesh.h"
#include <SPI.h>
//#include <printf.h>


// Each node needs a unique ID:
#define nodeID 1

uint32_t displayTimer = 0;
uint32_t sensorTimer = 0;


struct payload_t {
  unsigned long ms;
  unsigned long counter;
};


/**** Configure the nrf24l01 CE and CS pins ****/
RF24 radio(9, 8);
RF24Network network(radio);
RF24Mesh mesh(radio, network);

/********************************************************************/
// Data wire is plugged into pin 2 on the Arduino 
#define ONE_WIRE_BUS 2 
/********************************************************************/
// Setup a oneWire instance to communicate with any OneWire devices  
// (not just Maxim/Dallas temperature ICs) 
OneWire oneWire(ONE_WIRE_BUS); 
/********************************************************************/
// Pass our oneWire reference to Dallas Temperature. 
DallasTemperature sensors(&oneWire);
/********************************************************************/ 


//Constants
#define DHTPIN 7     // what pin we're connected to
#define DHTTYPE DHT22   // DHT 22  (AM2302)
DHT dht(DHTPIN, DHTTYPE); //// Initialize DHT sensor for normal 16mhz Arduino


//Variables:  Set the item ids to correspond with items in OpenHAB
String probe_temp_id = "probe_1_temp";
String dht_hum_id = "dht_1_temp";
String dht_temp_id = "dht_1_hum";

int chk;
float dht_hum;  //Stores humidity value
float dht_temp; //Stores temperature value
float probe_temp;



void setup() {
  Serial.begin(9600); 

  sensors.begin();
  dht.begin();

  mesh.setNodeID(nodeID);
  // Connect to the mesh
  Serial.println(F("Connecting to the mesh..."));
  mesh.begin();
  Serial.println("mesh begun...");
  SPI.begin();      // Init SPI bus
  
  radio.setPALevel(RF24_PA_MAX);  //options: RF24_PA_MIN, RF24_PA_LOW, RF24_PA_HIGH and RF24_PA_MAX
}

void loop() {
  mesh.update();

  // Send to the master node every second
  if (millis() - displayTimer >= 1000) {
    displayTimer = millis();
    
    // Send an 'M' type message containing the current millis()
    if (!mesh.write(&displayTimer, 'M', sizeof(displayTimer))) {

      // If a write fails, check connectivity to the mesh network
      if ( ! mesh.checkConnection() ) {
        //refresh the network address
        Serial.println("Renewing Address");
        mesh.renewAddress();
      } else {
        Serial.println("Send fail, Test OK");
      }
    } else {
      Serial.print("Sent millis(): "); Serial.println(displayTimer);
    }
  }


  // Check the sensors every 5 seconds and send the info to master node:
  if (millis() - sensorTimer >= 5000) {
    sensorTimer = millis();
    
    sensors.requestTemperatures(); // Send the command to get temperature readings 

    probe_temp = sensors.getTempCByIndex(0);
    dht_hum = dht.readHumidity();
    dht_temp= dht.readTemperature();

    String buf;
    buf += String(probe_temp_id);
    buf += String(":");
    buf += String(probe_temp, 4);
    buf += String("|");
    buf += String(dht_temp_id);
    buf += String(":");
    buf += String(dht_temp, 4);
    buf += String("|");
    buf += String(dht_hum_id);
    buf += String(":");
    buf += String(dht_hum, 1);
    Serial.println(buf);

//    const char buf[] = "woo hoo!!";
    
//    Serial.print("Probe temp: "); 
//    Serial.print(probe_temp);
//    Serial.print(", DHT temp: ");
//    Serial.print(dht_temp);
//    Serial.print(", DHT humidity: ");
//    Serial.print(dht_hum);
//    Serial.println("%");

    if (!mesh.write(buf.c_str(), 'I', buf.length())) {

      // If a write fails, check connectivity to the mesh network
      if ( ! mesh.checkConnection() ) {
        //refresh the network address
        Serial.println("Renewing Address");
        mesh.renewAddress();
      } else {
        Serial.println("Payload send fail, Test OK");
      }
    } else {
      Serial.print("Sent buf: "); Serial.print(buf); Serial.print(" - size: "); Serial.println(buf.length());
    }
  }


  while (network.available()) {
    RF24NetworkHeader header;
    payload_t payload;
    network.read(header, &payload, sizeof(payload));
    Serial.print("Header: ");
    Serial.print(header.type);
    Serial.print("  Received packet #");
    Serial.print(payload.counter);
    Serial.print(" at ");
    Serial.println(payload.ms);
  }
}
