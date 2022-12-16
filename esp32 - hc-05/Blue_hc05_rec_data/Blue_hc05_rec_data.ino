/**
 * 
 * e-mail : rachelsysteme@gmail.com
 * gitHub : https://github.com/RS-malik-el
 * Donation : paypal.me/RachelSysteme
 *
 * @AUTHEUR : RACHEL SYSTEME
 * DATE : 07/12/2022
 * 
 * @Board : Arduino Uno
 * 
 * Ce programme permet de recevoir les données bluetooth via le module HC-O5
 * afin de contrôler l'allumage de 4 lampes via un relais.
 * 
*/

#include <SoftwareSerial.h>

// pins leds 
#define LED_1 2 
#define LED_2 3 
#define LED_3 4 
#define LED_4 5

// Pins HC-O5
#define PIN_STATE 9 // Lecture de l'état du bluetooth
#define RX 10 // inverser les connexions Rx--->Tx 
#define TX 11 // inverser les connexions Tx<---Rx

#define ON LOW // ralais actif à LOW et inactif à HIGH

// Déclaration de l'objet
SoftwareSerial bluetooth(RX, TX);

void setup(){
    Serial.begin(9600);
    bluetooth.begin(9600); // Initialisation
    // Configuration des pins
    pinMode(PIN_STATE, INPUT);
    for(int i = LED_1; i <= LED_4 ; ++i){
      pinMode(i, OUTPUT);  
      digitalWrite(i, not ON);
    }
}

void loop(){
    if(digitalRead(PIN_STATE) == true){
        if(bluetooth.available()){
            String rec = bluetooth.readStringUntil('\n');
            rec.toLowerCase(); // minuscule
            rec.trim(); // suppression des espaces en début et fin
            Serial.println(rec);
            // Allumage
            if (rec == "on_1")
              digitalWrite(LED_1, ON);
            else if (rec == "on_2")
                digitalWrite(LED_2, ON);
            else if (rec == "on_3")
                digitalWrite(LED_3, ON);
            else if (rec == "on_4")
                digitalWrite(LED_4, ON);
            // Extinction
            else if (rec == "off_1")
                digitalWrite(LED_1, not ON);
            else if (rec == "off_2")
                digitalWrite(LED_2, not ON);
            else if (rec == "off_3")
                digitalWrite(LED_3, not ON);
            else if (rec == "off_4")
                digitalWrite(LED_4, not ON);
        }       
    }
    else{
        // Etat par défaut des voyants
        for(int i = LED_1; i <= LED_4 ; ++i){
            digitalWrite(i, not ON);
        }
    }
}// fin loop
