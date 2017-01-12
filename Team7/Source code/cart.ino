#include <hid.h>
#include <hiduniversal.h>
#include <usbhub.h>
#include <avr/pgmspace.h>
#include <Usb.h>
#include <usbhub.h>
#include <avr/pgmspace.h>
#include <hidboot.h>
USB     Usb;
USBHub     Hub(&Usb); //I enable this
lineString codeString;
char z;
int cont = 0;
String readString;
HIDUniversal      Hid(&Usb);

HIDBoot<HID_PROTOCOL_KEYBOARD>    Keyboard(&Usb);

class KbdRptParser : public KeyboardReportParser {
    void PrintKey(uint8_t mod, uint8_t key);
    
    protected:  virtual void OnKeyDown (uint8_t mod, uint8_t key);
    
    virtual void OnKeyPressed(uint8_t key);
};

void KbdRptParser::OnKeyDown(uint8_t mod, uint8_t key)  {
    uint8_t c = OemToAscii(mod, key);

    if (c)
        OnKeyPressed(c);
               
}

/* what to do when symbol arrives */

void KbdRptParser::OnKeyPressed(uint8_t key)  {
    static uint32_t next_time = 0;
    static uint8_t current_cursor = 0;
    z = ((char)key);
    codeString += z;
    cont = cont + 1;
    
    if (char(key) == 19) {
        codeString.remove(cont - 1);
        Serial.println(codeString);
        codeString = "";
        cont = 0;
    }
}

KbdRptParser Prs;

void setup() {
    Serial.begin( 9600 );
    Serial.println("Start");

    if (Usb.Init() == -1) {
        Serial.println("OSC did not start.");
           
    }
    
    Hid.SetReportParser(0, (HIDReportParser*)&Prs);
    delay( 200 );
}

void loop() {
    Usb.Task();
}
