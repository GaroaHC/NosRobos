//código line-follower básico
// por Erin Pinheiro 2014-11-14
// usa Arduino Motor Shield com 2 motores DC e 3 sensores IR na frente do robô

//pinos de controle dos motores
// A = esquerdo, B = direito
#define DIRA 12
#define PWMA 3
#define BRKA 9
#define DIRB 13
#define PWMB 11
#define BRKB 8

//pinos de leitura dos sensores
#define IRL 5
#define IRC 6
#define IRR 7

//full speed
#define FULLSP 200
//half speed
#define HALFSP 150

//delay para curva
#define TURNDLY 20
//delay para curva aguda
#define SHARPDLY 80

void setup() {
  pinMode(IRL,INPUT);
  pinMode(IRC,INPUT);
  pinMode(IRR,INPUT);
  pinMode(DIRA,OUTPUT);
  pinMode(PWMA,OUTPUT);
  pinMode(BRKA,OUTPUT);
  pinMode(DIRB,OUTPUT);
  pinMode(PWMB,OUTPUT);
  pinMode(BRKB,OUTPUT);
}

void loop() {
  //esta linha transforma a leitura LOW dos sensores em
  // um byte, onde 001 é esq, 010 é meio e 100 é dir.
  // isso facilita a lógica pra mim
  byte sens = (digitalRead(IRL)==LOW) + (digitalRead(IRC)==LOW)*2 + (digitalRead(IRR)==LOW)*4;
  
  switch(sens) {
    case B00000001: // 1 0 0
      turn_left(); break;
    case B00000100: // 0 0 1
      turn_right(); break;
    case B00000011: // 1 1 0
      sharp_left(); break;
    case B00000110: // 0 1 1
      sharp_right(); break;
    case B00000010: // 0 1 0
      forward(); break;
    case B00000111: // 1 1 1
      forward(); break;
    default:
      forward();
  }
}

void forward() {
  digitalWrite(DIRA,HIGH); // frente
  digitalWrite(DIRB,HIGH); // frente
  analogWrite(PWMA,FULLSP); // full speed ahead!
  analogWrite(PWMB,FULLSP);
  digitalWrite(BRKA,LOW); // sem freio
  digitalWrite(BRKB,LOW);
}

void turn_left() {
  digitalWrite(DIRA,HIGH); // frente
  digitalWrite(DIRB,HIGH); // frente
  analogWrite(PWMA,0);
  analogWrite(PWMB,FULLSP);
  digitalWrite(BRKA,LOW);
  digitalWrite(BRKB,LOW);
  delay(TURNDLY);
}

void turn_right() {
  digitalWrite(DIRA,HIGH); // frente
  digitalWrite(DIRB,HIGH); // frente
  analogWrite(PWMA,FULLSP);
  analogWrite(PWMB,0);
  digitalWrite(BRKA,LOW);
  digitalWrite(BRKB,LOW);
  delay(TURNDLY);
}

void sharp_left() {
  digitalWrite(DIRA,LOW);  // trás
  digitalWrite(DIRB,HIGH); // frente
  analogWrite(PWMA,HALFSP);
  analogWrite(PWMB,HALFSP);
  digitalWrite(BRKA,LOW);
  digitalWrite(BRKB,LOW);
  delay(SHARPDLY);
}

void sharp_right() {
  digitalWrite(DIRA,HIGH); // frente
  digitalWrite(DIRB,LOW);  // trás
  analogWrite(PWMA,HALFSP);
  analogWrite(PWMB,HALFSP);
  digitalWrite(BRKA,LOW);
  digitalWrite(BRKB,LOW);
  delay(SHARPDLY);
}

void brake() {
  digitalWrite(DIRA,HIGH); // frente
  digitalWrite(DIRB,HIGH); // frente
  analogWrite(PWMA,0); // não acelera
  analogWrite(PWMB,0);
  digitalWrite(BRKA,HIGH); // freio
  digitalWrite(BRKB,HIGH);
}
