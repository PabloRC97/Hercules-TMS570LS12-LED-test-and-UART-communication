/** @file sys_main.c 
*   @brief Application main file
*   @date 11-Dec-2018
*   @version 04.07.01
*
*   This file contains an empty main function,
*   which can be used for the application.
*/

/* 
* Copyright (C) 2009-2018 Texas Instruments Incorporated - www.ti.com 
* 
* 
*  Redistribution and use in source and binary forms, with or without 
*  modification, are permitted provided that the following conditions 
*  are met:
*
*    Redistributions of source code must retain the above copyright 
*    notice, this list of conditions and the following disclaimer.
*
*    Redistributions in binary form must reproduce the above copyright
*    notice, this list of conditions and the following disclaimer in the 
*    documentation and/or other materials provided with the   
*    distribution.
*
*    Neither the name of Texas Instruments Incorporated nor the names of
*    its contributors may be used to endorse or promote products derived
*    from this software without specific prior written permission.
*
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
*  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
*  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
*  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
*  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
*  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
*  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
*  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
*  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
*  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
*/


/* USER CODE BEGIN (0) */
#define BIT_LED 1
#define BIT_PUSH_BUTTON 2
/* USER CODE END */

/* Include Files */

#include "sys_common.h"

/* USER CODE BEGIN (1) */
#include "gio.h"
#include "sci.h"
#include "stdio.h"
#include "stdint.h"
/* USER CODE END */

/** @fn void main(void)
*   @brief Application main function
*   @note This function is empty by default.
*
*   This function is called after startup.
*   The user can use this function to implement the application.
*/

/* USER CODE BEGIN (2) */
uint8_t Buffer[100];
void wait(uint32 time);
void UART_Display_Text(sciBASE_t *, uint32, uint8 *);

#define UART scilinREG
/* USER CODE END */

int main(void)
{
/* USER CODE BEGIN (3) */
    gioInit();
    sciInit();

    int8_t Button_prev_status =0, LED_status=0, Button_status=1;
    int Length_buffer=0;


    while(1){
        Button_prev_status=Button_status;
        Button_status=gioGetBit(gioPORTB, BIT_PUSH_BUTTON);

        if (Button_status==0 && Button_prev_status==1){

            if(LED_status==0){
                LED_status=1;
                 Length_buffer=sprintf(Buffer, "Turning  LED on! , LED status= %d\n",LED_status );
                 UART_Display_Text(UART, Length_buffer, Buffer);
            }
            else {
                LED_status=0;
                 Length_buffer=sprintf(Buffer, "Turning  LED off! , LED status= %d\n",LED_status );
                 UART_Display_Text(UART, Length_buffer, Buffer);
            }

            gioSetBit(gioPORTB, BIT_LED, LED_status);
        }

    }

/* USER CODE END */

    return 0;
}


/* USER CODE BEGIN (4) */
void UART_Display_Text(sciBASE_t * UART_, uint32 length, uint8 * Data){
      sciSend( UART_, length, (uint8 *) Data);
      sciSend( UART_, (uint32) 2, (uint8 *)"\r\n");
}

void wait(uint32 time)
{
    time--;
}
/* USER CODE END */
