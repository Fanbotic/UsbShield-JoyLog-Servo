/* Simplified Logitech Extreme 3D Pro Joystick Report Parser */

#include <usbhid.h>
#include <hiduniversal.h>
#include <usbhub.h>

#include "le3dp_rptparser.h"

// Satisfy the IDE, which needs to see the include statment in the ino too.
#ifdef dobogusinclude
#include <spi4teensy3.h>
#include <SPI.h>
#endif

USB                                             Usb;
USBHub                                          Hub(&Usb);
HIDUniversal                                    Hid(&Usb);
JoystickEvents                                  JoyEvents;
JoystickReportParser                            Joy(&JoyEvents);
InitServoPin                                    inpx;
InitServoPin                                    inpy;
InitServoPin                                    inph;
InitServoPin                                    inpt;
InitServoPin                                    inps;
InitServoPin                                    inpa;
InitServoPin                                    inpb;

//int servoX;

void setup()
{
inpx.initx(6);
inpy.inity(7);
inph.inith(8);
inpt.initt(5);
inps.inits(4);
inpa.inita(2);
inpb.initb(3);
  
  Serial.begin( 115200 );
#if !defined(__MIPSEL__)
  while (!Serial); // Wait for serial port to connect - used on Leonardo, Teensy and other boards with built-in USB CDC serial connection
#endif
  Serial.println("Start");

  if (Usb.Init() == -1)
      Serial.println("OSC did not start.");

  delay( 200 );

  if (!Hid.SetReportParser(0, &Joy))
      ErrorMessage<uint8_t>(PSTR("SetReportParser"), 1  );
}

void loop()
{
    Usb.Task();   
    inpx.wrx();
    inpy.wry();
    inph.wrh();
    inpt.wrt();
    inps.wrs();
    inpa.wra();
    inpb.wrb();                    
}

