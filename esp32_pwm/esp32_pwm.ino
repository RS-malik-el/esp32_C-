/**
 * 
 * e-mail : rachelsysteme@gmail.com
 * gitHub : https://github.com/RS-malik-el
 *
 * @AUTEUR : Exaucé KIMBEMBE / OpenProgramming
 * DATE : 30/10/2022
 * 
 * * @Board : esp32
 * 
 * Dans ce programme nous allons apprendre comment utiliser les sorties PWM
 * et contrôler l'allumage d'une led avec un potentiomètre
 * 
 * Etape 1:
 *  ** Choisir un canal PWM. Il y a 16 canaux de 0 à 15.
 * Etape 2:
 *  ** Définir la fréquence du signal PWM.
 * Etape 3:
 *  ** Définir la résolution du cycle de service du signal: de 1 à 16 bits. 
 * Etape 4:
 *  ** Spécifier sur quel(s) GPIO ou GPIO le signal apparaîtra.
 * Etape 5:
 * ** Definir le cycle du GPIO
 * 
 * NB: Un canal peut être associé à différent GPIO(s)
*/

#define PIN_POT 34 // Pin connecté au pententiomètre
#define PIN_LED 22 // Pin connecté à la LED

// Paramètre PWM 
#define FREQ  1000
#define CHANNEL  0
#define RESOLUTION  8 // 8 bits (0 - 255)

int cycle = 0;

void setup(){
    Serial.begin(9600); // Initialisation de la communication série

    pinMode(PIN_POT,INPUT); // Définition du pin comme entrée
    pinMode(PIN_LED,OUTPUT);// Pin définit comme une sortie
    
    // Potentiomètre
    analogSetWidth(10); // Définition de la résolution du signal(0-1023)
    
    //Initialisation du canal PWM
    ledcSetup(CHANNEL, FREQ, RESOLUTION); // Configure le canal pmw
    ledcAttachPin(PIN_LED, CHANNEL); // Attache le pin au canal pwm
}

void loop(){
    cycle = map(analogRead(PIN_POT),0,1023,0,255); // Lecture et conversion des valeurs analogique
    ledcWrite(CHANNEL, cycle); // Définit le signal de sortie du canal
    Serial.println(ledcRead(CHANNEL)); // Affiche le cycle du canal
}
