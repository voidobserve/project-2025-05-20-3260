#ifndef __FUEL_CAPACITY_H
#define __FUEL_CAPACITY_H

#include "include.h"   // 使用芯片官方提供的头文件
#include "my_config.h" // 包含自定义的头文件

extern u32 fuel_capacity_scan_cnt; // 扫描时间计数，在1ms定时器中断中累加

void fuel_capacity_scan(void);

#endif
