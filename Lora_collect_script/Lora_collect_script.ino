#include <SPI.h>
#include <LoRa.h>
#include <MKRWAN.h>
#include "arduino_secrets.h"

LoRaModem modem;
String appEui = SECRET_APP_EUI;
String appKey = SECRET_APP_KEY;

uint16_t counter = 0;
int buttonPin = 2;
int buttonState;
int lastButtonState = LOW;

unsigned long lastDebounceTime = 0;  
unsigned long debounceDelay = 100;  

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);
  Serial.begin(115200);
  
  while (!Serial);{
  if (!modem.begin(EU868)) {
    Serial.println("Failed to start module");
    while (1) {}
  };
  
 int connected = modem.joinOTAA(appEui, appKey);
  if (!connected) {
    Serial.println("connection fail");
    while (1) {}
  }
  delay(1000);
}

}

void loop() {
  int reading = digitalRead(buttonPin);
  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }
  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading != buttonState) {
      buttonState = reading;
      if (buttonState == HIGH) {
        buttonState == LOW;
        byte payload[2];
        payload[0] = highByte(counter);
        payload[1] = lowByte(counter);
        // send packet
        modem.beginPacket();
        modem.write(payload, sizeof(payload));
        modem.endPacket();
        counter++;
        Serial.print("Sending packet: ");
        Serial.println(counter);
        delay(1000);
        
      }
    }
  }

  // set the LED:
  //digitalWrite(ledPin, ledState);

  // save the reading. Next time through the loop, it'll be the lastButtonState:
  lastButtonState = reading;

  //buttonState = digitalRead(button);
  //if (buttonState == HIGH) {
    //delay(500);
    
  }
  //buttonState == LOW;
