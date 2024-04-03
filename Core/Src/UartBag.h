//
// Created by 24106 on 2024/3/9.
//

#ifndef MOTOR3_UARTBAG_H
#define MOTOR3_UARTBAG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f1xx_hal.h"
#include "usart.h"


#ifdef  __cplusplus
}
#endif

/*
 * include pid for CMD2
 */





/*
 * variable
 */
extern uint8_t bag[15];   //指定集 //data bag
extern uint8_t first ; //验证包头@，在结束收包时清除标记@置1 //the first receive byte, if it receives '@', then receive data bag, else nothing
extern uint8_t val; //验证是否是数据包 //it tells the program whether receive the data bag
extern uint8_t i;  //包数组的位置 //it is the data bag's index
extern uint8_t out; //数据包超过10个的检验结束标志！ //it tells the program whether the data bag is more than 10 bytes,if it happens, the program will not receive the data bag and will do loop until receive the last byte '!'
extern uint8_t open;

/*
 * function
 */

void TransmitBag(const uint8_t *b, uint8_t n,uint8_t end);
uint8_t ReceiveBag();
void test();
void print(UART_HandleTypeDef* huart, const char* buf, ...);
void number(char* str,int *s,int *p);
uint8_t ReceiveBag_3();
#endif //MOTOR3_UARTBAG_H
