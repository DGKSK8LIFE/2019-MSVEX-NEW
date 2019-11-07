// To complete the VEXcode V5 Text project upgrade process, please follow the
// steps below.
// 
// 1. You can use the Robot Configuration window to recreate your V5 devices
//   - including any motors, sensors, 3-wire devices, and controllers.
// 
// 2. All previous code located in main.cpp has now been commented out. You
//   will need to migrate this code to the new "int main" structure created
//   below and keep in mind any new device names you may have set from the
//   Robot Configuration window. 
// 
// If you would like to go back to your original project, a complete backup
// of your original (pre-upgraded) project was created in a backup folder
// inside of this project's folder.

// ---- START VEXCODE CONFIGURED DEVICES ----
// ---- END VEXCODE CONFIGURED DEVICES ----

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
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

// define your global instances of motors and other devices here
controller Controller;
motor frontLeftMotor  (PORT10,  gearSetting::ratio18_1, false);
motor backLeftMotor   (PORT1,   gearSetting::ratio18_1, false);
motor frontRightMotor (PORT20,  gearSetting::ratio18_1, false);
motor backRightMotor  (PORT11,  gearSetting::ratio18_1, false);
motor ctaMotor        (PORT16,  gearSetting::ratio18_1, false);
motor intakeMotorOne  (PORT21,  gearSetting::ratio18_1, false);
motor intakeMotorTwo  (PORT22,  gearSetting::ratio18_1, false);



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
  ctaMotor.setRotation(0, rotationUnits::deg);
  
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

void usercontrol( void ) {
  // User control code here, inside the loop
  double straight;
  double rotate;
  bool isPullingBack = false;
  while (1) {

    // Drive Code (Split Arcade) //
    straight = Controller.Axis3.position();
    rotate = Controller.Axis1.position();

    frontLeftMotor  .spin(directionType::fwd, (straight - rotate), velocityUnits::pct);
    backLeftMotor   .spin(directionType::fwd, (straight - rotate), velocityUnits::pct);
    frontRightMotor .spin(directionType::fwd, (straight + rotate), velocityUnits::pct);
    backRightMotor  .spin(directionType::fwd, (straight + rotate), velocityUnits::pct);


    // Cube Tray Angler //
    if (Controller.ButtonR1.pressing()){ // Top Right Bumper (R1): Push Cube Tray Forward
      isPullingBack = false;
      while (1) {
        ctaMotor.spin(directionType::fwd, 50, velocityUnits::pct);
        if (ctaMotor.rotation(rotationUnits::deg) > 90){
          ctaMotor.stop(coast);
          break;
        }
      }
    } else if (Controller.ButtonR2.pressing()) { // Bottom Right Bumper (R2): Pull Cube Tray Back
      isPullingBack = true;
    }

    if (isPullingBack) { // Code to Pull Cube Tray Back
      if (ctaMotor.rotation(rotationUnits::deg) < 45) {
        ctaMotor.spin(directionType::rev, 50, velocityUnits::pct);
      } else {
        ctaMotor.stop();
      }
    }

    if (Controller.ButtonL1.pressing()){
      intakeMotorOne.spin(directionType::fwd, 100, velocityUnits::pct);
      intakeMotorTwo.spin(directionType::rev, 100, velocityUnits::pct);
    }
  }
}


//
// Main will set up the competition functions and callbacks.
//
int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  Competition.autonomous( autonomous );
  Competition.drivercontrol( usercontrol );
    
  //Run the pre-autonomous function.                         
  while(1) {
    vex::task::sleep(100);//Sleep the task for a short amount of time to prevent wasted resources.
  } 
}

        
