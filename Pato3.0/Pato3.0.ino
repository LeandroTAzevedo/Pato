#include <Servo.h>

int portBase = 3;                                               // Porta associada ao motor do pescoço - PWM
int portNeck = 6;                                               // Porta associada ao motor da base - PWM
int difb;
int difn;
unsigned long posqb = 0;
unsigned long posqn = 40;
unsigned long posb = 90;    
unsigned long posn = 40;                                                  // Variável auxiliar para armazenar a posição do motor de interesse
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
  Serial.println("Salve tropa!");
}

unsigned long getUserInputBlocking(const char * message) {
  unsigned long result = 0;
  bool receiving = true;
  bool acquisitionStarted = false;
  Serial.println(message);
  do {
    int r = Serial.peek();
    if (r != -1) { // got something
      if (isdigit(r)) {
        acquisitionStarted = true;
        Serial.read(); // remove the byte from the incoming stream
        result = 10 * result + (r - '0'); // do the math, might overflow.
      } else {
        if (acquisitionStarted) {
          receiving = false; // we are done
        } else {
          Serial.read(); // ignore that byte and remove it from the incoming stream
        }
      }
    }
  } while (receiving);
  return result;
}



void loop() {
  //Teste da excursão do motor do pescoço
  unsigned long menuchoice = getUserInputBlocking("Digite o caso desejado : ");
  Serial.print(menuchoice);
  delay(100);

  // read the incoming byte:
  if(menuchoice == 1){
    posqn = getUserInputBlocking("digite sua posição do Pescoco: ");
    flagn = true;
    if (posqn >= 180){
      Serial.print("Apenas valores menores que 180");
      flagn = false;
    }
    delay(500);}

  if(menuchoice == 2){
    // read the incoming byte:
    posqb = getUserInputBlocking("digite sua posição da Base: ");
    flagb = true;
    if (posqb >= 180){
      Serial.print("Apenas valores menores que 180");
      flagb = false;
    }
    delay(500);}


  if(flagn == true && flagb == true){

    while(posqn != posn || posqb != posb){
      Serial.println("------");
      Serial.println(posqn);
      Serial.println(posn);
      Serial.println(posqb);
      Serial.println(posb);
      difb = posqb - posb;
      difn = posqn - posn;

    if (difb < 5 && difb > -5){
      Serial.println("oi1");
      posb = posqb;
      motBase.write(posb);
      delay(30);
    }

    if (difn <= 5 && difn >= -5){
      Serial.println("oi2");
      posn = posqn;
      motNeck.write(posn);
      delay(30);
    }

    if (posqb > posb){
        posb += 3;
        motBase.write(posb);
        delay(30);
    }

    if (posqb < posb){
      posb -= 3;
      motBase.write(posb);
      delay(30);
    }

    if (posqn > posn){
      posn += 3;
      motNeck.write(posn);
      delay(30);
    }

    if (posqn < posn){
      posn -= 3;
      motNeck.write(posn);
      delay(30);
    }

    delay(50);
    }
    flagn = false;
    flagb = false;
    }
  }