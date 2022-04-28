#include <Arduino.h>
#include <LowPower.h>

#define ARM_BUTTON 3
#define DISARM_BUTTON 4
#define LED_PIN A0
#define INTERRUPT_PIN 2

bool isAwaken = false;

void Arm();

void WakeUp();

void setup()
{
  Serial.begin(9600);
  pinMode(ARM_BUTTON, INPUT);
  pinMode(DISARM_BUTTON, INPUT);
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
    if (digitalRead(ARM_BUTTON) == HIGH && digitalRead(DISARM_BUTTON) == HIGH)
    {
      for (int i = 0; i < 100; i++)
      {
        digitalWrite(LED_PIN, HIGH);
        delay(50);
        digitalWrite(LED_PIN, LOW);
        delay(50);
      }
    }
    else if (digitalRead(ARM_BUTTON) == HIGH)
    {
      for (int i = 0; i < 10; i++)
      {
        digitalWrite(LED_PIN, HIGH);
        delay(100);
        digitalWrite(LED_PIN, LOW);
        delay(100);
      }
    }
    else if (digitalRead(DISARM_BUTTON) == HIGH)
    {
      digitalWrite(LED_PIN, HIGH);
      delay(1000);
      digitalWrite(LED_PIN, LOW);
    }
  }

  isAwaken = false;

  LowPower.powerDown(SLEEP_FOREVER, ADC_OFF, BOD_OFF);
}
