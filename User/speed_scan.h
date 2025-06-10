#ifndef __SPEED_SCAN_H
#define __SPEED_SCAN_H

#include "include.h"   // 使用芯片官方提供的头文件
#include "my_config.h" // 包含自定义的头文件

// ======================================================
// 检测时速所需的配置：
#define SPEED_SCAN_PIN P15 // 检测时速的引脚
// 检测到 多少个脉冲 表示 车轮走过一圈
// #define SPEED_SCAN_PULSE_PER_TURN (32)
#define SPEED_SCAN_PULSE_PER_TURN (3)
// 车轮的一圈对应多少毫米
// #define SPEED_SCAN_MM_PER_TURN (1795) // 一圈 xx 毫米
#define SPEED_SCAN_MM_PER_TURN (1070) // 一圈 xx 毫米
// 累计检测多久的时速：(单位：ms)
#define SPEED_SCAN_TIME_MS (100)
// 重复检测多少次时速，才更新：(不能为0，也不能太大)
// 例如 5次，  5(次) *  SPEED_SCAN_TIME_MS 之后，才更新速度
#define SPEED_SCAN_FILTER_CNT (200)

// 检测时速所需的配置
// ======================================================

extern volatile bit flag_is_update_speed_pulse_cnt; // 标志位，是否由更新计数,由定时器来置位
extern volatile u16 speed_scan_time_cnt;            // 速度扫描时，用到的时间计数值，会在定时器中断中累加
extern volatile u16 speed_actual_scan_time_cnt; // 存放实际的速度扫描时间(实际的速度扫描用时)
extern volatile u32 detect_speed_pulse_cnt[2];      // 检测时速的脉冲计数值



 
extern volatile bit flag_is_speed_scan_over_time;
extern volatile u32 speed_pulse_cnt;
extern volatile u32 speed_scan_time_ms;


void speed_scan_config(void);
void speed_scan(void);

#endif
