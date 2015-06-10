/*
 * Etopia Kids - IoT
 * Campamento de Verano 2015
 *
 * Tutorial 4 - Ejemplo 2 - BINLDS VENTANA
 *
 * Lee informacion de un sensor analogico de una de las paginas
 * del campamento. Toma el nombre del grupo para cuyo sensor quieres
 * leer. Ejemplo:
 *
 * http://verkstad.cc/iot/zgz/1 donde "1" es el numero de ese grupo
 *
 * Puedes elegir numeros del 1 al 10. Esto permitira que leer los
 * valores de los sensores en la nube sin problema.
 *
 * Conecta un LED en el conector O0 para representar la luminosidad.
 *
 * (c) 2015 D. Cuartielles para Arduino Verkstad
 *
 * Este programa es GPLv3, usalo bajo tu responsabilidad
 *
 */

#include <ZGZ_IoT.h>
#include <Bridge.h>
#include <HttpClient.h>
#include <Servo.h>

HttpClient client;

Servo motor;

const int MAX_LENGTH = 1000;
const int MAX_LIGHT = 255;
int light = 0;
int level = 0;

void setup() {
  // configura el pin del LED
  motor.attach(O4);

  // apaga el led y enciendelo cuando este todo listo
  digitalWrite(O0, LOW);
  //Bridge.begin();
  digitalWrite(O0, HIGH);

  // configura el puerto serie
  Serial.begin(9600);

  //  while (!Serial); // espera a abrir el monitor serie
}

void loop() {
  /* // cambia este numero por el numero del grupo a leer grupo
   int grupo = 1;

   // url
   String url =  "http://verkstad.cc/iot/zgz/";
   url += grupo;
   url += "/get_value.php";
   // leee la informacion de la luminosidad
   client.get(url);

   int light = 0;

   while (client.available()) {
     char c = client.read();
     light = light * 10 + c - 48;
   }
   */
  //light = analogRead(I0);

  //Serial.flush();

  // imprime el valor por el puerto serie
  Serial.print("Luminosidad: ");
  Serial.println(light);
  Serial.print("Lenght level:");
  Serial.println(level);

  light = map(light, 0, 1023, 0, 180 );
  
  //level += light * 0.1;
   
  light =100;
  level += light * 0.5;
  level = constrain(level,0,MAX_LENGTH);
  
  if ( 0 < level  && level < MAX_LENGTH ) {
    // cambia la luminosidad del LED
    Serial.println(light);
    // servo motor
    motor.write(map(level,0,MAX_LENGTH,(-180),180));
  }
  delay(100);
}


