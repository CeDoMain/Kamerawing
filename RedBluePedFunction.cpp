#include "RedBluePedFunction.h"

RedBluePedFunction::RedBluePedFunction(SSD1331* disp, CamHE130* cam)
    : RangeFunction(disp, cam,
        { 0, 0, 200, 50, SSD1331::Color::Red, "Pdstl"},
        { 0, 0, 200, 50, SSD1331::Color::Blue, "Pdstl"})
{

}

void RedBluePedFunction::Begin()
{
    RangeFunction::Begin();
}

void RedBluePedFunction::TopValueChanged()
{
    RangeFunction::TopValueChanged();
    Cam->SetPedR(TopConf.Value + 50);
}

void RedBluePedFunction::BtmValueChanged()
{
    RangeFunction::BtmValueChanged();
    Cam->SetPedB(BtmConf.Value + 50);
}