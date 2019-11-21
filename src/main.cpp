
// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// frontLeft            motor         20              
// frontRight           motor         11              
// backLeft             motor         10              
// backRight            motor         2               
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

using namespace vex;
competition Competition;

void autonomous() {}

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
      vertArmMotor.spin(directionType::fwd, 100, velocityUnits::pct);
    } else if (Controller1.ButtonR1.pressing()){
      vertArmMotor.spin(directionType::rev, 100, velocityUnits::pct);
    } else {
      vertArmMotor.stop(brakeType::hold);
    }

    if (Controller1.ButtonL2.pressing()){
      clawMotor.spin(directionType::rev, 100, velocityUnits::pct);
    } else if (Controller1.ButtonL1.pressing()) {
      clawMotor.spin(directionType::fwd, 100, velocityUnits::pct);
    } else {
      clawMotor.stop(brakeType::hold);
    }
  }
}


//
// Main will set up the competition functions and callbacks.
//
int main(){
    //Set up callbacks for autonomous and driver control periods.
    Competition.autonomous( autonomous );
    Competition.drivercontrol( usercontrol );

    //Prevent main from exiting with an infinite loop.                        
    while(1) {
      vex::task::sleep(20);//Sleep the task for a short amount of time to prevent wasted resources.
    }
}