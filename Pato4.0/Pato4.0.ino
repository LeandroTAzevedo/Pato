#include <Servo.h>

int portBase = 3;                                               // Porta associada ao motor do pescoço - PWM
int portNeck = 6;                                               // Porta associada ao motor da base - PWM
int difb;
int difn;
unsigned long posqb;
unsigned long posqn;
unsigned long posb = 90;    
unsigned long posn = 90;                                                  // Variável auxiliar para armazenar a posição do motor de interesse

Servo motNeck;                                                  // Motor do pescoço
Servo motBase;                                                  // Motor da base

void setup() {
  motNeck.attach(portNeck);                                     // Acopla o pino ao motor da base
  motBase.attach(portBase);                                     // Acopla o pino ao motor do pescoço

motNeck.write(posn);                                             // Coloca o motor na posição inicial
motBase.write(posb);

  delay(30);                                                    // Garante que as informações foram armazenadas                                             // Coloca o motor na posição inicial

  Serial.begin(9600); // opens serial port, sets data rate to 9600 bps
  Serial.println("Salve tropa!");

}

unsigned long movB(unsigned long querob, unsigned long posb){
  while (posb != querob){
    Serial.println(querob);
    Serial.println(posb);
    difb = querob - posb;
    if (difb < 5 && difb > -5){
      Serial.println("oi1");
      posb = querob;
      motBase.write(posb);
      delay(70);
    }

  if (querob > posb){
        posb += 3;
        motBase.write(posb);
        delay(70);
    }

  if (querob < posb){
      posb -= 3;
      motBase.write(posb);
      delay(70);
    }
  }
  return posb;
  delay(500);

}

unsigned long movN(unsigned long queron, unsigned long posn){
  while (posn != queron){
    Serial.println(queron);
    Serial.println(posn);
    difn = queron - posn;
    if (difn < 5 && difn > -5){
      Serial.println("oi2");
      posn = queron;
      motNeck.write(posn);
      delay(30);
    }

  if (queron > posn){
        posn += 3;
        motNeck.write(posn);
        delay(30);
    }

  if (queron < posn){
      posn -= 3;
      motNeck.write(posn);
      delay(30);
    }
}
return posn;
delay(500);
}






void loop() {
  //Teste da excursão do motor do pescoço
posqb = 120;
posb = movB(posqb, posb);
delay(1000);
posqn = 180;
posn = movN(posqn, posn);
delay(100);
posqn = 85;
posn = movN(posqn, posn);
delay(1000);
posqb = 60;
posb = movB(posqb, posb);
delay(1000);
posqn = 180;
posn = movN(posqn, posn);
delay(100);
posqn = 85;
posn = movN(posqn, posn);
delay(1000);
    
  }