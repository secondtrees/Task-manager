#ifndef __APP_H__
#define __APP_H__

#include "stdio.h"

/* ------------------- callback function define ----------------------- */
/*按键执行回调函数 */
extern void Keys_on_keydown(uint8_t key);
/*USART0接收回调函数*/
extern void USART0_on_recv(uint8_t* data, uint32_t len);
/*-------------------------- Init Functions ----------------------------*/

/*-------------------------- Control Functions -------------------------*/

/*-------------------------- Task Functions ----------------------------*/
//按键扫描
void key_scan_task();


#endif