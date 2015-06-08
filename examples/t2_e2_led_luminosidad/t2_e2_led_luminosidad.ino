/*
 * Etopia Kids - IoT 
 * Campamento de Verano 2015 
 *
 * Tutorial 2 - Ejemplo 2 - LEDS POR LUMINOSIDAD
 *
 * Enciende un LED segun la luminosidad de una ciudad del
 * mundo que tu elijas. Este programa mostrara las condiciones
 * de las nubes y la hora del dia de una ciudad que tu escribas
 * por el monitor serie gracias a las paginas web de:
 *
 * http://openweathermap.org
 * 
 * y
 *
 * http://api.geonames.org/
 * 
 * Puedes ver cualquier ciudad del mundo que tu elijas, solo
 * tienes que poner el nombre de la ciudad y el codigo del
 * pais con dos letras (por ejemplo: Zaragoza,es o London,uk)
 *
 * Los codigos de nubes de las ciudades se descodifican segun la
 * siguiente tabla:
 *
 * ID   Significado
 * 800  cielo despejado  
 * 801  pocas nubes  
 * 802  nubes medianas  
 * 803  nubes rotas por zonas de sol  
 * 804  muy cubierto de nubes
 *
 * Para ver los codigos de los diferentes paises, puedes mirar
 * en esta pagina web: http://es.wikipedia.org/wiki/ISO_3166-1
 *
 * Conecta un LED en el conector O0 de tu Shield.
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
int nubosidad = 0;
int noche = 0; // 0 - dia, 1 - noche

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
  // pide la informacion de nubes
  client.get("http://verkstad.cc/iot/zgz/code/get_luminosity.php?city=Zaragoza&country=es");

  // inicializa la nubosidad y el dia
  nubosidad = 0;
  noche = 0;
  
  // cuando lleguen datos de internet
  // sumalos en la variable nubosidad
  while (client.available()) {
    String nub = client.readStringUntil(';');
    String n = client.readStringUntil(';');
//    char c = client.read();
//    nubosidad = nubosidad * 10 + int(c) - 48;
    nubosidad = nub.toInt();
    noche = n.toInt();
  }
  Serial.flush();

  Serial.print("Nubosidad: ");  
  Serial.println(nubosidad);
  Serial.print("Noche: ");  
  Serial.println(noche);
  
  if( nubosidad == 800 ) 
    analogWrite(O0, 00);    // si el cielo esta despejado no hace falta luz
  if( nubosidad == 801 ) 
    analogWrite(O0, 64);    // cuantas mas nubes, mas luz
  if( nubosidad == 802 ) 
    analogWrite(O0, 128);   // luz a mitad de intensidad
  if( nubosidad == 803 ) 
    analogWrite(O0, 192);   // enciende mas la luz
  if( nubosidad == 804 ) 
    analogWrite(O0, 255);   // si esta cubierto, enciende la luz del todo
  if( noche )
    analogWrite(O0, 255);   // si es de noche, enciende la luz del todo
    
  delay(5000);
}


