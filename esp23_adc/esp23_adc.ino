/**
 * 
 * e-mail : rachelsysteme@gmail.com
 * gitHub : https://github.com/RS-malik-el
 * Donation : paypal.me/RachelSysteme
 *
 * @AUTHEUR : RACHEL SYSTEME
 * DATE : 30/10/2022
 * 
 * * @Board : esp32
 * 
 * Dans ce programme, nous allons apprendre comment utiliser l'ADC de l'ESP32.
 * l'ESP32 dipose de deux convertiseurs ADC (ADC1 et ADC2)
 * ** ADC1 : 32, 33, 34, 35, 36,39.
 * ** ADC2 : 0, 2, 4, 12, 13, 14, 15, 25, 26, 27, 
 *  l'ADC2 est utilisé en interne quand le wifi est activé.
 * 
 * ADC.ATTN_0DB   : la tension de gamme complète: 1,2 V
 * ADC.ATTN_2_5DB : la tension de gamme complète: 1,5 V
 * ADC.ATTN_6DB   : la tension de la gamme complète: 2.0V
 * ADC.ATTN_11DB  : la tension de gamme complète: 3.3V
 * 
*/

#define POT 34 // Pin connecté au pententiomètre
#define ATTENTE 1000 

void setup(){
    Serial.begin(9600); // Initialisation de la communication série
    pinMode(POT,INPUT); // Définition du pin comme entrée
    // analogSetAttenuation(ADC_11db);// Définition de l'attenuation(default:ADC_11db)
    analogSetWidth(10); // Définition de la résolution du signal(0-1023)
}

void loop(){
    Serial.println("Valeur lue : " + String(analogRead(POT))); 
    Serial.println("Valeur en pourcentage :" + String(map(analogRead(POT),0,1023,0,100)) + " %");
    Serial.println("Tension : " + String(analogReadMilliVolts(POT)) + " mv\n");
    delay(ATTENTE);
}