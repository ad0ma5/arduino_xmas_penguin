

#include "pitches.h"

//L293D
//Motor A
const int motorPin1  = A3;// 8;  // Pin 14 of L293
const int motorPin2  = A2; //9;  // Pin 10 of L293
//Motor B
const int motorPin3  = A1; //10; // Pin  7 of L293
const int motorPin4  = A0; //11;  // Pin  2 of L293
//leds
const int led1 = 12;
const int led2 = 13;
//timeout
const int timeout = 330;

//interrupt
const byte interruptPinOut = 6;

const byte interruptPin = 2;
volatile byte state = LOW;
//no delay
unsigned long currentMillis = 0;
unsigned long previousMillis = 0; 
// constants won't change:
const long interval = 1000;//step interval
int millsStep = 0; //0 to 10; 10 = 1s
int loopStep = 0;
bool doLoopOn = false;
int r = 0; //random times to move
int cur_step = 0; //step for motor
int quarterstep = 0;

 int i = 0;
// TONES  ========================================== // Start by defining the relationship between

 // Define a special note, 'R', to represent a rest
 #define  R     0
 // SETUP ============================================
 // Set up speaker on a PWM pin (digital 9, 10 or 11)
 int speakerOut = 10;
 // Do we want debugging on serial out? 1 for yes, 0 for no
 int DEBUG = 0;
  // MELODY and TIMING  =======================================
 //  melody[] is an array of notes, accompanied by beats[],
 //  which sets each note's relative length (higher #, longer note)
 int melody[] = {
  //*
//  JINGLE BELLS, JINGLE BELLS
 NOTE_B5, R, NOTE_B5, R, NOTE_B5, R, R, R,
 NOTE_B5, R, NOTE_B5, R, NOTE_B5, R, R, R,
// NOTE_B5, NOTE_B5, NOTE_B5,R,
//JINGLE ALL THE WAY
NOTE_B5, R, NOTE_D6, R,  NOTE_G5, R, NOTE_A5, R, 
NOTE_B5, NOTE_B5, NOTE_B5, NOTE_B5, NOTE_B5, NOTE_B5, R,R,
//OH WHAT FUN IT IS TO RIDE
NOTE_C6, R, NOTE_C6, R, NOTE_C6, R,   NOTE_C6, R, 
NOTE_C6, R, NOTE_B5,  R,  NOTE_B5, R,   NOTE_B5, NOTE_C6, 
//IN A ONE-HORSE OPEN SLEIGH, HEY
NOTE_B5, R,  NOTE_A5,  R, NOTE_A5,  R, NOTE_B5,  R,
  NOTE_A5,   R, R, R, NOTE_D6, R, R,R,

//JINGLE BELLS, JINGLE BELLS
 NOTE_B5, R, NOTE_B5, R, NOTE_B5, R, R, R,
 NOTE_B5, R, NOTE_B5, R, NOTE_B5, R, R, R,
//JINGLE ALL THE WAY
NOTE_B5, R, NOTE_D6, R,  NOTE_G5, R, NOTE_A5, R, 
NOTE_B5, NOTE_B5, NOTE_B5, NOTE_B5, NOTE_B5, NOTE_B5, R,R,
//OH WHAT FUN IT IS TO RIDE
NOTE_C6, R, NOTE_C6, R, NOTE_C6, R,   NOTE_C6, R, 
NOTE_C6, R, NOTE_B5,  R,  NOTE_B5, R,   NOTE_B5,  NOTE_B5,
//IN A ONE-HORSE OPEN SLEIGH
 NOTE_D6,  R, NOTE_D6,  R, NOTE_C6, R,  NOTE_A5, R, 
 NOTE_G5, NOTE_G5,  NOTE_G5, R, R, R, R,R,
 //*/

 

//DASHING THROUGH THE SNOW
NOTE_D5,  NOTE_D5,  NOTE_B5, R, NOTE_A5, R, NOTE_G5, R,
NOTE_D5,  NOTE_D5,  NOTE_D5, R, R,       R, R,       R,
//IN A ONE-HORSE OPEN SLEIGH
NOTE_D5,  NOTE_D5,  NOTE_B5, R, NOTE_A5, R, NOTE_G5,R,  
NOTE_E5,  NOTE_E5,  NOTE_E5, R, R,       R, R,       R,
//O’ER THE FIELS WE GO
NOTE_E5, NOTE_E5, NOTE_C6, R,NOTE_B5, R, NOTE_A5, R, 
NOTE_FS5, NOTE_FS5, NOTE_FS5,R, R,       R,  NOTE_D6, R,
//LAUGHING ALL THE WAY
NOTE_E6, R, NOTE_D6, R,  NOTE_C6, R, NOTE_A5,
NOTE_B5, NOTE_B5, NOTE_B5, R, R,       R, R,       R,

//BELLS ON BOBTAILS RING
NOTE_D5,  NOTE_D5,  NOTE_B5, R, NOTE_A5, R, NOTE_G5, R,
NOTE_D5,  NOTE_D5,  NOTE_D5, R, R,       R, R,       R, 
//MAKING SPIRITS BRIGHT
NOTE_D5,  NOTE_D5,  NOTE_B5, R, NOTE_A5, R, NOTE_G5,R,  
NOTE_E5,  NOTE_E5,  NOTE_E5, R, R,       R, R,       R,
//WHAT FUN IT IS TO RIDE AND SING
NOTE_E5, NOTE_E5, NOTE_C6, R, NOTE_B5, R, NOTE_A5, R, 
NOTE_D6, NOTE_D6, NOTE_D6, R, R,       R, NOTE_D6, R,
//A SLEIGHING SONG TONIGHT, HEY
NOTE_E6, R, NOTE_D6, R,  NOTE_C6, R,NOTE_A5, R, 
NOTE_G5,NOTE_G5, NOTE_G5, R, NOTE_D6,  R ,R ,R ,

/*
 
 

//JINGLE BELLS, JINGLE BELLS
B B B   B B B
//JINGLE ALL THE WAY
B NOTE_DS5,  NOTE_G5,NOTE_A5,B
//OH WHAT FUN IT IS TO RIDE
NOTE_CS5,NOTE_CS5,NOTE_CS5,  NOTE_CS5,NOTE_CS5,B B
//IN A ONE-HORSE OPEN SLEIGH, HEY
B B B NOTE_A5,NOTE_A5,B NOTE_A5,  NOTE_DS5, 
//JINGLE BELLS, JINGLE BELLS
B B B   B B B
//JINGLE ALL THE WAY
B NOTE_DS5,  NOTE_G5,NOTE_A5,B
//OH WHAT FUN IT IS TO RIDE
NOTE_CS5,NOTE_CS5,NOTE_CS5,  NOTE_CS5,NOTE_CS5,B B
//IN A ONE-HORSE OPEN SLEIGH
B B NOTE_DS5,  NOTE_DS5,  NOTE_CS5,NOTE_A5,G
*/

 };
 int MAX_COUNT = sizeof(melody) / 2; // Melody length, for looping.
 // Set overall tempo
 long tempo = 5000;
 // Set length of pause between notes
 int pause = 100;
 // Loop variable to increase Rest length
 int rest_count = 100; //<-BLETCHEROUS HACK; See NOTES
 // Initialize core variables
 unsigned int tone_ = 0;
 int beat = 0;
 long duration  = 400;
 bool playing = false;
 long previousTone = 0;

 //int noteStep = 0;
 
//This will run only one time.
void setup(){
  setupTone();
  
    pinMode(led1, OUTPUT);
    pinMode(led2, OUTPUT);

    pinMode(interruptPinOut, OUTPUT);
    pinMode(interruptPin, INPUT);
    attachInterrupt(digitalPinToInterrupt(interruptPin), blink, CHANGE);
    //Set pins as outputs
    pinMode(motorPin1, OUTPUT);
    pinMode(motorPin2, OUTPUT);
    pinMode(motorPin3, OUTPUT);
    pinMode(motorPin4, OUTPUT);
    
    //Motor Control - Motor A: motorPin1,motorpin2 & Motor B: motorpin3,motorpin4

    //moveit();
    digitalWrite(interruptPinOut, LOW);
    stopMotors();
    //pinMode(interruptPin, INPUT_PULLUP);
    digitalWrite(led1, HIGH);
    digitalWrite(led2, HIGH);
    delay(timeout); 
    
  
}
void blink() {  
  state = HIGH;
}
void loop(){  
  
 
//  if(timeoutMills){
//    timeoutMills = false;
    doLoop(); 
    
//  }
  
}
//doLoop
void doLoop(){
  //sort time
  if(state == HIGH){
    
    
    currentMillis = millis();
    if (currentMillis - previousMillis >= interval) {
      // save the last time you blinked the LED
      previousMillis = currentMillis;
      millsStep++;
      //if(millsStep >= 10) millsStep = 0;
    }
    //
    if(doLoopOn == false){ 
      r = MAX_COUNT/4;//random(10);
      digitalWrite(led1, state);
      digitalWrite(led2, state);      
      digitalWrite(interruptPinOut, state);
      loopStep = millsStep;
      doLoopOn = true;
      i = 0;
    }  
    loopTone(); //music
    loopRand(millsStep - loopStep);  
    //if(millsStep < loopStep) loopStep = loopStep = 10;  
    if(doLoopOn && millsStep - loopStep == r){
      state = LOW;
      digitalWrite(interruptPinOut, state);
      digitalWrite(led1, state);
      digitalWrite(led2, state);
      loopStep = 0;
      doLoopOn = false;
      stopMotors();
      quarterstep = 0;
    }
  }
}
void loopRand(int cur_step){
  
  
  //moveit();
  
  //for (int i = 0; i<r;i++){
    //digitalWrite(led1, HIGH);
    //digitalWrite(led2, HIGH);
    //delay(timeout);
    if(cur_step%2 == 0)
      moveit(cur_step);
    else
      moveitBoth(cur_step);
  //}


  //int rr = random(5000);
  //delay(r+5000);
  //delay(rr);
}
void moveON(int p1, int p2, int p3, int p4){
    analogWrite(motorPin1, p1);
    analogWrite(motorPin2, p2);
    analogWrite(motorPin3, p3);
    analogWrite(motorPin4, p4);  
}
void eyesON(int l1,int l2){
    digitalWrite(led1, l1);
    digitalWrite(led2, l2);
}
void moveit(int cur_step){
   unsigned long curr = millis() - previousMillis;
    if(quarterstep == 0){
      //digitalWrite(led1, HIGH);
      //digitalWrite(led2, LOW);    
      eyesON(HIGH,LOW);
      //This code  will turn Motor A clockwise for 2 sec.
      //    analogWrite(motorPin1, 180);
      //    analogWrite(motorPin2, 0);
      //    analogWrite(motorPin3, 0);
      //    analogWrite(motorPin4, 0); 
      moveON(180, 0,0,0);
      quarterstep++;
    }
    //delay(timeout); 

    if(quarterstep == 1 && curr >= interval/4){
      //digitalWrite(led1, LOW);
      //digitalWrite(led2, HIGH);
      eyesON(LOW, HIGH);
      //This code will turn Motor A counter-clockwise for 2 sec.
      //    analogWrite(motorPin1, 0);
      //    analogWrite(motorPin2, 0);
      //    analogWrite(motorPin3, 180);
      //    analogWrite(motorPin4, 0);
      moveON(0,0,180, 0);
      quarterstep++;
    }
    //delay(timeout);
    if(quarterstep  == 2 && curr >= interval/2){
      //    digitalWrite(led1, HIGH);
      //    digitalWrite(led2, LOW);
      eyesON(HIGH,LOW);
      //This code will turn Motor B clockwise for 2 sec.
      //    analogWrite(motorPin1, 0);
      //    analogWrite(motorPin2, 180);
      //    analogWrite(motorPin3, 0);
      //    analogWrite(motorPin4, 0);
      moveON(0,180, 0,0);
      quarterstep++;
    }
    //delay(timeout); 
    if(quarterstep == 3  && curr >= interval/2 + interval/4){
      //    digitalWrite(led1, LOW);
      //    digitalWrite(led2, HIGH);
      eyesON(LOW, HIGH);
      //This code will turn Motor B counter-clockwise for 2 sec.
      //    analogWrite(motorPin1, 0);
      //    analogWrite(motorPin2, 0);
      //    analogWrite(motorPin3, 0);
      //    analogWrite(motorPin4, 180);
      moveON(0, 0,0,180);
      quarterstep++;
    }
    //delay(timeout); 
    if(quarterstep == 4 && curr > interval/2 + interval/4 +interval/5){   
      //    digitalWrite(led1, HIGH);
      //    digitalWrite(led2, LOW);
      eyesON(HIGH,LOW);
      
      //And this code will stop motors
      //    analogWrite(motorPin1, 0);
      //    analogWrite(motorPin2, 0);
      //    analogWrite(motorPin3, 0);
      //    analogWrite(motorPin4, 0); 
      stopMotors();
      quarterstep = 0;
    }
    //delay(timeout);  
  
}
void stopMotors(){
   //And this code will stop motors
    analogWrite(motorPin1, 0);
    analogWrite(motorPin2, 0);
    analogWrite(motorPin3, 0);
    analogWrite(motorPin4, 0);  
}
void moveitBoth(int in){
    unsigned long curr = millis() - previousMillis;
   
  
    //delay(timeout*2);
    if(quarterstep == 2 && curr >= interval- interval/4){   
      //    digitalWrite(led1, LOW);
      //    digitalWrite(led2, HIGH);
      eyesON(LOW, HIGH);
      //And this code will stop motors
      //    analogWrite(motorPin1, 0);
      //    analogWrite(motorPin2, 0);
      //    analogWrite(motorPin3, 0);
      //    analogWrite(motorPin4, 0);  
      stopMotors();
      quarterstep = 0;
    }
    //delay(timeout*2);
  //delay(timeout*2); 
    
    if(quarterstep == 1 && curr >= interval/2){ // half step passed  
      //    digitalWrite(led1, HIGH);
      //    digitalWrite(led2, LOW);
      eyesON(HIGH,LOW);
      //This code will turn Motor A B counter-clockwise for 2 sec.
      //    analogWrite(motorPin1, 0);
      //    analogWrite(motorPin2, 180);
      //    analogWrite(motorPin3, 0);
      //    analogWrite(motorPin4, 180);
      moveON(0,180, 0,180);
      quarterstep++;
    }
    
    if(quarterstep == 0){
      //    digitalWrite(led1, LOW);
      //    digitalWrite(led2, HIGH);
      eyesON(LOW, HIGH);
      
      //This code  will turn Motor A B clockwise for 2 sec.
      //    analogWrite(motorPin1, 180);
      //    analogWrite(motorPin2, 0);
      //    analogWrite(motorPin3, 180);
      //    analogWrite(motorPin4, 0);
      moveON(180, 0,180,0);
      quarterstep++;
    }
  
}
//*
///////////////////
//TONE
//////////////////
// * Jingle Bellsl
// * Coded By - http://www.instructables.com/id/Arduino-Controlled-Flashing-Christmas-Fairy-Lights/step5/Code-for-Jingle-Bells/
// * Use BSD Clause 2 License for Distribution
// * Collection by GitHub User @abhishekghosh - https://github.com/AbhishekGhosh/Arduino-Buzzer-Tone-Codes


 void setupTone() {
   pinMode(speakerOut, OUTPUT);
   if (DEBUG) {
     Serial.begin(9600); // Set serial out if we want debugging
   }
 }

 // PLAY TONE  ==============================================
 // Pulse the speaker to play a tone for a particular duration
 void playTone() {
  //unsigned long curr = millis() - previousTone;
   long elapsed_time = 0;
   if (true || tone_ > 0) { // if this isn't a Rest beat, while the tone has
     //  played less long than 'duration', pulse speaker HIGH and LOW
        /*    
              
     while (elapsed_time < duration) {
      if(!playing && curr >= tone_ / 2){
       digitalWrite(speakerOut,HIGH);
       playing = true;
      }
       delayMicroseconds(tone_ / 2);
       // DOWN
       if(playing && curr >= tone_ / 2 ){
        digitalWrite(speakerOut, LOW);
        playing = false;
       }
       delayMicroseconds(tone_ / 2);

       // Keep track of how long we pulsed
       elapsed_time += (tone_);
         }
         //*/   
         //tone(pin, frequency)
         // tone(pin, frequency, duration)
         tone(speakerOut, tone_, interval);
   }
   else { // Rest beat; loop times delay
    
     //for (int j = 0; j < rest_count; j++) { // See NOTE on rest_count
       //delayMicroseconds(duration); 
     //} 
   }                                
 }
 // LET THE WILD RUMPUS BEGIN =============================
 void loopTone() {
  //for (int i=0; i<MAX_COUNT; i++) {
  if(millis() - previousTone >= interval/8){
    if(i > MAX_COUNT) i = 0;
    tone_ = melody[i];
    
    beat = 50;

    duration = beat * tempo; // Set up timing
    
    playTone();
    previousTone = millis();//
    i++;
    
  }
    
    
    
    // A pause between notes...
    //delayMicroseconds(pause);
  
 }
 //*/
