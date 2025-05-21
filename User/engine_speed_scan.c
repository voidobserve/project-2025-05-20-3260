#include "engine_speed_scan.h"

// 发动机每转一圈，能检测到的脉冲个数
#ifndef ENGINE_SPEED_SCAN_PULSE_PER_TURN
#define ENGINE_SPEED_SCAN_PULSE_PER_TURN (16)
#endif

volatile u16 engine_scan_time_cnt = 0;        // 发动机转速扫描时，用到的时间计数值，会在定时器中断中累加
volatile u16 engine_actual_scan_time_cnt = 0; // 存放实际的发动机转速扫描用时

// 标志位，是否有更新脉冲计数,由定时器来置位
// 0--未更新脉冲计数，1--有新的脉冲计数
volatile bit flag_is_update_engine_pulse_cnt = 0;
/*
    存放 检测到的发送机转速的脉冲计数值，会在中断内累加
    使用了双缓冲，[0]用在定时器中断中，[1]用在发动机转速处理函数中
    当 flag_is_update_engine_pulse_cnt == 1时，说明已经有数据更新
*/
volatile u32 detect_engine_pulse_cnt[2] = {0};

// 发动机转速的相关配置
void engine_speed_scan_config(void)
{
#if 1 // 使用定时器扫描IO电平的方式

    P0_MD0 &= ~GPIO_P02_MODE_SEL(0x3); // 输入模式

#endif // 使用定时器扫描IO电平的方式
}

// 发动机转速扫描
void engine_speed_scan(void)
{
#define CONVER_ONE_MINUTE_TO_MS (60000) // 将1min转换成以ms为单位的数据
    volatile u32 rpm = 0;
    static volatile u8 engine_speed_scan_cnt = 0; // 重复扫描的检测次数(用于滤波)
    static volatile u32 cur_rpm_average = 0;      // 存放发动机转速的平均值

    if (flag_is_update_engine_pulse_cnt)
    {
        // 如果有数据更新
        flag_is_update_engine_pulse_cnt = 0; // 清除标志位

        /*
            (1min / 1min转过的圈数) == (扫描时间 / 扫描时间内的转过的圈数)
            1min转过的圈数 == 1min * 扫描时间内转过的圈数 / 扫描时间
            1min转过的圈数 == 1min * (扫描时间内采集到的脉冲个数 / 发动机转过一圈对应的脉冲个数) / 扫描时间
            转换成单片机能计算的形式：
            1min转过的圈数 == 扫描时间内采集到的脉冲个数 * 1min / 发动机转过一圈对应的脉冲个数 / 扫描时间
            1min转过的圈数 == 扫描时间内采集到的脉冲个数 * 1min / 扫描时间 / 发动机转过一圈对应的脉冲个数
        */

#if USE_MY_DEBUG

        // if (detect_engine_pulse_cnt[1])
        // {
        //     printf("pulse_cnt %lu \n", detect_engine_pulse_cnt[1]);
        //     printf("engine actual scan time %u\n",engine_actual_scan_time_cnt);
        // }

#endif // #if USE_MY_DEBUG

        rpm = detect_engine_pulse_cnt[1] * (CONVER_ONE_MINUTE_TO_MS / ENGINE_SPEED_SCAN_PULSE_PER_TURN) / engine_actual_scan_time_cnt;
        if (engine_speed_scan_cnt < ENGINE_SPEED_SCAN_FILTER_CNT)
        {
            // 如果未达到重复扫描的检测次数
            engine_speed_scan_cnt++;
            cur_rpm_average += rpm;

            // if (rpm)
            // {
            //     printf("ori rpm %lu\n", rpm);
            // }
        }
        else
        {
            // 如果达到的重复扫描的检测次数
            cur_rpm_average /= ENGINE_SPEED_SCAN_FILTER_CNT;

            engine_speed_scan_cnt = 0; // 清除扫描次数的计数值

            // 限制待发送的发动机转速
            if (cur_rpm_average >= 65535)
            {
                cur_rpm_average = 65535;
            }

#ifdef USE_MY_DEBUG
#if USE_MY_DEBUG

            if (cur_rpm_average != 0)
            {
                printf("engine speed %lu rpm\n", cur_rpm_average);
            }

#endif // #if USE_MY_DEBUG
#endif // #ifdef USE_MY_DEBUG

            fun_info.engine_speeed = cur_rpm_average; // 向全局变量存放发动机转速
            cur_rpm_average = 0;

            flag_get_engine_speed = 1; // 发送发动机转速
        }
    }
}
