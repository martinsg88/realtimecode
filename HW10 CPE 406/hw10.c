#include "includes.h"

#define TRUE 					1
#define FALSE 					0
#define DATA 					0x0378
#define CTRL		 			0x037A

#define ESC			         0x1B
#define MIN 					0x2D
#define PLS						0x2B
#define lft                0x6C
#define blft               0x4C
#define rgt						0x52
#define brgt					0x72

#define clkw  0 //clockwise
#define cclkw 1 //counter clockwise

#define pos1 0x01   //motor pos 1-8
#define pos2 0x05
#define pos3 0x04
#define pos4 0x06
#define pos5 0x02
#define pos6 0x0A
#define pos7 0x08
#define pos8 0x09

INT8U position; //motor position
INT8U direction; //motor direction
INT8U controls;

void DispInit(void);
void goMotor(void);


void  main (void)
{
	INT16S   key;
	INT8U speeds = 22;
	char s[20];
	INT8U mspeeds[] = {7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22,
								23, 24, 25, 26, 27, 28, 29};

	INT8U quit = 1;
	DispInit();
	position = 0;
	outportb(CTRL, inportb(CTRL)& 0xDF);

   sprintf(s, "%2d", speeds);
	PC_DispStr(11, 9, s, DISP_FGND_BLACK + DISP_BGND_LIGHT_GRAY);

	for (;;) {
	  if(quit == TRUE){
		if (PC_GetKey(&key)) {
			if (key == ESC) {
				quit = FALSE;
				PC_DispStr( 0, 23, "                             <-Hit ESC once more->                    ", DISP_FGND_BLACK + DISP_BGND_LIGHT_GRAY + DISP_BLINK);
			}
			if (key == MIN){
				if ( speeds <= 21){
					speeds++;
					sprintf(s, "%2d", speeds);
					PC_DispStr(11, 9, s, DISP_FGND_BLACK + DISP_BGND_LIGHT_GRAY);
				}
				controls =  mspeeds[speeds];
			}
			if (key == PLS){
				if ( speeds > 0){
					speeds--;
					sprintf(s, "%2d", speeds);
					PC_DispStr(11, 9, s, DISP_FGND_BLACK + DISP_BGND_LIGHT_GRAY);
				}
				controls = mspeeds[speeds];
			}
			if((key == rgt) || (key == brgt)){
				direction  = clkw;
			}
			if((key == lft) || (key == blft)){
				direction = cclkw;
			}
		}
		goMotor();
	  }
	  else if (quit == FALSE){
		  if (PC_GetKey(&key)) {
			 if (key == ESC) {
				 PC_DispStr( 0, 23, "                             <-Good Bye->                    ", DISP_FGND_BLACK + DISP_BGND_LIGHT_GRAY + DISP_BLINK);
             delay(500);
				 PC_DispClrScr(DISP_FGND_WHITE + DISP_BGND_BLACK);
				 exit(0);
				}
		  }
	  }
	 delay(controls);
	}
}
void goMotor(void)
{
	 INT8U posclkw[]  = { pos1, pos2, pos3, pos4, pos5, pos6, pos7, pos8};
	 INT8U poscclkw[] = { pos8, pos7, pos6, pos5, pos4, pos3, pos2, pos1};

	 position++;

	 if( position >= 8 ){
			  position = 0;
	 }
	 if( direction == clkw){
		outportb(DATA, posclkw[position]);
	 }
	 else{
		outportb(DATA, poscclkw[position]);
	 }
}
void  DispInit (void)
{
	 PC_DispStr( 0,  0, "                                                                                ", DISP_FGND_WHITE + DISP_BGND_RED + DISP_BLINK);
	 PC_DispStr( 0,  1, "                                                                                ", DISP_FGND_BLACK + DISP_BGND_LIGHT_GRAY);
	 PC_DispStr( 0,  2, "                                      HW10 Guilherme Martins                    ", DISP_FGND_BLACK + DISP_BGND_LIGHT_GRAY);
	 PC_DispStr( 0,  3, "										                                         ", DISP_FGND_BLACK + DISP_BGND_LIGHT_GRAY);
	 PC_DispStr( 0,  4, "                                                                                ", DISP_FGND_BLACK + DISP_BGND_LIGHT_GRAY);
	 PC_DispStr( 0,  5, "                                                                                ", DISP_FGND_BLACK + DISP_BGND_LIGHT_GRAY);
	 PC_DispStr( 0,  6, "                                                                                ", DISP_FGND_BLACK + DISP_BGND_LIGHT_GRAY);
	 PC_DispStr( 0,  7, "                                                                                ", DISP_FGND_BLACK + DISP_BGND_LIGHT_GRAY);
	 PC_DispStr( 0,  8, "                                                                                ", DISP_FGND_BLACK + DISP_BGND_LIGHT_GRAY);
	 PC_DispStr( 0,  9, "    SPEED:                                                                      ", DISP_FGND_BLACK + DISP_BGND_LIGHT_GRAY);
	 PC_DispStr( 0, 10, "                                                                                ", DISP_FGND_BLACK + DISP_BGND_LIGHT_GRAY);
	 PC_DispStr( 0, 11, "                                                                                ", DISP_FGND_BLACK + DISP_BGND_LIGHT_GRAY);
	 PC_DispStr( 0, 12, "    HIT R to go Clockwise                                                       ", DISP_FGND_BLACK + DISP_BGND_LIGHT_GRAY);
	 PC_DispStr( 0, 13, "    HIT L to go Counter Clockwise                                               ", DISP_FGND_BLACK + DISP_BGND_LIGHT_GRAY);
	 PC_DispStr( 0, 14, "                                                                                ", DISP_FGND_BLACK + DISP_BGND_LIGHT_GRAY);
	 PC_DispStr( 0, 15, "    HIT - to go slower                                                          ", DISP_FGND_BLACK + DISP_BGND_LIGHT_GRAY);
	 PC_DispStr( 0, 16, "    HIT + to go faster                                                          ", DISP_FGND_BLACK + DISP_BGND_LIGHT_GRAY);
	 PC_DispStr( 0, 17, "                                                                                ", DISP_FGND_BLACK + DISP_BGND_LIGHT_GRAY);
	 PC_DispStr( 0, 18, "                                                                                ", DISP_FGND_BLACK + DISP_BGND_LIGHT_GRAY);
	 PC_DispStr( 0, 19, "                                                                                ", DISP_FGND_BLACK + DISP_BGND_LIGHT_GRAY);
	 PC_DispStr( 0, 20, "                                                                                ", DISP_FGND_BLACK + DISP_BGND_LIGHT_GRAY);
	 PC_DispStr( 0, 21, "                                                                                ", DISP_FGND_BLACK + DISP_BGND_LIGHT_GRAY);
	 PC_DispStr( 0, 22, "                                                                                ", DISP_FGND_BLACK + DISP_BGND_LIGHT_GRAY);
	 PC_DispStr( 0, 23, "                             <-PRESS 'ESC'x2 to quit->                    ", DISP_FGND_BLACK + DISP_BGND_LIGHT_GRAY + DISP_BLINK);
}
