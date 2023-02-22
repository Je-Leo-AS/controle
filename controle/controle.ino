#include <Arduino.h>

#define PIN_INPUT 0
#define PIN_OUTPUT 9


double input, output, error;

double Kp, ki;

void setup() {
  Serial.begin(9600);
  pinMode(PIN_INPUT, INPUT);
  pinMode(PIN_OUTPUT, OUTPUT);

  // Recebimento do valor de Kp via serial

    Kp = 1;
}

void loop() {
  input = analogRead(PIN_INPUT);
  error = SETPOINT - input;
  output = Kp * error;
  analogWrite(PIN_OUTPUT, output);
  if (Serial.available()) {
  Kp = Serial.parseFloat();
    }

  // Plotagem da saída via serial
  Serial.println(output);
}
