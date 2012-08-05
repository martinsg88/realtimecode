#include "includes.h"

INT16U           gcount;
INT8U            test;

static  void  TaskStartDispInit(void);
void interrupt far newtick();
void interrupt (*oldtick)(void);

void  main (void)
{
	 char    s[25];
	 char    dispStr[25];
	 INT16S  key;
	 INT8U   out = 2;
	 gcount = 0;

	 TaskStartDispInit();

	 oldtick = getvect(0x08);
	 setvect(0x08, &newtick);

	 PC_GetDateTime(s);
	 sprintf(dispStr, "START TIME: %s", s );
	 PC_DispStr(0, 5, dispStr, DISP_FGND_YELLOW + DISP_BGND_BLUE);

	 while(out != 0){
		if(test >= 36){
			gcount = gcount + 1;
			sprintf(dispStr, "TICKS: %d", gcount );
			PC_DispStr(0, 11, dispStr, DISP_FGND_YELLOW + DISP_BGND_BLUE);
			test = 0;
		}
		 if (PC_GetKey(&key)){
					if (key == 0x1B){
						PC_GetDateTime(s);
						sprintf(dispStr, "END TIME: %s", s );
						PC_DispStr(0, 8, dispStr, DISP_FGND_YELLOW + DISP_BGND_BLUE);
						out = out -1;
					}
		 }
		else if (PC_GetKey(&key)){
						if (key == 0x1B){
							out = out -1;
					}
		}
	 }
	 out = 1;

	 setvect(0x08, oldtick);
}

void interrupt newtick()
{
	test = test + 1;
	_chain_intr(oldtick);
}

void  TaskStart (void *pdata)
{
#if OS_CRITICAL_METHOD == 3                                /* Allocate storage for CPU status register */
	 OS_CPU_SR  cpu_sr;
#endif
	 INT16S     key;
	 char       s[80];
	 char       dispStr[160];
	 INT8U      err;

	 pdata = pdata;                                         /* Prevent compiler warning                 */
	 TaskStartDispInit();                                   /* Setup the display                        */


}
static  void  TaskStartDispInit (void)
{
/*                                1111111111222222222233333333334444444444555555555566666666667777777777 */
/*                      01234567890123456789012345678901234567890123456789012345678901234567890123456789 */
	 PC_DispStr( 0,  0, "                         uC/OS-II, The Real-Time Kernel                         ", DISP_FGND_WHITE + DISP_BGND_RED + DISP_BLINK);
	 PC_DispStr( 0,  1, "                                Jean J. Labrosse                                ", DISP_FGND_BLACK + DISP_BGND_LIGHT_GRAY);
	 PC_DispStr( 0,  2, "                                                                                ", DISP_FGND_BLACK + DISP_BGND_LIGHT_GRAY);
	 PC_DispStr( 0,  3, "    															                                ", DISP_FGND_BLACK + DISP_BGND_LIGHT_GRAY);
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
	 PC_DispStr( 0, 23, "                            <-PRESS 'ESC' 2x to exit->                       ", DISP_FGND_BLACK + DISP_BGND_LIGHT_GRAY + DISP_BLINK);
/*                                1111111111222222222233333333334444444444555555555566666666667777777777 */
/*                      01234567890123456789012345678901234567890123456789012345678901234567890123456789 */
}
