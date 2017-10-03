#pragma config(Sensor, in6,    xAccel,         sensorAccelerometer)
#pragma config(Motor,  port1,           LeftMotor,     tmotorVex393_HBridge, openLoop)
#pragma config(Motor,  port10,          RightMotor,    tmotorVex393_HBridge, openLoop, reversed)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/*----------------------------------------------------------------------------------------------------*\
|*                                 - Wait for Acceleration ADVANCED -                                 *|
|*                                      ROBOTC on VEX 2.0 CORTEX                                      *|
|*                                                                                                    *|
|*  This program instructs the robot to wait until the Accelerometer senses a change in the           *|
|*  forward acceleration of the robot, and then move forward for one second. This program             *|
|*  takes in an initial reading of the sensor, and compares all of its values to the inital           *|
|*  reading. This helps to eliminate bias in the sensor readings. There is a two second wait          *|
|*  at the beginning of the program.                                                                  *|
|*                                                                                                    *|
|*                                        ROBOT CONFIGURATION                                         *|
|*    NOTES:                                                                                          *|
|*    1)  Reversing 'rightMotor' (port 2) in the "Motors and Sensors Setup" is needed with the        *|
|*        "Squarebot" mode, but may not be needed for all robot configurations.                       *|
|*                                                                                                    *|
|*    MOTORS & SENSORS:                                                                               *|
|*    [I/O Port]          [Name]              [Type]                [Description]                     *|
|*    Motor Port 2        rightMotor          VEX 3-wire module     Right side motor                  *|
|*    Motor Port 3        leftMotor           VEX 3-wire module     Left side motor                   *|
|*    Analog Port 6       xAccel              VEX Accelerometer     x-axis acceleration               *|
\*----------------------------------------------------------------------------------------------------*/


//+++++++++++++++++++++++++++++++++++++++++++++| MAIN |+++++++++++++++++++++++++++++++++++++++++++++++
task main()
{
	wait1Msec(2000);						// Robot waits for 2000 milliseconds before executing program

	int currentX;                         // Variable to calculate the current reading of the sensor, allows them to be viewed in the debugger
  int threshold = 3;                    // Variable to help cancel noise
	int xBias = abs(SensorValue[xAccel]); // Variable to store the inital readings of the sensors
  int waitTime = 25;                    // Variable to help cancel value jumping

	// Using a do-while loop has the calculation run at least once before checking values
	do
	{
	  currentX = abs(SensorValue[xAccel]) - xBias; // Take a reading and subtract out the bias, store this value as current reading
	  wait1Msec(waitTime);                         // Small wait statement to eliminate irregular sensor values
	}
	while(currentX < threshold); // Loop while the Accelerometer senses no or very little acceleration in the forward direction

	motor[rightMotor] = 127;		  // Motor on port2 is run at full (127) power forward
	motor[leftMotor]  = 127;		  // Motor on port3 is run at full (127) power forward
	wait1Msec(90000);       // Robot runs previous code for 1000 milliseconds before moving on
}												        // Program ends, and the robot stops

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
