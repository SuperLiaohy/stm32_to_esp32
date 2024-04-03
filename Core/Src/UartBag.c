//
// Created by 24106 on 2024/3/9.
//

#include "UartBag.h"
#include "stdio.h"
#include "stdarg.h"
#include "string.h"

/*
 * global variable
 */

uint8_t bag[15] = "         ";   //指定集 //data bag
uint8_t first = '1'; //验证包头@，在结束收包时清除标记@置1 //the first receive byte, if it receives '@', then receive data bag, else nothing
uint8_t val; //验证是否是数据包 //it tells the program whether receive the data bag
uint8_t i=0;  //包数组的位置 //it is the data bag's index
uint8_t out=' '; //数据包超过10个的检验结束标志！ //it tells the program whether the data bag is more than 10 bytes,if it happens, the program will not receive the data bag and will do loop until receive the last byte '!'
uint8_t open = 0;
/*
 * tool
 * it can change int to string,
 * but can only 0~100
 */

void number(char* str,int *s,int *p){
    int num=0;
    int val_fu=0;
    for (int i = 0; str[i] != 'b' ; ++i) {
        if (str[i]<='9'&&'0'<=str[i]){
            if (val_fu)
                num = num * 10 - (str[i] - '0');
            else
                num = num * 10 + (str[i] - '0');
        } else if (str[i]=='-'){
            val_fu = 1;
        } else{
            *s = num;
            num = 0;
            val_fu = 0;
        }
    }
    *p = num;
}



void IntToString(char string[3],int a){
    if (a/100){
        string[0] = '1';
        string[1] = '0';
        string[2] = '0';
    }else{
        string[0] = '0';
        string[1] = '0' + a / 10;
        string[2] = '0' + a % 10;
    }
}

/*
 * judge some part of data bag whether is num
 * if yes
 * change them into int
 * if no
 * transmit err and return -1
 */

int isNum(uint8_t *s, uint8_t from, uint8_t to){
    int number=0;
    for (int j = from; j < to; ++j) {
        number = number*10 + (s[j]-'0');
        if (s[j]>'9'||s[j]<'0') {
            TransmitBag((uint8_t*)"err cmd",7,1);
            return -1;
        }
    }
    return number;
}


/*
 * transmit data bag
 * default \r\n
 */

void TransmitBag(const uint8_t* b, uint8_t n,uint8_t end){
    HAL_UART_Transmit(&huart2,b, n,0xffff);
    if (end)
        HAL_UART_Transmit(&huart2,(uint8_t*)"\r\n",2,0xffff);
}
void TransmitBag_3(const uint8_t* b, uint8_t n,uint8_t end){
    HAL_UART_Transmit(&huart3,b, n,0xffff);
    if (end)
        HAL_UART_Transmit(&huart3,(uint8_t*)"\r\n",2,0xffff);
}

/*
 * receive data bag
 * the first is the '@'
 * and the last is the '!'
 * the maximum capacity of the data bag is 10 bytes;
 */

uint8_t ReceiveBag(){
    while (HAL_UART_Receive_IT(&huart2,&first,1));
    if (val){
        TransmitBag(bag,10,1);
        i=0;
        val = 0;
        return 1;
    }
    return 0;
}
uint8_t ReceiveBag_3(){
    while ((HAL_UART_Receive_IT(&huart3,&first,1)));
    if (val){
//        TransmitBag(bag,15,1);
        i=0;
        val = 0;
        return 1;
    }
    return 0;
}

void test(){
    if (bag[0] == 'p'&& bag[1] == 'i' && bag[2] == 'd'){
        open = 1;
    }
}


void print(UART_HandleTypeDef* huart, const char* buf, ...)
{
    const char *p = buf;
    char str[255] = {0};
    va_list v;
    va_start(v, buf);
    vsprintf(str, buf, v); //使用可变参数的字符串打印。类似sprintf
    HAL_UART_Transmit(huart, str, strlen(str), 0xff);
    va_end(v);
}




