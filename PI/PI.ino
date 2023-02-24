#include "TimerOne.h"

double kp = 0.10;//0.36357869628624995; // Constante proporcional
double ki = 1000.341559306706; //750 // Constante integral



double setpoint =  455.0; // Valor desejado
double error, integral, proportional, error_total= 0;
double last_error = 0;


unsigned long last_time;
double dt = 0.00001;  // Intervalo de amostragem em segundos
bool chave = false;

void reset_PWM(){
    chave = !chave;
}
void Controle_PI(){
  int sensor_value = analogRead(A0);
  
  Serial.println(sensor_value);

  // Calcula o erro atual
  error = setpoint - sensor_value;

  error_total = error_total + error;

  // Calcula a parte proporcional
  proportional = kp * error;

  // Calcula a parte integral
  integral = error_total*ki ;

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


  // Armazena o tempo atual para uso no próximo ciclo
  last_time = millis();
  //ki = ki*dt;

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

}

void loop() {
    if(chave){
      Controle_PI();
    }else{
      analogWrite(6,0);
      Serial.println(analogRead(A0));
      
    }
    delay(dt * 1000);
  }
