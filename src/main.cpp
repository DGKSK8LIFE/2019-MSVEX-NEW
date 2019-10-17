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
vex::competition Competition;

// define your global instances of motors and other devices here
vex::controller Controller;
vex::brain Brain;
vex::motor frontLeftMotor(vex::PORT10, vex::gearSetting::ratio18_1, false);
vex::motor backLeftMotor(vex::PORT1, vex::gearSetting::ratio18_1, false);
vex::motor frontRightMotor(vex::PORT20, vex::gearSetting::ratio18_1, false);
vex::motor backRightMotor(vex::PORT11, vex::gearSetting::ratio18_1, false);
vex::motor ctaMotor(vex::PORT16, vex::gearSetting::ratio18_1, false);
vex::motor intakeMotorOne(vex::PORT21, vex::gearSetting::ratio18_1, false);
vex::motor intakeMotorTwo(vex::PORT22, vex::gearSetting::ratio18_1, false);



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

void usercontrol( void ) {
  // User control code here, inside the loop
  double straight;
  double rotate;
  while (1) {
    // This is the main execution loop for the user control program.
    // Each time through the loop your program should update motor + servo 
    // values based on feedback from the joysticks.

    straight = Controller.Axis3.position();
    rotate = Controller.Axis1.position();

    frontLeftMotor.spin(vex::directionType::fwd, (straight-rotate), vex::velocityUnits::pct);
    backLeftMotor.spin(vex::directionType::fwd, (straight-rotate), vex::velocityUnits::pct);
    frontRightMotor.spin(vex::directionType::fwd, (straight + rotate), vex::velocityUnits::pct);
    backRightMotor.spin(vex::directionType::fwd, (straight+rotate), vex::velocityUnits::pct);
  
    if (Controller.ButtonR1.pressing()){
      ctaMotor.spin(vex::directionType::fwd, 25, vex::velocityUnits::pct);
    } else if (Controller.ButtonR2.pressing()) {
      ctaMotor.spin(vex::directionType::rev, 25, vex::velocityUnits::pct);
    }

    if (Controller.ButtonL1.pressing()){
      intakeMotorOne.spin(vex::directionType::rev, 50, vex::velocityUnits::pct);
      intakeMotorTwo.spin(vex::directionType::rev, 50, vex::velocityUnits::pct);
    }
  }
}

//
// Main will set up the competition functions and callbacks.
//
int main() {
    //Set up callbacks for autonomous and driver control periods.
    Competition.autonomous( autonomous );
    Competition.drivercontrol( usercontrol );
    
    //Run the pre-autonomous function. 
    pre_auton();
       
    //Prevent main from exiting with an infinite loop.                        
    while(1) {
      vex::task::sleep(100);//Sleep the task for a short amount of time to prevent wasted resources.
    }    
       
}