#include "TimerOne.h"
#define SETPOINT 457


double input, output, error;
double dt = 0.01;
double Kp = 1;
bool chave = false;
char inBuffer[4];

void reset_PWM(){
    chave = !chave;
    delay(500);
}

void Controle_P(){
  input = analogRead(A0);
  error = SETPOINT - input;
  output = Kp * error;
  int PWM = int(constrain(output,0,255));
  analogWrite(6, PWM);
  // Plotagem da saída via serial
}
void setup() {
  // Configura a porta do PWM para controlar a saída do sinal
  pinMode(6, OUTPUT);
  Serial.begin(9600);
  Timer1.initialize(3000000); 
  Timer1.setPeriod(3000000);
  Timer1.attachInterrupt(reset_PWM);

}

void loop() {
    if(chave){
      Controle_P();
    }else{
      analogWrite(6,0);
    }
  Serial.print(analogRead(A0)); Serial.print("  "); Serial.println(Kp);
  delay(dt);

 if (Serial.available() > 0) {   //analisa se há dados na serial 
    Serial.readBytes(inBuffer, 4);  //lê o dado da serial em 3 caracteres ASCII
    Kp = atoi(inBuffer);    //converte o valor ASCII lido em um número inteiro  } 
    }
}
