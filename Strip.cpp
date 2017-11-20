#include "Strip.h"

#define ISSET(x, y) ((x & (1 << y)) != 0)
#define ISUNSET(x, y) ((x & (1 << y)) == 0)

Strip::Strip(byte A2A1A0)
    : I2CAddressAtTiny(AtTinyBaseAddress | (A2A1A0 & 0x07)), Gpio(A2A1A0), Oled()
{
    
}

void Strip::Begin(byte type)
{
    switch (type)
    {
        case 1: Layers[0] = new RedBlueGainFunction(&Oled, &Global::Cam4); break;
        case 2: Layers[0] = new RedBluePedFunction(&Oled, &Global::Cam4); break;
        case 3: Layers[0] = new PanTiltSpeedFunction(&Oled, &Global::Cam4); break;
        default: Layers[0] = new NoFunction(&Oled); break;
    }

    Gpio.Begin();
    Oled.Begin(Gpio.GetDigitalOut(MCP23017::GPA0), Gpio.GetDigitalOut(MCP23017::GPA2), Gpio.GetDigitalOut(MCP23017::GPA1), true, true);
    ButtonTop.Begin(new Trigger(new DigitalIn([this]() -> bool { return ButtonTopState; })));
    ButtonBtm.Begin(new Trigger(new DigitalIn([this]() -> bool { return ButtonBtmState; })));

    ButtonTop.ClickEvent = new Delegate<>([this]() { Layers[SelectedLayer]->EncoderTopClicked(); });
    ButtonTop.LongPressEvent = new Delegate<>([this]() { Layers[SelectedLayer]->EncoderTopLongPressed(); });
    ButtonBtm.ClickEvent = new Delegate<>([this]() { Layers[SelectedLayer]->EncoderBtmClicked(); });
    ButtonBtm.LongPressEvent = new Delegate<>([this]() { Layers[SelectedLayer]->EncoderBtmLongPressed(); });
    
    for (int i = 0; i < 1; i++)
        Layers[i]->Begin();

    SelectLayer(Layer::A);
}

void Strip::Update()
{
    // AtTiny auslesen
    if (Wire.requestFrom(I2CAddressAtTiny, 3) == 3)
    {
        byte data = Wire.read();
        int EncoderTopChange = -Wire.read() + 128;
        int EncoderBtmChange = -Wire.read() + 128;
    
        // Encoder Drehung verarbeiten
        if (EncoderTopChange != 0)
            Layers[SelectedLayer]->EncoderTopChanged(EncoderTopChange);
        if (EncoderBtmChange != 0)
            Layers[SelectedLayer]->EncoderBtmChanged(EncoderBtmChange);
    
        // Encoder Taster verarbeiten
        ButtonTopState = ISSET(data, 0);
        ButtonBtmState = ISSET(data, 1);
    }
    ButtonTop.Update();
    ButtonBtm.Update();

    // Aktives Layer updaten
    Layers[SelectedLayer]->Update();
}

void Strip::SelectLayer(Layer newLayer)
{
    SelectedLayer = newLayer;
    Layers[SelectedLayer]->Refresh();
}