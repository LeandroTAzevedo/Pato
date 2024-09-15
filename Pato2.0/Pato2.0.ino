#include <Servo.h>

int portBase = 3;                                               // Porta associada ao motor do pescoço - PWM
int portNeck = 6;                                               // Porta associada ao motor da base - PWM
int posqb = 0;
int posqn = 40;
int posb = 0;    
int posn = 40;                                                  // Variável auxiliar para armazenar a posição do motor de interesse
bool flagn = false;
bool flagb = false;

Servo motNeck;                                                  // Motor do pescoço
Servo motBase;                                                  // Motor da base

void setup() {
  motNeck.attach(portNeck);                                     // Acopla o pino ao motor da base
  motBase.attach(portBase);                                     // Acopla o pino ao motor do pescoço

  delay(30);                                                    // Garante que as informações foram armazenadas

  motNeck.write(posn);                                             // Coloca o motor na posição inicial
  motBase.write(posb);                                             // Coloca o motor na posição inicial

  Serial.begin(9600); // opens serial port, sets data rate to 9600 bps

}

void loop() {
  

  delay(1000);                                                  // 1s de espera até o próximo teste

  //Teste da excursão do motor do pescoço
Serial.println("Digite o caso desejado:");
while (Serial.available() == 0) {}
int menuchoice = Serial.parseInt();

switch (menuchoice){

// read the incoming byte:
case 1: {
Serial.println("digite sua posição do pescoco: ");
while (Serial.available() == 0) {}
int posqn = Serial.parseInt();
flagn = true;
Serial.println(posqn);
delay(1000);}
break;



case 2:{
// read the incoming byte:
Serial.println("digite sua posição da base: ");
while (Serial.available() == 0) {}
int posqb = Serial.parseInt();
flagb = true;
Serial.println(posqb);
delay(1000);}
break;

default:{

if(flagn == true && flagb == true){
while(posqn != posn || posqb != posb){
Serial.println("ta rodando em");
if (posqb > posb){
  posb++;
  motBase.write(posb);
  delay(30);
}

if (posqb < posb){
  posb--;
  motBase.write(posb);
  delay(30);
}

if (posqn > posn){
  posb++;
  motBase.write(posn);
  delay(30);
}

if (posqn < posn){
  posn--;
  motBase.write(posn);
  delay(30);
}
delay(500);
}
}
}
}
}