#ifndef REDBLUEGAINFUNCTION_H
#define REDBLUEGAINFUNCTION_H

#include "RangeFunction.h"

class RedBlueGainFunction : public RangeFunction
{
    // Konstruktor
public:
    RedBlueGainFunction(SSD1331* disp, CamHE130* cam);

    // Methoden
public:
    // Initialisiert eine Stripfunktion aus dem Configfile
    virtual void Begin();

    // Wird aufgerufen, wenn sich der obere Wert verändert hat
    virtual void TopValueChanged();
    
    // Wird aufgerufen, wenn sich der untere Wert verändert hat
    virtual void BtmValueChanged();
};

#endif