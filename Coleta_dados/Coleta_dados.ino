#include "TimerOne.h"
double dt = 0.0001 ; // Intervalo de amostragem em segundos
bool chave = false;
double last_error = 0;
unsigned long last_time;


void reset_PWM(){
    chave = !chave;
    delay(500);
}
void Dados(){
  int sensor_value = analogRead(A0);
  
  Serial.println(sensor_value);

  // Envia o sinal de controle para o atuador
  analogWrite(6, 127);

  // Espera o intervalo de amostragem
  delay(dt * 1000);

  // Armazena o tempo atual para uso no próximo ciclo
  last_time = millis();


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
      Dados();
    }else{
      analogWrite(6,0);
      Serial.println(analogRead(A0));
      delay(dt * 1000);
    }
  }
