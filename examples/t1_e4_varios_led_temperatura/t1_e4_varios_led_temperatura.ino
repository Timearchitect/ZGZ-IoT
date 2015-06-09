/*
 * Etopia Kids - IoT 
 * Campamento de Verano 2015 
 *
 * Tutorial 1 - Ejemplo 4 - VARIOS LEDS POR TEMPERATURA
 *
 * Enciende uno u otro LED segun la temperatura de una ciudad del
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
 * Conecta dos LEDs en los conectores O0 y O1 de tu Shield.
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
  // configura los pines de los LEDs
  pinMode(O0, OUTPUT);
  pinMode(O1, OUTPUT);
  
  // apaga el led y enciendelo cuando este todo listo
  digitalWrite(O0, LOW);
  Bridge.begin();
  digitalWrite(O0, HIGH);

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
  
  if( temperatura > 25 ) {
    digitalWrite(O0, HIGH);
    digitalWrite(O1, LOW);
  } else {
    digitalWrite(O0, LOW);
    digitalWrite(O1, HIGH);
  }

  delay(5000);
}


