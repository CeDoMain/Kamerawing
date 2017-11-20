#ifndef NOFUNCTION_H
#define NOFUNCTION_H

#include "Function.h"

class NoFunction : public Function
{
    // Konstruktor
public:
    NoFunction(SSD1331* disp);

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
};

#endif