#pragma config(I2C_Usage, I2C1, i2cSensors)
#pragma config(Sensor, in1,    mogoTrack,      sensorPotentiometer)
#pragma config(Sensor, dgtl1,  mogoLimit,      sensorTouch)
#pragma config(Sensor, I2C_1,  rightEncoder,   sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Sensor, I2C_2,  leftEncoder,    sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Motor,  port2,           mogoLift,      tmotorServoContinuousRotation, openLoop)
#pragma config(Motor,  port3,           clawMotor,     tmotorServoContinuousRotation, openLoop)
#pragma config(Motor,  port4,           liftMotor,     tmotorServoContinuousRotation, openLoop)
#pragma config(Motor,  port5,           internalStack, tmotorServoContinuousRotation, openLoop)
#pragma config(Motor,  port6,           DriveRight_1,  tmotorServoContinuousRotation, openLoop)
#pragma config(Motor,  port7,           DriveRight_2,  tmotorServoContinuousRotation, openLoop)
#pragma config(Motor,  port8,           DriveLeft_1,   tmotorServoContinuousRotation, openLoop, reversed)
#pragma config(Motor,  port9,           DriveLeft_2,   tmotorServoContinuousRotation, openLoop, reversed)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#pragma competitionControl(Competition)
#pragma autonomousDuration(20)
#pragma userControlDuration(120)
#include "Vex_Competition_Includes.c"   //Main competition background code...do not modify
#pragma platform(VEX2)
void pre_auton()
{
	//SensorValue[rightEncoder] = 0;
	//SensorValue[leftEncoder] = 0;
}
task fullspeed() {

  motor[DriveLeft_1] = 127;
  motor[DriveLeft_2] = 127;
  motor[DriveRight_1] = 127;
  motor[DriveRight_2] = 127;
}
task stopmotors() {

  motor[DriveLeft_1] = 0;
  motor[DriveLeft_2] = 0;
  motor[DriveRight_1] = 0;
  motor[DriveRight_2] = 0;
}
task autonomous() {
motor[mogoLift] = -63;
wait(1);
motor[mogoLift] = 0;
 startTask(fullspeed);
 wait(3);
 startTask(stopmotors);
}

#define     JOY_DRIVE_V     vexJSLeftV
#define     JOY_DRIVE_H     vexJSLeftH
#define     JOY_THRESHOLD   15

#define MOTOR_NUM               kNumbOfTotalMotors
#define MOTOR_MAX_VALUE         127
#define MOTOR_MIN_VALUE         (-127)
#define MOTOR_DEFAULT_SLEW_RATE 10      // Default will cause 375mS from full fwd to rev
#define MOTOR_FAST_SLEW_RATE    256     // essentially off
#define MOTOR_TASK_DELAY        16      // task 1/frequency in mS (about 66Hz)
#define MOTOR_DEADBAND          11
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
DriveLeftMotor( int value ) //send filtered integer values to cortex motors
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
		ctl_v = vexRT[ JOY_DRIVE_V ];
		ctl_h = vexRT[ JOY_DRIVE_H ];

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
task mogoLiftControl() {
	motor[mogoLift] = -vexRT[Ch2];
	while(SensorValue[mogoLimit] == 1) {
		wait(1);
		motor[mogoLift] = 127;
		wait(2);
		motor[mogoLift] = -vexRT[Ch2];
	}
}
task usercontrol()
{

	//SensorValue(clawPotentiometer) = 0;
	// Start motor slew rate control
	startTask(MotorSlewRateTask);
motor[clawMotor] = 63;
	// Start driver control tasks
	startTask(ArcadeDrive);

	// Everything done in other t\\asks
	while( true )
	{
		wait1Msec( 100 );

		//motor[mogoLift] = -vexRT[Ch2];
		startTask(mogoLiftControl);
		motor[internalStack] = vexRT[Ch2Xmtr2]; //run the two lift system motors off of channel 2 input
		motor[liftMotor] = vexRT[Ch3Xmtr2]; //run the other two lift system motors off of channel 3 input
	}
}
