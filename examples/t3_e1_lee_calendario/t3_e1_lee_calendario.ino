/*
 * Etopia Kids - IoT 
 * Campamento de Verano 2015 
 *
 * Tutorial 3 - Ejemplo 1 - LEE CALENDARIO
 *
 * Lee el dia del mes de una pagina web y lo usa para hacer un
 * calendario fisico. Ejemplo:
 *
 * http://verkstad.cc/iot/zgz/code/get_date.php
 * 
 * Conecta un LED en el conector O0 y un servo en O4.
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

void setup() {
  // configura el pin del LED
  pinMode(O0, OUTPUT);

  // configura el pin del SERVO
  motor.attach(O4);
  
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
  String url =  "http://verkstad.cc/iot/zgz/code/get_date.php";
  // lee la informacion de la fecha
  client.get(url);

  int angulo = 0;

  while (client.available()) {
    char c = client.read();
    angulo = angulo * 10 + c - 48;
  }
  Serial.flush();

  // como la fecha va de 1 a 31, mapea eso en el angulo del motor
  angulo = map(angulo, 1, 31, 0, 180);

  // mueve el motor
  motor.write(angulo);

  // imprime el valor por el puerto serie
  Serial.print("Angulo: ");
  Serial.println(angulo);  
    
  delay(5000);
}


