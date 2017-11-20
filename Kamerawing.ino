#include "Strip.h"

Strip s[8] = { B000, B001, B010, B011, B100, B101, B110, B111 };

void setup()
{
    pinMode(LED_BUILTIN, OUTPUT);
    Serial.begin(9600);
    while (!Serial) { }
    Wire.setClock(400000L);
    Wire.begin();
    Global::Begin();
    for (int i = 0; i < 3; i++)
    {
        s[i].Begin(i + 1);
    }
    Serial.println(F("Setup end"));
}

void loop()
{
    digitalWrite(LED_BUILTIN, millis() % 1000 < 500 ? HIGH : LOW);
    Global::Update();
    
    for (int i = 0; i < 3; i++)
    {
        s[i].Update();
    }
}
