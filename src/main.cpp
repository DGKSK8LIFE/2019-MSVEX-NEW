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

// define your global instances of motors and other devices here
controller Controller;
motor frontLeftMotor   (PORT12,  gearSetting::ratio18_1, false);
motor backLeftMotor    (PORT11,   gearSetting::ratio18_1, false);
motor frontRightMotor  (PORT10,  gearSetting::ratio18_1, false);
motor backRightMotor   (PORT9,   gearSetting::ratio18_1, false);
motor ctaMotor         (PORT16,  gearSetting::ratio18_1, false);
motor intakeMotorLeft  (PORT13,  gearSetting::ratio18_1, false);
motor intakeMotorRight (PORT8,   gearSetting::ratio18_1, false);



/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the cortex has been powered on and    */ 
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void pre_auton( void ) {
  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...               
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void autonomous( void ) {
  // ..........................................................................
  // Insert autonomous user code here.
  // ..........................................................................

}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/
bool trayUp = false;
void setTray(bool up) {
  trayUp = up;
  const int ang = (up) ? -315 : 0;
  ctaMotor.rotateTo(ang, rotationUnits::deg, 50, velocityUnits::pct, false);
}
void toggleTray() {
  setTray(!trayUp);
}

void usercontrol() {
  while (true) {
    Controller.ButtonL2.pressed(toggleTray);

    // Drive Code (Split Arcade) //
    double straight = Controller.Axis3.position();
    double rotate = Controller.Axis1.position();

    frontLeftMotor  .spin(directionType::fwd, (straight + rotate), velocityUnits::pct);
    backLeftMotor   .spin(directionType::fwd, (straight + rotate), velocityUnits::pct);
    frontRightMotor .spin(directionType::fwd, (straight - rotate), velocityUnits::pct);
    backRightMotor  .spin(directionType::fwd, (straight - rotate), velocityUnits::pct);


    if (Controller.ButtonL1.pressing()) {
      intakeMotorLeft.spin(directionType::fwd, 100, velocityUnits::pct);
    } else {
      intakeMotorLeft.stop(brakeType::coast);
    }
    if (Controller.ButtonL1.pressing()) {
      intakeMotorRight.spin(directionType::fwd, 100, velocityUnits::pct);
    } else {
      intakeMotorRight.stop(brakeType::coast);
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
    
    //Run the pre-autonomous function. 
    pre_auton();
       
    //Prevent main from exiting with an infinite loop.                        
    while(1) {
      vex::task::sleep(20);//Sleep the task for a short amount of time to prevent wasted resources.
    }    
}