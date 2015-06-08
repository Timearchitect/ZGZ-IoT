/*
 * Etopia Kids - IoT
 * Campamento de Verano 2015
 *
 * Tutorial 2 - Ejemplo 1 - TOCA MELODIAS DE INTERNET
 *
 * Toca melodias que se descargan de una pagina de internet.
 * Hemos preparado un monton de canciones para que las puedas
 * tocar desde tu Arduino YUN. Solo tienes que conectar un PIEZO
 * ELECTRICO y un POTENCIOMETRO.
 *
 * Las canciones estan almacenadas en internet en un fichero
 * y tienen un numero identificador distinto cada una. Para ver
 * todas las canciones disponibles, ve a la url:
 * http://verkstad.cc/iot/zgz/code/get_song.php?number=-1
 *
 * Conecta un LED en el conector O0 un PIEZO en el O3 y un
 * POTENCIOMETRO en el I0 de tu Shield.
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
String notas;
String duraciones;
String titulo;
String longitud;

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
  // lee el potenciometro
  int sensor = analogRead(I0);

  // mapea el valor del sensor a uno que sea como
  // maximo el del maximo de canciones
  cancion = map(sensor, 0, 1024, 1, 3);

  // imprime que cancion se mostrara
  Serial.print("Buscando cancion: "); Serial.println(cancion);

  // pide la cancion
  String servidor = "http://verkstad.cc/iot/zgz/code/get_song.php?number=";
  String url = "";
  url = servidor + cancion;
  client.get(url);

  // antes de meter los datos de internet, borra lo viejo
  borraCancion();

  // cuando lleguen datos de internet
  // guardalos para poder tocar la cancion
  // la informacion en internet esta ordenada por:
  // titulo;longitud;notas;duraciones
  // y separada por punto y coma ';'
  while (client.available()) {
    titulo = client.readStringUntil(';');
    longitud = client.readStringUntil(';');
    notas = client.readStringUntil(';');
    duraciones = client.readStringUntil(';');
  }
  Serial.flush();

  Serial.print("Titulo: "); Serial.println(titulo);
  Serial.print("Longitud: "); Serial.println(longitud);
  Serial.print("Notas: "); Serial.println(notas);
  Serial.print("Duraciones: "); Serial.println(duraciones);
  Serial.println();
  Serial.println("listo");

  tocaMelodia();

  delay(5000);
}

void tocaMelodia() {
  for ( int i = 0; i < longitud.toInt(); i++) {
    int d = 1000 / extraeDuracion(i);
    float n = extraeNota(i);
    Serial.println(d);
    Serial.println(n);
    tone(O3, n, d);
    int pausa = d * 1.30;
    delay(pausa);
    // deja de tocar
    noTone(O3);
  }
}

float extraeNota(int j) {
  char nota[4];
  int cont = 0;
  int index = 0;
  for (int i = 0; i < notas.length(); i++) {
    if ( notas[i] != ',') {
      nota[cont] = notas.charAt(i);
      cont++;
    } else {
      float freq = frecuenciaNota(nota);
      if ( index == j ) {
        return freq;
      }
      cont = 0;
      for (int k = 0; k < 4; k++) nota[k] = 0;
      index++;
    }
  }
  return 0;
}

int extraeDuracion(int j) {
  char duracion[4];
  int cont = 0;
  int index = 0;
  Serial.println(duraciones.length());
  for (int i = 0; i < duraciones.length(); i++) {
    if ( duraciones[i] != ',' ) {
      duracion[cont] = duraciones.charAt(i);
      cont++;
    } else {
      if ( index == j ) {
        return String(duracion).toInt();
      }
      cont = 0;
      for (int k = 0; k < 4; k++) duracion[k] = 0;
      index++;
    }
  }
  return 0;
}

void borraCancion() {
  for (int i = 0; i < 64; i++) {
    notas[i] = 0;
    duraciones[i] = 0;
  }
}


float frecuenciaNota(char* s) {
  int octave;
  char letter, sharpFlat;

  letter = char(s[0]);
  if ( s[2] != 0 ) {
    sharpFlat = char(s[1]);
    octave = int(s[2]) - 48;
  } else {
    octave = int(s[1]) - 48;
    sharpFlat = ' ';
  }

  int semitones;
  int modifier;

  switch (letter)
  {
    case 'C' :
      semitones = 0;
      break;

    case 'D' :
      semitones = 2;
      break;

    case 'E' :
      semitones = 4;
      break;

    case 'F' :
      semitones = 5;
      break;

    case 'G' :
      semitones = 7;
      break;

    case 'A' :
      semitones = 9;
      break;

    case 'B' :
      semitones = 11;
      break;

    default :
      semitones = 2;
      break;
  }

  switch (sharpFlat)
  {
    case '#' :
      modifier = 1;
      break;

    case 'b' :
      modifier = -1;
      break;

    case ' ' :
      modifier = 0;
      break;
  }


  semitones = semitones + modifier + octave * 12;
  //  semitones = semitones + modifier;

  float basefreq = 16.35;
  float an = pow(1.059463, semitones);
  float freq = basefreq * an;

  return freq;
}
