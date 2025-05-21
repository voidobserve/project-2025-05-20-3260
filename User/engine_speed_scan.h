#ifndef __ENGINE_SPEED_SCAN_H
#define __ENGINE_SPEED_SCAN_H

#include "include.h"   // 使用芯片官方提供的头文件
#include "my_config.h" // 包含自定义的头文件

extern volatile bit flag_is_update_engine_pulse_cnt; // 标志位，是否有更新脉冲计数
extern volatile u16 engine_scan_time_cnt; // 发动机转速扫描时，用到的时间计数值，会在定时器中断中累加
extern volatile u16 engine_actual_scan_time_cnt; // 实际的发动机转速扫描用时
extern volatile u32 detect_engine_pulse_cnt[2]; // 检测发送机转速的脉冲计数值

extern void engine_speed_scan_config(void); // 发动机转速扫描的配置
extern void engine_speed_scan(void); // 发动机转速扫描

#endif