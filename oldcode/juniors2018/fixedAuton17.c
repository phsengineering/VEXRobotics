#pragma config(Sensor, in1,    Gyro,           sensorNone)
#pragma config(Sensor, in2,    potentiometer,  sensorPotentiometer)
#pragma config(Sensor, in3,    p,              sensorPotentiometer)
#pragma config(Sensor, in4,    h,              sensorLineFollower)
#pragma config(Sensor, in5,    g,              sensorReflection)
#pragma config(Sensor, dgtl1,  Jumper1,        sensorDigitalIn)
#pragma config(Sensor, dgtl2,  Jumper2,        sensorDigitalIn)
#pragma config(Sensor, dgtl3,  Jumper3,        sensorDigitalIn)
#pragma config(Sensor, dgtl4,  Jumper4,        sensorDigitalIn)
#pragma config(Sensor, dgtl5,  Jumper5,        sensorDigitalIn)
#pragma config(Sensor, dgtl6,  Quad,           sensorQuadEncoder)
#pragma config(Sensor, dgtl8,  mobileGoal,     sensorDigitalOut)
#pragma config(Sensor, dgtl9,  mobileGoal2,    sensorDigitalOut)
#pragma config(Sensor, dgtl10, Quad2,          sensorQuadEncoder)
#pragma config(Motor,  port2,           leftside,      tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port3,           rightside,     tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port4,           fly,           tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port5,           top,           tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port6,           bottom,        tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port7,           mobile,        tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port8,           mobilegoal,    tmotorVex393_MC29, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*        Description: Competition template for VEX EDR                      */
/*                                                                           */
/*---------------------------------------------------------------------------*/

// This code is for the VEX cortex platform
#pragma platform(VEX2)

// Select Download method as "competition"
#pragma competitionControl(Competition)

//Main competition background code...do not modify!
#include "Vex_Competition_Includes.c"

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the cortex has been powered on and    */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/



int four;
/*task Quadreset()
{
SensorValue[Quad]=0;
SensorValue[Quad2]=0;
} */
void pre_auton()
{
sensorValue(potentiometer)=0;
// Set bStopTasksBetweenModes to false if you want to keep user created tasks
	// running between Autonomous and Driver controlled modes. You will need to
	// manage all user created tasks if set to false.
	bStopTasksBetweenModes = true;

	// Set bDisplayCompetitionStatusOnLcd to false if you don't want the LCD
	// used by the competition include file, for example, you might want
	// to display your team name on the LCD in this function.
	// bDisplayCompetitionStatusOnLcd = false;

	// All activities that occur before the competition starts
	// Example: clearing encoders, setting servo positions, ...
}
task Quadreset()
{
	SensorValue[Quad]=0;
	SensorValue[Quad2]=0;
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

task autonomous()
{
	/*	if(SensorValue[Jumper1]==0) //run if jumper in port 1
	{
	startTask(Quadreset);
	motor(top)=127; //put lift up
	motor(bottom)=127;
	wait(1);//change
	motor(top)=0;
	motor(bottom)=0;
	while(SensorValue[Quad] < 573 || SensorValue[Quad2] < 573)
	{
	motor(leftside)=127; //drive to stationary
	motor(rightside)=127;
	}
	motor(leftside)=0;
	motor(rightside)=0;
	startTask(Quadreset);

	motor(fly)=127; //drop cone
	wait(.5);
	motor(fly)=0;
	while(SensorValue[Quad] > -218 || SensorValue[Quad2] > -218)
	{
	motor(leftside)=-127; //back up
	motor(rightside)=-127;
	}
	/* motor(top)=-127;
	motor(bottom)=-127;
	wait(1); //change
	motor(top)=0;
	motor(bottom)=0;
	startTask(Quadreset);
	while( SensorValue[Quad] > -240 || SensorValue[Quad2] < 240)
	{
	motor(rightside)=127; //turn tomards mobile
	}
	startTask(Quadreset);
	while(SensorValue[Quad] < 1905 || SensorValue[Quad2] > 1905)
	{
	motor(leftside)=127; //drive to mobile
	}
	startTask(Quadreset);
	motor(leftside)=0;
	motor(rightside)=0;

	SensorValue[mobileGoal]=1; //pick up mobile
	SensorValue[mobileGoal2]=1;
	while(SensorValue[Quad] > -1905 || SensorValue[Quad2] > -1905)
	{
	motor(leftside)=-127; //back up with mobile
	motor(rightside)=-127;
	}
	startTask(Quadreset);
	while( SensorValue[Quad] > -480 || SensorValue[Quad2] < 480)
	{
	motor(rightside)=127; // complete turn towards drop zone
	}
	startTask(Quadreset);
	while(SensorValue[Quad] < 60 || SensorValue[Quad2] < 60)
	{
	motor(leftside)=127; //drive to zone
	}
	startTask(Quadreset);
	motor(leftside)=0;
	motor(rightside)=0;

	SensorValue[mobileGoal]=0; // drop off mobile
	SensorValue[mobileGoal2]=0;
	while(SensorValue[Quad] > -60 || SensorValue[Quad2] > -60)
	{
	motor(leftside)=-127; //back up
	motor(rightside)=-127;
	}
	startTask(Quadreset);
	motor(leftside)=0;
	motor(rightside)=0;
	}
	if(SensorValue[Jumper2]==0) //run if jumper in port 2
	{
	startTask(Quadreset);
	motor(top)=127; //put lift up
	motor(bottom)=127;
	wait(1);//change
	motor(top)=0;
	motor(bottom)=0;

	while( SensorValue[Quad] < 573 || SensorValue[Quad2] < 573)
	{
	motor(leftside)=127; //drive to stationary
	motor(rightside)=127;
	}

	motor(leftside)=0;
	motor(rightside)=0;
	startTask(Quadreset);

	motor(fly)=-127; //drop cone
	wait(.5);
	motor(fly)=0;
	while(SensorValue[Quad] > -218 || SensorValue[Quad2] > -218)
	{
	motor(leftside)=-127; //back up
	motor(rightside)=-127;
	}
	startTask(Quadreset);
	/*	motor(top)=-127;
	motor(bottom)=-127;
	wait(1); //change
	motor(top)=0;
	motor(bottom)=0;

	while(SensorValue[Quad] > 240 || SensorValue[Quad2] < -240)
	{
	motor(leftside)=127;//turn towards mobile
	}
	startTask(Quadreset);
	while(SensorValue[Quad] < 1905 || SensorValue[Quad2] < 1905)
	{
	motor(leftside)=127; //drive to mobile
	}
	startTask(Quadreset);
	motor(leftside)=0;
	motor(rightside)=0;

	SensorValue[mobileGoal]=1; //pick up mobile
	SensorValue[mobileGoal2]=1;
	while(SensorValue[Quad] > -1905 || SensorValue[Quad2] > -1905)
	{
	motor(leftside)=-127; //back up with mobile
	motor(rightside)=-127;
	}
	startTask(Quadreset);
	while(SensorValue[Quad] > -480 || SensorValue[Quad2] < 480)
	{
	motor(leftside)=127; //finish turn towards drop offmzone
	}
	startTask(Quadreset);
	while(SensorValue[Quad] < 60 || SensorValue[Quad2] < 60)
	{
	motor(rightside)=127; //drive to drop off zone
	}
	startTask(Quadreset);
	motor(leftside)=0;
	motor(rightside)=0;

	SensorValue[mobileGoal]=0; //drop off mobile
	SensorValue[mobileGoal2]=0;
	while( SensorValue[Quad] < -60 || SensorValue [Quad2] < -60)
	{
	motor(leftside)=-127; //back up
	motor(rightside)=-127;
	}
	startTask(Quadreset);
	motor(leftside)=0;
	motor(rightside)=0;
	}
	*/
	motor(top)=127; //put lift up
	motor(bottom)=-127;
	wait(2);//change
	motor(top)=0;
	motor(bottom)=0;
	wait(1);
	motor(top)=50;
	motor(bottom)=-50;
	motor(leftside)=70;
	motor(rightside)=70;
	wait(1.2);
	motor(leftside)=-10;
	motor(rightside)=-10;
	wait(.5);
	motor(fly)=-127;
	wait(1);
	motor(fly)=0;
	motor(leftside)=-63;
	motor(rightside)=-63;
	wait(.75);
	motor(leftside)=0;
	motor(rightside)=0;
	motor(top)=0;
	motor(bottom)=0;


	//}
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

task usercontrol()
{
	// User control code here, inside the loop


	four=1;
	while(1==1)
	{

		motor[rightside] = vexRT[Ch2];
		motor[leftside] = vexRT[Ch3];
		if(vexRT[Btn5UXmtr2]==1)
		{
			motor[fly]=127;
		}

		else if(vexRT[Btn5DXmtr2]==1)
		{
			motor[fly]=-127;

		}
		else
		{
			motor[fly]=0;
		}

		if(vexRT[Btn6UXmtr2]==1)
		{
			motor(top)=127;
			motor(bottom)=-127;
		}

		else if(vexRT[Btn6DXmtr2]==1)
		{
			motor(top)=-127;
			motor(bottom)=127;
		}
		else
		{
			motor(top)=0;
			motor(bottom)=0;
		}

		//Rhea is my best friend :)
		//elephants are great & Dan is a butt
		//zezak I don't know how to code
		//MobileGoalDown
		/*	if(vexRT[Btn7D]==1)
		{
		SensorValue[mobileGoal]=0;
		SensorValue[mobileGoal2]=0;

		}
		//MobileGoalUp
		if(vexRT[Btn7U]==1)
		{
		SensorValue[mobileGoal]=1;
		SensorValue[mobileGoal2]=1;
		}
		*/	if(vexRT[Btn8D]==1)
		{
			if(four==1)
			{
				motor(mobile)=127;
			wait(.7)
				motor(mobile)=0;
				four=0;
			}
			else if(four==0)
			{
				motor(mobile)=-127;
				wait(.5)
				motor(mobile)=0;
				four=1;
			}
			else
			{
				motor(mobile)=0;
			}
	}	}
	if(vexRT[Btn8R]==1)
	{

		motor(top)=127; //put lift up
		motor(bottom)=127;
		wait(1.2);//change
		motor(top)=50;
		motor(bottom)=50;
		motor(leftside)=127;
		motor(rightside)=127;
		wait(1);
		motor(leftside)=0;
		motor(rightside)=0;
		motor(fly)=-127;
		wait(1);
		motor(fly)=0;

	}
}
