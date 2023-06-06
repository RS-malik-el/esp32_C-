/**
 * e-mail : openprogramming23@gmail.com
 * gitHub : https://github.com/RS-malik-el
 * Donation : paypal.me/RachelSysteme
 *
 * @AUTEUR : Exaucé KIMBEMBE / @OpenProgramming
 * DATE : 05/06/2023
 * 
 * Ce code en C++ est conçu pour contrôler un véhicule éviteur d'obstacles. 
 * Il est compatible avec une carte ESP32, mais peut également fonctionner sur une carte Arduino. 
 * 
 * Le projet utilise plusieurs composants, notamment :
 * - Une carte ESP32 ou Arduino : Cette carte est le cœur du système et sert de plateforme de développement.
 * - 4 LEDs : Les LEDs sont utilisées pour fournir des indications visuelles.
 * - 2 capteurs d'obstacle : Ces capteurs sont utilisés pour détecter les obstacles dans l'environnement du véhicule. 
 * - 2 motoreducteurs : Les moteurs sont responsables du mouvement du véhicule. 
 * - Un driver moteur : Le driver moteur permet de contrôler la vitesse et la direction des moteurs.
 * 
 * Le code met en œuvre l'algorithme de détection et d'évitement d'obstacles. 
 * Il utilise les informations fournies par les capteurs d'obstacle pour prendre des décisions quant 
 * à la direction et aux actions du véhicule. En fonction de ces décisions, les moteurs sont activés 
 * pour déplacer le véhicule de manière appropriée et éviter les obstacles détectés.
 * 
 * Ce projet offre une expérience pratique pour comprendre et mettre en pratique les concepts de détection d'obstacles,
 * de contrôle des moteurs et d'intégration des composants électroniques. Il est adapté aux amateurs de robotique 
 * et d'électronique souhaitant explorer le domaine des véhicules autonomes et des systèmes intelligents.
 *
 *  */

// Pins utilisés
#if defined (ESP32)
	#define MG_IN1 15
	#define MG_IN2 2
	#define MD_IN1 4
	#define MD_IN2 16
	#define LED_AV_G 5
	#define LED_AV_D 17
	#define LED_AR_D 12
	#define LED_AR_G 13
	#define CPTR_AV 27
	#define CPTR_AR 14
	#define PIN_REF 34
#elif defined (_AVR_)
	#define MG_IN1   2
	#define MG_IN2   3
	#define MD_IN1   4
	#define MD_IN2   5
	#define LED_AV_G 6
	#define LED_AV_D 7
	#define LED_AR_D 8
	#define LED_AR_G 9
	#define CPTR_AV  10
	#define CPTR_AR  11
	#define PIN_REF  A0
#else
	#error Selectionner une carte ESP32 ou Arduino
#endif

#define DETECTION false

// Prototype des fonctions
void avance(void);
void arriere(void);
void gauche(void);
void droite(void);
void stop(void);
void far_AV(bool etat=true);
void far_AR(bool etat=true);
void blink(uint8_t pin1, uint8_t pin2, bool etat=true);

void setup(){
	randomSeed(analogRead(PIN_REF));

	pinMode(MG_IN1,OUTPUT);
	pinMode(MG_IN2,OUTPUT);
	pinMode(MD_IN1,OUTPUT);
	pinMode(MD_IN2,OUTPUT);

	pinMode(LED_AV_G,OUTPUT);
	pinMode(LED_AV_D,OUTPUT);
	pinMode(LED_AR_G,OUTPUT);
	pinMode(LED_AR_D,OUTPUT);

	pinMode(CPTR_AV,INPUT);
	pinMode(CPTR_AR,INPUT);
}


void loop(){
	const int attente = 3000;

	if(digitalRead(CPTR_AV) == not DETECTION){
		far_AV();
		avance();
	}
	
	else{
		far_AV(false);
		far_AR();
		stop();
		delay(attente);

		unsigned long init = millis();

		while(digitalRead(CPTR_AR) == not DETECTION){
			if((millis()-init) >= attente)
				break;// fin de la boucle
			
			blink(LED_AR_D, LED_AR_G);
			arriere();
		}

		stop();
		blink(LED_AR_D, LED_AR_G, false);

		int d = random(0,2); // Choix de la direction
		init = millis();

		while(true){
			if((millis()-init) >= attente)
				break;// fin de la boucle

			if(d == 0){
				blink(LED_AV_G, LED_AR_G);
				gauche();
			}
			else{
				blink(LED_AV_D, LED_AR_D);
				droite();
			}
		}
		
		stop();
		far_AV();
		far_AR();

		delay(attente);
		
		far_AV(false);
		far_AR(false);
	}
}

void avance(void){
	digitalWrite(MG_IN1,HIGH);
	digitalWrite(MG_IN2,LOW);
	digitalWrite(MD_IN1,HIGH);
	digitalWrite(MD_IN2,LOW);
}

void arriere(void){
	digitalWrite(MG_IN1,LOW);
	digitalWrite(MG_IN2,HIGH);
	digitalWrite(MD_IN1,LOW);
	digitalWrite(MD_IN2,HIGH);
}

void gauche(void){
	digitalWrite(MG_IN1,HIGH);
	digitalWrite(MG_IN2,LOW);
	digitalWrite(MD_IN1,LOW);
	digitalWrite(MD_IN2,HIGH);
}

void droite(void){
	digitalWrite(MG_IN1,LOW);
	digitalWrite(MG_IN2,HIGH);
	digitalWrite(MD_IN1,HIGH);
	digitalWrite(MD_IN2,LOW);
}

void stop(void){
	digitalWrite(MG_IN1,LOW);
	digitalWrite(MG_IN2,LOW);
	digitalWrite(MD_IN1,LOW);
	digitalWrite(MD_IN2,LOW);
}

void far_AV(bool etat){

	if (etat){
		digitalWrite(LED_AV_D,HIGH);
		digitalWrite(LED_AV_G,HIGH);
	}
	else{
		digitalWrite(LED_AV_D,LOW);
		digitalWrite(LED_AV_G,LOW);
	}
}

void far_AR(bool etat){
	if (etat){
		digitalWrite(LED_AR_D,HIGH);
		digitalWrite(LED_AR_G,HIGH);
	}
	else{
		digitalWrite(LED_AR_D,LOW);
		digitalWrite(LED_AR_G,LOW);
	}
}

void blink(uint8_t pin1, uint8_t pin2, bool etat){
	static unsigned long init = millis();
	static bool state = false;

	if(etat){
		if((millis()-init) > 250){
			state = not state;

			digitalWrite(pin1,state);
			digitalWrite(pin2,state);

			init = millis();
		}
	}
	else{
		digitalWrite(pin1,LOW);
		digitalWrite(pin2,LOW);		
	}
}