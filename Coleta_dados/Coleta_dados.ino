#include "TimerOne.h"
double dt = 0.0001 ; // Intervalo de amostragem em segundos
bool chave = false;
double last_error = 0;
unsigned long last_time;
char inBuffer[4];

void reset_PWM(){
    chave = !chave;
}

void setup() {
  // Configura a porta do PWM para controlar a saída do sinal
  pinMode(6, OUTPUT);
  Serial.begin(9600);
  last_time = millis();
  Timer1.initialize(3000000); 
  Timer1.setPeriod(3000000);
  Timer1.attachInterrupt(reset_PWM);

}

void loop() {
    if(chave){
      analogWrite(6,127);
    }else{
      analogWrite(6,0);
    }
    Serial.println(analogRead(A0));
    delay(dt * 1000);
    if (Serial.available() > 0) {   //analisa se há dados na serial 
    Serial.readBytes(inBuffer, 4);  //lê o dado da serial em 3 caracteres ASCII
    dt = atof(inBuffer);    //converte o valor ASCII lido em um número inteiro  } 
    }
  }
