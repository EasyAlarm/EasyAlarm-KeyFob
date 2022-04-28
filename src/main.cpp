#include <Arduino.h>
#include <LowPower.h>
#include "pins.h"

bool isAwaken = false;

void Arm();

void WakeUp();

void setup()
{
  Serial.begin(9600);
  pinMode(ARM_LOCKDOWN_BUTTON, INPUT);
  pinMode(ARM_NIGHT_BUTTON, INPUT);
  pinMode(DISARM_BUTTON, INPUT);
  pinMode(PANIC_BUTTON, INPUT);
  pinMode(INTERRUPT_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);

  attachInterrupt(digitalPinToInterrupt(INTERRUPT_PIN), WakeUp, HIGH);
  // put your setup code here, to run once:
}
void Arm()
{
  digitalWrite(LED_PIN, HIGH);
  delay(1000);
  digitalWrite(LED_PIN, LOW);
}

void WakeUp()
{
  Serial.println("Interrupt called");
  isAwaken = true;
}

void loop()
{
  if (isAwaken)
  {
    delay(100);
    //if both buttons are pressed
    if (digitalRead(ARM_LOCKDOWN_BUTTON) == HIGH)
    {
      Serial.println("lockdown");
    }
    else if (digitalRead(ARM_NIGHT_BUTTON) == HIGH)
    {
      Serial.println("night");
    }
    else if (digitalRead(DISARM_BUTTON) == HIGH)
    {
      Serial.println("disarm");
    }
    else if (digitalRead(PANIC_BUTTON) == HIGH)
    {
      Serial.println("panic");
    }
  }

  isAwaken = false;

  Serial.flush();
  LowPower.powerDown(SLEEP_FOREVER, ADC_OFF, BOD_OFF);
}
