///
/// @file       mouse_operation.c
/// @author     Kyeong Soo (Joseph) Kim <k.s.kim@swansea.ac.uk>
/// @date       2012-02-21
///
/// @brief      Implements functions for mouse operation modes.
///
/// @remarks    This program is based on Dr Tim Davies' assembly version of
///             micro mouse program and the C port of it by Mr Gareth Evans.
///
/// @copyright  Copyright (C) 2012 Swansea University. All rights reserved.
///
/// @copyright  This software is written and distributed under the GNU General
///             Public License Version 2 (http://www.gnu.org/licenses/gpl-2.0.html).
///             You must not remove this notice, or any other, from this software.
///


#include "mouse.h"	// for the declaration of types, constants, variables and function

void AvoidObstacle()
{
    void TouchBar();
    mouseMode = MOUSE_MODE_OBSTACLE_AVOIDING;

    for (;;) {
        // first move forward
        

        
            if (infraredFrontLeft && infraredFrontRight) {
                // both touched; reverse
            ControlMouse(MOUSE_ACTION_STOP);
            Delay(100);
            ControlMouse(MOUSE_ACTION_REVERSE);
            Delay(180);
            ControlMouse(MOUSE_ACTION_TURNAROUND);
            Delay(180);
            //TouchBar();
            }
            else if (infraredFrontLeft && !infraredFrontRight) {
                // left sensor detects; avoid left obstacle
            ControlMouse(MOUSE_ACTION_STOP);
            Delay(100);
            ControlMouse(MOUSE_ACTION_REVERSE);
            Delay(180);
            ControlMouse(MOUSE_ACTION_TURNRIGHT);
            Delay(180);
            //TouchBar();

            }
            else if (!infraredFrontLeft && infraredFrontRight) {
                // right sensor detects; avoid right obstacle
            ControlMouse(MOUSE_ACTION_STOP);
            Delay(100);
            ControlMouse(MOUSE_ACTION_REVERSE);
            Delay(180);
            ControlMouse(MOUSE_ACTION_TURNLEFT);
            Delay(180);
            //TouchBar();

            } 
         
        else {  
        ControlMouse(MOUSE_ACTION_FORWARD);
        //TouchBar();
        }   

    } 
// end of for() loop
}
/*void TouchBar(){
  
         if (touchBarFrontLeft && !touchBarFrontRight) {
            // left bar is touched; avoid left obstacle
            ControlMouse(MOUSE_ACTION_STOP);
            Delay(100);
            ControlMouse(MOUSE_ACTION_REVERSE);
            Delay(180);
            ControlMouse(MOUSE_ACTION_TURNRIGHT);
            Delay(180);
        }
        else if (!touchBarFrontLeft && touchBarFrontRight) {
            // right bar is touched; avoid right obstacle
            ControlMouse(MOUSE_ACTION_STOP);
            Delay(100);
            ControlMouse(MOUSE_ACTION_REVERSE);
            Delay(180);
            ControlMouse(MOUSE_ACTION_TURNLEFT);
            Delay(180);
        }
        else if (touchBarFrontLeft && touchBarFrontRight) {
            // both bars are touched; avoid front obstacle
            ControlMouse(MOUSE_ACTION_STOP);
            Delay(100);
            ControlMouse(MOUSE_ACTION_REVERSE);
            Delay(180);
            ControlMouse(MOUSE_ACTION_TURNAROUND);
            Delay(180);
        }// 180 dgree turn  
        else {
        ControlMouse(MOUSE_ACTION_FORWARD);
        }  
}
  */
void LineFollowing ()
{
    mouseMode = MOUSE_MODE_OBSTACLE_AVOIDING;

    for (;;) {
    ADC1SC1 = 0;		/*PTD0/AD0 for ADC*/
	while(ADC1SC1_COCO == 0){     //test coco bit
	}
	
	if( ADC1RL > THRESH0){
        ControlMouse(MOUSE_ACTION_TURNRIGHT);
        Delay(10);
        } 
        else if (ADC)  
        {
        ControlMouse(MOUSE_ACTION_TURNLEFT);
        Delay(10);
        }

        else {
            ControlMouse(MOUSE_ACTION_FORWARD);	// 180 dgree turn
        }
    } // end of for() loop
}


void Combat()
{
    // fill your code here for the combat mode    
}


// debug mode with simple command-line interface
void Debug()
{
    byte command;

    // display a welcome message with a list of commands
    SCISendNewLine();
    SCISendStr("Welcome to the debug mode of EG-252 sample micromouse programme!\r\n");
    SCISendNewLine();
    SCISendNewLine();
    SCISendStr("List of available commands:\r\n");
    SCISendStr("F\tForward\r\n");
    SCISendStr("R\tReverse\r\n");
    SCISendStr("S\tStop\r\n");
    SCISendStr("A\troate Anticlockwise\r\n");
    SCISendStr("C\trotate Clockwise\r\n");
    SCISendStr("V\tVeer left Clockwise\r\n");
    SCISendStr("B\tVeer right Clockwise\r\n");
    SCISendStr("+\tIncrement speed by 256 units\r\n");
    SCISendStr("-\tDecrement speed by 256 units\r\n");
    SCISendStr("D\tDisplay ADC value 7 through 0\r\n");
    SCISendStr("P\tDisplay PTA as binary number\r\n");

  while (1) {
        // display prompt and wait for a user input
        SCIDisplayPrompt();
        command = SCIGetChar();
        
        // TEST
        SCIDisplayBitString(command);
        SCIDisplayBitString((char)'F');
        SCIDisplayBitString((byte)'R');
        SCIDisplayBitString('S');
        if ((int)command == 70)
        {
            SCISendStr("Forward ... \r\n");
        }
        if ((command & 0b01111111) == 0x52)
        {
            SCISendStr("Reverse ... \r\n");
        }
        if ((int)command > 256) 
        {
            SCISendStr("Greater than 256\r\n");
        }
        else if ((int)command > 128) 
        {
            SCISendStr("Greater than 128\r\n");
        }
        else if ((int)command > 64)
        {
            SCISendStr("Greater than 64\r\n");
        }
        else
        {
            SCISendStr("Less than or eqal to 64\r\n");
        }
        // TEST

        switch(command) {
            case 70:  // ascii code for 'F'
                SCISendStr("Forward ... \r\n");
                break;
            case 82:  // ascii code for 'R'
                SCISendStr("Reverse ... \r\n");
                break;
            case 83:  // ascii code for 'S'
                SCISendStr("Stop ... \r\n");
                break;
            case 'A':
                break;
            case 'C':
                break;        
            case '+':
                break;
            case '-':
                break;
            case 'D':
                break;
            case 'P':
                break;
            case 'V':
                break;
            case 'B':
                break;
            case '?':
                break;
            default:
                break;
        }
    }   // end of while ()
}


// simple test mode for testing functions
void Test()
{
  int opDelay = 10000;
  
  while (1) {
    ControlMouse(MOUSE_ACTION_FORWARD);
    Delay(opDelay);
    ControlMouse(MOUSE_ACTION_REVERSE);
    Delay(opDelay);
    ControlMouse(MOUSE_ACTION_TURNLEFT);
    Delay(opDelay);
    ControlMouse(MOUSE_ACTION_TURNRIGHT);
    Delay(opDelay);
    ControlMouse(MOUSE_ACTION_TURNAROUND);
    Delay(opDelay);
    ControlMouse(MOUSE_ACTION_STOP);
    Delay(opDelay);

  }
}