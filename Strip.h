#ifndef STRIP_H
#define STRIP_H

#include "Function.h"
#include "RedBlueGainFunction.h"
#include "RedBluePedFunction.h"
#include "PanTiltSpeedFunction.h"
#include "NoFunction.h"

#include "Global.h"
#include "Button.h"
#include "SSD1331.h"
#include "MCP23017.h"

class Strip
{
    // Datentypen
public:
    enum Layer
    {
        A, B, C, D, E
    };

    // Felder
private:
    static const byte AtTinyBaseAddress = 0x78;
    const byte I2CAddressAtTiny;
    MCP23017 Gpio;
    SSD1331 Oled;
    bool ButtonTopState, ButtonBtmState;
    Button ButtonTop, ButtonBtm;
    Function* Layers[5];
    Layer SelectedLayer;

    // Konstruktor
public:
    Strip(byte A2A1A0);

    // Methoden
public:
    // Initialisiert den Strip aus dem Configfile
    void Begin(byte type);

    // Muss in jedem Frame aufgerufen werden
    void Update();

    // Wählt einen Layer aus und aktualisiert die Funktionen
    void SelectLayer(Layer newLayer);
};

#endif