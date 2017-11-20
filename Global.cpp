#include "Global.h"

CamHE130 Global::Cam3("  Kamera 3", { 10, 1, 10, 23 }, 40003);
CamHE130 Global::Cam4("  Kamera 4", { 10, 1, 10, 24 }, 40004);

void Global::Begin()
{
    // EthernetShield initialisieren
    byte mac[] = { 0xCE, 0xD0, 0xCE, 0xD0, 0xCE, 0xD0 };
    byte ip[] = { 10, 1, 10, 16 };
    byte gateway[] = { 10, 1, 2, 1 };
    byte subnet[] = { 255, 255, 128, 0 };
    Ethernet.begin(mac, ip, gateway, subnet);
}

void Global::Update()
{
    Cam3.Update();
    Cam4.Update();
}