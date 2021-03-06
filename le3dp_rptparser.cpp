#include "le3dp_rptparser.h"
#include <Servo.h>
#define rad2grad 57.295779513
Servo servox, servoy, servoh, servot, servos;
int srvxval = 90;
int srvyval = 90;
int srvhval = 10;
int srvtval = 90;
int srvsval = 10;
int actaval = 0;
int actbval = 0;
double sen   = 0;
float grado  = 0;

JoystickReportParser::JoystickReportParser(JoystickEvents *evt) :
	joyEvents(evt)
{}

void JoystickReportParser::Parse(USBHID *hid, bool is_rpt_id, uint8_t len, uint8_t *buf)
{
	bool match = true;

	// Checking if there are changes in report since the method was last called
	for (uint8_t i=0; i<RPT_GAMEPAD_LEN; i++) {
		if( buf[i] != oldPad[i] ) {
			match = false;
			break;
		}
  }
  	// Calling Game Pad event handler
	if (!match && joyEvents) {
		joyEvents->OnGamePadChanged((const GamePadEventData*)buf);

		for (uint8_t i=0; i<RPT_GAMEPAD_LEN; i++) oldPad[i] = buf[i];
	}
}

void JoystickEvents::OnGamePadChanged(const GamePadEventData *evt)
{

        uint16_t myX = evt->x;
        int srvX = map(myX, 0, 1023, 10, 170);
        srvxval = srvX;
        Serial.print("X: ");
        Serial.println(srvxval);         

        uint16_t myY = evt->y;
        int srvY = map(myY, 0, 1023, 10, 170);
        srvyval = srvY;
        Serial.print("Y: ");
        Serial.println(srvyval);         

        uint16_t myH = evt->hat;
        int srvH = map(myH, 0, 7, 10, 170);
        srvhval = srvH;
        Serial.print("Hat: ");
        Serial.println(srvhval);        
        
        uint16_t myT = evt->twist;
        int srvT = map(myT, 0, 255, 0, 180);
        srvtval = srvT;
        Serial.print("Twist: ");
        Serial.println(srvtval);         
        sen = sin( (srvtval/rad2grad) );
        grado = (( sen * 80 ) + |90| );
        
        
        uint16_t myS = evt->slider;
        int srvS = map(myS, 0, 255, 10, 170);
        srvsval = srvS;
        Serial.print("Slider: ");
        Serial.println(srvsval);        

        uint16_t myBA = evt->buttons_a;
        actaval = myBA;
        Serial.print("Buttons A: ");
        Serial.println(actaval);                

        uint16_t myBB = evt->buttons_b;
        actbval = myBB;
        Serial.print("Buttons B: ");
        Serial.println(actbval);
        

/*        Serial.print("X: ");
	PrintHex<uint16_t>(evt->x, 0x80);
	Serial.print(" Y: ");
	PrintHex<uint16_t>(evt->y, 0x80);
	Serial.print(" Hat Switch: ");
	PrintHex<uint8_t>(evt->hat, 0x80);
	Serial.print(" Twist: ");
	PrintHex<uint8_t>(evt->twist, 0x80);
	Serial.print(" Slider: ");
	PrintHex<uint8_t>(evt->slider, 0x80);
  Serial.print(" Buttons A: ");
	PrintHex<uint8_t>(evt->buttons_a, 0x80);
	Serial.print(" Buttons B: ");
	PrintHex<uint8_t>(evt->buttons_b, 0x80);
	Serial.println(""); */
}

void InitServoPin::initx (byte pinServX)
{
pinGlobX = pinServX;
servox.attach(pinGlobX);
}

void InitServoPin::inity (byte pinServY)
{
pinGlobY = pinServY;
servoy.attach(pinGlobY);
}

void InitServoPin::inith (byte pinServH)
{
pinGlobH = pinServH;
servoh.attach(pinGlobH);
}

void InitServoPin::initt (byte pinServT)
{
pinGlobT = pinServT;
servot.attach(pinGlobT);
}

void InitServoPin::inits (byte pinServS)
{
pinGlobS = pinServS;
servos.attach(pinGlobS);
}

void InitServoPin::inita (byte pinActuA)
{
pinGlobA = pinActuA;
pinMode(pinGlobA, OUTPUT);
}

void InitServoPin::initb (byte pinActuB)
{
pinGlobB = pinActuB;
pinMode(pinGlobB, OUTPUT);
}

void InitServoPin::wrx(void)
{
servox.write(srvxval);
}

void InitServoPin::wry(void)
{
servoy.write(srvyval);
}

void InitServoPin::wrh(void)
{
servoh.write(srvhval);
}

void InitServoPin::wrt(void)
{
servot.write(grado);
}

void InitServoPin::wrs(void)
{
servos.write(srvsval);
}

void InitServoPin::wra(void)
{
    switch (actaval) {
      case 0:    // your hand is on the sensor
        digitalWrite(pinGlobA, LOW);
        break;
      case 1:    // your hand is on the sensor
        digitalWrite(pinGlobA, HIGH);
        break;
      case 2:    // your hand is close to the sensor
        digitalWrite(pinGlobA, HIGH);
        delay(250);
        digitalWrite(pinGlobA, LOW);
        delay(250);
        digitalWrite(pinGlobA, HIGH);
        delay(1000);
        digitalWrite(pinGlobA, LOW);
        delay(250);        
        break;
      case 4:    // your hand is a few inches from the sensor
        
        break;
      case 8:    // your hand is nowhere near the sensor
        
        break;
      case 16:    // your hand is on the sensor
        
        break;
      case 32:    // your hand is close to the sensor
        
        break;
      case 64:    // your hand is a few inches from the sensor
        
        break;
      case 128:    // your hand is nowhere near the sensor
        
        break;        
    }
    delay(1);        // delay in between reads for stability  
}

void InitServoPin::wrb(void)
{
    switch (actbval) {
      case 1:    // your hand is on the sensor
        digitalWrite(pinGlobB, HIGH);
        break;
      case 2:    // your hand is close to the sensor
        
        break;
      case 4:    // your hand is a few inches from the sensor
        
        break;
      case 8:    // your hand is nowhere near the sensor
        
        break;        
    }
    delay(1);        // delay in between reads for stability  
}

