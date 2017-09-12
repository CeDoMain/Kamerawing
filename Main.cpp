#include "Main.hpp"

void EncoderChanged(int index, int count, AnalogOut* led, int Top, SSD1331::Color foreground);
void HE2_ZoomSpeed(byte value, IPAddress ip);
void HE130_ZoomSpeed(byte value, IPAddress ip);
void HE130_Iris(byte value, IPAddress ip);
void HE130_Focus(byte value, IPAddress ip);

byte mac[] = { 0xCE, 0xD0, 0xCE, 0xD0, 0xCE, 0xD0 };
IPAddress locIp(10, 1, 10, 15);
IPAddress camIp(10, 1, 10, 24);
EthernetClient client;

Encoder enc[3] = { 4, 4, 2};
Button btn[3];
MCP23017 chip[3] = { B000, B001, B010 };
SSD1331 oled;
AnalogOut* r;
AnalogOut* g;
AnalogOut* b;

void setup()
{
  // Status LED
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(53, OUTPUT);
  digitalWrite(53, HIGH);
  Serial.begin(9600);

  // Netzwerk verbinden
  Ethernet.begin(mac, locIp);

  // OLED konfigurieren
  oled.Begin(
    chip[1].GetDigitalOut(MCP23017::IOPort::GPA7),
    chip[0].GetDigitalOut(MCP23017::IOPort::GPA4),
    chip[0].GetDigitalOut(MCP23017::IOPort::GPA5));

  oled.DrawString(0, 0, "Rot", SSD1331::FontSize::pt9, SSD1331::Color::Red);
  oled.DrawString(0, 20, "Gruen", SSD1331::FontSize::pt9, SSD1331::Color::Green);
  oled.DrawString(0, 40, "Blau", SSD1331::FontSize::pt9, SSD1331::Color::Blue);

  // RGB Led konfigurieren
  r = ArduinoMega::GetAnalogOut(ArduinoMega::AnalogOutPin::PWM6);
  g = ArduinoMega::GetAnalogOut(ArduinoMega::AnalogOutPin::PWM7);
  b = ArduinoMega::GetAnalogOut(ArduinoMega::AnalogOutPin::PWM5);

  // IO Expander konfigurieren
  chip[0].Begin();
  chip[1].Begin();
  chip[2].Begin();

  // Encoder konfigurieren
  enc[0].CounterChangedEvent.Connect([](long count)
  {
    EncoderChanged(0, count, r, 0, SSD1331::Color::Red);
  });
  enc[1].CounterChangedEvent.Connect([](long count)
  {
    EncoderChanged(1, count, g, 20, SSD1331::Color::Green);
  });
  enc[2].CounterChangedEvent.Connect([](long count)
  {
    EncoderChanged(2, count, b, 40, SSD1331::Color::Blue);
  });
  enc[0].Begin(
    new Trigger(chip[0].GetDigitalIn(MCP23017::IOPort::GPA7), true, 0),
    new Trigger(chip[0].GetDigitalIn(MCP23017::IOPort::GPA6), true, 0));
  enc[1].Begin(
    new Trigger(chip[1].GetDigitalIn(MCP23017::IOPort::GPA1), true, 0),
    new Trigger(chip[1].GetDigitalIn(MCP23017::IOPort::GPA2), true, 0));
  enc[2].Begin(
    new Trigger(chip[2].GetDigitalIn(MCP23017::IOPort::GPA7), true, 0),
    new Trigger(chip[2].GetDigitalIn(MCP23017::IOPort::GPA6), true, 0));

  // Knöpfe konfigurieren
  btn[0].ClickEvent.Connect([&enc]() { enc[0].Reset(0); });
  btn[1].ClickEvent.Connect([&enc]() { enc[1].Reset(0); });
  btn[2].ClickEvent.Connect([&enc]() { enc[2].Reset(0); });
  btn[0].LongPressEvent.Connect([&enc]() { enc[0].Reset(255); });
  btn[1].LongPressEvent.Connect([&enc]() { enc[1].Reset(255); });
  btn[2].LongPressEvent.Connect([&enc]() { enc[2].Reset(255); });
  btn[0].Begin(new Trigger(chip[0].GetDigitalIn(MCP23017::IOPort::GPA0)));
  btn[1].Begin(new Trigger(chip[1].GetDigitalIn(MCP23017::IOPort::GPA0)));
  btn[2].Begin(new Trigger(chip[2].GetDigitalIn(MCP23017::IOPort::GPA0)));

  // Reset
  enc[0].Reset(50);
  enc[1].Reset(50);
  enc[2].Reset(50);
}

void loop()
{
  analogWrite(LED_BUILTIN, 128 + sin(millis() / 1000.0 * 3.14159) * 128);
  chip[0].Update();
  chip[1].Update();
  chip[2].Update();
  enc[0].Update();
  enc[1].Update();
  enc[2].Update();
  btn[0].Update();
  btn[1].Update();
  btn[2].Update();
}

void EncoderChanged(int index, int count, AnalogOut* led, int Top, SSD1331::Color foreground)
{
  const int max = 99;
  if (count < 0)
    enc[index].Reset(50);
  else if (count > max)
    enc[index].Reset(max);
  else
  {
    // Balken zeichnen
    byte length = count / (float)max * 94;
    oled.DrawRect(0, Top + 14, length, Top + 18, foreground, true, foreground);
    oled.DrawRect(length + 1, Top + 14, 95, Top + 18, SSD1331::Color::Black, true, SSD1331::Color::Black);

    // Kamera steuern
    switch (index)
    {
      case 0: HE130_ZoomSpeed(count, camIp); break;
      case 1: HE130_Iris(count, camIp); break;
      case 2: HE130_Focus(count, camIp); break;
    }
  }
}

void HE2_ZoomSpeed(byte value, IPAddress ip)
{
  if (client.connect(ip, 80) == 1)
  {
    byte msg[96];
    sprintf(msg, "GET /cgi-bin/aw_ptz?cmd=%%23Z%i&res=1 HTTP/1.1\r\nHost: %i.%i.%i.%i\r\n\r\n", value, ip[0], ip[1], ip[2], ip[3]);
    client.write(msg, sizeof(msg));
    client.stop();
  }
}
void HE130_ZoomSpeed(byte value, IPAddress ip)
{
  if (client.connect(ip, 80) == 1)
  {
    byte msg[96];
    sprintf(msg, "GET /cgi-bin/aw_ptz?cmd=%%23Z%i&res=1 HTTP/1.1\r\nHost: %i.%i.%i.%i\r\n\r\n", value, ip[0], ip[1], ip[2], ip[3]);
    client.write(msg, sizeof(msg));
    client.stop();
  }
}
void HE130_Iris(byte value, IPAddress ip)
{
  if (client.connect(ip, 80) == 1)
  {
    byte msg[96];
    sprintf(msg, "GET /cgi-bin/aw_ptz?cmd=%%23I%i&res=1 HTTP/1.1\r\nHost: %i.%i.%i.%i\r\n\r\n", value, ip[0], ip[1], ip[2], ip[3]);
    client.write(msg, sizeof(msg));
    client.stop();
  }
}
void HE130_Focus(byte value, IPAddress ip)
{
  if (client.connect(ip, 80) == 1)
  {
    byte msg[96];
    sprintf(msg, "GET /cgi-bin/aw_ptz?cmd=%%23AXF%x&res=1 HTTP/1.1\r\nHost: %i.%i.%i.%i\r\n\r\n", map(value, 0, 99, 0x555, 0xFFF), ip[0], ip[1], ip[2], ip[3]);
    client.write(msg, sizeof(msg));
    client.stop();
  }
}
