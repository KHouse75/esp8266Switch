#include <Bounce2.h>
#include <Homie.h>
#include <Button.h>

const int PIN_RELAY = 15;
const int PIN_LED = 2;
const int PIN_BUTTON = 13;

HomieNode switchNode("switch", "switch");

Button button1(PIN_BUTTON); // Connect your button between pin 2 and GND

bool lightOnHandler(HomieRange range, String value) {
  if (value == "on") {
    digitalWrite(PIN_RELAY, HIGH);
    switchNode.setProperty("state").send("on");
    Serial.println("Light is on");
  } else if (value == "off") {
    digitalWrite(PIN_RELAY, LOW);
    switchNode.setProperty("state").send("off");
    Serial.println("Light is off");
  } else {
    Serial.print("Error Got: ");
    Serial.println(value);
    return false;
  }

  return true;
}



void setup() {
  Serial.begin(115200);
  Serial.println();
  Serial.println();
  
  pinMode(PIN_BUTTON,INPUT_PULLUP);
  pinMode(PIN_RELAY, OUTPUT);
  
  digitalWrite(PIN_RELAY, LOW);
  Homie.setLedPin(PIN_LED, LOW);
  Homie_setFirmware("ecoplug", "1.0.0");
  switchNode.advertise("state").settable(lightOnHandler);
  button1.begin();
  pinMode(PIN_BUTTON, INPUT);
  Homie.setup();
}

void loop() {
  Homie.loop();
  if (button1.pressed())
  {
    if (digitalRead(PIN_RELAY) == HIGH)
    {
        digitalWrite(PIN_RELAY, LOW);
        switchNode.setProperty("state").send("off");
        Serial.println("Light is off");
    } else if (digitalRead(PIN_RELAY) == LOW)
    {
        digitalWrite(PIN_RELAY, HIGH);
        switchNode.setProperty("state").send("on");
        Serial.println("Light is on");
    }
  }
}
