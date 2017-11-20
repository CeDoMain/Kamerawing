#include "NoFunction.h"

NoFunction::NoFunction(SSD1331* disp)
    : Function(disp)
{
    
}

void NoFunction::Begin()
{
    
}

void NoFunction::Update()
{
    
}

void NoFunction::Refresh()
{
    Disp->StartDrawing();
    Disp->Clear();
    Disp->DrawRectFilled(8, 8, 87, 55, SSD1331::Color::LightGrey, SSD1331::Color::LightGrey);
    Disp->DrawString(26, 14, "Keine", SSD1331::Color::Red, SSD1331::Color::LightGrey);
    Disp->DrawString(14, 34, "Funktion", SSD1331::Color::Red, SSD1331::Color::LightGrey);
    Disp->EndDrawing();
}

void NoFunction::EncoderTopChanged(short relativeValue)
{
    
}

void NoFunction::EncoderBtmChanged(short relativeValue)
{
    
}

void NoFunction::EncoderTopClicked()
{
    
}

void NoFunction::EncoderBtmClicked()
{
    
}

void NoFunction::EncoderTopLongPressed()
{

}

void NoFunction::EncoderBtmLongPressed()
{

}