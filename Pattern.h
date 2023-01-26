#define qsubd(x, b)  ((x>b)?b:0)
#define qsuba(x, b)  ((x>b)?x-b:0)

CRGB rBow[] = { CRGB::Red,
                CRGB::Yellow,
                CRGB::Green,
                CRGB::Cyan,
                CRGB::Blue,
                CRGB::Violet,
                CRGB::Magenta };
                
void addGlitter(uint8_t chanceOfGlitter){
  if(random8()<chanceOfGlitter)
    leds[random16(NUM_LEDS)] += CRGB::White;
}

void push(uint16_t k){
  #if HAS_MAP
    for(uint16_t i=k; i>0; --i)
      leds[mapIt[i]] = leds[mapIt[i-1]];
    for(uint16_t i=k; i>0; --i)
      leds[i] = leds[i-1];
  #endif
}
void pull(uint16_t k){
  #if HAS_MAP
    for(uint16_t i=0; i<k; ++i)
      leds[mapIt[i]] = leds[mapIt[i+1]];
  #else
    for(uint16_t i=0; i<k; ++i)
      leds[i] = leds[i+1];
  #endif
}
void mirror(uint16_t k){
  #if HAS_MAP
    for(uint16_t i=0; i<k; ++i)
      leds[mapIt[k-i]] = leds[mapIt[i]];
  #else
    for(uint16_t i=0; i<k; ++i)
      leds[k-i]=leds[i];
  #endif
}
void copyIt(byte k){
  memcpy(leds+NUM_LEDS/k, leds, modus[k]<1? NUM_LEDS/k*sizeof(CRGB):NUM_LEDS/k*sizeof(CRGB)+sizeof(CRGB));
}

void rainFlow(){
  speed = buff[1];
  FastLED.setBrightness(buff[2]);
  c.setRGB(buff[3], buff[4], buff[5]);
  
  bool zero = speed == 0 ? true : false;
  
  uint16_t edge = edges[speed];
  uint16_t halfEdge = edge >> 1;
  uint16_t i = invert? (zero? edge: halfEdge): 0;
  Serial.print(edge);
  Serial.print(" ");
  Serial.print(halfEdge);
  Serial.print(" ");
  Serial.println(i);

  
#ifdef FIBO256
  invert? pull(zero? edge: halfEdge): push(zero? edge: halfEdge);
  invert? pull(zero? edge: halfEdge): push(zero? edge: halfEdge);
#else
  currentMillis = millis();
  if(currentMillis - lastFrameMillis > PUSHPULLDELAY){
    invert? pull(zero? edge: halfEdge): push(zero? edge: halfEdge);
    lastFrameMillis = currentMillis;
  }  
#endif
  
 // #if HAS_MAP
    leds[mapIt[i]] = c;
 // #else
 //   leds[i] = c;
 // #endif

  if(!zero){
  //if(speed>0)
  //  mirror(edges[speed]);
  //if(speed>1)
  //  mirror(edges[speed-1]);
    for(byte b = 0; b<speed*NUM_STRIPS; ++b)
      mirror(edge*(b+1));
    //if(speed>1){
      //copyIt(speed*NUM_STRIPS);
    //}
  }
}

void plasma(){
  FastLED.setBrightness(buff[1]);
  spectrumAvg = buff[2];
  currentPaletteIndex = buff[3];
  
  static int16_t thisphase = 0;
  static int16_t thatphase = 0;
  
  uint16_t briIdx;
  uint16_t huey;
  
  thisphase += beatsin8(6,-4,4);
  thatphase += beatsin8(7,-4,4);
  
  for(int k=0; k<NUM_LEDS; k++){
    briIdx = cubicwave8((k*8)+thisphase)/2;
    briIdx += cos8((k*10)+thatphase)/2;
    huey = briIdx;
    briIdx = qsuba(briIdx, 255-spectrumAvg);
    leds[k] = ColorFromPalette(palettes[currentPaletteIndex], huey, briIdx, LINEARBLEND);
  }
  addGlitter(spectrumAvg/2);
}

void mappedPlasma(){
  FastLED.setBrightness(buff[1]);
  spectrumAvg = buff[2];
  currentPaletteIndex = buff[3];
  
  static int16_t thisphase = 0;
  static int16_t thatphase = 0;
  
  uint16_t briIdx;
  uint16_t huey;
  
  thisphase += beatsin8(6,-4,4);
  thatphase += beatsin8(7,-4,4);
  
  for(int k=0; k<NUM_LEDS; k++){
    briIdx = cubicwave8((k*8)+thisphase)/2;
    briIdx += cos8((k*10)+thatphase)/2;
    huey = briIdx;
    briIdx = qsuba(briIdx, 255-spectrumAvg);
    leds[mapIt[k]] = ColorFromPalette(palettes[currentPaletteIndex], huey, briIdx, LINEARBLEND);
  }
  addGlitter(spectrumAvg/2);
}

void paletteG() {
  FastLED.setBrightness(buff[1]);
  spectrumAvg = buff[2];
  currentPaletteIndex = buff[3];
  
  uint8_t beatA = beatsin8(17, 0, 255);
  uint8_t beatB = beatsin8(13, 0, 255);
  uint8_t beatC = beatsin8(11, 0, 255);
  for (int i=0; i < NUM_LEDS; i++) {
    int huey = (beatA+beatB+beatC)/3 * i * 4 / NUM_LEDS;
    leds[i] = ColorFromPalette(palettes[currentPaletteIndex], huey, spectrumAvg, LINEARBLEND);
  }
  addGlitter(spectrumAvg);
}

void mappedPaletteG() {
  FastLED.setBrightness(buff[1]);
  spectrumAvg = buff[2];
  currentPaletteIndex = buff[3];
  
  uint8_t beatA = beatsin8(17, 0, 255);
  uint8_t beatB = beatsin8(13, 0, 255);
  uint8_t beatC = beatsin8(11, 0, 255);
  for (int i=0; i < NUM_LEDS; i++) {
    int huey = (beatA+beatB+beatC)/3 * i * 4 / NUM_LEDS;
    leds[mapIt[i]] = ColorFromPalette(palettes[currentPaletteIndex], huey, spectrumAvg, LINEARBLEND);
  }
  addGlitter(spectrumAvg);
}

void vuPalette(){
  #ifdef FIBO256
    speed = 0;
  #else
    speed = buff[1];
  #endif
  FastLED.setBrightness(buff[2]);
  spectrumAvg = buff[3];
  currentPaletteIndex = buff[4];
  memset(leds, 0, sizeof(leds));
  bool   zero = speed==0? true:false;
  // segment creation
  uint16_t  k = edges[speed]+1;
  uint16_t hk = k >> 1;
  if(k%2 > 0)
    ++hk;
  uint16_t newSpec = map(spectrumAvg,0,255,0,(zero?k-1:hk-1));
  for(uint16_t i=0; i<(zero?k:hk); ++i){
    uint8_t j = map(i,0, (zero?k-1:hk-1), 0, (zero?255:127));
    if(true ? i <= newSpec : i >= newSpec){
      leds[i] = ColorFromPalette(palettes[currentPaletteIndex], invert? j: 255-j);
      if(!zero)
        leds[k-1-i] = ColorFromPalette(palettes[currentPaletteIndex], invert? 255-j: j);
    } else {
      leds[i] = CRGB::Black;
      if(!zero)
        leds[k-1-i] = CRGB::Black;
    }
  }
  if(speed>1) copyIt(speed);
}

void sevenBands(){
  FastLED.setBrightness(buff[1]);
  uint8_t spectrumByte = buff[2];
  memset(leds, 0, sizeof(leds));
  uint16_t mappedByte = map(spectrumByte, 0, 255, 0, NUM_LEDS-1);
  for(uint16_t i=0; i<NUM_LEDS; ++i)
    if(i <= mappedByte)
      if (spectrumByte == 9)
        leds[i] = CHSV(i,255,255);
      else
        leds[i] = rBow[BAND];
}

void xPalette(){
  speed = buff[1];
  FastLED.setBrightness(buff[2]);
  gHue = buff[3];
  currentPaletteIndex = buff[4];
  #if HAS_MAP
    #ifdef FIBO256
      for(uint16_t i = 0; i < NUM_LEDS; ++i)
        //leds[i] = ColorFromPalette(palettes[currentPaletteIndex], beat8(speed) - (coordsX[i] * gHue) + XOFFSET);
        leds[i] = ColorFromPalette(palettes[currentPaletteIndex], (coordsX[i]) + (gHue*speed) + XOFFSET, 255, LINEARBLEND);
    #else
      for(uint16_t i = 0; i < NUM_LEDS; ++i)
        //leds[i] = ColorFromPalette(palettes[currentPaletteIndex], beat8(speed) - (coordsX[i] * gHue) + XOFFSET);
        leds[i] = ColorFromPalette(palettes[currentPaletteIndex], (coordsX[i]>>3) + (gHue*speed) + XOFFSET, 255, LINEARBLEND);
    #endif
  #else
    for(uint16_t i = 0; i < NUM_LEDS; ++i)
      //leds[i] = ColorFromPalette(palettes[currentPaletteIndex], beat8(speed) - (coordsX[i] * gHue) + XOFFSET);
      leds[i] = ColorFromPalette(palettes[currentPaletteIndex], (gHue*speed) + XOFFSET, 255, LINEARBLEND);
  #endif
}

void yPalette(){
  speed = buff[1];
  FastLED.setBrightness(buff[2]);
  gHue = buff[3];
  currentPaletteIndex = buff[4];
  #if HAS_MAP
    #ifdef FIBO256
      for(uint16_t i = 0; i < NUM_LEDS; ++i)
        //leds[i] = ColorFromPalette(palettes[currentPaletteIndex], beat8(speed) - (coordsY[i] * gHue) + YOFFSET);
        leds[i] = ColorFromPalette(palettes[currentPaletteIndex], (gHue*speed) - (coordsY[i]>>2) +  YOFFSET, 255, LINEARBLEND);
    #else
      for(uint16_t i = 0; i < NUM_LEDS; ++i)
        //leds[i] = ColorFromPalette(palettes[currentPaletteIndex], beat8(speed) - (coordsY[i] * gHue) + YOFFSET);
        leds[i] = ColorFromPalette(palettes[currentPaletteIndex], (coordsY[i]>>2) + (gHue*speed) + YOFFSET, 255, LINEARBLEND);
    #endif
  #else
    for(uint16_t i = 0; i < NUM_LEDS; ++i)
      //leds[i] = ColorFromPalette(palettes[currentPaletteIndex], beat8(speed) - (coordsY[i] * gHue) + YOFFSET);
      leds[i] = ColorFromPalette(palettes[currentPaletteIndex], (gHue*speed) + YOFFSET, 255, LINEARBLEND);
  #endif
}

void xyPalette(){
  speed = buff[1];
  FastLED.setBrightness(buff[2]);
  gHue = buff[3];
  currentPaletteIndex = buff[4];
  #if HAS_MAP
    #ifdef FIBO256
      for(uint16_t i = 0; i < NUM_LEDS; ++i)
        //leds[i] = ColorFromPalette(palettes[currentPaletteIndex], beat8(speed) - ((coordsX[i] + coordsY[i]) * gHue));
        leds[i] = ColorFromPalette(palettes[currentPaletteIndex], (gHue*speed) - (coordsY[i]>>1) - (coordsX[i]>>2) + XOFFSET + YOFFSET, 255, LINEARBLEND);
    #else
      for(uint16_t i = 0; i < NUM_LEDS; ++i)
        //leds[i] = ColorFromPalette(palettes[currentPaletteIndex], beat8(speed) - ((coordsX[i] + coordsY[i]) * gHue));
        leds[i] = ColorFromPalette(palettes[currentPaletteIndex], (coordsY[i]>>1) + (coordsX[i]>>1) + (gHue*speed) + XOFFSET + YOFFSET, 255, LINEARBLEND);
    #endif
  #else
    for(uint16_t i = 0; i < NUM_LEDS; ++i)
      //leds[i] = ColorFromPalette(palettes[currentPaletteIndex], beat8(speed) - ((coordsX[i] + coordsY[i]) * hues));
      leds[i] = ColorFromPalette(palettes[currentPaletteIndex], (gHue*speed) + XOFFSET + YOFFSET, 255, LINEARBLEND);
  #endif
}

void pride(){
  FastLED.setBrightness(buff[1]);
  
  static uint16_t sPseudotime = 0;
  static uint16_t sLastMillis = 0;
  static uint16_t sHue16 = 0;

  uint8_t sat8 = beatsin88( 43.5, 220, 250);
  uint8_t brightdepth = beatsin88(171, 96, 224);
  uint16_t brightnessthetainc16 = beatsin88( 102, (25 * 256), (40 * 256));
  
  uint8_t msmultiplier = buff[2];
  
  uint16_t hue16 = sHue16;
  uint16_t hueinc16 = beatsin88(57, 1, 128);
  uint16_t ms = millis();
  uint16_t deltams = ms - sLastMillis ;
  sLastMillis  = ms;
  sPseudotime += deltams * msmultiplier;
  sHue16 += deltams * beatsin88( 200, 5, 9);
  uint16_t brightnesstheta16 = sPseudotime;
  for ( uint16_t i = 0 ; i < NUM_LEDS; i++) {
    hue16 += hueinc16;
    uint8_t hue8 = hue16 / 256;
    brightnesstheta16  += brightnessthetainc16;
    uint16_t b16 = sin16( brightnesstheta16  ) + 32768;
    uint16_t bri16 = (uint32_t)((uint32_t)b16 * (uint32_t)b16) / 65536;
    uint8_t bri8 = (uint32_t)(((uint32_t)bri16) * brightdepth) / 65536;
    bri8 += (255 - brightdepth);
    CRGB newcolor = CHSV( hue8, sat8, bri8);
    uint16_t pixelnumber = i;
    #ifdef FIBO256
      pixelnumber = mapIt[i];
    #endif
    pixelnumber = (NUM_LEDS - 1) - pixelnumber;
    nblend( leds[pixelnumber], newcolor, 64);
  }
}
void colorWaves(){
  FastLED.setBrightness(buff[1]);
  Serial.println("waving");
  
  static uint16_t sPseudotime = 0;
  static uint16_t sLastMillis = 0;
  static uint16_t sHue16 = 0;

  uint8_t brightdepth = beatsin88(171, 96, 224);
  uint16_t brightnessthetainc16 = beatsin88( 102, (25 * 256), (40 * 256));
  uint8_t msmultiplier = buff[2];

  uint16_t hue16 = sHue16;//gHue * 256;
  uint16_t hueinc16 = beatsin88(57, 1, 128);

  uint16_t ms = millis();
  uint16_t deltams = ms - sLastMillis ;
  sLastMillis  = ms;
  sPseudotime += deltams * msmultiplier;
  sHue16 += deltams * beatsin88( 200, 5, 9);
  uint16_t brightnesstheta16 = sPseudotime;
  
  for ( uint16_t i = 0 ; i < NUM_LED; i++) {
    hue16 += hueinc16;
    uint8_t hue8 = hue16 / 256;
    uint16_t h16_128 = hue16 >> 7;
    if ( h16_128 & 0x100) {
      hue8 = 255 - (h16_128 >> 1);
    } else {
      hue8 = h16_128 >> 1;
    }

    brightnesstheta16  += brightnessthetainc16;
    uint16_t b16 = sin16( brightnesstheta16  ) + 32768;

    uint16_t bri16 = (uint32_t)((uint32_t)b16 * (uint32_t)b16) / 65536;
    uint8_t bri8 = (uint32_t)(((uint32_t)bri16) * brightdepth) / 65536;
    bri8 += (255 - brightdepth);

    uint8_t index = hue8;
    index = scale8( index, 240);

    CRGB newcolor = ColorFromPalette( gCurrentPalette, index, bri8);

    uint16_t pixelnumber = i;
#ifdef FIBO256
  pixelnumber = mapIt[i];
#endif
   // pixelnumber = (NUM_LEDS - 1) - pixelnumber;

    nblend( leds[pixelnumber], newcolor, 128);
  }
  if(NUM_STRIPS>1)
    for(byte b = 1; b<NUM_STRIPS; ++b)
      mirror(NUM_LED*(b+1)-1);
  
}

void giantRuler(){
  for(uint16_t k=0; k<NUM_LEDS; ++k)
    if(k%10==9) leds[k] = CHSV(80, 255, 100);
    else        leds[k] = CRGB::Black;
}

void showSolidColor(){
  CRGB c;
  c.setRGB(buff[2], buff[3], buff[4]);
  FastLED.setBrightness(buff[1]);
  fill_solid(leds, NUM_LEDS, c);
}

void off(){ fill_solid(leds, NUM_LEDS, CRGB::Black); }

typedef void (*Pattern)();
typedef Pattern PatternList[];

const PatternList patterns = {
  off,            // 0
  rainFlow,       // 1
  plasma,         // 2
  mappedPlasma,   // 3
  paletteG,       // 4
  mappedPaletteG, // 5
  vuPalette,      // 6
  sevenBands,     // 7
  xPalette,       // 8
  yPalette,       // 9
  xyPalette,      // 10
  pride,          // 11
  colorWaves,     // 12
  giantRuler,     // 13
  showSolidColor  // 14
  };

const uint8_t patternCount = ARRAY_SIZE(patterns);
