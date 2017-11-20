#include "RedBlueGainFunction.h"

RedBlueGainFunction::RedBlueGainFunction(SSD1331* disp, CamHE130* cam)
    : RangeFunction(disp, cam,
        { 0, 0, 300, 50, SSD1331::Color::Red, " Gain"},
        { 0, 0, 300, 50, SSD1331::Color::Blue, " Gain"})
{

}

void RedBlueGainFunction::Begin()
{
    RangeFunction::Begin();
}

void RedBlueGainFunction::TopValueChanged()
{
    RangeFunction::TopValueChanged();
    Cam->SetGainR(TopConf.Value);
}

void RedBlueGainFunction::BtmValueChanged()
{
    RangeFunction::BtmValueChanged();
    Cam->SetGainB(BtmConf.Value);
}