#ifndef __SPEED_SCAN_H
#define __SPEED_SCAN_H

#include "include.h"   // 使用芯片官方提供的头文件
#include "my_config.h" // 包含自定义的头文件

extern volatile bit flag_is_update_speed_pulse_cnt; // 标志位，是否由更新计数,由定时器来置位
extern volatile u16 speed_scan_time_cnt;            // 速度扫描时，用到的时间计数值，会在定时器中断中累加
extern volatile u16 speed_actual_scan_time_cnt; // 存放实际的速度扫描时间(实际的速度扫描用时)
extern volatile u32 detect_speed_pulse_cnt[2];      // 检测时速的脉冲计数值

void speed_scan_config(void);
void speed_scan(void);

#endif
