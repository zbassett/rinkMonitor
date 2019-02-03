#include "RF24.h"
#include "RF24Network.h"
#include "RF24Mesh.h"
#include <SPI.h>

/**** Configure the nrf24l01 CE and CS pins ****/
RF24 radio(9,8);
RF24Network network(radio);
RF24Mesh mesh(radio, network);

#define nodeID 2

uint32_t displayTimer = 0;

struct payload_t {
  unsigned long ms;
  unsigned long counter;
};

void setup() {
  Serial.begin(9600);
  
  mesh.setNodeID(nodeID);
  // Connect to the mesh
  Serial.println(F("Connecting to the mesh1..."));
  mesh.begin();
  Serial.println("mesh begun");
  
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
}