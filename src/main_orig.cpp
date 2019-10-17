#include "vex.h"

// controller, brain, and motor instances
vex::controller Controller;
vex::brain Brain;
vex::motor frontLeftMotor(vex::PORT10, vex::gearSetting::ratio18_1, false);
vex::motor backLeftMotor(vex::PORT1, vex::gearSetting::ratio18_1, false);
vex::motor frontRightMotor(vex::PORT20, vex::gearSetting::ratio18_1, false);
vex::motor backRightMotor(vex::PORT11, vex::gearSetting::ratio18_1, false);
vex::motor ctaMotor(vex::PORT16, vex::gearSetting::ratio18_1, false);
vex::motor intakeMotorOne(vex::PORT21, vex::gearSetting::ratio18_1, false);
vex::motor intakeMotorTwo(vex::PORT22, vex::gearSetting::ratio18_1, false);

int main(){
  double straight;
  double rotate;
  while(1){
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