/*
 * Etopia Kids - IoT 
 * Campamento de Verano 2015 
 *
 * Tutorial 1 - Ejemplo 2 - SONIDO POR TEMPERATURA
 *
 * Toca un sonido segun la temperatura de una ciudad del
 * mundo que tu elijas. Este programa mostrara la temperatura
 * por el monitor serie y, ademas, tomara la temperatura de la
 * pagina web de: http://openweathermap.org
 * 
 * Puedes ver cualquier ciudad del mundo que tu elijas, solo
 * tienes que poner el nombre de la ciudad y el codigo del
 * pais con dos letras (por ejemplo: Zaragoza,es o London,uk)
 *
 * Para ver los codigos de los diferentes paises, puedes mirar
 * en esta pagina web: http://es.wikipedia.org/wiki/ISO_3166-1
 *
 * Conecta un PIEZO ELECTRICO en el conector O3 de tu Shield.
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
int temperatura = 0;

void setup() {
  // configura el pin del LED
  //pinMode(O0, OUTPUT);
  
  // configura el pin del PIEZO
  pinMode(O3, OUTPUT);

  // apaga el led y enciendelo cuando este todo listo
 // digitalWrite(O0, LOW);
  Bridge.begin();
  //digitalWrite(O0, HIGH);

  // configura el puerto serie
  Serial.begin(9600);

  while (!Serial); // espera a abrir el monitor serie
}

void loop() {
  // pide la temperatura
  client.get("http://verkstad.cc/iot/zgz/code/get_temperature.php?city=Zaragoza&country=es");

  // inicializa la temperatura
  temperatura = 0;
  
  // cuando lleguen datos de internet
  // sumalos en la variable temperatura
  while (client.available()) {
    char c = client.read();
    temperatura = temperatura * 10 + int(c) - 48;
  }
    // Quitamos los decimales de la temperatura
  if(temperatura >99)temperatura*=0.01; 
  
  Serial.flush();

  Serial.print("Temperatura: ");  
  Serial.println(temperatura);
  
  // si la temperatura esta por encima de 25 grados
  // toca un sonido durante medio segundo
  if( temperatura > 25 ) 
    tone(O3, 440, 500);
  else
    noTone(O3);

  delay(5000);
}


