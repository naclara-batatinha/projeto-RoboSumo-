#include <HCSR04.h>

#define pinoReceptor 9  //pino que recebe impulso ultrassonico(echo cinza)
#define pinoEmissor 8   //pino que emite impulso ultrassonico(trig branco)
#define velmotor_a 2
#define motor1a 13
#define motor2a 12
#define velmotor_b 3
#define motor1b 10
#define motor2b 11
#define InfravermelhoFrente 7
#define InfravermelhoCosta 6
unsigned int duracao = 0;
unsigned int distancia = 0;

void setup() {
  pinMode(pinoReceptor, INPUT);
  pinMode(pinoEmissor, OUTPUT);
  Serial.begin(9600);
  // motores
  pinMode(motor1a, OUTPUT);
  pinMode(motor2a, OUTPUT);
  pinMode(motor1b, OUTPUT);
  pinMode(motor2b, OUTPUT);
}
//leitura ultrasssonico 1
void ReadSensor() {
  digitalWrite(pinoEmissor, HIGH);
  delayMicroseconds(10);
  digitalWrite(pinoEmissor, LOW);
}
void Infravermelho1() {
  pinMode(InfravermelhoFrente, INPUT);   //DEFINE O PINO COMO ENTRADA
  delayMicroseconds(10);
  pinMode(InfravermelhoFrente, OUTPUT);  //DEFINE O PINO COMO SAÍDA
}
void Infravermelho2(){
pinMode(InfravermelhoCosta, INPUT);
pinMode(InfravermelhoCosta, OUTPUT);
}
//movimentação
void Forward() {
  digitalWrite(motor1a, LOW);
  digitalWrite(motor2a, HIGH);
  digitalWrite(motor1b, HIGH);
  digitalWrite(motor2b, LOW);
}

void StopCar() {
  digitalWrite(motor1a, LOW);
  digitalWrite(motor2a, LOW);
  digitalWrite(motor1b, LOW);
  digitalWrite(motor2b, LOW);
}
void Right() {
  digitalWrite(motor1a, LOW);
  digitalWrite(motor2a, HIGH);
  digitalWrite(motor1b, LOW);
  digitalWrite(motor2b, HIGH);
}

void Left() {
  digitalWrite(motor1a, HIGH);
  digitalWrite(motor2a, LOW);
  digitalWrite(motor1b, HIGH);
  digitalWrite(motor2b, LOW);
}
void Backward() {
  digitalWrite(motor1a, HIGH);
  digitalWrite(motor2a, LOW);
  digitalWrite(motor1b, LOW);
  digitalWrite(motor2b, HIGH);
}

// mostrar distancia em monitor serial
void PrintDistance(unsigned int distancia) {
  Serial.print(distancia);
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
  if (distancia < 40) {
    Backward();
  } 
  else {
    StopCar();
  }
    if (digitalRead(InfravermelhoFrente)== LOW){
      StopCar();
      Forward(); 
      Left();
    }
    
     else if (digitalRead(InfravermelhoCosta)== LOW){
      Backward();
    }
}
