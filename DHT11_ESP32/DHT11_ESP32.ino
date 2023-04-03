/**
 * 
 * e-mail : rachelsysteme@gmail.com
 * gitHub : https://github.com/RS-malik-el
 * Donation : paypal.me/RachelSysteme
 *
 * @AUTEUR : Exaucé KIMBEMBE / @OpenProgramming
 * DATE : 06/03/2023
 * 
 * @Board : esp32
 * 
*/

#include <DHTesp.h>

#ifndef ESP32
#error Ce code ne marche que sur une carte ESP 32
#endif

#define PIN_DHT11   23  // DHT11 (capteur de température et d'humidité)

DHTesp dht;   
TempAndHumidity value;

void setup(){
    Serial.begin(115200);
    // Configuration du DHT11
    dht.setup(PIN_DHT11, DHTesp::DHT11);
    delay(2000); // Pause
}

void loop(){
    value = dht.getTempAndHumidity();
    Serial.println("T "+String(value.temperature)+"°C");
    Serial.println("H "+String(value.humidity)+"%\n");

    Serial.println("@T "+String(dht.getTemperature())+"°");
    Serial.println("@H "+String(dht.getHumidity())+"%\n"); 
    delay(2000);
}