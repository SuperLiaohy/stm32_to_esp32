//
// Created by 24106 on 2024/3/27.
//

#ifndef STM32_TO_ESP32_ENCOER_H
#define STM32_TO_ESP32_ENCOER_H
struct encoder{
    int code;

    short pulse;
    short last_pulse;


    short speed;

};
extern struct encoder encoder1;
extern struct encoder encoder2;
void setpwm(int pwm1,int pwm2);
#endif //STM32_TO_ESP32_ENCOER_H
