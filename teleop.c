#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTServo,  none)
#pragma config(Sensor, S2,     gyro,           sensorI2CHiTechnicGyro)
#pragma config(Sensor, S3,     ir,             sensorHiTechnicIRSeeker1200)
#pragma config(Sensor, S4,     sonar,          sensorSONAR)
#pragma config(Motor,  mtr_S1_C1_1,     left1,         tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     left2,         tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_1,     right1,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_2,     right2,        tmotorTetrix, openLoop)
#pragma config(Servo,  srvo_S1_C3_1,    hook,               tServoStandard)
#pragma config(Servo,  srvo_S1_C3_2,    servo2,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_3,    servo3,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_6,    servo6,               tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "JoystickDriver.c"

int targetRight = 0,
		actualRight = 0,
		targetLeft = 0,
		actualLeft = 0;

void init()
{
	bDisplayDiagnostics = false;

	servo[hook] = 135;

	return;
}

void setDriveMotors(int left, int right)
{
	targetLeft = left;
	targetRight = right;
}

void stopDriveMotors()
{
	targetLeft = 0;
	targetRight = 0;
	actualLeft = 0;
	actualRight = 0;
}

task motorManagement()
{
	while (true)
	{
		if (actualLeft < targetLeft)
		{
			actualLeft++;
		}
		else if (actualLeft > targetLeft)
		{
			actualLeft--;
		}

		if (actualRight < targetRight)
		{
			actualRight++;
		}
		else if (actualRight > targetRight)
		{
			actualRight--;
		}
		motor[left1] = actualLeft;
		motor[left2] = actualLeft;
		motor[right1] = actualRight;
		motor[right2] = actualRight;
		wait1Msec(25);
	}
}

task main()
{
	init();

	waitForStart();

	startTask(motorManagement);

	int joy1 = 0, joy2 = 0;

	while (true)
	{
		getJoystickSettings(joystick);

		joy1 = joystick.joy1_y1 * 0.75;
		joy2 = joystick.joy1_x2 * 0.75;

		nxtDisplayTextLine(1, "%d", joy1);
		nxtDisplayTextLine(2, "%d", joy2);

		if (abs(joy1) > 10)
		{
			setDriveMotors(joy1, joy1);
		}
		else if (abs(joy2) > 10)
		{
			setDriveMotors(joy2, -joy2);
		}
		else
		{
			stopDriveMotors();
		}
	}
}
