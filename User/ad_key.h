#ifndef __AD_KEY_H
#define __AD_KEY_H

#include "include.h"   // 使用芯片官方提供的头文件
#include "my_config.h" // 包含自定义的头文件

// 上拉电阻阻值，单位：欧姆
#define AD_KEY_PULL_UP_VAL ((u32)5100)

// ad按键下拉电阻阻值，按从小到大排列（注意要修饰成u32类型，否则下面的计算会溢出）
#define AD_KEY_PULL_DOWN_VAL_1 ((u32)10)   //
#define AD_KEY_PULL_DOWN_VAL_2 ((u32)1000) //
#define AD_KEY_PULL_DOWN_VAL_3 ((u32)3300) //
#define AD_KEY_PULL_DOWN_VAL_4 ((u32)5600) //
#define AD_KEY_PULL_DOWN_VAL_5 ((u32)8200) //

/*
    参考电压为VCC，并且ad按键的上拉电阻连接的是VCC，
    adc12位精度，填写ad按键对应的ad值，根据下拉电阻阻值从小到大排列
*/
#define AD_KEY_NONE_VAL ((u32)4095) // 无按键按下，对应的ad值
#define __AD_KEY_1_VAL (AD_KEY_NONE_VAL * AD_KEY_PULL_DOWN_VAL_1 / (AD_KEY_PULL_DOWN_VAL_1 + AD_KEY_PULL_UP_VAL))
#define __AD_KEY_2_VAL (AD_KEY_NONE_VAL * AD_KEY_PULL_DOWN_VAL_2 / (AD_KEY_PULL_DOWN_VAL_2 + AD_KEY_PULL_UP_VAL))
#define __AD_KEY_3_VAL (AD_KEY_NONE_VAL * AD_KEY_PULL_DOWN_VAL_3 / (AD_KEY_PULL_DOWN_VAL_3 + AD_KEY_PULL_UP_VAL))
#define __AD_KEY_4_VAL (AD_KEY_NONE_VAL * AD_KEY_PULL_DOWN_VAL_4 / (AD_KEY_PULL_DOWN_VAL_4 + AD_KEY_PULL_UP_VAL))
#define __AD_KEY_5_VAL (AD_KEY_NONE_VAL * AD_KEY_PULL_DOWN_VAL_5 / (AD_KEY_PULL_DOWN_VAL_5 + AD_KEY_PULL_UP_VAL))
#define __AD_KEY_6_VAL ((u32)4095) // 没有该按键，填上拉连接到的VCC对应的值

// 存放各个ad按键划分的阈值:
#define AD_KEY_ID_1_VAL (((u16)__AD_KEY_1_VAL + (u16)__AD_KEY_2_VAL) / 2)
#define AD_KEY_ID_2_VAL (((u16)__AD_KEY_2_VAL + (u16)__AD_KEY_3_VAL) / 2)
#define AD_KEY_ID_3_VAL (((u16)__AD_KEY_3_VAL + (u16)__AD_KEY_4_VAL) / 2)
#define AD_KEY_ID_4_VAL (((u16)__AD_KEY_4_VAL + (u16)__AD_KEY_5_VAL) / 2)
#define AD_KEY_ID_5_VAL (((u16)__AD_KEY_5_VAL + (u16)__AD_KEY_6_VAL) / 2)

enum
{
    AD_KEY_ID_NONE = 0,
    AD_KEY_ID_1,
    AD_KEY_ID_2,
    AD_KEY_ID_3,
    AD_KEY_ID_4,
    AD_KEY_ID_5,
};

// #define AD_KEY_INTERVAL (75)         // 判断区间，检测到ad值在(目标ad值-区间区 ~ 目标ad值+区间值,认为条件成立)
// #define AD_KEY_ONE_LEFT_VAL (876)    // 从左往下数，第一个按键对应的ad值 (1.07V)
// #define AD_KEY_TWO_LEFT_VAL (3604)   // 从左往下数，第二个按键对应的ad值 (4.40V)
// #define AD_KEY_THREE_LEFT_VAL (2859) // 从左往下数，第三个按键对应的ad值 (3.49V)

// #define AD_KEY_ONE_RIGHT_VAL (1499)   // 从右往下数，第一个按键对应的ad值 (1.83V)
// #define AD_KEY_TWO_RIGHT_VAL (1744)   // 从右往下数，第二个按键对应的ad值 (2.13V)
// #define AD_KEY_THREE_RIGHT_VAL (2359) // 从右往下数，第三个按键对应的ad值 (2.88V)

// 不能使用这种方式，ad值不在定义的按键对应的ad值区间时，都认为按键没有按下:
// #define AD_KEY_NONE (4095) // 没有按键按下时，对应的ad值

extern volatile struct key_driver_para ad_key_para;
// extern key_driver_para_t ad_key_para; // 写成这种编译器会报错
// extern volatile struct key_driver_para *p_ad_key_para;

// void ad_key_scan(void);
void ad_key_handle(void);

#endif
