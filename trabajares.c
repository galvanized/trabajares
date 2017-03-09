#pragma config(Motor,  port1,           mLB,           tmotorNone, openLoop)
#pragma config(Motor,  port2,           mRF,           tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port3,           mLF,           tmotorVex393_MC29, openLoop, encoderPort, None)
#pragma config(Motor,  port4,           mALB,          tmotorVex393_MC29, openLoop, reversed, encoderPort, None)
#pragma config(Motor,  port5,           mRB,           tmotorVex393_MC29, openLoop, reversed, encoderPort, None)
#pragma config(Motor,  port6,           mC,            tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port7,           mALT,          tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port8,           mART,          tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port9,           mARB,          tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port10,          mW,            tmotorVex393_HBridge, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//
/*
       Y+
 LB     ^    LF
  1     |     0
        |
 X-<----+----> X+  FRONT
        |
        |
 RB     v     RF
  2     Y-     3


    Platform Type: VEX 2.0 Cortex
    Natural Language PLTW


Shane Galvin 2017
MIT License
*/

// This code is for the VEX cortex platform
#pragma platform(VEX2)

// Select Download method as "competition"
#pragma competitionControl(Competition)

//Main competition background code...do not modify!
#include "Vex_Competition_Includes.c"

byte armUpPow = 127;
byte armDownPow = -128;
byte armNeutralPow = 0;

byte clawOpenPow = 127;
byte clawClosePow = -127;
byte clawNeutralPow = 0;

byte winchPow = 127;

byte axisScale(byte in){ // provides deadzone functionality
        byte threshold = 20; // deadzone
        if(abs(in)<threshold){
            return 0;
        }
        else{
        	return in;
        }
}

byte capSum(byte x, byte y, byte z){
    // add up three bytes, returning a byte
    // prevents overflows
    short sum = (short) x + (short) y + (short) z;

    if( sum > 127 ) sum = 127;
    else if( sum < -128 ) sum = -128;

    return (byte) sum;
}

void omniDrive(byte x, byte y, byte r){

    motor[mLF] = capSum(x, y, r);//short(x) + short(y) + short(r);
    motor[mLB] = capSum(x, -y, r);//short(x) + short(-y) + short(r);
    motor[mRF] = capSum(x, -y, -r);//short(x) + short(y) + short(-r);
    motor[mRB] = capSum(x, y, -r);//short(x) + short(-y) + short(-r);

}

void setArm(byte power){
    //Set arm power. Up is positive.
    motor[mALT] = power;
    motor[mALB] = power;
    motor[mART] = power;
    motor[mARB] = power;
}


void rcControl(){
    /* allow human control of the arm and pinchers
                            Control Setup

        left                                            right
        5U - Claw Open                      6U - Arm Up
        5D - Claw Close                     6D - Arm Down

        8U & 8D
        Winch Retract & Reverse
        (reverse only with ratchet up!)

    */
    omniDrive(axisScale(vexRT[Ch3]), axisScale(vexRT[Ch4]), axisScale(vexRT[Ch1]));

    if(vexRT[Btn6U]) setArm(armUpPow);
    else{
        if(vexRT[Btn6D]) setArm(armDownPow);
        else setArm(armNeutralPow);
    }

    if(vexRT[Btn5U]) motor[mC] = clawOpenPow;
    else{
        if(vexRT[Btn5D]) motor[mC] = clawClosePow;
        else motor[mC] = clawNeutralPow;
    }

    if(vexRT[Btn8U]) motor[mW] = winchPow;
    else{
        if(vexRT[Btn8D]) motor[mW] = -winchPow;
        else motor[mW] = 0;
    }

}

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the cortex has been powered on and    */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void pre_auton()
{
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
  // ..........................................................................
  // Insert user code here.
  // ..........................................................................

  // Remove this function call once you have "real" code.
  AutonomousCodePlaceholderForTesting();
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

  while(true)
	{
		delay(10);
		rcControl();
	}
}
