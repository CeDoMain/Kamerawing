#ifndef FUNCTION_H
#define FUNCTION_H

#include "CamHE130.h"
#include "SSD1331.h"

class Function
{
protected:
    SSD1331* Disp;

    // Konstruktor
public:
    Function(SSD1331* disp);

    // Methoden
public:
    // Initialisiert eine Stripfunktion aus dem Configfile
    virtual void Begin() = 0;

    // Muss in jedem Frame aufgerufen werden
    virtual void Update() = 0;

    // Displayinhalt neuzeichnen
    virtual void Refresh() = 0;

    // Wird aufgerufen, wenn sich der obere Encoder verändert hat
    virtual void EncoderTopChanged(short relativeValue) = 0;

    // Wird aufgerufen, wenn sich der untere Encoder verändert hat
    virtual void EncoderBtmChanged(short relativeValue) = 0;

    // Wird aufgerufen, wenn der obere Encoder kurz gedrückt wurde
    virtual void EncoderTopClicked() = 0;

    // Wird aufgerufen, wenn der untere Encoder kurz gedrückt wurde
    virtual void EncoderBtmClicked() = 0;

    // Wird aufgerufen, wenn der obere Encoder lang gedrückt wurde
    virtual void EncoderTopLongPressed() = 0;

    // Wird aufgerufen, wenn der untere Encoder lang gedrückt wurde
    virtual void EncoderBtmLongPressed() = 0;
};

#endif