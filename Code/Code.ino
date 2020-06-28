#include <Stepper.h>

#define STEPS 200 //as the stepper charctaristics


Stepper stepper(STEPS, 6, 7, 8, 9);

const int button = 4; 
const int potmeter = A0; 
 
void setup()
{
  pinMode(button, INPUT_PULLUP);
} 

int Direc = 1, Speed = 0;
 
void loop()
{
  if ( digitalRead(button) == 0 )  
    if ( debounce() )  
    {
      Direc*= -1;  // reverse direction variable
      while ( debounce() ) ;  // wait for button release
    }
 
  // read analog value from the potentiometer
  int val = analogRead(potmeter);
 
  if ( Speed!= map(val, 0, 1023, 5, 100) ) // map digital value
  {
    Speed = map(val, 0, 1023, 5, 100);
    stepper.setSpeed(Speed);
  }
  stepper.step(Direc);
}
 
// debounce
bool debounce()
{
  byte count = 0;
  for(byte i = 0; i < 5; i++) {
    if (digitalRead(button) == 0)
      count++;
    delay(10);
  }
  if(count > 2)  return 1;
  else           return 0;
}
