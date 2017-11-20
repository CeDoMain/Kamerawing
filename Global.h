#ifndef GLOBAL_H
#define GLOBAL_H

#include "Ethernet2.h"
#include "CamHE130.h"

class Global
{
    // Felder
public:
    static CamHE130 Cam3;
    static CamHE130 Cam4;

    // Methoden
public:
    // Initialisiert die globalen Objekte
    static void Begin();

    // Muss in jedem Frame aufgerufen werden
    static void Update();
};

#endif