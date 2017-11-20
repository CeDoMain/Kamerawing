#ifndef CAMHE130_H
#define CAMHE130_H

#include "Arduino.h"
#include "Ethernet2.h"

class CamHE130
{
    // Felder
public:
    const char* Name;
    
private:
    IPAddress CamIp;
    unsigned short RecvPort;
    static EthernetClient Camera;
    unsigned long LastMessageTimestamp;
    //EthernetServer Controller;

    // Konstruktor
public:
    CamHE130(const char* name, IPAddress camIp, unsigned short recvPort);

    // Methoden
public:
    // Initialisiert die Kameraverbindung
    void Begin();

    // Muss in jedem Frame aufgerufen werden
    void Update();

    // Verändert Pan mit der angegeben Geschwindigkeit (1 - 50 - 99)
    void SetPanSpeed(byte speed);
    
    // Verändert Tilt mit der angegeben Geschwindigkeit (1 - 50 - 99)
    void SetTiltSpeed(byte speed);

    // Verändert Zoom mit der angegebenen Geschwindigkeit (1 - 50 - 99)
    void SetZoomSpeed(byte speed);

    // Setzt Fokus Position (0 - 2730)
    void SetFocus(word focus);

    // Setzt Iris Position (0 - 2730)
    void SetIris(word iris);

    // Speichert ein Preset (0 - 99)
    void SavePreset(byte id);

    // Ruft ein Preset auf (0 - 99)
    void RecallPreset(byte id);

    // De-/Aktiviert Autofokus
    void EnableAF(bool enable);

    // De-/Aktiviert Autoiris
    void EnableAI(bool enable);

    // Startet "One Touch AF"
    void OneTouchAF();

    // Setzt Gain Rot (0 - 150 - 300)
    void SetGainR(word gain);
    
    // Setzt Gain Blau (0 - 150 - 300)
    void SetGainB(word gain);
    
    // Setzt Pedestal Rot (0 - 100 - 200)
    void SetPedR(word ped);
    
    // Setzt Pedestal Blau (0 - 100 - 200)
    void SetPedB(word ped);
    
    // Setzt Pedestal Schwarz (0 - 150 - 300)
    void SetPedestal(word ped);

private:    
    // Sendet einen Befehl an den PTZ-Controller der Kamera
    void SendToPtz(char* cmd);

    // Sendet einen Befehl an den CAM-Controller der Kamera
    void SendToCam(char* cmd);
    
    /*
    
    Datentypen:
    hex 0000 - 8000 - FFFF      65535   word
    hex  000 -  096 -  12C      300     word
    hex  032 -  096 -  0FA      200     byte
    hex  555 -  FFF             2730    word
    dez  01  -  50  -  99       99      byte
    dez  00  -  99              100     byte
    bin    0 - 1                2       bool
    
    Pan/Tilt Position	/cgi-bin/aw_ptz	APC[####][####]	"PanPos (0000-8000-FFFF) TiltPos (0000-8000-FFFF)"
    Pan Speed	/cgi-bin/aw_ptz	P[##]	PanSpeed (01-50-99)
    Tilt Speed	/cgi-bin/aw_ptz	T[##]	TiltSpeed (01-50-99)
    Zoom Position	/cgi-bin/aw_ptz	AXZ[###]	ZoomPos (555-FFF)
    Zoom Speed	/cgi-bin/aw_ptz	Z	ZoomSpeed (01-50-99)
    Focus Position	/cgi-bin/aw_ptz	AXF[###]	FocusPos (555-FFF)
    Iris Position	/cgi-bin/aw_ptz	AXI[###]	IrisPos (555-FFF)
    Preset Register	/cgi-bin/aw_ptz	M[##]	Preset (00-99)
    Preset Playback	/cgi-bin/aw_ptz	R[##]	Preset (00-99)
    Focus Auto	/cgi-bin/aw_cam	OAF:[#]	Manual - Auto (0-1)
    Iris Auto	/cgi-bin/aw_cam	ORS:[#]	Manual - Auto (0-1)
    One Touch AF	/cgi-bin/aw_cam	OSE:69:1	OTAF
    R Gain	/cgi-bin/aw_cam	ORI:[###]	Rgain (000-096-12C)
    B Gain	/cgi-bin/aw_cam	OBI:[###]	Bgain (000-096-12C)
    R Pedestal	/cgi-bin/aw_cam	ORP:[###]	Rped (032-096-0FA)
    B Pedestal	/cgi-bin/aw_cam	OBP:[###]	Bped (032-096-0FA)
    Pedestal	/cgi-bin/aw_cam	OTP:[###]	Ped (000-096-12C)
    
    Kameratyp /cgi-bin/aw_cam QID Response überprüfen 
    Tally An/Aus
    Lens information notification
    min 130ms delay

    */
};

#endif