/**
 * 
 * e-mail : rachelsysteme@gmail.com
 * gitHub : https://github.com/RS-malik-el
 * Donation : paypal.me/RachelSysteme
 *
 *@AUTEUR : Exaucé KIMBEMBE / OpenProgramming
 * DATE : 30/10/2022
 * 
 * * @Board : esp32
 * 
 * Dans ce programme, nous allons apprendre comment lire une entrée digital avec l'ESP32.
 * l'appuie sur le bouton poussoir allume ou éteint la led.
 * 
 * Mode :
 *  ** INPUT : définit le pin comme une entrée sans activation de la resistance interne     
 *  ** INPUT_PULLUP : définit le pin comme une entrée avec resistance interne connecté en pull-up
 *  ** INPUT_PULLDOWN : définit le pin comme une entrée avec resistance interne connecté en pull-down
 * 
*/

#define BTN 23 // Pin connecté au bouton poussoir
#define LED 22 // Pin connecté à la LED
#define ATTENTE 200 

bool etat = false;

void setup(){
    pinMode(BTN,INPUT_PULLUP);
    pinMode(LED,OUTPUT);
}

void loop(){
    if (not digitalRead(BTN) == true){
        etat = not etat;
        digitalWrite(LED,etat);
        delay(ATTENTE);
    }
}
