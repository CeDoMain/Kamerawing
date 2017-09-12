#ifndef STRIP_H
#define STRIP_H

#include "CamHE130.h"
#include "SSD1331.h"

class Strip
{
    // Felder
protected:
    CamHE130* Cam;
    SSD1331* Disp;

    // Konstruktor
    Strip(CamHE130* cam, SSD1331* disp);

    // Methoden
public:
    virtual void Begin();
    virtual void Update();
    virtual void Refresh();
    virtual void EncoderTopChanged(int value);
    virtual void EncoderBtnChanged(int value);
    virtual void EncoderTopClicked();
    virtual void EncoderBtnClicked();
    virtual void EncoderTopLongPressed();
    virtual void EncoderBtnLongPressed();
};

#endif