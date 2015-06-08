/*
 * Etopia Kids - IoT
 * Campamento de Verano 2015
 *
 * Tutorial 1 - Ejemplo 3 - TUITEA
 *
 * Manda un mensaje a la cuenta IoT de Etopia Kids desde tu
 * Arduino YUN. El programa mandara un tuit cuando presiones
 * un boton que habras conectado como entrada a tu Arduino.
 *
 * Puedes mandar cualquier texto que tu quieras. Solo tienes
 * que cambiar el texto en el programa. Para ver tu mensaje
 * abre un navegador en: https://twitter.com/zgz_iot
 *
 * Eso si, Twitter se proteje de que alguien intente mandar el
 * mismo mensaje muchas veces seguidas, asi que tendras que
 * esperar a que alguien mande otro mensaje antes de poder enviar
 * de nuevo el mismo.
 *
 * ATENCION: Asegurate de que tu mensaje es diferente del que
 *           estan mandando los demas en el taller ;-)
 *
 * Conecta un BOTON en el conector I0 de tu Shield.
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
int boton = 0;
int botonViejo = 0;

// este es el mensaje para Twitter, cambialo por lo que quieras
String mensaje = "Nada no pasa nada!";

void setup() {
  // configura el pin del LED
  pinMode(O0, OUTPUT);

  // configura el pin del BOTON
  pinMode(I0, OUTPUT);

  // apaga el led y enciendelo cuando este todo listo
  digitalWrite(O0, LOW);
  Bridge.begin();
  digitalWrite(O0, HIGH);

  // configura el puerto serie
  Serial.begin(9600);

  while (!Serial); // espera a abrir el monitor serie
}

void loop() {
  boton = digitalRead(I0);

  if ( boton == HIGH && botonViejo == LOW) {
    // envia un tuit, majete
    String servidor = "http://verkstad.cc/iot/zgz/code/twitter/code/sendTweet.php?pass=tobbe&message=";
    String url = "";
    mensaje = urlEncode(mensaje); // esto ajusta el mensaje para ponerlo en la url
    url = servidor + mensaje;
    client.get(url);

    Serial.println("Tuit enviado!");
  }

  // reinicia las variables del boton
  botonViejo = boton;
}


