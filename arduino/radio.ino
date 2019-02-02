#include "RF24.h"
#include "RF24Network.h"
#include "RF24Mesh.h"
#include <SPI.h>

/**** Configure the nrf24l01 CE and CS pins ****/
RF24 radio(9,8);
RF24Network network(radio);
RF24Mesh mesh(radio, network);

#define nodeID 2