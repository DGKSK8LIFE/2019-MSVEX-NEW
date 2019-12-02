// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// frontLeft            motor         20              
// frontRight           motor         11              
// backLeft             motor         10              
// backRight            motor         4               
// vertArmMotor         motor         1               
// clawMotor            motor         3               
// ---- END VEXCODE CONFIGURED DEVICES ----

/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\AwtyCAD2                                         */
/*    Created:      Thu Oct 17 2019                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/
#include "vex.h"

#define PI 3.14159265358979323846
#define REVS_PER_DEGREES 0.02
const float wheel_diameter = 3;

using namespace vex;
competition Competition;

float revsPerDegrees (float degrees){
  return degrees * REVS_PER_DEGREES;
}
float revsPerInches(float wheelDiameter, float inches) {
  return inches / (wheelDiameter * PI);
}
void setSpeed(int speed) {
  frontLeft.setVelocity(speed, velocityUnits::pct);
  frontRight.setVelocity(speed, velocityUnits::pct);
  backLeft.setVelocity(speed, velocityUnits::pct);
  backRight.setVelocity(speed, velocityUnits::pct);
}
void driveInches(float inches) {
  const float revs = revsPerInches(wheel_diameter, inches);
  frontLeft.rotateFor(revs, rotationUnits::rev, false);
  frontRight.rotateFor(revs, rotationUnits::rev, false);
  backLeft.rotateFor(revs, rotationUnits::rev, false);
  backRight.rotateFor(revs, rotationUnits::rev);
}
void rotateDegrees(int degrees) {
  const float revs = revsPerDegrees(degrees);
  frontLeft.rotateFor(revs, rotationUnits::rev, false);
  frontRight.rotateFor(revs, rotationUnits::rev, false);
  backLeft.rotateFor(-revs, rotationUnits::rev, false);
  backRight.rotateFor(-revs, rotationUnits::rev);
}

void pre_auton() {
  clawMotor.spin(directionType::rev, 100, velocityUnits::pct);
}

void autonomous() {
  setSpeed(100);
  driveInches(12);
}

void usercontrol(void){
  // loop
  while (1) {
    double thrust = Controller1.Axis3.position();
    double rotate = Controller1.Axis1.position();
    frontRight.spin(directionType::fwd, thrust - rotate, velocityUnits::pct);
    backLeft.spin(directionType::fwd, thrust + rotate, velocityUnits::pct);
    frontLeft.spin(directionType::fwd, thrust + rotate, velocityUnits::pct);
    backRight.spin(directionType::fwd, thrust - rotate, velocityUnits::pct);

    if (Controller1.ButtonR2.pressing()) {
      clawMotor.spin(directionType::fwd, 100, velocityUnits::pct);
    } else if (Controller1.ButtonR1.pressing()){
      clawMotor.spin(directionType::rev, 100, velocityUnits::pct);
    } else {
      clawMotor.stop(brakeType::hold);
    }

    if (Controller1.ButtonL2.pressing()){
      vertArmMotor.spin(directionType::rev, 50, velocityUnits::pct);
    } else if (Controller1.ButtonL1.pressing()) {
      vertArmMotor.spin(directionType::fwd, 50, velocityUnits::pct);
    } else {
      vertArmMotor.stop(brakeType::hold);
    }
  }
}


//
// Main will set up the competition functions and callbacks.
//
int main(){
    // pre_auton 
    pre_auton();
    //Set up callbacks for autonomous and driver control periods.
    Competition.autonomous( autonomous );
    Competition.drivercontrol( usercontrol );

    //Prevent main from exiting with an infinite loop.                        
    while(1) {
      vex::task::sleep(20);//Sleep the task for a short amount of time to prevent wasted resources.
    }
}