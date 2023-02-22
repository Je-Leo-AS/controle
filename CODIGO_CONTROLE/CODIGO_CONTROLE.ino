#include "TimerOne.h"

double kp = 0.8; // Constante proporcional
double ki = 50; // Constante integral

double setpoint =  455.0; // Valor desejado
double error, integral = 0;
double last_error = 0;


unsigned long last_time;
double dt = 0.005; ; // Intervalo de amostragem em segundos
bool chave = false;

void reset_PWM(){
    chave = !chave;
}
void Controle_PI(){
  int sensor_value = analogRead(A0);
  
  Serial.println(sensor_value);

  // Calcula o erro atual
  error = setpoint - sensor_value;

  // Calcula a parte proporcional
  double proportional = kp * error;

  // Calcula a parte integral
  integral = integral + ki * error * dt;

  // Limita o valor da integral para evitar saturação
  if (integral > 255) {
    integral = 255;
  } else if (integral < -255) {
    integral = -255;
  }

  // Calcula a saída do controlador
  double output = proportional + integral;

  // Limita o valor da saída
  if (output > 255) {
    output = 255;
  } else if (output < 0) {
    output = 0;
  }

  // Envia o sinal de controle para o atuador
  analogWrite(6, output);

  // Armazena o valor do erro para uso no próximo ciclo
  last_error = error;

  

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
      Controle_PI();
    }else{
      analogWrite(6,0);
      Serial.println(analogRead(A0));
      delay(dt * 1000);
    }
  }
