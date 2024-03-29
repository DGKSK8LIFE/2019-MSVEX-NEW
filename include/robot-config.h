using namespace vex;

extern brain Brain;

// VEXcode devices
extern controller Controller1;
extern motor frontLeft;
extern motor frontRight;
extern motor backLeft;
extern motor backRight;
extern motor vertArmLeftMotor;
extern motor clawMotor;
extern motor vertArmRightMotor;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Text.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );