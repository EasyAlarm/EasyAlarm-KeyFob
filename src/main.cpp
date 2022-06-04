#include <Arduino.h>
#include <LowPower.h>
#include "pins.h"
#include "pair.h"
#include "addresses.h"
#include "radio_manager.h"
#include "reset.h"
#include "radio_packet_handler.h"
#include "EEPROM.h"

uint16_t thisNode = PAIRING_NODE;
RadioManager radioManager;

bool isAwaken = false;
void WakeUp();
void OnPairButton();

void setup()
{
  Serial.begin(9600);
  pinMode(ARM_LOCKDOWN_BUTTON, INPUT);
  pinMode(ARM_NIGHT_BUTTON, INPUT);
  pinMode(DISARM_BUTTON, INPUT);
  pinMode(PANIC_BUTTON, INPUT);
  pinMode(INTERRUPT_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);

  if (Pair::IsPaired())
  {
    thisNode = EEPROM.read(0);
  }

  radioManager = RadioManager(CE_PIN, CSN_PIN, thisNode);

  radioManager.Init();

  attachInterrupt(digitalPinToInterrupt(INTERRUPT_PIN), WakeUp, HIGH);
  // put your setup code here, to run once:
}


void loop()
{
  if (isAwaken)
  {
    delay(100);
    if (digitalRead(DISARM_BUTTON) == HIGH && digitalRead(PANIC_BUTTON) == HIGH)
    {
      OnPairButton();
    }
    else if (digitalRead(ARM_LOCKDOWN_BUTTON) == HIGH)
    {
      radioManager.SendPacket(HUB_NODE, &RadioPacket(PayloadType::TRIGGERED, "1"));
    }
    else if (digitalRead(ARM_NIGHT_BUTTON) == HIGH)
    {
      radioManager.SendPacket(HUB_NODE, &RadioPacket(PayloadType::TRIGGERED, "2"));
    }
    else if (digitalRead(DISARM_BUTTON) == HIGH)
    {
      radioManager.SendPacket(HUB_NODE, &RadioPacket(PayloadType::TRIGGERED, "0"));
    }
    else if (digitalRead(PANIC_BUTTON) == HIGH)
    {
      radioManager.SendPacket(HUB_NODE, &RadioPacket(PayloadType::TRIGGERED, "3"));
    }
    digitalWrite(LED_PIN, HIGH);
    delay(1000);
    digitalWrite(LED_PIN, LOW);
  }

  isAwaken = false;
  radioManager.PowerDown();
  Serial.flush();
  LowPower.powerDown(SLEEP_FOREVER, ADC_OFF, BOD_OFF);
}

void WakeUp()
{
  Serial.println("Interrupt called");
  radioManager.PowerUp();
  isAwaken = true;
}

void OnPairButton()
{
  if (Pair::IsPaired())
  {
    Serial.println("is paired");
    Pair::Reset();
    reset();
    return;
  }

  Pair pair(&radioManager);

  if (pair.Init())
  {
    Serial.println("Pairing successful");
    reset();
    return;
  }

  Serial.println("Pairing failed");
}