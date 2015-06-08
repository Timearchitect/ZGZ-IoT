/*
 * Etopia Kids - IoT 
 * Campamento de Verano 2015 
 *
 * Tutorial 2 - Ejemplo 5 - MUESTRA DISTANCIA
 *
 * Lee de internet la distancia entre dos sitios y te devuelve
 * un valor en kilometros. Ejemplo:
 *
 * http://verkstad.cc/iot/zgz/code/get_distance.php?city1=Zaragoza&country1=es&city2=Madrid&country2=es
 * 
 * Puedes elegir cualquier ciudad del mundo para comparar.
 *
 * Conecta un LEDs en los conectores O0, O1 y O2 para representar la distancia.
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

// almacena la distancia
int distancia = 0;

String ciudad1 = "Madrid";
String pais1 = "es";
String ciudad2 = "Zaragoza";
String pais2 = "es";

void setup() {
  // configura los LEDs
  pinMode(O0, OUTPUT);
  pinMode(O1, OUTPUT);
  pinMode(O2, OUTPUT);
  
  // apaga el led y enciendelo cuando este todo listo
  digitalWrite(O0, LOW);
  Bridge.begin();
  digitalWrite(O0, HIGH);

  // configura el puerto serie
  Serial.begin(9600);

  while (!Serial); // espera a abrir el monitor serie
}

void loop() {
  // url 
  String url =  "http://verkstad.cc/iot/zgz/code/get_distance.php?city1=";
  url += ciudad1;
  url += "&country1=";
  url += pais1;
  url += "&city2=";
  url += ciudad2;
  url += "&country2=";
  url += pais2;
  // leee la informacion de la luminosidad
  client.get(url);

  String dist = "";

  while (client.available()) {
    char c = client.read();
//    distancia = distancia * 10 + int(c) - 48;
    dist += c;
  }
  Serial.flush();

  distancia = dist.toInt();

  // imprime el valor por el puerto serie
  Serial.print("Distancia: ");
  Serial.println(distancia);  
    
  // Enciende diferentes LEDS en funcion de la distancia
  if (distancia < 150 && distancia > 0) {
    digitalWrite(O0, HIGH);
    digitalWrite(O1, LOW);
    digitalWrite(O2, LOW);
  }
  if (distancia > 150 && distancia < 500) {
    digitalWrite(O0, LOW);
    digitalWrite(O1, HIGH);
    digitalWrite(O2, LOW);
  }
  if (distancia < 500) {
    digitalWrite(O0, LOW);
    digitalWrite(O1, LOW);
    digitalWrite(O2, HIGH);
  }
    
  delay(5000);
}


