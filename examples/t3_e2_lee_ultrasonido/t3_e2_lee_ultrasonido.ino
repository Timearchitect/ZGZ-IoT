/*
 * Etopia Kids - IoT 
 * Campamento de Verano 2015 
 *
 * Tutorial 3 - Ejemplo 2 - PUBLICA ULTRASONIDO
 *
 * Lee informacion de un sensor de ULTRASONIDOS
 * y publica su valor en una de las paginas
 * web del campamento. Toma el nombre de tu grupo para 
 * publicar los datos. Ejemplo:
 *
 * http://verkstad.cc/iot/zgz/1 donde "1" es el numero de tu grupo
 * 
 * Puedes elegir numeros del 1 al 10. Esto permitira que subas los
 * valores de tus sensores a la nube sin problema.
 *
 * Conecta un LED en el conector O0, y un ULTRASONIDO en
 * el conector I3 de tu Shield.
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

UltrasonicSensor us = UltrasonicSensor(I3, I3);

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
  int sensor = us.getDistance();
  
  // url 
  String url =  "http://verkstad.cc/iot/zgz/";
  url += grupo;
  url += "/index.php?distancia=";
  url += sensor;
  // sube la informacion de la luminosidad
  client.get(url);

  // imprime el valor por el puerto serie
  Serial.print("Distancia: ");
  Serial.println(sensor);  
    
  delay(5000);
}


