#include <Servo.h>

int x = A0; //Saída analógica (Eixo X)
int y = A1; //Saída analógica (Eixo Y)

int portBase = 3;                                               // Porta associada ao motor do pescoço - PWM
int portNeck = 6;                                               // Porta associada ao motor da base - PWM
int difb;                                                       // variaveis de verificaçao
int difn;
int hor;
int ver;
unsigned long posqb = 90;                                       //Variavel auxiliar para armazenar a posição desejada para o motor
unsigned long posqn = 90;
unsigned long posb = 90;    
unsigned long posn = 90;                                        // Variável auxiliar para armazenar a posição do motor de interesse

Servo motNeck;                                                  // Motor do pescoço
Servo motBase;                                                  // Motor da base


void setup() {
  // put your setup code here, to run once:
  motNeck.attach(portNeck);                                     // Acopla o pino ao motor da base
  motBase.attach(portBase);                                     // Acopla o pino ao motor do pescoço

  delay(30);                                                    // Garante que as informações foram armazenadas

  motNeck.write(posn);                                             // Coloca o motor na posição inicial
  motBase.write(posb);                                             // Coloca o motor na posição inicial

  Serial.begin(9600); // opens serial port, sets data rate to 9600 bps

}

unsigned long movB(unsigned long querob, unsigned long posb){
  while (posb != querob){                                           // Faz com que a base se mexa caso a posição desejada seja diferente da posicao atual
    Serial.println(querob);
    Serial.println(posb);
    difb = querob - posb;
    if (difb < 5 && difb > -5){   // pula direto para o resultado requerido para evitar que o valor não seja multiplo do passo
      posb = querob;
      motBase.write(posb);
      delay(70);
    }

  if (querob > posb){                                                //Faz com que o motor atue suavemente
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
  delay(50);                                                        //Garante um tempo de espera entre as açoes

}

unsigned long movN(unsigned long queron, unsigned long posn){        //Mesma coisa da base, mas para o pescoço
  while (posn != queron){
    Serial.println(queron);
    Serial.println(posn);
    difn = queron - posn;
    if (difn < 5 && difn > -5){    // pula direto para o resultado requerido para evitar que o valor não seja multiplo do passo
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
  hor = analogRead(x);                                                //Le os valores das entradas analógicas
  ver = analogRead(y);
  
  if (hor >= 1010){                                                   //Verifica a posição do joystick e incremente os valores desejados de posição
    posqb += 5;                                                       //baseado na direção que o joystick mudou, além de bloquear de mudar caso passe do valor max
    if (posqb >= 180){
      posqb = 180;
    }
    posb = movB(posqb, posb);
  }
if (hor <= 10){
    posqb -= 5;
    if (posqb <= 0 || posqb > 400){
      posqb = 0;
    }
    posb = movB(posqb, posb);
  }

  if (ver <= 10){
    posqn += 5;
    if (posqn >= 180){
      posqn = 180;
    }
    posn = movN(posqn, posn);
  }
if (ver >= 1010){
    posqn -= 5;
    if (posqn <= 0 || posqn > 400){
      posqn = 0;
    }
    posn = movN(posqn, posn);
  }
delay(200);
}
