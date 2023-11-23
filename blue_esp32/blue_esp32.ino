/**
 * 
 * e-mail : rachelsysteme@gmail.com
 * gitHub : https://github.com/RS-malik-el
 * Donation : paypal.me/RachelSysteme
 *
 * @AUTEUR : Exaucé KIMBEMBE / OpenProgramming
 * DATE : 15/11/2022
 * 
 * * @Board : esp32
 * 
 * Dans ce programme, nous allons apprendre à utiliser le bluetooth
 * avec l'esp32 pour allumer une lampe via un relais
 * 
*/

#include "BluetoothSerial.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial bluetooth;

#define PIN_RELAIS 23

void setup() {
  bluetooth.begin("OP_ESP32"); //Nom du bluetooth
  pinMode(PIN_RELAIS,OUTPUT); 
}

void loop() {
	String cmd;  
	if (bluetooth.available()) {
    	cmd = bluetooth.readStringUntil('\n');
    	if (cmd=="on")
   			digitalWrite(PIN_RELAIS,HIGH);
   		if (cmd=="off")
   			digitalWrite(PIN_RELAIS,LOW);
  	}
  	delay(20);
}
