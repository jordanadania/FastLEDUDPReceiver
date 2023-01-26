#define FASTLED_INTERRUPT_RETRY_COUNT 0
#define FASTLED_INTERNAL
#include <FastLED.h>

#include "user_interface.h"

#include <ArduinoOTA.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <ESP8266mDNS.h>

#define ARRAY_SIZE(A) (sizeof(A)/sizeof((A)[0]))

#define MASTERPACKETSIZE 8

#include "config.h"

CRGB leds[NUM_LEDS];

WiFiUDP Udp;
               byte lastPat,
     buff[MASTERPACKETSIZE];

uint16_t edges[26];
uint8_t  modus[26];

uint8_t        invert = true,
                 gHue,
                 huey,
               bright,
          spectrumAvg,
  currentPaletteIndex = 0,
gCurrentPaletteNumber = 0,
    secondsPerPalette = 20;

CRGB solidColor = CRGB::Black;

TBlendType currentBlending = LINEARBLEND;
  
#if defined(FIBO256)
  uint8_t speed = 0;
#else
  uint8_t speed = 0;
#endif

CRGB c = CRGB::Black;

unsigned long currentMillis,
            lastFrameMillis;
            
#include "Palette.h"        
#include "Pattern.h"

void setup() {
  //Serial.begin(115200);
  delay(100);
  Serial.setDebugOutput(true);
  Serial.println();
  if(NUM_STRIPS>1)
    // Parallel output: 6, 7, 5, 8
    FastLED.addLeds<WS2811_PORTA, NUM_STRIPS>(leds, NUM_LED);
    //FastLED.addLeds<LED_TYPE, DATA_PIN_2, COLOR_ORDER>(leds, NUM_LEDS);
  else
    FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS);
  LEDS.setDither(false);
  LEDS.setCorrection(TypicalLEDStrip);
  //LEDS.setBrightness(BRIGHTNESS);
  LEDS.setMaxPowerInVoltsAndMilliamps(5, MILLI_AMPS);
  memset(leds, 0, sizeof(leds));
  LEDS.show();
  #include "OtA.h"
  //for(byte b=0; b<=25; ++b)
  //  edges[b] = b==0? NUM_LED-1: NUM_LED/(b*1)-1;
  //for(byte b=0; b<=25; ++b)
  //  modus[b] = b==0? 0: NUM_LED%(b*1);  
  for(byte b=0; b<=25; ++b)
    edges[b] = b==0? NUM_LEDS-1: NUM_LEDS/(b*NUM_STRIPS)-1;
  for(byte b=0; b<=25; ++b)
    modus[b] = b==0? 0: NUM_LEDS%(b*NUM_STRIPS);   
}

void loop() {
  ArduinoOTA.handle();
  yield();  // No Answer Otherwise
  
  EVERY_N_SECONDS( secondsPerPalette ) {
    gCurrentPaletteNumber = addmod8( gCurrentPaletteNumber, 1, gGradientPaletteCount);
    gTargetPalette = gGradientPalettes[ gCurrentPaletteNumber ];
  }

  EVERY_N_MILLISECONDS(40){ nblendPaletteTowardPalette( gCurrentPalette, gTargetPalette, 8); }
  
  int packetSize = Udp.parsePacket();
  if (packetSize){
    buff[packetSize];
    Udp.read(buff, packetSize);
    lastPat = buff[0];
    patterns[buff[0]]();
  } else {
    patterns[lastPat]();
  }
  FastLED.delay(4); // DONT CHANGE EVER
}
