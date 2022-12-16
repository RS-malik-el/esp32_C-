/**
 * 
 * e-mail : rachelsysteme@gmail.com
 * gitHub : https://github.com/RS-malik-el
 * Donation : paypal.me/RachelSysteme
 *
 * @AUTHEUR : RACHEL SYSTEME
 * DATE : 07/12/2022
 * 
 * @Board : esp32
 * 
 * Dans ce programme, nous allons apprendre à connecter l'esp32
 * au module HC-05, le système dispose de deux boutons : un bouton
 * pour se connecter et un autre pour se déconnecter.
 * 
*/

#include "BluetoothSerial.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial bluetooth;

#define LED_STATE_BLUE 2 // Indique si le bluetooth est connecté

// pins boutons
#define BTN_1 15  // Connexion
#define BTN_2 18  // Déconnexion

// adresse mac HC-05 
// 00:21:04:08:27:DB
uint8_t mac_address[] = {0x00,0x21,0x04,0x08,0x27,0xDB};

void setup(){
    bluetooth.begin("RS_ESP32",true); //Nom du bluetooth   
    bluetooth.connect(mac_address);
    // Configuration des pins 
    pinMode(LED_STATE_BLUE, OUTPUT); 
    pinMode(BTN_1, INPUT_PULLUP);
    pinMode(BTN_2, INPUT_PULLUP);
}

void loop(){
    int attente = 200;

    // Gestion LED témoin
    if (bluetooth.hasClient()==true)
        digitalWrite(LED_STATE_BLUE, HIGH);
    else
        digitalWrite(LED_STATE_BLUE, LOW);

    // Connexion
    if(!digitalRead(BTN_1)){
        delay(attente);
        if(!digitalRead(BTN_1))
            return;// si la touche est maintenue: fin loop
        bluetooth.connect();
    }

    // Déconnexion
    if(!digitalRead(BTN_2)){
        delay(attente);
        if(!digitalRead(BTN_2))
            return;// si la touche est maintenue: fin loop
        bluetooth.disconnect();
    }
}