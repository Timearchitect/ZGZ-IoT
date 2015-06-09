#include <ZGZ_IoT.h>
#include <Bridge.h>
#include <HttpClient.h>
#define COIN_VALUE_1 1
#define COIN_VALUE_2 2
#define COIN_VALUE_3 10


HttpClient client;
int boton1 = 0;
int boton2 = 0;
int boton3 = 0;
int botonViejo1 = 0;
int botonViejo2 = 0;
int botonViejo3 = 0;

int money = 0;
// este es el mensaje para Twitter, cambialo por lo que quieras
String mensaje = "Nada no pasa nada!";

void setup() {
  // configura el pin del LED
  pinMode(O0, OUTPUT); // 1 euro
  pinMode(O1, OUTPUT); // 2 euro
  pinMode(O2, OUTPUT); // 10 euro

  // configura el pin del BOTON
  pinMode(I0, INPUT); // 1 euro
  pinMode(I1, INPUT); // 2 euro
  pinMode(I2, INPUT); // 10 euro

  // apaga el led y enciendelo cuando este todo listo
  //digitalWrite(O0, LOW);
  Bridge.begin();
  // digitalWrite(O0, HIGH);

  // configura el puerto serie
  Serial.begin(9600);

  while (!Serial); // espera a abrir el monitor serie
}

void loop() {
  boton1 = digitalRead(I0);
  boton2 = digitalRead(I1);
  boton3 = digitalRead(I2);

  if ( boton1 == HIGH && botonViejo1 == LOW) {
    money += COIN_VALUE_1;
    Serial.print("+");
    Serial.println(COIN_VALUE_1);
    digitalWrite(O0, HIGH);
    sendAmount();
  }
  if ( boton2 == HIGH && botonViejo2 == LOW) {
    money += COIN_VALUE_2;
    Serial.print("+");
    Serial.println(COIN_VALUE_2);
    digitalWrite(O1, HIGH);
    sendAmount();
  }
  if ( boton3 == HIGH && botonViejo3 == LOW) {
    money += COIN_VALUE_3;
    Serial.print("+");
    Serial.println(COIN_VALUE_3);
    digitalWrite(O2, HIGH);
    sendAmount();
  }

  // reinicia las variables del boton
  botonViejo1 = boton1;
  botonViejo2 = boton2;
  botonViejo3 = boton3;

  Serial.print("My hucha : ");
  Serial.println(money);

  delay(50);
  digitalWrite(O0, LOW);
  digitalWrite(O1, LOW);
  digitalWrite(O2, LOW);

}


void sendAmount() {

  // envia un tuit, majete
  String servidor = "http://verkstad.cc/iot/zgz/code/twitter/code/sendTweet.php?pass=tobbe&message=";
  String url = "";
  mensaje = mensaje + money;
  mensaje = urlEncode(mensaje); // esto ajusta el mensaje para ponerlo en la url
  url = servidor + mensaje;
  client.get(url);

  Serial.print("Tuit enviado! " );
  Serial.println(money);

  delay(500);
}
