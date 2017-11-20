#include "PanTiltSpeedFunction.h"

PanTiltSpeedFunction::PanTiltSpeedFunction(SSD1331* disp, CamHE130* cam)
    : RangeFunction(disp, cam,
        { 0, -30, 30, 0, SSD1331::Color::Green, "TltSp"},
        { 0, -30, 30, 0, SSD1331::Color::Yellow, " PanSp"})
{

}

void PanTiltSpeedFunction::Begin()
{
    RangeFunction::Begin();
}

void PanTiltSpeedFunction::TopValueChanged()
{
    RangeFunction::TopValueChanged();
    Cam->SetTiltSpeed(map(TopConf.Value, -30, 30, 1, 99));
}

void PanTiltSpeedFunction::BtmValueChanged()
{
    RangeFunction::BtmValueChanged();
    Cam->SetPanSpeed(map(BtmConf.Value, -30, 30, 1, 99));
}