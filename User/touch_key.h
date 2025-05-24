#ifndef __TOUCH_KEY_H
#define __TOUCH_KEY_H

#include "my_config.h"

/*
    触摸按键的扫描周期，单位：ms
    用在定时器中断，注意不能超过变量的最大值
*/
#define TOUCH_KEY_SCAN_CIRCLE_TIMES (10)
#define TOUCH_KEY_FILTER_TIMES (3)         // 触摸按键消抖次数
#define DETECT_DOUBLE_CLICK_INTERVAL (150) // 检测双击的时间间隔(单位：ms)
#define LONG_PRESS_TIME_THRESHOLD_MS (500) // 长按时间阈值（单位：ms）
// #define HOLD_PRESS_TIME_THRESHOLD_MS (25) // 长按持续(不松手)的时间阈值(单位：ms)，每隔 xx 时间认为有一次长按持续事件
#define HOLD_PRESS_TIME_THRESHOLD_MS (150) // 长按持续(不松手)的时间阈值(单位：ms)，每隔 xx 时间认为有一次长按持续事件
#define LOOSE_PRESS_CNT_MS (30)            // 松手计时，松开手多久，才认为是真的松手了

// #define TOUCH_KEY_ID_NONE 0
// #define TOUCH_KEY_ID_1 TK_CH10_VALIB // 按键标识 
// #define TOUCH_KEY_ID_2 TK_CH9_VALIB  // 按键标识 

enum TOUCH_KEY_ID
{
    TOUCH_KEY_ID_NONE = 0x00,
    TOUCH_KEY_ID_1,
    TOUCH_KEY_ID_2,
};


// enum
// {
//     TOUCH_KEY_SCAN_STATUS_NONE = 0,              // 空状态，检测是否有按键按下
//     TOUCH_KEY_SCAN_STATUS_IS_DETECT_LOOG_PRESS,  // 正在检测是否为长按（要跟检测长按作区分）
//     TOUCH_KEY_SCAN_STATUS_IS_HANDLE_LONG_PRESS,  // 正在处理长按
//     TOUCH_KEY_SCAN_STATUS_IS_HANDLE_HOLD_PRESS,  // 正在处理长按持续（不松手）
//     TOUCH_KEY_SCAN_STATUS_IS_HANDLE_SHORT_PRESS, // 正在处理短按

//     TOUCH_KEY_SCAN_STATUS_IS_WAIT_SHORT_PRESS_RELEASE, // 正在等待短按松开
//     TOUCH_KEY_SCAN_STATUS_IS_WAIT_LONG_PRESS_RELEASE,  // 正在等待长按松开
//     TOUCH_KEY_SCAN_STATUS_IS_END,                      // 收尾处理
// };

// enum
// {
//     TOUCH_KEY_EVENT_NONE = 0,
//     TOUCH_KEY_EVENT_ID_1_CLICK,
//     TOUCH_KEY_EVENT_ID_1_DOUBLE,
//     TOUCH_KEY_EVENT_ID_1_LONG,
//     TOUCH_KEY_EVENT_ID_1_HOLD,
//     TOUCH_KEY_EVNET_ID_1_LOOSE,

//     TOUCH_KEY_EVENT_ID_2_CLICK,
//     TOUCH_KEY_EVENT_ID_2_DOUBLE,
//     TOUCH_KEY_EVENT_ID_2_LONG,
//     TOUCH_KEY_EVENT_ID_2_HOLD,
//     TOUCH_KEY_EVNET_ID_2_LOOSE,
// };

extern volatile struct key_driver_para touch_key_para;

/*
    标志位，触摸按键的扫描周期是否到来
    由定时器中断置位，扫描函数中判断该标志位的状态，再决定是否要进行按键扫描
*/
// extern volatile bit flag_is_touch_key_scan_circle_arrived;
// extern void touch_key_scan(void);

extern void touch_key_handle(void);

#endif
