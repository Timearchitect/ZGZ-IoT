/*
 * Campamento de Verano 2015
 *
 * Tutorial 4 - Ejemplo 1 - HUCHA COMUNITARIA
 *
 * Conecta el LED rojo en el pin 00, el amarillo en el pin 01 y el verde en el pin 02
 * Conecta los botones a los conectores I0, I1 e I2
 *
 * Cuando introduces la moneda y aprietas el boton correspondiente
 * Este programa pone un tweet con la cantidad total de dinero
 * Arduino cuenta la cantidad total de dinero que tu tienes y se pone a 0 cuando lo apagas
 *
 *
 * Etiqueta tus botones para identificar diferentes tipos de monedas
 * Ajusta los numeros en el codigo de abajo
 *
 * (c) 2015 D. Cuartielles para Arduino Verkstad
 *
 */


#include <ZGZ_IoT.h>
#include <Bridge.h>
#include <HttpClient.h>

HttpClient client;

// cambia los valores basándote en las monedas que vas a utilizar
const int VALOR_ROJO = 1;       // ajusta el valor de la moneda para e color rojo
const int VALOR_AMARILLO = 2;    // ajusta el valor de la moneda para e color amarillo
const int VALOR_VERDE = 10;  // ajusta el valor de la moneda para e color verde


// Estado de los botones
int boton1 = 0;
int boton2 = 0;
int boton3 = 0;

// Inicializa los botones para detectar si los cambias de estado
int botonViejo1 = 0;
int botonViejo2 = 0;
int botonViejo3 = 0;

int dinero = 0;

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

  // Lee el estado de los botones
  boton1 = digitalRead(I0);
  boton2 = digitalRead(I1);
  boton3 = digitalRead(I2);

  // Comprueba si el botón se ha pulsado pero no apretado continuamente
  if ( boton1 == HIGH && botonViejo1 == LOW) {
    // Suma el dinero en la hucha
    dinero += VALOR_ROJO;
    Serial.print("+");
    Serial.println(VALOR_ROJO);
    // Enciende el LED rojo
    digitalWrite(O0, HIGH);
    enviaCantidad();
  }
  if ( boton2 == HIGH && botonViejo2 == LOW) {
    // Suma el dinero en la hucha
    dinero += VALOR_AMARILLO;
    Serial.print("+");
    Serial.println(VALOR_AMARILLO);
    // Enciende el LED amarillo
    digitalWrite(O1, HIGH);
    enviaCantidad();
  }
  if ( boton3 == HIGH && botonViejo3 == LOW) {
    // Suma el dinero en la hucha
    dinero += VALOR_VERDE;
    Serial.print("+");
    Serial.println(VALOR_VERDE);
    // Enciende el LED verde
    digitalWrite(O2, HIGH);
    enviaCantidad();
  }

  // reinicia las variables del boton
  botonViejo1 = boton1;
  botonViejo2 = boton2;
  botonViejo3 = boton3;

  Serial.print("I hucha : ");
  Serial.println(dinero);

  delay(50);

  // Apaga los LEDs
  digitalWrite(O0, LOW);
  digitalWrite(O1, LOW);
  digitalWrite(O2, LOW);
}


void enviaCantidad() {

  // envia un tuit, majete
  // Tweet con la cantidad total de dinero que tu tienes

  String servidor = "http://verkstad.cc/iot/zgz/code/twitter/code/sendTweet.php?pass=tobbe&message=";
  String url = "";
  mensaje = mensaje + dinero;
  mensaje = urlEncode(mensaje); // esto ajusta el mensaje para ponerlo en la url
  url = servidor + mensaje;
  client.get(url);

  Serial.print("Tuit enviado! " );
  Serial.println(dinero);

  delay(500);
}
