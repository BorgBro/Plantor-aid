
#include "Particle.h"
#include "Adafruit_SSD1306.h"
#include "Adafruit_GFX.h"
#include "Adafruit_BME280.h"
//#include "Adafruit_MQTT_SPARK.h"
//#include "Adafruit_MQTT.h"
//#include "Credentials.h"

const int OLED_RESET =-1;
const int OLED_ADDRESS = 0x3C; //OLED display 

const int PROBEPIN = A0;
int probReading;
const int RELAYPIN = D4;

int soilDry = 2700;
int soilWet = 1414;
int waterWet = 1616;
int tempF;
int humidH;
bool status;
bool pumpOn = false;
unsigned int lastPump = 0;  

//TCPClient TheClient;

// Setup the MQTT client class by passing in the WiFi client and MQTT server and login details.
//Adafruit_MQTT_SPARK mqtt(&TheClient,AIO_SERVER,AIO_SERVERPORT,AIO_USERNAME,AIO_KEY);


Adafruit_SSD1306 display(OLED_RESET);
Adafruit_BME280 bme;


SYSTEM_MODE(SEMI_AUTOMATIC);


void setup() {
Serial.begin(9600);
waitFor(Serial.isConnected, 1000);

pinMode(PROBEPIN,INPUT);
pinMode(RELAYPIN,OUTPUT);

digitalWrite(RELAYPIN, LOW);

display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDRESS);
display.display();
delay(2000);
display.clearDisplay();
display.setTextColor(WHITE);
display.setTextSize(1);
display.display();

bme.begin(0x76);
  Serial.printf("BME OK\n");


}

void loop(){
  display.clearDisplay();
  display.setCursor(0,0); 
 
  probReading = analogRead(PROBEPIN);

  tempF = bme.readTemperature();
  tempF = tempF * (9.0/5.0)+32.0;
  humidH = bme.readHumidity();

  display.printf("Moist Level: %i\n\n", probReading);
  display.printf("Temp:     %i\n\n", tempF);
  display.printf("RH:       %i\n\n", humidH);
  
  display.display();
  Serial.printf("Moist Level: %i\n", probReading);
  

if((millis() - lastPump) > 3000){
  if (probReading> soilDry){
    digitalWrite(RELAYPIN, HIGH);
    delay(500);
    digitalWrite(RELAYPIN, LOW);
  }
  else{
    digitalWrite(RELAYPIN, LOW);
  
  }
 lastPump = millis();
}
  
  
  
 
}




