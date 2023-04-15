/**
 * 
 * e-mail : rachelsysteme@gmail.com
 * gitHub : https://github.com/RS-malik-el
 * Donation : paypal.me/RachelSysteme
 *
 * @AUTEUR : Exaucé KIMBEMBE / @OpenProgramming
 * DATE : 15/04/2023
 * 
 * @Board : esp32
 * 
 *  Ce code utilise un L298N pour contrôler deux moteurs.
 *  Les entrées IN1, IN2, IN3 et IN4 sont utilisées pour déterminer
 *  le sens de rotation des moteurs. Utilise les PWM pour contrôler la vitesse.
*/


#ifndef ESP32
#error "Ce code ne fonctionne que sur une carte ESP 32, selectionner la bonne carte"
#endif

// Pins driver L298N
#define I1 21 
#define I2 22
#define I3 23
#define I4 19
// Paramètre PWM 
#define FREQ  1000
#define CHANNEL_I1  0
#define CHANNEL_I2  1
#define CHANNEL_I3  2
#define CHANNEL_I4  3
#define RESOLUTION  8 // 8 bits (0 - 255)

void moteur(int channel_1, int channel_2);

void setup(){
	// Pin définit comme une sortie
	pinMode(I1, OUTPUT);
	pinMode(I2, OUTPUT);
	pinMode(I3, OUTPUT);
	pinMode(I4, OUTPUT);
	//Initialisation du canal PWM
    ledcSetup(CHANNEL_I1, FREQ, RESOLUTION); // Configure le canal pmw
    ledcSetup(CHANNEL_I2, FREQ, RESOLUTION); // Configure le canal pmw
    ledcSetup(CHANNEL_I3, FREQ, RESOLUTION); // Configure le canal pmw
    ledcSetup(CHANNEL_I4, FREQ, RESOLUTION); // Configure le canal pmw
    ledcAttachPin(I1, CHANNEL_I1); // Attache le pin au canal pwm
    ledcAttachPin(I2, CHANNEL_I2); // Attache le pin au canal pwm
    ledcAttachPin(I3, CHANNEL_I3); // Attache le pin au canal pwm
    ledcAttachPin(I4, CHANNEL_I4); // Attache le pin au canal pwm
}

void loop(){
	// Moteur 1
	moteur(CHANNEL_I1,CHANNEL_I2); // sens 1
	moteur(CHANNEL_I2,CHANNEL_I1); // sens 2
	// Moteur 2
	moteur(CHANNEL_I3,CHANNEL_I4); // sens 1
	moteur(CHANNEL_I4,CHANNEL_I3); // sens 2
}

void moteur(int channel_1, int channel_2){
	ledcWrite(channel_2, 0); // Définit le signal de sortie du canal
	for (int i = 20; i <= 100; i+=20){
    	ledcWrite(channel_1, map(i,0,100,0,255)); // Définit le signal de sortie du canal
    	delay(2500);
	}
	// Arrêt moteur
	ledcWrite(channel_1, 0);
	ledcWrite(channel_2, 0);
	delay(1000);
}