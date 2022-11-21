/**
 * 
 * e-mail : rachelsysteme@gmail.com
 * gitHub : https://github.com/RS-malik-el
 * Donation : paypal.me/RachelSysteme
 *
 * @AUTHEUR : RACHEL SYSTEME
 * DATE : 17/11/2022
 * 
 * * @Board : esp32
 * 
 * Transmission
 * 
 * Ce programme permet de contrôler l'allumage d'une led et le
 * positionnement d'un servomoteur 180°. l'état de la led ainsi
 * que la position de l'angle est transmis via le port série et
 * sera reçu par une autre carte (dans notre cas la carte arduino uno).
 * 
 * Note: L'appui sur la touche "EN" de l'ESP32 envoie les informations
 * non attendues dans le port série, ce qui crée des bugs dans le programme coté
 * arduino, car ses informations non attendues seront traité et donnera un comportement 
 * indésirable au système. Déconnecter la carte arduino si appuie sur "EN".
 * 
*/
 
#define POT 34 // Pin potentiomètre
#define BP  23 // Pin bouton poussoir

// Variable de contrôle de la position du servomoteur
int angle    = 0;
int preAngle = angle;
// Variable de contrôle de l'état de la led
bool etat = false;
bool preEtat = etat;

void setup(){
    // Initialisation de la communication série
    Serial.begin(115200);
    // Configuration des pins
    pinMode(POT,INPUT);
    pinMode(BP,INPUT_PULLUP);
    // Définition de la résolution du signal(0-1023)
    analogSetWidth(10);
}


void loop(){
    // Changement d'état de la variable après appuis
    if(!digitalRead(BP)){
        delay(100);
        if(!digitalRead(BP))
            return;
        etat = !etat;
    }
    // Lecture du potentiomètre et conversion des valeurs
    angle = map(analogRead(POT),0,1023,0,180);

    if(preAngle != angle or preEtat != etat){
        // Mise à jour des variables
        preAngle = angle;
        preEtat  = etat;
        // Transfert des données via le port série
        Serial.write(etat);
        Serial.write(angle);
        delay(100);
    }
}
