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

int state_var;
//int held;
//bool once;
//bool once0;
//int upper_lim = 300;
//int lower_lim = 10;

long duration, cm;

// Fill strip pixels one after another with a color. Strip is NOT cleared
// first; anything there will be covered pixel by pixel. Pass in color
// (as a single 'packed' 32-bit value, which you can get by calling
// strip.Color(red, green, blue) as shown in the loop() function above),
// and a delay time (in milliseconds) between pixels.
void colorWipe(uint32_t color, int wait) {
  for(int i=0; i<strip.numPixels(); i++) { // For each pixel in strip...
    strip.setPixelColor(i, color);         //  Set pixel's color (in RAM)
    strip.show();                          //  Update strip to match
    delay(wait);                           //  Pause for a moment
  }
}

void setup() {
  // put your setup code here, to run once:

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  Serial.begin (9600);


//  strip.begin();            // INITIALIZE NeoPixel strip object (REQUIRED)
//  strip.show();             // Turn OFF all pixels ASAP
//  strip.setBrightness(50);  // Set BRIGHTNESS to about 1/5 (max = 255)

  state_var = 0;
//  held = 0;
//  once = false;
//  once0 = false;

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

 
  // Convert the time into a distance
  cm = (duration/2) / 29.1;     // Divide by 29.1 or multiply by 0.0343

  Serial.println(cm);
  delay(1000);

  if(cm < 20){
    state_var = 1;
  }
  else if(cm > 100) {
    state_var = 0;
  }

  Serial.println(state_var);
  if( state_var = 1){
    colorWipe(strip.Color(250, 0, 0), 10);
  }
  else if( state_var = 0){
    colorWipe(strip.Color(0,0,0), 100);
  }




//------------Changing States-----------------

/*
//if cm is greater than Upper Limit then reset ONS
  if(cm >= upper_lim) {
    once = false;
  }

//if cm is lower than Lower Limit
  if(cm <= lower_lim && once==false) {
    state_var++;
    once = true;
  }

  if(once){
    held++;
  }

//Start of State Machine
//--------------State 0------------------------
   if (state_var == 0) {
//    colorWipe(strip.Color(0,   0,   0), 10); //Turn OFF all pixels
   }//--------------State 1------------------------
   else if (state_var == 1) {
//    colorWipe(strip.Color(250, 0, 0), 10); //red
   }//--------------State 2------------------------
   else if (state_var == 2) {
//    colorWipe(strip.Color(0, 250, 0), 10); //green
   }//--------------Catch All-------------------- (hopefully doesn't get stuck unbounded)
   else {
    state_var = 0;
   }

//   strip.show(); 

   Serial.println("state var" + state_var);
   */
}

//void example_function (int wait){
//  uint32_t color;
//  delay(wait);
//}

//long microsecondsToInches(long microseconds) {
//   return microseconds / 74 / 2;
//}
//
//long microsecondsToCentimeters(long microseconds) {
//   return microseconds / 29 / 2;
//}
