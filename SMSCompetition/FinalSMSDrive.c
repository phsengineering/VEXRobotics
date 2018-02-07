#pragma config(Sensor, in1,    clawPotentiometer, sensorPotentiometer)
#pragma config(Sensor, dgtl12,  solenoid,       sensorDigitalOut)
#pragma config(Sensor, dgtl9,  leftEncoder,    sensorQuadEncoder)
#pragma config(Sensor, dgtl11, rightEncoder,   sensorQuadEncoder)
#pragma config(Motor,  port2,           DriveLeft_1,   tmotorServoContinuousRotation, openLoop)
#pragma config(Motor,  port3,           DriveLeft_2,   tmotorServoContinuousRotation, openLoop)
#pragma config(Motor,  port4,           DriveRight_1,  tmotorServoContinuousRotation, openLoop, reversed)
#pragma config(Motor,  port5,           DriveRight_2,  tmotorServoContinuousRotation, openLoop, reversed)
#pragma config(Motor,  port6,           leftArm,       tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port7,           armAngle,      tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port8,           rightArm,      tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port9,           clawMotor,     tmotorVex393TurboSpeed_MC29, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#pragma competitionControl(Competition)
#pragma autonomousDuration(20)
#pragma userControlDuration(120)
#include "Vex_Competition_Includes.c"   //Main competition background code...do not modify
#pragma platform(VEX2)
void pre_auton()
{
	SensorValue[rightEncoder] = 0;
	SensorValue[leftEncoder] = 0;
	SensorValue[solenoid] = 0;
	//hack(nsa);
}
task resetEverything() { //this is a subroutine that will reset the motors and encoders in one go
	motor[DriveLeft_1] = 0;
	motor[DriveLeft_2] = 0;
	motor[DriveRight_1] = 0;
	motor[DriveRight_2] = 0;
	SensorValue[rightEncoder] = 0;
	SensorValue[leftEncoder] = 0;
}


task autonomous() {
	startTask(resetEverything); //startmotorby resetting all of the motors/sensors
	SensorValue[solenoid] = 0; //reset the pneumatics controller
	motor[armAngle] = 127;
	wait1Msec(500);
	motor[armAngle] = 0;
	startTask(resetEverything);

		motor[DriveLeft_1] = 100; //move at half speed
		motor[DriveLeft_2] = 100;
		motor[DriveRight_1] = 100;
		motor[DriveRight_2] = 100;
	wait1Msec(3000);
	startTask(resetEverything);
	SensorValue[solenoid] = 1; //when the robot has reached the mobile goal, bring the pneumatics pistons up
	wait1Msec(1000); //wait 1 second

}

#define     JOY_DRIVE_V     vexJSLeftV
#define     JOY_DRIVE_H     vexJSLeftH
#define     JOY_THRESHOLD   15

#define MOTOR_NUM               kNumbOfTotalMotors
#define MOTOR_MAX_VALUE         127
#define MOTOR_MIN_VALUE         (-127)
#define MOTOR_DEFAULT_SLEW_RATE 10      // Default will cause 375mS from full fwd to rev
#define MOTOR_FAST_SLEW_RATE    256     // essentially off
#define MOTOR_TASK_DELAY        15      // task 1/frequency in mS (about 66Hz)
#define MOTOR_DEADBAND          10

// Array to hold requested speed for the motors
int motorReq[ MOTOR_NUM ];

// Array to hold "slew rate" for the motors, the maximum change every time the task
// runs checking current motor speed.
int motorSlew[ MOTOR_NUM ];


task MotorSlewRateTask()
{
	unsigned int motorIndex;
	int motorTmp;

	// Initialize crap
	for(motorIndex=0;motorIndex<MOTOR_NUM;motorIndex++)
	{
		motorReq[motorIndex] = 0;
		motorSlew[motorIndex] = MOTOR_DEFAULT_SLEW_RATE;
	}

	// run task until stopped
	while( true )
	{
		// run loop for every motor
		for( motorIndex=0; motorIndex<MOTOR_NUM; motorIndex++)
		{
			// So we don't keep accessing the internal storage
			motorTmp = motor[ motorIndex ];

			// Do we need to change the motor value ?
			if( motorTmp != motorReq[motorIndex] )
			{
				// increasing motor value
				if( motorReq[motorIndex] > motorTmp )
				{
					motorTmp += motorSlew[motorIndex];
					// limit
					if( motorTmp > motorReq[motorIndex] )
						motorTmp = motorReq[motorIndex];
				}

				// decreasing motor value
				if( motorReq[motorIndex] < motorTmp )
				{
					motorTmp -= motorSlew[motorIndex];
					// limit
					if( motorTmp < motorReq[motorIndex] )
						motorTmp = motorReq[motorIndex];
				}

				// finally set motor
				motor[motorIndex] = motorTmp;
			}
		}

		// Wait approx the speed of motor update over the spi bus
		wait1Msec( MOTOR_TASK_DELAY );
	}
}


void
DriveLeftMotor( int value )
{
	motorReq[ DriveLeft_1 ] = value;
	motorReq[ DriveLeft_2 ] = value;
}


void
DriveRightMotor( int value )
{
	motorReq[ DriveRight_1 ] = value;
	motorReq[ DriveRight_2 ] = value;
}


task ArcadeDrive()
{
	int    ctl_v;
	int    ctl_h;
	int    drive_l;
	int    drive_r;

	// Basic arcade control
	while( true )
	{
		// Get joystick H and V control
		ctl_v = vexRT[ Ch2 ];
		ctl_h = vexRT[ Ch3 ];

		// Ignore joystick near center
		if( (abs(ctl_v) <= JOY_THRESHOLD) && (abs(ctl_h) <= JOY_THRESHOLD) )
		{
			drive_l = 0;
			drive_r = 0;
		}
		else
		{
			// Create drive for left and right motors
			drive_l = (ctl_v + ctl_h) / 2;
			drive_r = (ctl_v - ctl_h) / 2;
		}

		// send out to motors
		DriveLeftMotor( drive_l );
		DriveRightMotor( drive_r );

		// Cortex is no bueno
		wait1Msec( 25 );
	}
}
task liftControl() {
	while(true) {
		motor[leftArm] = vexRT[Ch2]; //get input from the right side controller joystick and assign it to the left side arm
		motor[rightArm] = vexRT[Ch2];
		if(vexRT[Btn7L] == 1) {
			motor[armAngle] = 63;
		}
		else {
			motor[armAngle] = 0;
		}
		if(vexRT[Btn5U] == 1) { //if the left shoulder button is enabled
			motor[clawMotor] = -63;
		}
		else if (vexRT[Btn5D] == 1){
			motor[clawMotor] = 63;
	}
	}

	//	else if (vexRT[Btn5U] == 0) {
	//	while(SensorValue(clawPotentiometer) >= 100) {
	//	motor[clawMotor] = -63;
	//}
	//	}
}

task usercontrol()
{
	SensorValue(clawPotentiometer) = 0;
	// Start motor slew rate control
	// startTask(MotorSlewRateTask);

	// Start driver control tasks
	startTask(ArcadeDrive);

	// Start driver lift control
	//startTask(liftControl);

	// Everything done in other tasks
	while( true )
	{
		SensorValue[solenoid] = vexRT[Btn6U]; //pneumatics systems here
		wait1Msec( 100 );
	}
}
