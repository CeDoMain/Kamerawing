#ifndef RANGEFUNCTION_H
#define RANGEFUNCTION_H

#include "Function.h"

typedef short decimal;

class RangeFunction : public Function
{
    // Datentypen
public:
    struct RangeConfig
    {
        short Value;
        const short Low;
        const short High;
        const byte BigStep; // Wenn >1 wird ein doppelter Balken gezeichnet, andernfalls ein einfacher zentrierter Balken
                            // Sollte zwischen 0 und 94 liegen
        const SSD1331::Color Color;
        const char* Name;
    };
    // Felder
protected:
    CamHE130* Cam;
    RangeConfig TopConf;
    RangeConfig BtmConf;

private:
    const byte TopBarTop = 15;
    const byte BtmBarTop = 48;
    const byte BarNameTop = 32;
    const byte TopBarNameLeft = 0;
    const byte BtmBarNameLeft = 48;

    // Konstruktor
public:
    RangeFunction(SSD1331* disp, CamHE130* cam, RangeConfig topConf, RangeConfig btmConf);

    // Methoden
public:
    // Initialisiert eine Stripfunktion aus dem Configfile
    virtual void Begin();

    // Muss in jedem Frame aufgerufen werden
    virtual void Update();

    // Displayinhalt neuzeichnen
    virtual void Refresh();

    // Wird aufgerufen, wenn sich der obere Encoder verändert hat
    virtual void EncoderTopChanged(short relativeValue);

    // Wird aufgerufen, wenn sich der untere Encoder verändert hat
    virtual void EncoderBtmChanged(short relativeValue);

    // Wird aufgerufen, wenn der obere Encoder kurz gedrückt wurde
    virtual void EncoderTopClicked();

    // Wird aufgerufen, wenn der untere Encoder kurz gedrückt wurde
    virtual void EncoderBtmClicked();

    // Wird aufgerufen, wenn der obere Encoder lang gedrückt wurde
    virtual void EncoderTopLongPressed();

    // Wird aufgerufen, wenn der untere Encoder lang gedrückt wurde
    virtual void EncoderBtmLongPressed();

protected:
    // Wird aufgerufen, wenn sich der obere Wert verändert hat
    virtual void TopValueChanged();

    // Wird aufgerufen, wenn sich der untere Wert verändert hat
    virtual void BtmValueChanged();

private:
    // Zeichnet einen Balken
    void DrawBar(byte y1, byte y2, decimal value, SSD1331::Color color);

    // Zeichnet einen zentrierten Balken (0 und der Mitte)
    void DrawCenterBar(byte y1, byte y2, decimal value, SSD1331::Color color);

    // Zeichnet das Benutzerinterface
    void DrawUI();
};

#endif