// my_config.h -- 自定义的配置文件
#ifndef __MY_CONFIG_H
#define __MY_CONFIG_H

#include "include.h"        // 使用芯片官方提供的头文件
#include "typedef_struct.h" // 包含结构体类型和别名的定义

#define ARRAY_SIZE(arry) (sizeof(arry) / sizeof(arry[0]))

#define USE_MY_DEBUG 0

// 串口0波特率
#define UART0_BAUDRATE (115200)
// 串口1波特率
// #define UART1_BAUDRATE 115200 // 这款芯片（TX3260）不能使用UART1的DMA来接收不定长的数据

// 串口0接收缓冲区的大小（单位：字节）
#define UART0_RXBUF_LEN (30) // 最大不能超过255，超过之后，串口接收会出错

// 长度单位
// USE_INTERNATIONAL -- 国际通用单位
// USE_IMPERIAL -- 英制单位
#define USE_INTERNATIONAL
// ======================================================
// 引脚电平扫描配置：
// 扫描时间，每隔 xx ms更新一次状态(不能大于变量类型对应的最大值)
#define PIN_LEVEL_SCAN_TIME_MS (200)
// 引脚电平扫描配置
// ======================================================

// ======================================================
// 检测发动机转速所需的配置：
#define ENGINE_SPEED_SCAN_PIN P02 // 检测发动机转速的引脚
// 检测到 多少个脉冲 表示 发动机转过一圈
#define ENGINE_SPEED_SCAN_PULSE_PER_TURN (16)
// 累计检测多久的发动机转速： (单位：ms)(不能大于1min,不能大于变量类型对应的最大值)
#define ENGINE_SPEED_SCAN_TIME_MS (100)
// 重复检测多少次时速，才更新：
#define ENGINE_SPEED_SCAN_FILTER_CNT (5)

// 检测发动机转速所需的配置
// ======================================================

// ======================================================
// 检测时速所需的配置：
#define SPEED_SCAN_PIN P15 // 检测时速的引脚
// 检测到 多少个脉冲 表示 车轮走过一圈
#define SPEED_SCAN_PULSE_PER_TURN (32)
// 车轮的一圈对应多少毫米
#define SPEED_SCAN_MM_PER_TURN (1795) // 一圈 xx 毫米
// 累计检测多久的时速：(单位：ms)
#define SPEED_SCAN_TIME_MS (100)
// 重复检测多少次时速，才更新：(不能为0，也不能太大)
// 例如 5次，  5(次) *  SPEED_SCAN_TIME_MS 之后，才更新速度
#define SPEED_SCAN_FILTER_CNT (10)

// 检测时速所需的配置
// ======================================================

// ======================================================
// 油量检测配置：
// 油量检测并更新的时间(单位：ms)
#define FUEL_CAPACITY_SCAN_TIME_MS (500)
// 油量最大时，对应的ad值
#define FUEL_MAX_ADC_VAL (600)
// 油量最小时，对应的ad值
#define FUEL_MIN_ADC_VAL (2700)

// 油量各个百分比下，对应的ad值
#define FUEL_10_PERCENT_ADC_VAL (2654)
#define FUEL_20_PERCENT_ADC_VAL (2570)
#define FUEL_30_PERCENT_ADC_VAL (2480)
#define FUEL_40_PERCENT_ADC_VAL (2320)
#define FUEL_50_PERCENT_ADC_VAL (2150)
#define FUEL_60_PERCENT_ADC_VAL (2020)
#define FUEL_70_PERCENT_ADC_VAL (1850)
#define FUEL_80_PERCENT_ADC_VAL (1735)
#define FUEL_90_PERCENT_ADC_VAL (1335)
// 油量检测配置
// ======================================================

// ======================================================
// 触摸按键配置
// 使用5V参考电压，外部没有分压的情况下：
#define AD_KEY_INTERVAL (75)         // 判断区间，检测到ad值在(目标ad值-区间区 ~ 目标ad值+区间值,认为条件成立)
#define AD_KEY_ONE_LEFT_VAL (876)    // 从左往下数，第一个按键对应的ad值 (1.07V)
#define AD_KEY_TWO_LEFT_VAL (3604)   // 从左往下数，第二个按键对应的ad值 (4.40V)
#define AD_KEY_THREE_LEFT_VAL (2859) // 从左往下数，第三个按键对应的ad值 (3.49V)

#define AD_KEY_ONE_RIGHT_VAL (1499)   // 从右往下数，第一个按键对应的ad值 (1.83V)
#define AD_KEY_TWO_RIGHT_VAL (1744)   // 从右往下数，第二个按键对应的ad值 (2.13V)
#define AD_KEY_THREE_RIGHT_VAL (2359) // 从右往下数，第三个按键对应的ad值 (2.88V)

// 不能使用这种方式，ad值不在定义的按键对应的ad值区间时，都认为按键没有按下:
// #define AD_KEY_NONE (4095) // 没有按键按下时，对应的ad值

// 触摸按键键值定义(检测到短按/持续时，要发送的键值)：
#define TOUCH_KEY_VAL_MUTE ((u16)0x0040)    // 左2 从左往下数，第二个按键
#define TOUCH_KEY_VAL_VOL_INC ((u16)0x0041) // 左3 从左往下数，第三个按键
#define TOUCH_KEY_VAL_VOL_DEC ((u16)0x0042) // 左1 从左往下数，第一个按键
#define TOUCH_KEY_VAL_MODE ((u16)0x0065)    // 右2 从右往下数，第二个按键
#define TOUCH_KEY_VAL_PRE ((u16)0x00E3)     // 右1 从右往下数，第一个按键
#define TOUCH_KEY_VAL_NEXT ((u16)0x00E4)    // 右3 从右往下数，第三个按键

// 检测到长按时要发送的键值：
#define TOUCH_KEY_VAL_POWER ((u16)0x0046) // 左2 从左往下数，第二个按键
#define TOUCH_KEY_VAL_MAIN ((u16)0x0011)  // 右2 从右往下数，第二个按键

// 注意：只有 TOUCH_KEY_VAL_VOL_INC 和 TOUCH_KEY_VAL_VOL_DEC 需要检测持续按下

// 扫描时间配置：
// #define DETECT_DOUBLE_CLICK_INTERVAL (100) // 检测双击的时间间隔(单位：ms)(没有用到双击操作)
#define LONG_PRESS_TIME_THRESHOLD_MS (500) // 长按时间阈值(单位：ms)(注意不能大于变量类型的大小)
#define HOLD_PRESS_TIME_THRESHOLD_MS (25)  // 长按持续(不松手)的时间阈值(单位：ms)，每隔 xx 时间认为有一次长按持续事件(注意不能大于变量类型的大小)
#define LOOSE_PRESS_CNT_MS (0)             // 松手计时，松开手多久，才认为是真的松手了(注意不能大于变量类型的大小)

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

// ======================================================
// 电池电量检测配置:
// 电池电量检测的更新时间(单位：ms，每隔 xx ms更新一次)
// 注意更新时间不能过长(不超过1min)，否则在求电池电压平均值前，会计数溢出
#define BATTERY_SCAN_UPDATE_TIME_MS (1000)

// 电池满电时的电压:(例， 电池4.2V满电， MAX_VOLTAGE_OF_BATTERY == 42)
// 目前外部使用45K上拉，22K下拉
#define MAX_VOLTAGE_OF_BATTERY (150)
// 电池放电的截止电压：（例，电池2.3V截止,MIN_VOLTAGE_OF_BATTERY == 23）
// #define MIN_VOLTAGE_OF_BATTERY (90)
// 电池满电时，在检测引脚检测到的ad值
// #define MAX_VOLTAGE_OF_BATTERY_AD_VAL (4034)
// 电池电量检测配置
//======================================================

// 里程的配置:
// 大小里程的更新时间(单位:ms,使用的是 ONE_CYCLE_TIME_MS 作为时基,可以不准时):
#define MILEAGE_UPDATE_TIME_MS (5000)

// 主函数完成一次循环所需的时间，单位：ms (0--说明每次调用该函数的时间很短，可以忽略不计)(注意不能大于变量类型的大小)
// 功能全部开放后，每一轮的时间可能都不一样，不在时间要求高的场合使用(目前最短的一个周期是8ms)
#define ONE_CYCLE_TIME_MS (8)

#include <stdio.h>   // printf()
#include "my_gpio.h" // 自定义的、使用到的引脚

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
#include "aip1302.h"

#endif // end file
