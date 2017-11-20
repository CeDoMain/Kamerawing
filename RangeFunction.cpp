#include "RangeFunction.h"

RangeFunction::RangeFunction(SSD1331* disp, CamHE130* cam, RangeConfig topConf, RangeConfig btmConf)
    : Function(disp), Cam(cam), TopConf(topConf), BtmConf(btmConf)
{

}

void RangeFunction::Begin()
{
    
}

void RangeFunction::Update()
{
    
}

void RangeFunction::Refresh()
{
    // Anzeigen zeichnen
    DrawUI();
}

void RangeFunction::EncoderTopChanged(short relativeValue)
{
    // Neuen Wert berechnen und Grenzen prüfen
    short newValue = constrain(TopConf.Value + relativeValue, TopConf.Low, TopConf.High);
    if (newValue != TopConf.Value)
    {
        // Wert wurde geändert > Backend informieren und UI neuzeichnen
        TopConf.Value = newValue;
        TopValueChanged();
    }
}

void RangeFunction::EncoderBtmChanged(short relativeValue)
{
    // Neuen Wert berechnen und Grenzen prüfen
    short newValue = constrain(BtmConf.Value + relativeValue, BtmConf.Low, BtmConf.High);
    if (newValue != BtmConf.Value)
    {
        // Wert wurde geändert > Backend informieren und UI neuzeichnen
        BtmConf.Value = newValue;
        BtmValueChanged();
    }
}

void RangeFunction::EncoderTopClicked()
{
    // Oberen Encoder auf 0 zurücksetzen
    EncoderTopChanged(-TopConf.Value);
}

void RangeFunction::EncoderBtmClicked()
{
    // Unteren Encoder auf 0 zurücksetzen
    EncoderBtmChanged(-BtmConf.Value);
}

void RangeFunction::EncoderTopLongPressed()
{

}

void RangeFunction::EncoderBtmLongPressed()
{

}

void RangeFunction::TopValueChanged()
{
    Disp->StartDrawing();
    if (TopConf.BigStep > 1)
    {
        // Doppelten Balken zeichnen
        decimal smallValue = map(TopConf.Value % TopConf.BigStep, 0, TopConf.BigStep - 1, 0, 10000);
        decimal bigValue = map(TopConf.Value, TopConf.Low, TopConf.High, 0, 10000);
        DrawBar(TopBarTop + 1, TopBarTop + 3, smallValue, TopConf.Color);
        DrawBar(TopBarTop + 7, TopBarTop + 11, bigValue, TopConf.Color);
    }
    else
    {
        // Einfachen zentrierten Balken zeichnen
        DrawCenterBar(TopBarTop + 1, TopBarTop + 11,
            map(TopConf.Value, TopConf.Low, TopConf.High, -10000, 10000), TopConf.Color);
    }
    Disp->EndDrawing();
}

void RangeFunction::BtmValueChanged()
{
    Disp->StartDrawing();
    if (BtmConf.BigStep > 1)
    {
        // Doppelten Balken zeichnen
        decimal smallValue = map(BtmConf.Value % BtmConf.BigStep, 0, BtmConf.BigStep - 1, 0, 10000);
        decimal bigValue = map(BtmConf.Value, BtmConf.Low, BtmConf.High, 0, 10000);
        DrawBar(BtmBarTop + 1, BtmBarTop + 3, smallValue, BtmConf.Color);
        DrawBar(BtmBarTop + 7, BtmBarTop + 11, bigValue, BtmConf.Color);
    }
    else
    {
        // Einfachen zentrierten Balken zeichnen
        DrawCenterBar(BtmBarTop + 1, BtmBarTop + 11,
            map(BtmConf.Value, BtmConf.Low, BtmConf.High, -10000, 10000), BtmConf.Color);
    }
    Disp->EndDrawing();
}

void RangeFunction::DrawBar(byte y1, byte y2, decimal value, SSD1331::Color color)
{
    const byte x1 = 1;
    const byte x2 = 94;

    byte x = map(value, 0, 10000, x1 - 1, x2);
    if (x >= x1)
        Disp->DrawRectFilled(x1, y1, x, y2, color, color);
    if (x != x2)
        Disp->DrawRectFilled(x + 1, y1, x2, y2, SSD1331::Color::Black, SSD1331::Color::Black);
}

void RangeFunction::DrawCenterBar(byte y1, byte y2, decimal value, SSD1331::Color color)
{
    const byte x1 = 1;
    const byte x2 = 46;
    const byte x3 = 49;
    const byte x4 = 94;

    // Linken Bereich füllen
    byte x = value < 0 ? map(value, -10000, 0, x1, x2 + 1) : x2 + 1;
    if (x <= x2)
        Disp->DrawRectFilled(x, y1, x2, y2, color, color);
    if (x != x1)
        Disp->DrawRectFilled(x1, y1, x - 1, y2, SSD1331::Color::Black, SSD1331::Color::Black);
    
    // Rechten Bereich füllen
    x = value > 0 ? map(value, 0, 10000, x3 - 1, x4) : x3 - 1;
    if (x >= x3)
        Disp->DrawRectFilled(x3, y1, x, y2, color, color);
    if (x != x4)
        Disp->DrawRectFilled(x + 1, y1, x4, y2, SSD1331::Color::Black, SSD1331::Color::Black);
}

void RangeFunction::DrawUI()
{
    Disp->StartDrawing();
    Disp->Clear();

    // Kameraname
    Disp->DrawString(0, 0, Cam->Name, SSD1331::Color::White, SSD1331::Color::Black);

    // Beschriftung für die beiden Werte
    Disp->DrawString(TopBarNameLeft, BarNameTop, TopConf.Name, TopConf.Color, SSD1331::Color::Black);
    Disp->DrawString(BtmBarNameLeft, BarNameTop, BtmConf.Name, BtmConf.Color, SSD1331::Color::Black);
    
    if (TopConf.BigStep > 1)
    {
        // Rahmen für doppelten Balken zeichnen
        Disp->DrawRect(0, TopBarTop, 95, TopBarTop + 4, TopConf.Color);
        Disp->DrawRect(0, TopBarTop + 6, 95, TopBarTop + 12, TopConf.Color);
    }
    else
    {
        // Rahmen für einfachen zentrierten Balken zeichnen
        Disp->DrawRect(0, TopBarTop, 95, TopBarTop + 12, TopConf.Color);
        Disp->DrawRect(47, TopBarTop, 48, TopBarTop + 12, TopConf.Color);
    }

    if (BtmConf.BigStep > 1)
    {
        // Rahmen für doppelten Balken zeichnen
    Disp->DrawRect(0, BtmBarTop, 95, BtmBarTop + 4, BtmConf.Color);
    Disp->DrawRect(0, BtmBarTop + 6, 95, BtmBarTop + 12, BtmConf.Color);
    }
    else
    {
        // Rahmen für einfachen zentrierten Balken zeichnen
        Disp->DrawRect(0, BtmBarTop, 95, BtmBarTop + 12, BtmConf.Color);
        Disp->DrawRect(47, BtmBarTop, 48, BtmBarTop + 12, BtmConf.Color);
    }
    Disp->EndDrawing();

    // Balken zeichnen
    TopValueChanged();
    BtmValueChanged();
}