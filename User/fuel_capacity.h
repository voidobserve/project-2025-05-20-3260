#ifndef __FUEL_CAPACITY_H
#define __FUEL_CAPACITY_H

#include "include.h"   // 使用芯片官方提供的头文件
#include "my_config.h" // 包含自定义的头文件


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

extern u32 fuel_capacity_scan_cnt; // 扫描时间计数，在1ms定时器中断中累加

void fuel_capacity_scan(void);

#endif
