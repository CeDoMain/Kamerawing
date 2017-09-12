#include "CamHE130.h"

CamHE130::CamHE130(IPAddress camIp, EthernetClient* client)
    : CamIp(camIp), Client(client)
{

}

void CamHE130::Begin()
{

}

void CamHE130::SendToPTZ(char* cmd)
{
    if (client.connect(CamIp, 80) == 1)
    {
        byte msg[96];
        sprintf(msg, F("GET /cgi-bin/aw_ptz?cmd=%%23%s&res=1 HTTP/1.1\r\nHost: %i.%i.%i.%i\r\n\r\n"), cmd, ip[0], ip[1], ip[2], ip[3]);
        client.write(msg, sizeof(msg));
        client.stop();
    }
}

void CamHE130::SendToCAM(char* cmd)
{
    if (client.connect(CamIp, 80) == 1)
    {
        byte msg[96];
        sprintf(msg, F("GET /cgi-bin/aw_cam?cmd=%%23%s&res=1 HTTP/1.1\r\nHost: %i.%i.%i.%i\r\n\r\n"), cmd, ip[0], ip[1], ip[2], ip[3]);
        client.write(msg, sizeof(msg));
        client.stop();
    }
}

void CamHE130::SetPanTilt(word pan, word tilt)
{
    byte msg[16];
    sprintf(msg, F("APC%X04%X04"), constrain(pan, 0, 65535), constrain(tilt, 0, 65535));
    SendToPTZ(msg);
}

void CamHE130::MovePan(byte speed)
{
    byte msg[16];
    sprintf(msg, F("P%u02"), constrain(speed, 1, 99));
    SendToPTZ(msg);
}

void CamHE130::MoveTilt(byte speed)
{
    byte msg[16];
    sprintf(msg, F("T%u02"), constrain(speed, 1, 99));
    SendToPTZ(msg);
}

void CamHE130::SetZoom(word zoom)
{
    byte msg[16];
    sprintf(msg, F("AXZ%X03"), constrain(speed, 1365, 4095));
    SendToPTZ(msg);
}

// Verändert Zoom mit der angegebenen Geschwindigkeit (1 - 50 - 99)
Zoom Speed	/cgi-bin/aw_ptz	Z	ZoomSpeed (01-50-99)
void CamHE130::MoveZoom(byte speed)

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

// Setzt Gain Rot (0 - 150 - 300)
R Gain	/cgi-bin/aw_cam	ORI:[###]	Rgain (000-096-12C)
void CamHE130::SetGainR(word gain);

// Setzt Gain Blau (0 - 150 - 300)
B Gain	/cgi-bin/aw_cam	OBI:[###]	Bgain (000-096-12C)
void CamHE130::SetGainR(word gain);

// Setzt Pedestal Rot (0 - 100 - 200)
R Pedestal	/cgi-bin/aw_cam	ORP:[###]	Rped (032-096-0FA)
void CamHE130::SetGainR(word ped);

// Setzt Pedestal Blau (0 - 100 - 200)
B Pedestal	/cgi-bin/aw_cam	OBP:[###]	Bped (032-096-0FA)
void CamHE130::SetGainR(word ped);

// Setzt Pedestal Schwarz (0 - 150 - 300)
Pedestal	/cgi-bin/aw_cam	OTP:[###]	Ped (000-096-12C)
void CamHE130::SetPedestal(word ped);