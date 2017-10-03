#pragma config(UART_Usage, UART2, uartVEXLCD, baudRate19200, IOPins, None, None)
#pragma config(I2C_Usage, I2C1, i2cSensors)
#pragma config(Sensor, dgtl2,  NoSensor,       sensorDigitalOut)
#pragma config(Sensor, dgtl7,  BackEN,         sensorQuadEncoder)
#pragma config(Sensor, dgtl9,  LeftClaw,       sensorDigitalOut)
#pragma config(Sensor, dgtl10, RightClaw,      sensorDigitalOut)
#pragma config(Sensor, dgtl11, RightEN,        sensorQuadEncoder)
#pragma config(Sensor, I2C_1,  FrontEN,        sensorQuadEncoderOnI2CPort,    , AutoAssign)
#pragma config(Sensor, I2C_2,  RightLiftEN,    sensorQuadEncoderOnI2CPort,    , AutoAssign)
#pragma config(Sensor, I2C_3,  BackEN,         sensorNone)
#pragma config(Motor,  port2,           LeftMotor,     tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port3,           RightMotor,    tmotorVex393_MC29, openLoop, reversed, encoderPort, dgtl11)
#pragma config(Motor,  port4,           BackMotor,     tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port5,           FrontMotor,    tmotorVex393_MC29, openLoop, reversed, encoderPort, I2C_1)
#pragma config(Motor,  port6,           Lift1,         tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port7,           Lift2,         tmotorVex393_MC29, openLoop, reversed, encoderPort, I2C_2)
#pragma config(Motor,  port8,           Lift1b,        tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port9,           Lift2b,        tmotorVex393_MC29, openLoop, reversed)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//                          !!*//

/*
Code Chooser
ROBOTC on VEX 2.0 Cortex

This program uses the Display functions of ROBOTC on the VEX 2.0 Cortex platform.
It allows the user to choose from 4 different pieces of code using the left and right buttons
on the VEX LCD. Once the center button is pressed, the code corresponding with the choice is run.
This code can be adapted for competition based settings - just place the code for the first
switch case in the pre_auton function, and the code for the second switch in the autonomous task.
Replace the basic movement behaviors in the second switch with your own autonomous routines.

ROBOT CONFIGURATION
MOTORS &amp; SENSORS:
[I/O Port]                    [Name]                            [Type]                                [Description]
UART Port 2                    none                                VEX LCD                                VEX LCD Screen
Motor Port 2                rightMotor                    VEX 3-wire module            Right side motor
Motor Port 3                leftMotor                        VEX 3-wire module            Left side motor
*/

const short leftButton = 1;
const short centerButton = 2;
const short rightButton = 4;


bool LeftPiston = true;
bool RightPiston = true;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void LinearMovement()
{
//Linear movement code : Forward, Left, Right, and Back with left stick
		motor(LeftMotor)=-vexRT[Ch3];
		motor(RightMotor)=-vexRT[Ch3];
		motor(FrontMotor)=vexRT[Ch4];
		motor(BackMotor)=vexRT[Ch4];
}


void Rotation()
{
//Rotation movement code: When 6D is pressed, move right joystick left and right to rotate left and right
	while(vexRT[Btn6D]==1)
	{
		motor(LeftMotor)=-vexRT[Ch1];
		motor(RightMotor)=vexRT[Ch1];
		motor(FrontMotor)=vexRT[Ch1];
		motor(BackMotor)=-vexRT[Ch1];

	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void LiftControl()
{

//Lift control: use buttons 5D and 5U to move up and down////Lift max: 8100
	if(vexRT[Btn5U]==1)
	{
		if(SensorValue[FrontEN]<8150 || vexRT[Btn7U]==1)
		{
			motor(Lift1)=127;
			motor(Lift2)=127;
			motor(Lift1b)=127;
			motor(Lift2b)=127;
		}
		else
		{
			motor(Lift1)=0;
			motor(Lift2)=0;
			motor(Lift1b)=0;
			motor(Lift2b)=0;
		}
	}
	else if(vexRT[Btn5D]==1)
	{
		if(SensorValue[FrontEN]>-5 || vexRT[Btn7D]==1)
		{
			motor(Lift1)=-127;
			motor(Lift2)=-127;
			motor(Lift1b)=-127;
			motor(Lift2b)=-127;
		}
		else
		{
			motor(Lift1)=0;
			motor(Lift2)=0;
			motor(Lift1b)=0;
			motor(Lift2b)=0;
		}
	}
	else
	{
		motor(Lift1)=0;
		motor(Lift2)=0;
		motor(Lift1b)=0;
		motor(Lift2b)=0;
	}
}
////////////////////////////////////////////////////////////////////////////////////////////////
void SkyrisePickup()
{
//skyrise pickup height
//Button that lifts to skyrise pickup height,
if(vexRT(Btn6U) == 1)
{
	while(SensorValue(FrontEN) < 1000 && (vexRT(Btn8D) == 0))
	{
		motor(Lift1) = 127;
		motor(Lift2) = 127;
		motor(Lift1b)=127;
		motor(Lift2b)=127;
		LinearMovement();
		Rotation();
	//	PistonClaws();
	}
	while(SensorValue(FrontEN) > 1000 && (vexRT(Btn8D) == 0))
	{
		motor(Lift1) = -127;
		motor(Lift2) = -127;
		motor(Lift1b)=-127;
		motor(Lift2b)=-127;
		LinearMovement();
		Rotation();
//		PistonClaws();
	}
}
}
//////////////////////////////////////////////////////////////////////////////////////////////////
void PistonClaws()
{
	SensorValue[LeftClaw]=1;
	if (vexRT[Btn7L]==1)
	{
	LeftPiston = true;
	}
	if (vexRT[Btn7R]==1)
	{
	LeftPiston = false;
	}
	if (LeftPiston)
	{
	SensorValue[LeftClaw]=1;
	}
	else
	{
	SensorValue[LeftClaw]=0;
	LeftPiston = false;
	}

	SensorValue[RightClaw]=1;
	if (vexRT[Btn8L]==1)
	{
	RightPiston = true;
	}
	if (vexRT[Btn8R]==1)
	{
	RightPiston = false;
	}
	if (RightPiston)
	{
	SensorValue[RightClaw]=1;
	}
	else
	{
	SensorValue[RightClaw]=0;
	RightPiston = false;
	}

}












//Wait for Press--------------------------------------------------
void waitForPress()
{
while(nLCDButtons == 0){}
wait1Msec(5);
}
//----------------------------------------------------------------

//Wait for Release------------------------------------------------
void waitForRelease()
{
while(nLCDButtons != 0){}
wait1Msec(5);
}
//----------------------------------------------------------------





task main()
{
//Declare count variable to keep track of our choice
int count = 0;

//------------- Beginning of User Interface Code ---------------
//Clear LCD
clearLCDLine(0);
clearLCDLine(1);
//Loop while center button is not pressed
while(nLCDButtons != centerButton)
{
//Switch case that allows the user to choose from 4 different options
switch(count)
{

case 0:
//Display first choice
displayLCDCenteredString(0, "Autonomous 1");
displayLCDCenteredString(1, "<         Enter        >");
waitForPress();
//Increment or decrement "count" based on button press
if(nLCDButtons == leftButton)
{
waitForRelease();
count = 3;
}
else if(nLCDButtons == rightButton)
{
waitForRelease();
count++;
}
break;




case 1:
//Display second choice
displayLCDCenteredString(0, "Autonomous 2");
displayLCDCenteredString(1, "<         Enter        >");
waitForPress();
//Increment or decrement "count" based on button press
if(nLCDButtons == leftButton)
{
waitForRelease();
count--;
}
else if(nLCDButtons == rightButton)
{
waitForRelease();
count++;
}
break;



case 2:
//Display third choice
displayLCDCenteredString(0, "Drive Away");
displayLCDCenteredString(1, "<         Enter        >");
waitForPress();
//Increment or decrement "count" based on button press
if(nLCDButtons == leftButton)
{
waitForRelease();
count--;
}
else if(nLCDButtons == rightButton)
{
waitForRelease();
count++;
}
break;



case 3:
//Display fourth choice
displayLCDCenteredString(0, "Driver Control");
displayLCDCenteredString(1, "<         Enter        >");
waitForPress();
//Increment or decrement "count" based on button press
if(nLCDButtons == leftButton)
{
waitForRelease();
count--;
}
else if(nLCDButtons == rightButton)
{
waitForRelease();
count = 0;
}
break;
default:
count = 0;
break;
}
}
//------------- End of User Interface Code ---------------------

//------------- Beginning of Robot Movement Code ---------------
//Clear LCD
clearLCDLine(0);
clearLCDLine(1);
//Switch Case that actually runs the user choice
switch(count){






case 0:
//If count = 0, run the code correspoinding with choice 1
displayLCDCenteredString(0, "Autonnomous 1");
displayLCDCenteredString(1, "is running!");
wait1Msec(2000);                        // Robot waits for 2000 milliseconds

// Move forward at full power for 3 seconds
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////// run blue cube and skyrise auton/////////////////////////////
		SensorValue[FrontEN]=0;
		SensorValue[RightLiftEN]=0;
		SensorValue[RightEN]=0;

		//Put the cube in the nub
		while(SensorValue[RightEN] > -45)
		{
			motor(RightMotor) = 127;
			motor(LeftMotor) = 127;
		}
			motor(RightMotor) = 0;
			motor(LeftMotor) = 0;
			wait1Msec(100);

		/*motor(LeftMotor)=-127;
		motor(RightMotor)=-127;
		wait1Msec(285);
		motor(LeftMotor)=0;
		motor(RightMotor)=0;
		wait1Msec(100);
		*/

		//skyrise auton

//Open Claws
		SensorValue[LeftClaw]=1;
		SensorValue[RightClaw]=1;
		wait1Msec(100);


		//Lift to skyrise pull altitude
		while(SensorValue[FrontEN]>1000)
		{
			motor(Lift1)=127;
			motor(Lift2)=127;
			motor(Lift1b)=127;
			motor(Lift2b)=127;
		}
		motor(Lift1)=0;
		motor(Lift2)=0;
		motor(Lift1b)=0;
		motor(Lift2b)=0;

		//move and grab skyrise
		motor(FrontMotor)=80;
		motor(BackMotor)=80;
		wait1Msec(585);
		motor(FrontMotor)=0;
		motor(BackMotor)=0;
		wait1Msec(100);

		//Lift up to higher altitude with the skyrise
		motor(Lift1)=127;
		motor(Lift2)=127;
		motor(Lift1b)=127;
		motor(Lift2b)=127;
		wait1Msec(2300);
		motor(Lift1)=0;
		motor(Lift2)=0;
		motor(Lift1b)=0;
		motor(Lift2b)=0;
		wait1Msec(100);

		//Backup to orginial spot
		motor(FrontMotor)=127;
		motor(BackMotor)=127;
		wait1Msec(508);
		motor(FrontMotor)=0;
		motor(BackMotor)=0;
		wait1Msec(100);


		//Rotate to align with skyrise nub
		while(SensorValue[RightEN] < 128)
			{
			motor(LeftMotor)=-127;
			motor(RightMotor)=127;
			motor(FrontMotor)=127;
			motor(BackMotor)=-127;
			}
			motor(LeftMotor)=0;
			motor(RightMotor)=0;
			motor(FrontMotor)=0;
			motor(BackMotor)=0;


		/*motor(LeftMotor)=-127;
		motor(RightMotor)=127;
		motor(FrontMotor)=127;
		motor(BackMotor)=-127;
		wait1Msec(367);
		motor(LeftMotor)=0;
		motor(RightMotor)=0;
		motor(FrontMotor)=0;
		motor(BackMotor)=0;
		wait1Msec(100);
		*/


		//Move torwards to skyrise nub
		motor(FrontMotor)=-127;
		motor(BackMotor)=-127;
		wait1Msec(175);
		motor(FrontMotor)=0;
		motor(BackMotor)=0;
		wait1Msec(100);

 /* //slight right movement
		motor(FrontMotor)=100;
		motor(BackMotor)=100;
		wait1Msec(175);
		motor(FrontMotor)=0;
		motor(BackMotor)=0;
		wait1Msec(100);
*/
		//put the skyrise back
		while(SensorValue[FrontEN]<-355)
		{
			motor(Lift1)=-127;
			motor(Lift2)=-127;
			motor(Lift1b)=-127;
			motor(Lift2b)=-127;
		}
		motor(Lift1)=0;
		motor(Lift2)=0;
		motor(Lift1b)=0;
		motor(Lift2b)=0;
		wait1Msec(240);

		//wiggle


		//Move away from skyrise
		motor(FrontMotor)=127;
		motor(BackMotor)=127;
		wait1Msec(650);
		motor(FrontMotor)=0;
		motor(BackMotor)=0;
		wait1Msec(100);

		//go down all the way
		while(SensorValue[FrontEN]<5)
		{
			motor(Lift1)=-127;
			motor(Lift2)=-127;
			motor(Lift1b)=-127;
			motor(Lift2b)=-127;
		}
		motor(Lift1)=0;
		motor(Lift2)=0;
		motor(Lift1b)=0;
		motor(Lift2b)=0;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
break;









case 1:
//If count = 1, run the code correspoinding with choice 2
displayLCDCenteredString(0, "Autonomous 2");
displayLCDCenteredString(1, "is running!");


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// run red cube and skyrise auton
			/////////// run red cube and skyrise auton/////////////////////////////////////////////////////////////////////
		SensorValue[FrontEN]=0;
		SensorValue[RightLiftEN]=0;
		SensorValue[RightEN]=0;

//Put the cube in the nub
		while(SensorValue[RightEN] > -45)
		{
			motor(RightMotor) = -127;
			motor(LeftMotor) = -127;
		}
			motor(RightMotor) = 0;
			motor(LeftMotor) = 0;

		//skyrise auton
		//shake the manipulator fold off
		motor(FrontMotor)=127;
		motor(BackMotor)=127;
		wait1Msec(150);
		motor(FrontMotor)=-127;
		motor(BackMotor)=-127;
		wait1Msec(150);
		motor(FrontMotor)=0;
		motor(BackMotor)=0;
		wait1Msec(100);

		//Lift to skyrise pull altitude
		while(SensorValue[FrontEN]>-2200)
		{
			motor(Lift1)=127;
			motor(Lift2)=127;
			motor(Lift1b)=127;
			motor(Lift2b)=127;
		}
		motor(Lift1)=0;
		motor(Lift2)=0;
		motor(Lift1b)=0;
		motor(Lift2b)=0;

		//move and grab skyrise
		motor(FrontMotor)=75;
		motor(BackMotor)=75;
		wait1Msec(525);
		motor(FrontMotor)=0;
		motor(BackMotor)=0;
		wait1Msec(100);

		//Lift up to higher altitude with the skyrise
		motor(Lift1)=127;
		motor(Lift2)=127;
		motor(Lift1b)=127;
		motor(Lift2b)=127;
		wait1Msec(2300);
		motor(Lift1)=0;
		motor(Lift2)=0;
		motor(Lift1b)=0;
		motor(Lift2b)=0;
		wait1Msec(100);

		//Backup to orginial spot
		motor(FrontMotor)=-127;
		motor(BackMotor)=-127;
		wait1Msec(469);
		motor(FrontMotor)=0;
		motor(BackMotor)=0;
		wait1Msec(100);

		//Rotate to align with skyrise nub
	while(SensorValue[RightEN] > -279)
		{
		motor(LeftMotor)=127;
		motor(RightMotor)=-127;
		motor(FrontMotor)=-127;
		motor(BackMotor)=127;
		}
		motor(LeftMotor)=0;
		motor(RightMotor)=0;
		motor(FrontMotor)=0;
		motor(BackMotor)=0;
		wait1Msec(100);

		//Move torwards to skyrise
		motor(FrontMotor)=127;
		motor(BackMotor)=127;
		wait1Msec(187);
		motor(FrontMotor)=0;
		motor(BackMotor)=0;
		wait1Msec(100);

		//Slight movement backwards
		motor(FrontMotor)=-127;
		motor(BackMotor)=-127;
		wait1Msec(160);
		motor(FrontMotor)=0;
		motor(BackMotor)=0;
		wait1Msec(100);

		//put the skyrise back
		while(SensorValue[FrontEN]<-392)
		{
			motor(Lift1)=-127;
			motor(Lift2)=-127;
			motor(Lift1b)=-127;
			motor(Lift2b)=-127;
		}
		motor(Lift1)=0;
		motor(Lift2)=0;
		motor(Lift1b)=0;
			motor(Lift2b)=0;
		wait1Msec(240);

		//Move away from skyrise
		motor(FrontMotor)=-127;
		motor(BackMotor)=-127;
		wait1Msec(650);
		motor(FrontMotor)=0;
		motor(BackMotor)=0;
		wait1Msec(100);

		//go down all the way
		while(SensorValue[FrontEN]<5)
		{
				motor(Lift1)=-127;
			motor(Lift2)=-127;
			motor(Lift1b)=-127;
			motor(Lift2b)=-127;
		}
		motor(Lift1)=0;
		motor(Lift2)=0;
		motor(Lift1b)=0;
			motor(Lift2b)=0;

wait1Msec(2000);                        // Robot waits for 2000 milliseconds

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
break;














case 2:
//If count = 2, run the code correspoinding with choice 3
displayLCDCenteredString(0, "Drive Away");
displayLCDCenteredString(1, "is running!");


//Turn right for 3seconds
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//run away from cube
		motor(LeftMotor) = -127;
		motor(RightMotor) = -127;
		wait1Msec(2000);
		motor(LeftMotor) = 0;
		motor(RightMotor) = 0;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
wait1Msec(3000);                            // Robot runs previous code for 3000 milliseconds before moving on
break;

















case 3:
//If count = 2, run the code correspoinding with choice 3
displayLCDCenteredString(0, "Driver Control");
displayLCDCenteredString(1, "is running!");
wait1Msec(2000);                        // Robot waits for 2000 milliseconds


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


SensorValue[RightEN]=0;
SensorValue[BackEN]=0;
SensorValue[FrontEN]=0;
SensorValue[RightLiftEN]=0;

while(vexRT[Btn8D]==0)///////////////while loop/////////////////////////
{

		LinearMovement();
		Rotation();
		LiftControl();
		SkyrisePickup();
		PistonClaws();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
break;





















///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
wait1Msec(3000);                            // Robot runs previous code for 3000 milliseconds before moving on
break;
default:
displayLCDCenteredString(0, "Nothing");
displayLCDCenteredString(1, "is running");
break;
}
//------------- End of Robot Movement Code -----------------------
}
