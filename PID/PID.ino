#include "TimerOne.h"

double kp = 1.2; // Constante proporcional
double ki = 5999.999999999999; // Constante integral
double kd = 0.00048; // Constante diferencial


double setpoint =  455.0; // Valor desejado
double error, integral, proportional, diferencial, error_total, delta_error = 0;
double last_error = 0;


unsigned long last_time;
double dt = 0.0001;  // Intervalo de amostragem em segundos
bool chave = false;


void reset_PWM(){
    chave = !chave;
}
void Controle_PID(){
  int sensor_value = analogRead(A0);

  // Calcula o erro atual
  error = setpoint - sensor_value;

  error_total = error_total + error;

  delta_error = error - last_error;



  // Calcula a parte proporcional
  proportional = kp * error;

  // Calcula a parte integral
  integral = ki*error_total;

  // Calcula a parte diferencial
  diferencial = kd*delta_error;


  // Limita o valor da integral para evitar saturação
  if (integral > 255) {
    integral = 255;
  } else if (integral < -255) {
    integral = -255;
  }

  // Calcula a saída do controlador
  double output = proportional + integral + diferencial;

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


  // Armazena o tempo atual para uso no próximo ciclo
  last_time = millis();

//  ki = ki*dt;
//  kd = kd/dt;


}
void setup() {
  // Configura a porta do PWM para controlar a saída do sinal
  pinMode(6, OUTPUT);
  Serial.begin(9600);
  last_time = millis();
  Timer1.initialize(3000000); 
  Timer1.setPeriod(3000000);
  Timer1.attachInterrupt(reset_PWM);
  ki = ki*dt;
  kd = kd/dt;

}

void loop() {
    if(chave){
      Controle_PID();
    }else{
      analogWrite(6,0);
    }
    Serial.println(analogRead(A0));
    delay(dt*1000);
  }
