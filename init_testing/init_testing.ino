//This sketch is to make automated lights that illuminate under the island around my kitchen


#include <Adafruit_NeoPixel.h>

//D2 - D12 are pins 2 - 12
//A0 - A5 are 14 - 19
#define LED_PIN     8
#define LED_COUNT   60

#define trigPin 3    // Trigger
#define echoPin 4    // Echo

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);
// Argument 1 = Number of pixels in NeoPixel strip
// Argument 2 = Arduino pin number (most are valid)
// Argument 3 = Pixel type flags, add together as needed:
//  NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)

int state_var,alt;
long duration, cm;
bool lights_on, changed;

void setup() {
  // put your setup code here, to run once:

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

//  Serial.begin(9600);

  alt = 0;
  lights_on = 0;
  changed = 0;

  strip.begin();            // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();             // Turn OFF all pixels ASAP
  strip.setBrightness(50);  // Set BRIGHTNESS to about 1/5 (max = 255)

  state_var = 0;

}

void loop() {

  // put your main code here, to run repeatedly:


// The sensor is triggered by a HIGH pulse of 10 or more microseconds.
// Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
 
  // Read the signal from the sensor: a HIGH pulse whose
  // duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH);

//------Removed-Don't-need-to-troubleshoot--------
//  Serial.println(lights_on);
//  Serial.println(cm);

  // Convert the time into a distance
  cm = (duration/2) / 29.1;     // Divide by 29.1 or multiply by 0.0343

  if(cm < 20 and state_var == 0){
    state_var = 1;
    alt++;
  }
  else if(cm > 100) {
    state_var = 0;
  }

  if(alt%2){
    lights_on = 1;
  } else {
    lights_on = 0;
  }

randSpookyColors();

  
  if(lights_on and not changed){
//    colorWipe(strip.Color(165, 255, 25), 0); //green? rgb(255,105,180)
    changed = lights_on;
  } else if( not lights_on and changed){
    colorWipe(strip.Color(0, 0, 0), 0);   //off
    changed = lights_on;
  }

  
  delay(50);
}

//-------------------------FUNCTIONS!----------------------------------------

// Fill strip pixels one after another with a color. Strip is NOT cleared
// first; anything there will be covered pixel by pixel. Pass in color
// (as a single 'packed' 32-bit value, which you can get by calling
// strip.Color(red, green, blue) as shown in the loop() function above),
// and a delay time (in milliseconds) between pixels.
//(GREEN, RED, BLUE) is the Color coding for the uint32_t for some reason
void colorWipe(uint32_t color, int wait) {
  for(int i=0; i<strip.numPixels(); i++) { // For each pixel in strip...
    strip.setPixelColor(i, color);         //  Set pixel's color (in RAM)
    strip.show();                          //  Update strip to match
    delay(wait);                           //  Pause for a moment
  }
}

void randSpookyColors(){
  int tmWait = 10*rand();
  int pix = strip.numPixels()*rand();
  int rd =  255;
  int grn = round(160*rand());
  int blue = round(40*rand());
//  delay(tmWait);
  strip.setPixelColor(pix, strip.Color(grn, rd, blue));
//  Serial.print("led #:" + pix);
//  Serial.print(" grn:" + grn);
//  Serial.print(" red:" + rd);
//  Serial.print(" blue:" + blue);
  strip.show();
}

void sexyColors(){
  for(int i=0; i<strip.numPixels(); i=i+2){
    strip.setPixelColor(i, strip.Color(105, 255, 180));
  }
  strip.show();
}
