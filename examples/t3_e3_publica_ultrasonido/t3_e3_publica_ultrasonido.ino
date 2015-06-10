/*
 * Etopia Kids - IoT
 * Campamento de Verano 2015
 *
 * Tutorial 2 - Ejemplo 3 - PUBLICA ULTRASONIDO
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

// para almacenar el numero de la cancion a escuchar
int cancion = 0;

// declara las variables donde se guardan las notas y
// las duraciones al bajarlas de internet


const int  umbral = 100;
void setup() {
  // configura el pin del LED
  pinMode(O0, OUTPUT);
  
  // configura el pin del PIEZO
  pinMode(O3, OUTPUT);

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
  int distancia = analogRead(I1);

  // url
  String url =  "http://verkstad.cc/iot/zgz/";
  url += grupo;
  url += "/index.php?distancia=";
  url += distancia;
  // sube la informacion de la distancia
  client.get(url);

  // imprime el valor por el puerto serie
  Serial.print("distancia: ");
  Serial.println(distancia);

  // check if it should trigger the alarm
  if (distancia > umbral) 
  tone(O3, 1500, 1000);
    

  delay(5000);

}

