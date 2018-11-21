//www.elegoo.com
//2016.12.12


volatile boolean TurnDetected;  // need volatile for Interrupts
volatile boolean rotationdirection;  // CW or CCW rotation

const int PinCLK=2;   // Generating interrupts using CLK signal
const int PinDT=3;    // Reading DT signal
const int PinSW=4;    // Reading Push Button switch

int RotaryPosition=0;    // To store Stepper Motor Position

int PrevPosition;     // Previous Rotary position Value to check accuracy
int StepsToTake;      // How much to move Stepper


// Interrupt routine runs if CLK goes from HIGH to LOW
void isr ()  {
  delayMicroseconds(50);  // delay for Debouncing
  if (digitalRead(PinCLK))
    rotationdirection= digitalRead(PinDT);
  else
    rotationdirection= !digitalRead(PinDT);
  TurnDetected = true;
}

void setup ()  {

  Serial.begin(9600);
  
pinMode(PinCLK,INPUT);
pinMode(PinDT,INPUT);  
pinMode(PinSW,INPUT);
digitalWrite(PinSW, HIGH); // Pull-Up resistor for switch
attachInterrupt (0,isr,FALLING); // interrupt 0 always connected to pin 2 on Arduino UNO
}

void loop ()  {
  
  if (!(digitalRead(PinSW))) {   // check if button is pressed
    if (RotaryPosition == 0) {  // check if button was already pressed
    } else {
        Serial.println(RotaryPosition);
      }
    }

  // Runs if rotation was detected
  if (TurnDetected)  {
    PrevPosition = RotaryPosition; // Save previous position in variable
    if (rotationdirection) {
      RotaryPosition=RotaryPosition-1;
    } // decrase Position by 1
    else {
      RotaryPosition=RotaryPosition+1;
    } // increase Position by 1
    
    

    TurnDetected = false;  // do NOT repeat IF loop until new rotation detected

   
    
  }
}
