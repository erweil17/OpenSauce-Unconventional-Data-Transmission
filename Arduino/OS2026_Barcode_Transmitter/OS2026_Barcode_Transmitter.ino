#define TFT_RST       4   
#define TFT_CS        15     
#define TFT_DC        2  
#define TFT_BACKLIGHT 5
#define TFT_MOSI      13
#define TFT_SCLK      14  

#include <Adafruit_GFX.h>      
#include <Adafruit_ST7789.h>   
#include <SPI.h>
#include <qrcode_st7789.h>

String data = "";      //String entered by user

Adafruit_ST7789 display = Adafruit_ST7789(&SPI, TFT_CS, TFT_DC, TFT_RST);
QRcode_ST7789 qrcode (&display);


void setup() {

   Serial.begin(9600);
  // enable debug qrcode
  // qrcode.debug();
  SPI.begin(TFT_SCLK,TFT_RST,TFT_MOSI,TFT_CS);
  display.init(240,320);
  display.fillScreen(ST77XX_WHITE);
  pinMode(TFT_BACKLIGHT, OUTPUT);
  digitalWrite(TFT_BACKLIGHT, HIGH);

  // Initialize QRcode display using library
  qrcode.init();

  for (int i=0; i<64; i++){
    data[i] = '\0';
  }

}

void loop() { 
  if (Serial.available() > 0){                                 //Check if data is waiting
    delay(100);                                                //If so, wait 100ms for it to all show up
    data = Serial.readString();                              //Read 1 char
    Serial.write("1");                                       //Tell transmitter app to send more chars
    
    for (int i=0; i<data.length(); i++){
      if (data[i] == 0){
        data[i] = 129;
      }
    }

    qrcode.create(data);
    delay(1000);  
    display.fillScreen(ST77XX_WHITE);
  }

  data = "";
}

