/**
 * 
 * e-mail : rachelsysteme@gmail.com
 * gitHub : https://github.com/RS-malik-el
 * Donation : paypal.me/RachelSysteme
 *
 * @AUTEUR : Exaucé KIMBEMBE / OpenProgramming
 * DATE : 06/12/2022
 * 
 * @Board : esp32
 * 
 * Dans ce programme, nous allons apprendre à connecter l'esp32 au module
 * HC-05 afin de contrôler l'allumage de 4 leds. l'esp32 envoie les données
 * de contrôle et dispose des leds témoin.
 * 
*/

#include "BluetoothSerial.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial bluetooth;

// pins boutons
#define BTN_1 4  // Contrôle le voyant 1
#define BTN_2 5  // Contrôle le voyant 2
#define BTN_3 15 // Contrôle le voyant 3
#define BTN_4 18 // Contrôle le voyant 4

// pins leds témoin
#define LED_1 19 // indique l'état du voyant 1
#define LED_2 21 // indique l'état du voyant 2
#define LED_3 22 // indique l'état du voyant 3
#define LED_4 23 // indique l'état du voyant 4
#define LED_STATE_BLUE 2 // Indique si le bluetooth est connecté à un appareil ou pas

// Variable de contrôle des voyants
bool etat_1 = false;
bool etat_2 = false;
bool etat_3 = false;
bool etat_4 = false;


// adresse mac HC-05 
// 00:21:04:08:27:DB / Remplacer par votre adresse mac
uint8_t mac_address[] = {0x00,0x21,0x04,0x08,0x27,0xDB}; 

void setup() {
  	bluetooth.begin("RS_ESP32",true); //Nom du bluetooth  
    bluetooth.connect(mac_address);
  	// Configuration des pins
  	pinMode(LED_1, OUTPUT);
  	pinMode(LED_2, OUTPUT);
  	pinMode(LED_3, OUTPUT);
  	pinMode(LED_4, OUTPUT); 
  	pinMode(LED_STATE_BLUE, OUTPUT); 
  	pinMode(BTN_1, INPUT_PULLUP);
  	pinMode(BTN_2, INPUT_PULLUP);
  	pinMode(BTN_3, INPUT_PULLUP);
  	pinMode(BTN_4, INPUT_PULLUP);
}

void loop(){
	// Voyant témoin de connexion bluetooth
	if (bluetooth.hasClient()==true){
		int attente = 200;
		digitalWrite(LED_STATE_BLUE, HIGH);

		// Gestion voyant 1 
		if(!digitalRead(BTN_1)){
			delay(attente);
			if(!digitalRead(BTN_1))
				return;// si la touche est maintenue: fin loop
			bluetooth.flush();
			etat_1 = not etat_1;
			if(etat_1 == true){
				digitalWrite(LED_1, HIGH);
				bluetooth.println("on_1");			
			}
			else{
				digitalWrite(LED_1, LOW);
				bluetooth.println("off_1");		
			}
		}// fin gestion led 1

		// Gestion voyant 2 
		if(!digitalRead(BTN_2)){
			delay(attente);
			if(!digitalRead(BTN_2))
				return;// si la touche est maintenue: fin loop
			bluetooth.flush();
			etat_2 = not etat_2;
			if(etat_2 == true){
				digitalWrite(LED_2, HIGH);
				bluetooth.println("on_2");			
			}
			else{
				digitalWrite(LED_2, LOW);
				bluetooth.println("off_2");		
			}
		}// fin gestion led 2

		// Gestion voyant 3 
		if(!digitalRead(BTN_3)){
			delay(attente);
			if(!digitalRead(BTN_3))
				return;// si la touche est maintenue: fin loop
			bluetooth.flush();
			etat_3 = not etat_3;
			if(etat_3 == true){
				digitalWrite(LED_3, HIGH);
				bluetooth.println("on_3");			
			}
			else{
				digitalWrite(LED_3, LOW);
				bluetooth.println("off_3");		
			}
		}// fin gestion led 3

		// Gestion voyant 4 
		if(!digitalRead(BTN_4)){
			delay(attente);
			if(!digitalRead(BTN_4))
				return;// si la touche est maintenue: fin loop
			bluetooth.flush();
			etat_4 = not etat_4;
			if(etat_4 == true){
				digitalWrite(LED_4, HIGH);
				bluetooth.println("on_4");			
			}
			else{
				digitalWrite(LED_4, LOW);
				bluetooth.println("off_4");		
			}
		}// fin gestion led 4
	}// fin 

	else{
		bluetooth.connect();// Tentative de connexion
		etat_1 = false;
		etat_2 = false;
		etat_3 = false;
		etat_4 = false;
		// Etat initial du système si non connecté
		digitalWrite(LED_STATE_BLUE, LOW);
		digitalWrite(LED_1, LOW);  
		digitalWrite(LED_2, LOW); 
		digitalWrite(LED_3, LOW); 
		digitalWrite(LED_4, LOW); 
	}
}// fin loop
