/**
 * 
 * e-mail : rachelsysteme@gmail.com
 * gitHub : https://github.com/RS-malik-el
 * Donation : paypal.me/RachelSysteme
 *
 * @AUTHEUR : RACHEL SYSTEME
 * DATE : 17/11/2022
 * 
 * * @Board : arduino
 * 
 * Réception
 * 
 * Ce programme permet de contrôler l'allumage d'une led et le
 * positionnement d'un servomoteur 180°. l'état de la led ainsi
 * que la position de l'angle est reçu via le port série (envoyé
 * depuis une autre carte dans notre cas ESP32)
 * 
 * Note: L'appui sur la touche "EN" de l'ESP32 envoie les informations
 * non attendues dans le port série, ce qui crée des bugs dans le programme, 
 * car ses informations non attendues seront traité et donnera un comportement 
 * indésirable au système. Déconnecter la carte arduino si appuie sur "EN".
*/
#include <Servo.h>

// Pins utilisé
#define PIN_SERVO 2
#define LED       3

Servo servo;
int angle = 0;
bool etat = false;

#define INDEX_LED   0 // index dans le tableau
#define INDEX_ANGLE 1 // index dans le tableau
#define TAILLE      2 // Taille du tableau

// Tableau contenant les données reçu (état led, valeur angle)
uint8_t reception[TAILLE] ={etat,angle};

void setup(){
    // Initialisation de la communication série
    Serial.begin(115200);
    // Configuration de la led
    pinMode(LED,OUTPUT); 
    digitalWrite(LED,etat);
    // Configuration du servo
    servo.attach(PIN_SERVO);
    servo.write(angle);

    //Suppression des buffers
    while(Serial.available()){Serial.read();}
}


void loop(){
    // Réception et mise à jour des sorties
    if (Serial.available()){
        delay(10); 
        // Reception et stockage des données
        reception[INDEX_LED] = (int) Serial.read();
        delay(10);
        reception[INDEX_ANGLE] = (int) Serial.read();
        // Mise à jour des variables
        etat  = reception[INDEX_LED];
        angle = reception[INDEX_ANGLE];
        // Mise à jour des sorties
        digitalWrite(LED,etat);
        servo.write(angle);
        Serial.print(etat);
        Serial.print(" : ");
        Serial.println(angle);
    }
}