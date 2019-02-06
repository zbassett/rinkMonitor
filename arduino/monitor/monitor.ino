#include <DHT.h>
#include <DHT_U.h>

#include <OneWire.h> 
#include <DallasTemperature.h>
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


//Variables
int chk;
float dht_hum;  //Stores humidity value
float dht_temp; //Stores temperature value
float probe_temp;


void setup() {
  Serial.begin(9600); 
  sensors.begin();
  dht.begin();
}

void loop() {
  //  Serial.print(" Requesting temperatures..."); 
  sensors.requestTemperatures(); // Send the command to get temperature readings 
  //  Serial.println("DONE"); 
  
  probe_temp = sensors.getTempCByIndex(0);
  dht_hum = dht.readHumidity();
  dht_temp= dht.readTemperature();
  
  Serial.print("Probe temp: "); 
  Serial.print(probe_temp);
  Serial.print(", DHT temp: ");
  Serial.print(dht_temp);
  Serial.print(", DHT humidity: ");
  Serial.print(dht_hum);
  Serial.println("%");
  
  delay(5000);

}
