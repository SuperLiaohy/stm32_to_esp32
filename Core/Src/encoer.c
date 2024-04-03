//
// Created by 24106 on 2024/3/27.
//

#include "encoer.h"
#include "gpio.h"
#include "tim.h"

struct encoder encoder1;
struct encoder encoder2;

float myabs(float input){
    return input<0?-input:input;
}
float limit(float min,float input,float max){
    if (input<min)
        return min;
    if (max<input)
        return max;
    return input;
}
void setpwm(int pwm1,int pwm2){

    if (pwm1 > 0) {
        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1 , GPIO_PIN_RESET);

        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0 , GPIO_PIN_SET);
    } else if (pwm1 < 0) {
        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1 , GPIO_PIN_SET);

        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0 , GPIO_PIN_RESET);
    }

    if (pwm1){
        __HAL_TIM_SetCompare(&htim1,TIM_CHANNEL_2,myabs(pwm1));
    }



    if (pwm2 > 0) {
        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_RESET);

        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, GPIO_PIN_SET);
    } else if (pwm2 < 0) {
        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_SET);

        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, GPIO_PIN_RESET);
    }

    if (pwm2) {
        __HAL_TIM_SetCompare(&htim1, TIM_CHANNEL_1, myabs(pwm2));
    }
};