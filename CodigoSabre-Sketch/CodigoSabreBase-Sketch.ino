
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h>
#endif

// DEFINIÇÕES DE PINOS
#define pinRx 10
#define pinTx 11

#define pinBot 2

#define pinSensor 4

#define pinLed 6

// DEFINIÇÕES
#define volumeMP3 20
#define NUMPIXELS 123

#define DEBUG
// INSTANCIANDO OBJETOS
SoftwareSerial playerMP3Serial(pinRx, pinTx);
Adafruit_NeoPixel pixels(NUMPIXELS, pinLed, NEO_GRB + NEO_KHZ800);

DFRobotDFPlayerMini playerMP3;

// DECLARAÇÃO DE FUNÇÕES


// DECLARAÇÃO DE VARIÁVEIS

int control = 0;
int botao;

int esq1 = 123;
int dir1 = 0;
int esq2 = 123;
int dir2 = 0;
int cor = 127;

void setup() {
	Serial.begin(9600);
	playerMP3Serial.begin(9600);

  Serial.println();
  Serial.println(F("Iniciando DFPlayer ... (Espere 3~5 segundos)"));

  if (!playerMP3.begin(playerMP3Serial)) {  // COMUNICAÇÃO REALIZADA VIA SOFTWARE SERIAL
    Serial.println(F("Falha ao iniciar:"));
    Serial.println(F("1.Confira as conexões!"));
    Serial.println(F("2.Confira o cartão SD!"));
    while(true){
      delay(0);
    }
  }

  Serial.println(F("DFPlayer ligado!"));

  playerMP3.volume(volumeMP3);
  
	#ifdef DEBUG
		Serial.println("Fim Setup");
	#endif	
  playerMP3.playFolder(2, 3);

  pinMode(pinBot,INPUT_PULLUP);

  #if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
  #endif

  pixels.begin();
}

void loop() {

  botao = digitalRead(pinBot);
    
  if(botao == 0 && control == 0){
    playerMP3.playFolder(1, 3);
    Serial.println("Tocando pasta 01, musica 003");
    Serial.println(control);
    Serial.println(digitalRead(pinBot));
    control = 1;
    Serial.println(control);
    Serial.println(digitalRead(pinBot));

    while(dir1<62){
      pixels.setPixelColor(dir1, pixels.Color(127, 127, 127));
      pixels.setPixelColor(esq1, pixels.Color(127, 127, 127));

      pixels.show();

      delay(5);

      esq1--;
      dir1++;
    }

     while(0 <= cor){
      while(dir2<62){
        pixels.setPixelColor(dir2, pixels.Color(cor,127, cor));
        pixels.setPixelColor(esq2, pixels.Color(cor,127,cor));

        dir2++;
        esq2--;
      }
      pixels.show();
      delay(2);

      dir2 = 0;
      esq2 = 123;
      cor--;
    }
    cor = 127;
    delay(1000);
  }

  //if(botao == 0){
    //playerMP3.playFolder(1, 2);
    //Serial.println("Tocando pasta 01, musica 002");
    //delay(1000);
  //}

  if(botao == 1 && control == 1){
    playerMP3.playFolder(1, 1);
    Serial.println("Tocando pasta 01, musica 001");
    Serial.println(control);
    Serial.println(digitalRead(pinBot));
    control = 0;
    Serial.println(control);
    Serial.println(digitalRead(pinBot));

    while(dir1>=0){
      pixels.setPixelColor(dir1, pixels.Color(0, 0, 0));
      pixels.setPixelColor(esq1, pixels.Color(0, 0, 0));

      pixels.show();

      delay(20);

      esq1++;
      dir1--;
    }
    delay(1000);
  }
  
  if(digitalRead(pinSensor) == HIGH && !digitalRead(pinBot)){
    playerMP3.playFolder(1, 5);
    Serial.println("Tocando pasta 01, musica 005");
    delay(1000);
  }
}
