//#include <HCSR04.h>

#define pinoReceptor 9  //pino que recebe impulso ultrassonico
#define pinoEmissor 8  //pino que emite impulso ultrassonico
#define trig 4
#define velmotor_a 2
#define m1a 13
#define m2a 12
#define velmotor_b 3
#define m1b 10
#define m2b 11
#define pinoSensor 7
unsigned int duracao = 0;
unsigned int distancia = 0;

void setup() {
  pinMode(pinoReceptor, INPUT);
  pinMode(pinoEmissor, OUTPUT);
  pinMode(trig, INPUT);
  Serial.begin(9600);
  // motores
  pinMode(m1a, OUTPUT);
  pinMode(m2a, OUTPUT);
  pinMode(m1b, OUTPUT);
  pinMode(m2b, OUTPUT);
}
//leitura ultrasssonico 1
void ReadSensor() {
  digitalWrite(pinoEmissor, HIGH);
  delayMicroseconds(10);
  digitalWrite(pinoEmissor, LOW);
}
//leitura ultrassonico 2
void ReadSensor2() {
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
}

void Infravermelho() {
  pinMode(pinoSensor, INPUT);   //DEFINE O PINO COMO ENTRADA
  pinMode(pinoSensor, OUTPUT);  //DEFINE O PINO COMO SAÍDA
}
//movimentação
void Forward() {
  digitalWrite(m1a, HIGH);
  digitalWrite(m2a, LOW);
  digitalWrite(m1b, HIGH);
  digitalWrite(m2b, LOW);
}

void StopCar() {
  digitalWrite(m1a, HIGH);
  digitalWrite(m2a, HIGH);
  digitalWrite(m1b, HIGH);
  digitalWrite(m2b, HIGH);
}
void Right() {
  digitalWrite(m1a, HIGH);
  digitalWrite(m2a, LOW);
  digitalWrite(m1b, LOW);
  digitalWrite(m2b, HIGH);
}

void Left() {
  digitalWrite(m1a, LOW);
  digitalWrite(m2a, HIGH);
  digitalWrite(m1b, HIGH);
  digitalWrite(m2b, LOW);
}
void Backward() {
  digitalWrite(m1a, LOW);
  digitalWrite(m2a, HIGH);
  digitalWrite(m1b, LOW);
  digitalWrite(m2b, HIGH);
}

// mostrar distancia em monitor serial
void PrintDistance(unsigned int distance) {
  Serial.print(distance);
  Serial.println("cm");
  delay(100);
}

void loop() {
  ReadSensor();
  duracao = pulseIn(pinoReceptor, HIGH);
  //calculo de precisão para ultrassonico
  distancia = duracao * 0.017175;  // (343,5100) / 10e6, vel do som no ar 340 m/s, multiplica por 100 pra achar em cm.
  //depois divide por um milhao pois esta sendo medido em microsegundos.
  //divide por dois, pois o sinal vai ate o objeto, bate e volta. Fazendo o trajeto duas vezes.

  PrintDistance(distancia);  //printa a distancia no monitor serial
  //condicional de movimento
  if (distancia >= 40) {
    Forward();
    //Serial.println("Teste");
  } else {
    StopCar();
  }
  //se o infravermelho identificar ele para o carro
  if (digitalRead(pinoSensor) == HIGH) {
    Backward();
    Left();
  } else {
    Forward();
  }
}