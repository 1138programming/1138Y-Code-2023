#include "main.h"
#include "Base.h"
#include "constants.h"

/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */

//Variables
int BaseSpeed;
int BaseTurning;
int IntakeSpeed = 60;

//creates right and left motor groups

// creates drivebase object
Base robotBase(new pros::Motor_Group({KLeftFrontWheelPort,KLeftMidWheelPort,KLeftBackWheelPort}),
	new pros::Motor_Group({KRightFrontWheelPort,KRightMidWheelPort,KRightBackWheelPort}));
pros::Motor intakeMotor(KIntakePort);

//Controller
pros::Controller master (CONTROLLER_MASTER);

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol() {
	
	while (true) {
		//sets speed and turning for base
		BaseSpeed = (master.get_analog(ANALOG_LEFT_Y));
		BaseTurning = (master.get_analog(ANALOG_RIGHT_X));

		robotBase.splitArcadeDrive(BaseSpeed, BaseTurning);
        
		//intake forwards and backwards
		if (master.get_digital(DIGITAL_R2)) {
			intakeMotor.move(IntakeSpeed);
		}
		else if (master.get_digital(DIGITAL_R1)) {
			intakeMotor.move(-IntakeSpeed);
		}
		//stops motors when button is not pressed
		else {
			intakeMotor.move(0);
		}
	}
}
