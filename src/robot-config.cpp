#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
controller Controller1 = controller(primary);
motor frontLeft = motor(PORT20, ratio18_1, false);
motor frontRight = motor(PORT11, ratio18_1, true);
motor backLeft = motor(PORT10, ratio18_1, false);
motor backRight = motor(PORT4, ratio18_1, true);
motor vertArmLeftMotor = motor(PORT1, ratio18_1, true);
motor clawMotor = motor(PORT3, ratio18_1, false);
motor vertArmRightMotor = motor(PORT5, ratio18_1, false);

// VEXcode generated functions



/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Text.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}