#include "includes.h"



#define          LPT_ADDR            0x378            /* address of data register for LPT1              */
#define          LPT_DATA       LPT_ADDR+0
#define          LPT_STATUS     LPT_ADDR+1
#define          LPT_CONTROL    LPT_ADDR+2

#define          MOTOR_COUNT         8                /* number of motor positions                      */
#define          CLOCKWISE           0                /* motor directions                               */
#define          COUNTERCLOCKWISE    1


INT8U           motor_index;                          /* control motor position                        */
INT8U           motor_direction;                      /* control motor direction                       */

void showPortAddress(void      );
void moveMotor      (void      );
void printDosDisplay( int delay);

void  main (void)
{
#define          STATE_STARTUP       0                /* start up of program                            */
#define          STATE_TICK          1                /* show counter incrementing                      */
#define          STATE_FINAL         2                /* show end time and wait for user to Quit        */

        INT16S  key;
        char    s[20];
        INT8U   state;

        INT8U      speeds[] = {  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11,
                                                                         12, 13, 14, 15, 16, 18, 20, 25, 30, 35, 40, 45, 50,
                                                                         60, 70, 80, 90, 100 };
        INT8U      speed_count = sizeof(speeds) / sizeof(INT8U);
        INT8U      speed_index = (speed_count / 4) + (speed_count / 2);
        INT8U      motor_delay;                          /* control motor speed                           */

        motor_index     =  0;
        motor_delay     = speeds[speed_index];
        motor_direction = COUNTERCLOCKWISE;

        outp( LPT_CONTROL, inp(LPT_CONTROL) & 0xDF );

        state = STATE_TICK;
        printDosDisplay( motor_delay );

        /* display parallel port name                       */
        showPortAddress();

        state = STATE_TICK;

         for (;;) {
                  if (state == STATE_TICK ) {
                          if (PC_GetKey(&key)) {                             /* See if key has been pressed              */
                                        if (key == KEY_ESCAPE){
                                                 PC_GetDateTime(s);
                                                 printf("<-PRESS 'ESC' AGAIN TO QUIT->\r\n");

                                                 state = STATE_FINAL;
                                        }

                                        if (key == KEY_MINUS){
                                                 if( speed_index < (speed_count -1) ) {
                                                        speed_index++;
                                                 }
                                                 motor_delay = speeds[speed_index];
                                                 printDosDisplay(motor_delay);
                                                 printf("<-PRESS 'ESC' TO STOP->\r\n");
                                        }

                                        if (key == KEY_PLUS){
                                                 if( speed_index > 0 ) {  //don't allow negative
                                                        speed_index--;
                                                 }
                                                 motor_delay = speeds[speed_index];
                                                 printDosDisplay(motor_delay);
                                                 printf("<-PRESS 'ESC' TO STOP->\r\n");
                                        }

                                        if( (key == KEY_R) || (key == KEY_r) ) {
                                                motor_direction = CLOCKWISE;
                                        }

                                        if( (key == KEY_L) || (key == KEY_l) ) {
                                                motor_direction = COUNTERCLOCKWISE;
                                        }
                          }

                          moveMotor();
                  }
                  else if (state == STATE_FINAL ) {
                          if (PC_GetKey(&key)) {                    /* See if key has been pressed              */
                                        if (key == KEY_ESCAPE) {
                                                system("cls");
                                                return;                            /* Yes, return to DOS                       */
                                        }
                          }
                  }

                  delay( motor_delay );
         } //end of for(;;)
}

void printDosDisplay( int delay)
{
        system("cls");
        printf("Control a stepper motor,  I. Gibbs  4/19/2011\r\n\r\n");
        printf("motor delay = %3d\r\n", delay );
        printf("Directions for User Control\r\n");
        printf("\tPress + to speed up the motor          Press R to rotate clockwise\r\n");
        printf("\tPress - to slow down the motor         Press L to rotate counter clockwise\r\n");
}

void  moveMotor (void)
{
         #define          MOTOR_01         0x01                /* motor positions                                */
         #define          MOTOR_02         0x05
         #define          MOTOR_03         0x04
         #define          MOTOR_04         0x06
         #define          MOTOR_05         0x02
         #define          MOTOR_06         0x0A
         #define          MOTOR_07         0x08
         #define          MOTOR_08         0x09

#if MOTOR_COUNT == 4
         INT8U  motor_position_ccw[] = { MOTOR_01, MOTOR_03, MOTOR_05, MOTOR_07 };
         INT8U  motor_position_cw[]  = { MOTOR_01, MOTOR_03, MOTOR_05, MOTOR_07 };
#elif MOTOR_COUNT == 8
         INT8U  motor_position_ccw[] = { MOTOR_01, MOTOR_02, MOTOR_03, MOTOR_04,
                                                                                                MOTOR_05, MOTOR_06, MOTOR_07, MOTOR_08 };
         INT8U  motor_position_cw[]  = { MOTOR_08, MOTOR_07, MOTOR_06, MOTOR_05,
                                                                                                MOTOR_04, MOTOR_03, MOTOR_02, MOTOR_01 };
#endif   //note, will fail on compile if MOTOR_COUNT set incorrectly

        {

                  motor_index++;
                  if( motor_index >= MOTOR_COUNT )  {
                          motor_index = 0;                  //wrap count
                  }

                  if( motor_direction == CLOCKWISE )  {
                          outp( LPT_DATA, motor_position_cw[ motor_index] );   //set motor position
                  }
                  else {
                          outp( LPT_DATA, motor_position_ccw[motor_index] );   //set motor position
                  }
         }
}
void showPortAddress(void)
{
 unsigned int far *ptraddr;  /* Pointer to location of Port Addresses */
 unsigned int address;       /* Address of Port */
 int a;

 ptraddr=(unsigned int far *)0x00000408;

 for (a = 0; a < 3; a++)
 {
         address = *ptraddr;
         if (address == 0) {
                printf( "\tLPT%d: No port found for LPT%d \n", a+1, a+1 );
         }
         else {
                printf( "\tLPT%d: %xh\n", a+1, address );
         }
         *ptraddr++;
 }
}



