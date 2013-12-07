#include "WPILib.h"
#include "PIDJaguar.h"

#define PINCHEROPEN 6
#define PINCHERCLOSE 8
#define ARMUP 5
#define ARMDOWN 7
#define SLOW 1
#define TANKLEFT 2
#define TANKRIGHT 4
/**
 * This is a demo program showing the use of the RobotBase class.
 * The SimpleRobot class is the base of a robot application that will automatically call your
 * Autonomous and OperatorControl methods at the right time as controlled by the switches on
 * the driver station or the field controls.
 */ 
class RobotDemo : public SimpleRobot
{
	RobotDrive myRobot; // robot drive system
	Joystick stick; // only joystick
	Jaguar pincher;
	Jaguar arm;


public:
	RobotDemo(void):
		myRobot(1, 2),	// these must be initialized in the same order
		stick(1),		// as they are declared above.
		pincher(3),
		arm(4)

		
	{
		myRobot.SetExpiration(0.1);
	}

	/**
	 * Drive left & right motors for 2 seconds then stop
	 */
	void Autonomous(void)
	{
		myRobot.SetSafetyEnabled(false);
		myRobot.Drive(-0.5, 0.0); 	// drive forwards half speed
		Wait(2.0); 				//    for 2 seconds
		myRobot.Drive(0.0, 0.0); 	// stop robot
	}

	/**
	 * Runs the motors with arcade steering. 
	 */
	void OperatorControl(void)
	{
		float slow=1;

		myRobot.SetSafetyEnabled(true);
		while (IsOperatorControl() && IsEnabled())
		{
			myRobot.TankDrive(stick.GetRawAxis(TANKLEFT)/(2*slow),stick.GetRawAxis(TANKRIGHT)/(2*slow));
			if (stick.GetRawButton(PINCHEROPEN)==1) {
				pincher.Set(1.0/(2*slow));// drive with arcade style (use right stick)
			}
			else if (stick.GetRawButton(PINCHERCLOSE)==1) {
				pincher.Set(-1.0/(2*slow));// drive with arcade style (use right stick)
			}
			else {
				pincher.Set(0.0);
			}
			if (stick.GetRawButton(ARMUP)==1) {
				pincher.Set(1.0/(2*slow));// drive with arcade style (use right stick)
			}
			else if (stick.GetRawButton(ARMDOWN)==1) {
				pincher.Set((-1.0/(2*slow)));// drive with arcade style (use right stick)
			}
			else {
				pincher.Set(0.0);
			}
			bool last_slow=0;
			if (last_slow!=stick.GetRawButton(SLOW)) {
				if (last_slow==1) {
					slow=0.5;
				}
				else {
					slow=1;
				}
				last_slow=stick.GetRawButton(SLOW);
			}
				
		}

			Wait(0.005);				// wait for a motor update time
	}

	
	/**
	 * Runs during test mode
	 */
	void Test() {

	}
};

START_ROBOT_CLASS(RobotDemo);

