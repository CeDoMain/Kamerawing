#include "CamHE130.h"

EthernetClient CamHE130::Camera = EthernetClient();

CamHE130::CamHE130(const char* name, IPAddress camIp, unsigned short recvPort)
    : Name(name), CamIp(camIp), RecvPort(recvPort), LastMessageTimestamp(0)//, Controller(recvPort)
{
    
}

void CamHE130::Begin()
{
    // Update Notification aktivieren
}

void CamHE130::Update()
{

}

void CamHE130::SendToPtz(char* cmd)
{
    if (millis() - LastMessageTimestamp < 130)
        return;
        
    if (Camera.connect(CamIp, 80) == 1)
    {
        char msg[96];
        sprintf(msg, "GET /cgi-bin/aw_ptz?cmd=%%23%s&res=1 HTTP/1.0\r\nHost: %i.%i.%i.%i\r\nConnection: close\r\n\r\n", cmd, Ethernet.localIP()[0], Ethernet.localIP()[1], Ethernet.localIP()[2], Ethernet.localIP()[3]);
        Camera.write(msg);
        Camera.stop();
        LastMessageTimestamp = millis();
    }
}

void CamHE130::SendToCam(char* cmd)
{
    if (millis() - LastMessageTimestamp < 130)
        return;
        
    if (Camera.connect(CamIp, 80) == 1)
    {
        char msg[96];
        sprintf(msg, "GET /cgi-bin/aw_cam?cmd=%s&res=1 HTTP/1.0\r\nHost: %i.%i.%i.%i\r\nConnection: close\r\n\r\n", cmd, Ethernet.localIP()[0], Ethernet.localIP()[1], Ethernet.localIP()[2], Ethernet.localIP()[3]);
        Camera.write(msg);
        Camera.stop();
        LastMessageTimestamp = millis();
    }
}

void CamHE130::SetPanSpeed(byte speed)
{
    char msg[16];
    sprintf(msg, "P%02u", constrain(speed, 1, 99));
    SendToPtz(msg);
}

void CamHE130::SetTiltSpeed(byte speed)
{
    char msg[16];
    sprintf(msg, "T%02u", constrain(speed, 1, 99));
    SendToPtz(msg);
}

void CamHE130::SetZoomSpeed(byte speed)
{
    char msg[16];
    sprintf(msg, "Z%02u", constrain(speed, 1, 99));
    SendToPtz(msg);
}

void CamHE130::SetGainR(word gain)
{
    char msg[16];
    sprintf(msg, "ORI:%03X", constrain(gain, 0, 300));
    SendToCam(msg);
}

void CamHE130::SetGainB(word gain)
{
    char msg[16];
    sprintf(msg, "OBI:%03X", constrain(gain, 0, 300));
    SendToCam(msg);
}

void CamHE130::SetPedR(word ped)
{
    char msg[16];
    sprintf(msg, "ORP:%03X", constrain(ped, 50, 250));
    SendToCam(msg);
}

void CamHE130::SetPedB(word ped)
{
    char msg[16];
    sprintf(msg, "OBP:%03X", constrain(ped, 50, 250));
    SendToCam(msg);
}

/*

// Setzt Fokus Position (0 - 2730)
Focus Position	/cgi-bin/aw_ptz	AXF[###]	FocusPos (555-FFF)
void CamHE130::SetFocus(word focus);

// Setzt Iris Position (0 - 2730)
Iris Position	/cgi-bin/aw_ptz	AXI[###]	IrisPos (555-FFF)
void CamHE130::SetIris(word iris);

// Speichert ein Preset (0 - 99)
Preset Register	/cgi-bin/aw_ptz	M[##]	Preset (00-99)
void CamHE130::SavePreset(byte id);

// Ruft ein Preset auf (0 - 99)
Preset Playback	/cgi-bin/aw_ptz	R[##]	Preset (00-99)
void CamHE130::RecallPreset(byte id);

// De-/Aktiviert Autofokus
Focus Auto	/cgi-bin/aw_cam	OAF:[#]	Manual - Auto (0-1)
void CamHE130::EnableAF(bool enable);

// De-/Aktiviert Autoiris
Iris Auto	/cgi-bin/aw_cam	ORS:[#]	Manual - Auto (0-1)
void CamHE130::EnableAI(bool enable);

// Startet "One Touch AF"
One Touch AF	/cgi-bin/aw_cam	OSE:69:1	OTAF
void CamHE130::OneTouchAF();

// Setzt Pedestal Schwarz (0 - 150 - 300)
Pedestal	/cgi-bin/aw_cam	OTP:[###]	Ped (000-096-12C)
void CamHE130::SetPedestal(word ped);

*/