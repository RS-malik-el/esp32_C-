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
 *  Les entrées IN1 et IN3 sont utilisées pour contrôler le moteur.
 *  IN2 et IN4 sont connecté au GND.
 * 
*/

// Pins driver L298N
#define I1 23
#define I3 22

void setup(){
	// Pin définit comme une sortie
	pinMode(I1, OUTPUT);
	pinMode(I3, OUTPUT);
}

void loop(){
	digitalWrite(I1, HIGH);
	digitalWrite(I3, HIGH);
	delay(10000);
	digitalWrite(I1, LOW);
	digitalWrite(I3, LOW);
	delay(4000);
}