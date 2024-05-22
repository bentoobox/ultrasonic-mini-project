#include "Timer.h"
//#include "Tone.h"
//PINS
const int trigPin = A1;
const int echoPin = A2;
//TONES
//DEPRECATED
//Tone searchTone;
//Tone lockTone;
//RADAR VAR
float distance;
long duration;
int dist=0;
int count=0;
int tncnt=0;

//RANGES
int cls =50;
int mid=100;
int far=400;
//SM
enum LD_Tones {Tfr, Tmid, Tcls, Tzero} LD_Tone;
enum LD_Refreshs {Rtns, Rhns,Rthns,Rtms} LD_Refresh;
enum LD_Radars {RDSend1, RDSend2, RDRecieve,} LD_Radar;
//////////////////////////////////////////////
//THIS STATE MACHINE PULSES AND IDENTIFIES THE RANGE OF THE TARGET WITHOUT INTERRUPTING THE GLOBAL CLOCK EVERY ~12ms
//////////////////////////////////////////////
void TickFct_RdrControl() {
switch (LD_Radar){
    case RDSend1:
      if(count<2){
        digitalWrite(A1, LOW);
        if(TimerFlag){
          count++;
        }
      }else{
        LD_Radar=RDSend2;
        count=0;
        digitalWrite(A1, HIGH);
      }
        break;
    case RDSend2:
        if(count<10){
          if(TimerFlag){
          count++;
          }
        }else{
        LD_Radar=RDRecieve;
        digitalWrite(A1, LOW);
        count=0;
        }
      break;
    case RDRecieve:
      LD_Radar=RDSend1;
      break;
    default:
      LD_Radar=RDSend1;
}
switch (LD_Radar){
    case RDSend1:
    break;
    case RDSend2:
    break;
    case RDRecieve:
      // Measure the duration of the pulse from the echoPin
      duration = pulseIn(A0, HIGH);

      // Calculate the distance in centimeters
      distance = (duration * 0.0343) / 2;

      // Print the distance to the Serial Monitor
      //Serial.print("Distance: ");
      //Serial.print(distance);
      //Serial.println(" cm");

      // Convert distance to integer to ignore decimals
      dist = int(distance);
      break;
    default:
      Serial.println("ERROR IN RADAR EX");
}

}
//////////////////////////////////////////////
//THIS STATE MACHINE HANDLES THE TONES OF THE RANGE BUZZER, INCREASIING IN FREQUENCY AND RATE AS OBJECT GETS CLOSER
//////////////////////////////////////////////
void TickFct_TneControl() {
    //Transition
    switch (LD_Tone){
    case Tfr:
        if(dist>far){
          LD_Tone=Tzero;
          noTone(2);
        }else if(dist<mid){
          LD_Tone=Tmid;
          noTone(2);
        }
        break;
    case Tmid:
        if(dist>mid){
          LD_Tone=Tfr;
        }else if(dist<cls){
          LD_Tone=Tcls;
          tone(2,3000);
        }
        break;
    case Tcls:
        if(dist>cls){
          LD_Tone=Tmid;
          noTone(2);
        }
        break;
    case Tzero:
        if(dist<far){
          LD_Tone=Tfr;
          //Serial.println("Trnsition to Tfr");
        }
        break;

    default:
        LD_Tone = Tzero;
        Serial.print("ERROR");
    }
    //ACTION
    switch (LD_Tone) {
    case Tfr:
      if(tncnt<1){
        tone(2,1000);
      }else if(tncnt>500){
        noTone(2);
      }
        break;
    case Tmid:
        if(tncnt<1){
        tone(2,1500);
      }else if(tncnt==250){
        noTone(2);
      }else if(tncnt==500){
        tone(2,1500);
      }else if(tncnt==750){
        noTone(2);
      }
        break;
    case Tcls:
        //ALREADY FULL
        break;
    case Tzero:
        
        break;

    default:
        LD_Tone = Tzero;
        Serial.print("ERROR");
    }
}
//////////////////////////////////////////////
//THIS STATE MACHINE HANDLES THE 7-SEG Display
//////////////////////////////////////////////
void TickFct_RfsControl() {
    switch (LD_Refresh) {
    case Rtns: 
        LD_Refresh=Rhns;
        break;
    case Rhns:
        LD_Refresh=Rthns;
        break;
    case Rthns:
        LD_Refresh=Rtms;
        break;
    case Rtms:
        LD_Refresh=Rtns;
        break;
    default:
        LD_Refresh=Rhns;
        Serial.print("ERROR");
    }
    switch (LD_Refresh) {
    case Rtns:
        displayDigit(dist%10, 3);
        break;
    case Rhns:
        displayDigit((dist/10)%10, 4);
        break;
    case Rthns:
        displayDigit((dist/100)%10, 5);
        break;
    case Rtms:
        displayDigit(dist/1000%10, 6);
        break;
    default:
        LD_Refresh=Rhns;
        Serial.print("ERROR");
    }
}
void displayDigit(int number, int digitPin) {
  // Initialize segment pins as outputs
  for (int i = 3; i < 7; i++) {
    digitalWrite(i, HIGH);
  }
  for (int i = 7; i < 14; i++) {
    digitalWrite(i, LOW);
  }

  digitalWrite(digitPin, LOW);

  // Determine which segments to turn on based on the input number
  switch (number) {
    case 0:
      digitalWrite(7, HIGH);
      digitalWrite(8, HIGH);
      digitalWrite(9, HIGH);
      digitalWrite(10, HIGH);
      digitalWrite(11, HIGH);
      digitalWrite(12, HIGH);
      digitalWrite(13, LOW);
      break;

    case 1:
      digitalWrite(8, HIGH);
      digitalWrite(9, HIGH);
      break;

    case 2:
      digitalWrite(7, HIGH);
      digitalWrite(8, HIGH);
      digitalWrite(10, HIGH);
      digitalWrite(11, HIGH);
      digitalWrite(13, HIGH);
      break;

    case 3:
      digitalWrite(7, HIGH);
      digitalWrite(8, HIGH);
      digitalWrite(9, HIGH);
      digitalWrite(10, HIGH);
      digitalWrite(13, HIGH);
      break;

    case 4:
      digitalWrite(8, HIGH);
      digitalWrite(9, HIGH);
      digitalWrite(12, HIGH);
      digitalWrite(13, HIGH);
      break;

    case 5:
      digitalWrite(7, HIGH);
      digitalWrite(9, HIGH);
      digitalWrite(10, HIGH);
      digitalWrite(12, HIGH);
      digitalWrite(13, HIGH);
      break;

    case 6:
      digitalWrite(7, HIGH);
      digitalWrite(9, HIGH);
      digitalWrite(10, HIGH);
      digitalWrite(11, HIGH);
      digitalWrite(12, HIGH);
      digitalWrite(13, HIGH);
      break;

    case 7:
      digitalWrite(7, HIGH);
      digitalWrite(8, HIGH);
      digitalWrite(9, HIGH);
      digitalWrite(12, HIGH);
      break;

    case 8:
      digitalWrite(7, HIGH);
      digitalWrite(8, HIGH);
      digitalWrite(9, HIGH);
      digitalWrite(10, HIGH);
      digitalWrite(11, HIGH);
      digitalWrite(12, HIGH);
      digitalWrite(13, HIGH);
      break;

    case 9:
      digitalWrite(7, HIGH);
      digitalWrite(8, HIGH);
      digitalWrite(9, HIGH);
      digitalWrite(10, HIGH);
      digitalWrite(12, HIGH);
      digitalWrite(13, HIGH);
      break;

    default:
      // Display blank
      break;
  }
}
void setup() {
  Serial.begin(9600);
  // PINMODE
  for (int i = 1; i < 14; i++) {
    pinMode(i, OUTPUT);
  }
  for (int i = 7; i < 14; i++) {
    digitalWrite(i, HIGH);
  }
  for (int i = 3; i < 7; i++) {
    digitalWrite(i, HIGH);
  }

  pinMode(trigPin, OUTPUT);

  //searchTone.begin(A2);
  //lockTone.begin(2);
  digitalWrite(A1, LOW);
  TimerSet(1);
  TimerOn();
  tone(2,2000);
}
//////////////////////////////////////////////
//MAIN LOOP
//////////////////////////////////////////////
void loop() {
  //End constant Tone, free for range buzzer
  //---------------------------------------------------
  noTone(A2);

  //Count the number of seconds for the range buzzer
  if(TimerFlag){
    tncnt++;
    if(tncnt>1001){
      tncnt=0;
    }
    TimerFlag=false;
  }

  //RADAR SECTION  /////////////////////////////////////
  TickFct_RdrControl();
  //---------------------------------------------------
  //DEBUG SECTION
  //---------------------------------------------------
  //Serial.print("curr: ");

  // Debug statement to see the value of dist
  //Serial.print("dist: ");
  //Serial.println(dist);
  //////////////////////////////////////////////////////

  //////////////////////////////////////////////////////
  //DISPLAY
  //////////////////////////////////////////////////////
  TickFct_RfsControl();
  TickFct_TneControl();

  //Constant Tone.
  //----------------------------------
  tone(A2,500);
}
