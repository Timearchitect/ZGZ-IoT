/*
 * Etopia Kids - IoT 
 * Campamento de Verano 2015 
 *
 * Tutorial 2 - Ejemplo 3 - PUBLICA LUMINOSIDAD
 *
 * Lee informacion de un sensor analogico como una LDR o
 * un POTENCIOMETRO y publica su valor en una de las paginas
 * web del campamento. Toma el nombre de tu grupo para 
 * publicar los datos. Ejemplo:
 *
 * http://verkstad.cc/iot/zgz/1 donde "1" es el numero de tu grupo
 * 
 * Puedes elegir numeros del 1 al 10. Esto permitira que subas los
 * valores de tus sensores a la nube sin problema.
 *
 * Conecta un LED en el conector O0, y una LDR o POTENCIOMETRO en
 * el conector I1 de tu Shield.
 *
 * (c) 2015 D. Cuartielles para Arduino Verkstad
 *
 * Este programa es GPLv3, usalo bajo tu responsabilidad
 *
 */
 
#include <ZGZ_IoT.h>
#include <Bridge.h>
#include <HttpClient.h>

HttpClient client;

void setup() {
  // configura el pin del LED
  pinMode(O0, OUTPUT);
  
  // apaga el led y enciendelo cuando este todo listo
  digitalWrite(O0, LOW);
  Bridge.begin();
  digitalWrite(O0, HIGH);

  // configura el puerto serie
  Serial.begin(9600);

  while (!Serial); // espera a abrir el monitor serie
}

void loop() {
  // cambia este numero por el numero de tu grupo
  int grupo = 1;
 
  // lee el valor del sensor
  int sensor = analogRead(I1);
  
  // url 
  String url =  "http://verkstad.cc/iot/zgz/";
  url += grupo;
  url += "/index.php?luminosidad=";
  url += sensor;
  // sube la informacion de la luminosidad
  client.get(url);

  // imprime el valor por el puerto serie
  Serial.print("Luminosidad: ");
  Serial.println(sensor);  
    
  delay(5000);
}


