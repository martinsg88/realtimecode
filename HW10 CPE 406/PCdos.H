/*
*********************************************************************************************************
*                                          PC SUPPORT FUNCTIONS
*
*                        (c) Copyright 1992-1998, Jean J. Labrosse, Plantation, FL
*                                           All Rights Reserved
*
* File : PC.H
* By   : Jean J. Labrosse  modified by D. Egbert 2/19/09
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                               CONSTANTS
*                                    COLOR ATTRIBUTES FOR VGA MONITOR
*
* Description: These #defines are used in the PC_Disp???() functions.  The 'color' argument in these
*              function MUST specify a 'foreground' color, a 'background' and whether the display will
*              blink or not.  If you don't specify a background color, BLACK is assumed.  You would 
*              specify a color combination as follows:
*
*              PC_DispChar(0, 0, 'A', DISP_FGND_WHITE + DISP_BGND_BLUE + DISP_BLINK);
*
*              To have the ASCII character 'A' blink with a white letter on a blue background.
*********************************************************************************************************
*/
#define DISP_FGND_BLACK           0x00
#define DISP_FGND_RED             0x01
#define DISP_FGND_GREEN           0x02
#define DISP_FGND_BROWN           0x03
#define DISP_FGND_BLUE            0x04
#define DISP_FGND_PURPLE          0x05
#define DISP_FGND_CYAN            0x06
#define DISP_FGND_LIGHT_GRAY      0x07
#define DISP_FGND_DARK_GRAY       0x08
#define DISP_FGND_LIGHT_RED       0x09
#define DISP_FGND_LIGHT_GREEN     0x0A
#define DISP_FGND_YELLOW          0x0B
#define DISP_FGND_LIGHT_BLUE      0x0C
#define DISP_FGND_LIGHT_PURPLE    0x0D
#define DISP_FGND_LIGHT_CYAN      0x0E
#define DISP_FGND_WHITE           0x0F

#define DISP_BGND_BLACK           0x00
#define DISP_BGND_RED             0x10
#define DISP_BGND_GREEN           0x20
#define DISP_BGND_BROWN           0x30
#define DISP_BGND_BLUE            0x40
#define DISP_BGND_PURPLE          0x50
#define DISP_BGND_CYAN            0x60
#define DISP_BGND_LIGHT_GRAY      0x70

#define DISP_BLINK                0x80
 /*
*********************************************************************************************************
*                                              DATA TYPES
*                                         (Compiler Specific)
*********************************************************************************************************
*/

typedef unsigned char  BOOLEAN;
typedef unsigned char  INT8U;                    /* Unsigned  8 bit quantity                           */
typedef signed   char  INT8S;                    /* Signed    8 bit quantity                           */
typedef unsigned int   INT16U;                   /* Unsigned 16 bit quantity                           */
typedef signed   int   INT16S;                   /* Signed   16 bit quantity                           */
typedef unsigned long  INT32U;                   /* Unsigned 32 bit quantity                           */
typedef signed   long  INT32S;                   /* Signed   32 bit quantity                           */
typedef float          FP32;                     /* Single precision floating point                    */
typedef double         FP64;                     /* Double precision floating point                    */
typedef unsigned int   OS_STK;                   /* Each stack entry is 16-bit wide                    */
typedef unsigned short OS_CPU_SR;                /* Define size of CPU status register (PSW = 16 bits) */
#ifndef  FALSE
#define  FALSE                     0
#endif

#ifndef  TRUE
#define  TRUE                      1
#endif

#define BYTE           INT8S                     /* Define data types for backward compatibility ...   */
#define UBYTE          INT8U                     /* ... to uC/OS V1.xx.  Not actually needed for ...   */
#define WORD           INT16S                    /* ... uC/OS-II.                                      */
#define UWORD          INT16U
#define LONG           INT32S
#define ULONG          INT32U

/* 
*********************************************************************************************************
*/
/*
*********************************************************************************************************
*                                           FUNCTION PROTOTYPES
*********************************************************************************************************
*/

void    PC_DispClrScr(INT8U bgnd_color);
void    PC_DispClrLine(INT8U y, INT8U bgnd_color);
void    PC_DispChar(INT8U x, INT8U y, INT8U c, INT8U color);
void    PC_DispStr(INT8U x, INT8U y, INT8U *s, INT8U color);
void    setrc(INT8U r, INT8U c);
void    setatr(INT8U color);
void    putstr(INT8U *s);

void    PC_ElapsedInit(void);
void    PC_ElapsedStart(void);
INT16U  PC_ElapsedStop(void);

void    PC_GetDateTime(char *s);
BOOLEAN PC_GetKey(INT16S *c);


