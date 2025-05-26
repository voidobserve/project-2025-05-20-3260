// my_config.h -- 自定义的配置文件
#ifndef __MY_CONFIG_H
#define __MY_CONFIG_H

#include "include.h"        // 使用芯片官方提供的头文件
#include "typedef_struct.h" // 包含结构体类型和别名的定义

#define ARRAY_SIZE(arry) (sizeof(arry) / sizeof(arry[0]))

#define USE_MY_DEBUG 0

#define KEY_UP_VOL_UP       ((u16)209)
#define KEY_DOWN_VOL_DOWN   ((u16)210)
#define KEY_LEFT_PRE        ((u16)207)
#define KEY_RIGHT_NEXT      ((u16)208)
#define KEY_ENTER_MENU      ((u16)127)

// 长度单位（在检测时速和计算里程时使用）
// USE_INTERNATIONAL -- 国际通用单位
// USE_IMPERIAL -- 英制单位
#define USE_INTERNATIONAL

// 触摸按键键值定义(检测到短按/持续时，要发送的键值)：
// #define TOUCH_KEY_VAL_MUTE ((u16)0x0040)    // 左2 从左往下数，第二个按键
// #define TOUCH_KEY_VAL_VOL_INC ((u16)0x0041) // 左3 从左往下数，第三个按键
// #define TOUCH_KEY_VAL_VOL_DEC ((u16)0x0042) // 左1 从左往下数，第一个按键
// #define TOUCH_KEY_VAL_MODE ((u16)0x0065)    // 右2 从右往下数，第二个按键
// #define TOUCH_KEY_VAL_PRE ((u16)0x00E3)     // 右1 从右往下数，第一个按键
// #define TOUCH_KEY_VAL_NEXT ((u16)0x00E4)    // 右3 从右往下数，第三个按键

// // 检测到长按时要发送的键值：
// #define TOUCH_KEY_VAL_POWER ((u16)0x0046) // 左2 从左往下数，第二个按键
// #define TOUCH_KEY_VAL_MAIN ((u16)0x0011)  // 右2 从右往下数，第二个按键

// 注意：只有 TOUCH_KEY_VAL_VOL_INC 和 TOUCH_KEY_VAL_VOL_DEC 需要检测持续按下

// 扫描时间配置：
// #define DETECT_DOUBLE_CLICK_INTERVAL (100) // 检测双击的时间间隔(单位：ms)(没有用到双击操作)

// #define LONG_PRESS_TIME_THRESHOLD_MS (500) // 长按时间阈值(单位：ms)(注意不能大于变量类型的大小)
// #define HOLD_PRESS_TIME_THRESHOLD_MS (25)  // 长按持续(不松手)的时间阈值(单位：ms)，每隔 xx 时间认为有一次长按持续事件(注意不能大于变量类型的大小)
// #define LOOSE_PRESS_CNT_MS (0)             // 松手计时，松开手多久，才认为是真的松手了(注意不能大于变量类型的大小)

// 触摸按键配置
// ======================================================

// ======================================================
// 水温检测配置:
// 发送水温报警/解除水温报警的时间:(单位：ms，每隔xxms发送一次当前水温报警的状态)
#define TEMP_OF_WATER_UPDATE_TIME_MS (1000)

// 水温检测的累计时间(单位：ms)
#define TEMP_OF_WATER_ACCUMULATE_TIEM_MS (10000) // 10s
// 水温检测对应的报警ad值，满足该值且超过累计时间时，触发报警
#define TEMP_OF_WATER_WARNING_AD_VAL (3015)
// 水温检测对应的解除报警ad值，满足该值且超过累计时间时，解除报警
#define TEMP_OF_WATER_CANCEL_WARNING_AD_VAL (2048)

// 注意:水温报警和解除报警对应的ad值不能一致，差值也不能过小

// 水温检测配置
// ======================================================

// 里程的配置:
// 大小里程的更新时间(单位:ms,使用的是 ONE_CYCLE_TIME_MS 作为时基,可以不准时):
#define MILEAGE_UPDATE_TIME_MS (5000)

// 主函数完成一次循环所需的时间，单位：ms (0--说明每次调用该函数的时间很短，可以忽略不计)(注意不能大于变量类型的大小)
// 功能全部开放后，每一轮的时间可能都不一样，不在时间要求高的场合使用(目前最短的一个周期是8ms)
#define ONE_CYCLE_TIME_MS (8)

#include <stdio.h>  // printf()
#include "tk_set.h" // 包含触摸按键的初始化接口

#include "my_gpio.h" // 自定义的、使用到的引脚
#include "key_driver.h"

#include "uart0.h"             // 接收 / 发送 指令 使用的串口(使能USE_MY_DEBUG宏时，printf()也是使用该串口)
#include "uart1.h"             // printf()调试使用到的串口
#include "tmr0.h"              // 串口检测数据超时需要使用到的定时器
#include "tmr1.h"              // 用于 扫描发动机转速、扫描时速、定时将里程写入flash 的定时器
#include "tmr2.h"              // 用于定时扫描脉冲个数(时速、发动机转速)
#include "instruction.h"       // 扫描接收到的数据（必须要在串口0的头文件后面，串口要先接收并验证，才轮到它扫描指令）
#include "fun_info.h"          // 存放各个功能的状态信息
#include "pin_level_scan.h"    // 扫描引脚电平状态
#include "send_data.h"         // 发送带有数据的指令
#include "adc.h"               // adc
#include "speed_scan.h"        // 速度（时速）扫描
#include "engine_speed_scan.h" // 发动机转速扫描
#include "flash.h"             // 提供flash操作的接口
#include "mileage.h"           // 里程表的相关接口
#include "ad_key.h"            // 检测触摸IC发送过来的ad信号
#include "fuel_capacity.h"     // 油量检测
#include "temp_of_water.h"     // 水温报警检测
#include "battery.h"           // 电池电量检测
#include "aip1302.h"           // 时钟IC aip1302
#include "touch_key.h"         // 触摸按键

#endif // end file
