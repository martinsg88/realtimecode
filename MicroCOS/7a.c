#include <stdio.h>
#include <dos.h>
#include "PCdos.h"

#define outdata 0x0378
#define indata 0x037A


static  void  TaskStartDispInit(void);
void interrupt far isrnew(void);
void interrupt(*old_isr)(void);//pointer to an interrupt

/****************************************    MAIN    ***************************************************/

void  main (void)
{
	INT16U stripbits;

	INT16S key;
	
	//start critical region
	disable();
		//get the old isr
		old_isr = getvect(0x0F);
		setvect(0x0F, &isrnew); 
		stripbits = inportb(0x21);
		outportb(0x21, stripbits & 0x7F);			
		outportb(indata, inportb(indata) | 0x10);
	enable(); 
	//end critical region
                 
	TaskStartDispInit();                              

	while(1){		
		if (PC_GetKey(&key)) {                             			
			if (key == 0x1B) { 
				disable();							
					outportb(indata, inportb(indata) & 0x10);
					stripbits=inportb(0x21) | 0x80;
					outportb(0x21,stripbits);
					setvect(0x0F, old_isr);
				enable(); 	
				return;				
			}
			
		}		
	}
}
				
/*********************************************************************************************************/
static  void  TaskStartDispInit (void)
{
	 PC_DispStr( 0,  0, "                         uC/OS-II, The Real-Time Kernel                         ", DISP_FGND_WHITE + DISP_BGND_RED + DISP_BLINK);
	 PC_DispStr( 0,  1, "                                Jean J. Labrosse                                ", DISP_FGND_BLACK + DISP_BGND_LIGHT_GRAY);
	 PC_DispStr( 0,  2, "                                      HW7-A Guilherme Martins                   ", DISP_FGND_BLACK + DISP_BGND_LIGHT_GRAY);
	 PC_DispStr( 0,  3, "										     ", DISP_FGND_BLACK + DISP_BGND_LIGHT_GRAY);
	 PC_DispStr( 0,  4, "                                                                                ", DISP_FGND_BLACK + DISP_BGND_LIGHT_GRAY);
	 PC_DispStr( 0,  5, "                                                                                ", DISP_FGND_BLACK + DISP_BGND_LIGHT_GRAY);
	 PC_DispStr( 0,  6, "                                                                                ", DISP_FGND_BLACK + DISP_BGND_LIGHT_GRAY);
	 PC_DispStr( 0,  7, "                                                                                ", DISP_FGND_BLACK + DISP_BGND_LIGHT_GRAY);
	 PC_DispStr( 0,  8, "                                                                                ", DISP_FGND_BLACK + DISP_BGND_LIGHT_GRAY);
	 PC_DispStr( 0,  9, "                                                                                ", DISP_FGND_BLACK + DISP_BGND_LIGHT_GRAY);
	 PC_DispStr( 0, 10, "                                                                                ", DISP_FGND_BLACK + DISP_BGND_LIGHT_GRAY);
	 PC_DispStr( 0, 11, "                                                                                ", DISP_FGND_BLACK + DISP_BGND_LIGHT_GRAY);
	 PC_DispStr( 0, 12, "                                                                                ", DISP_FGND_BLACK + DISP_BGND_LIGHT_GRAY);
	 PC_DispStr( 0, 13, "                                                                                ", DISP_FGND_BLACK + DISP_BGND_LIGHT_GRAY);
	 PC_DispStr( 0, 14, "                                                                                ", DISP_FGND_BLACK + DISP_BGND_LIGHT_GRAY);
	 PC_DispStr( 0, 15, "                                                                                ", DISP_FGND_BLACK + DISP_BGND_LIGHT_GRAY);
	 PC_DispStr( 0, 16, "                                                                                ", DISP_FGND_BLACK + DISP_BGND_LIGHT_GRAY);
	 PC_DispStr( 0, 17, "                                                                                ", DISP_FGND_BLACK + DISP_BGND_LIGHT_GRAY);
	 PC_DispStr( 0, 18, "                                                                                ", DISP_FGND_BLACK + DISP_BGND_LIGHT_GRAY);
	 PC_DispStr( 0, 19, "                                                                                ", DISP_FGND_BLACK + DISP_BGND_LIGHT_GRAY);
	 PC_DispStr( 0, 20, "                                                                                ", DISP_FGND_BLACK + DISP_BGND_LIGHT_GRAY);
	 PC_DispStr( 0, 21, "                                                                                ", DISP_FGND_BLACK + DISP_BGND_LIGHT_GRAY);
	 PC_DispStr( 0, 22, "                                                                                ", DISP_FGND_BLACK + DISP_BGND_LIGHT_GRAY);
	 PC_DispStr( 0, 23, "                             <-PRESS 'ESC' to quit->                      ", DISP_FGND_BLACK + DISP_BGND_LIGHT_GRAY + DISP_BLINK);

}

/********************************************************************************************************/
void interrupt far isrnew(void)
{
	outportb(outdata, inportb(outdata) ^ 0x01);
	_chain_intr(old_isr);
}
