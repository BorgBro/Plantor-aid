
#include "Particle.h"
#include "Adafruit_SSD1306.h"
#include "Adafruit_GFX.h"

const int OLED_RESET =-1;
const int OLED_ADDRESS = 0x3C; //OLED display 

const int PROBEPIN = A0;
int rawData;
int probReading;
const int RELAYPIN = D4;

int soilDry = 2840;
int soilWet = 1414;
int waterWet = 1616;
int moistSoil;


Adafruit_SSD1306 display(OLED_RESET);


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


}


void loop() {
  display.clearDisplay();
  display.setCursor(0,0); 

  probReading = analogRead(PROBEPIN);
  Serial.printf("Moist Level: %i\n", probReading);
  display.printf("Moist Level: %i\n", probReading);
  display.display();
  delay(2000);

  digitalWrite(RELAYPIN, HIGH);

  if (moistSoil<1414){
  digitalWrite(RELAYPIN, HIGH);
  delay(3000);
  digitalWrite(RELAYPIN, HIGH);
  }

 else (moistSoil>2840);
  digitalWrite(RELAYPIN, LOW);
  delay(3000);

}



//display.clearDisplay();
//display.display();
//delay(2000);

  

