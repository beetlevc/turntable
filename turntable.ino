// Include the AccelStepper library found here :
// https://github.com/waspinator/AccelStepper
#include <AccelStepper.h>
// Include the Bounce2 library found here :
// https://github.com/thomasfredericks/Bounce2
#include <Bounce2.h>

#define HALFSTEP 8

// Motor pin definitions
#define motorPin1  2     // IN1 on the ULN2003
#define motorPin2  3     // IN2 on the ULN2003
#define motorPin3  4     // IN3 on the ULN2003
#define motorPin4  5     // IN4 on the ULN2003
#define BUTTON_PIN_1 A0  // Step CW
#define BUTTON_PIN_2 A1  // Step CCW

// Initialize with pin sequence IN1-IN3-IN2-IN4 for using the AccelStepper with 28BYJ-48
AccelStepper stepper1(HALFSTEP, motorPin1, motorPin3, motorPin2, motorPin4);

double stepsPerDegree = 4078.0 * 2.0 / 360.0;

Bounce debouncer1 = Bounce(); 
Bounce debouncer2 = Bounce(); 

double deltaAngle = 5.0;
double currentAngle = 0.0;

void setup() {
  stepper1.setMaxSpeed(1000.0);
  stepper1.setAcceleration(100.0);
  stepper1.setSpeed(200);
  
  // Setup the first button with an internal pull-up :
  pinMode(BUTTON_PIN_1,INPUT_PULLUP);
  // After setting up the button, setup the Bounce instance :
  debouncer1.attach(BUTTON_PIN_1);
  debouncer1.interval(50); // interval in ms
  
   // Setup the second button with an internal pull-up :
  pinMode(BUTTON_PIN_2,INPUT_PULLUP);
  // After setting up the button, setup the Bounce instance :
  debouncer2.attach(BUTTON_PIN_2);
  debouncer2.interval(50); // interval in ms
}

void loop() {
  // Update the Bounce instances :
  debouncer1.update();
  debouncer2.update();

  if ( debouncer1.fell() ) {
    currentAngle -= deltaAngle;
  } 
  if ( debouncer2.fell() ) {
    currentAngle += deltaAngle;
  } 
  stepper1.moveTo(currentAngle * stepsPerDegree);

  stepper1.run();
}


