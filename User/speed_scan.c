#include "speed_scan.h"

// 多少个脉冲表示一圈
#ifndef SPEED_SCAN_PULSE_PER_TURN
#define SPEED_SCAN_PULSE_PER_TURN (16)
#endif // 多少个脉冲表示一圈

// 车轮一圈表示多少毫米
#ifndef SPEED_SCAN_MM_PER_TURN
#define SPEED_SCAN_MM_PER_TURN (1795) // 一圈1795毫米
#endif                                // 车轮一圈表示多少毫米

// 标志位，是否由更新计数,由定时器来置位
// 0--未更新脉冲计数，1--有新的脉冲计数
volatile bit flag_is_update_speed_pulse_cnt = 0;
volatile u16 speed_scan_time_cnt = 0;        // 速度扫描时，用到的时间计数值，会在定时器中断中累加
volatile u16 speed_actual_scan_time_cnt = 0; // 存放实际的速度扫描时间(实际的速度扫描用时)
// volatile u32 detect_speed_pulse_cnt = 0; // 检测时速的脉冲计数值
/*
    存放 检测到的时速脉冲计数值，会在中断内累加
    使用了双缓冲，[0]用在定时器中断中，[1]用在处理函数中
    当 flag_is_update_speed_pulse_cnt == 1时，说明已经有数据更新
*/
volatile u32 detect_speed_pulse_cnt[2] = {0}; // 检测时速的脉冲计数值

// 时速扫描的配置
void speed_scan_config(void)
{
#if 1 // 使用定时器扫描IO电平变化来计算脉冲
    
    P1_MD1 &= ~GPIO_P15_MODE_SEL(0x3); // 输入模式
    P1_PU |= GPIO_P15_PULL_UP(0x1);    // 配置为上拉

#endif // 使用定时器扫描IO电平变化来计算脉冲
}

// 速度扫描函数
void speed_scan(void)
{
    volatile u32 cur_speed = 0;                    // 记录当前采集到的速度
    static volatile u32 cur_speed_average_val = 0; // 存放当前速度的平均值(单位：km/h)

    static volatile u8 speed_scan_cnt = 0;

    if (flag_is_update_speed_pulse_cnt) // 如果有数据更新
    {
        flag_is_update_speed_pulse_cnt = 0;
        /*
            计算 xx ms内走过了多少毫米
            xx ms内走过了多少毫米 == 当前扫描时间内检测到的脉冲个数 / 车轮一圈对应多少个脉冲 * 一圈对应 xx 毫米
            换成单片机可以计算的形式：
            xx ms内走过了多少毫米 == 当前扫描时间内检测到的脉冲个数 * 一圈对应 xx 毫米 / 车轮一圈对应多少个脉冲
        */
        cur_speed = detect_speed_pulse_cnt[1] * SPEED_SCAN_MM_PER_TURN / SPEED_SCAN_PULSE_PER_TURN;

        // printf("cur pulse cnt %lu \n", detect_speed_pulse_cnt[1]); // 临时测试用

        detect_speed_pulse_cnt[1] = 0; // 清空脉冲计数
        distance += cur_speed;         // 存放走过的距离，单位：毫米

        /*
            已知在扫描时间内走过了xx mm
            时速的计算公式:
            扫描时间内走过的距离 / 1000 * (1 / 扫描时间对1s的占比) * 3.6
                扫描时间内走过的距离 / 1000，转换成 m/扫描时间 的单位
                * (1 / 扫描时间对1s的占比)，转换成以s为单位的速度
                * 3.6，因为 1m/s == 3.6km/h，最后转换成 以km/h的单位
            转换成单片机可以计算的形式：
            时速 == 扫描时间内走过的距离 * 36 * (1 / 扫描时间对1s的占比) / 10000；

            逐渐变换成单片机可以计算的形式：
            cur_speed = cur_speed * 36 * (1 / (SPEED_SCAN_TIME_MS / 1000)) / 10000;
            cur_speed = cur_speed * 36 * 1000 / SPEED_SCAN_TIME_MS / 10000;
            cur_speed = cur_speed * 36 / SPEED_SCAN_TIME_MS / 10;
        */
        cur_speed = (cur_speed * 36) / speed_actual_scan_time_cnt / 10;

        // printf("cur speed %lu \n", cur_speed);

        if (speed_scan_cnt < SPEED_SCAN_FILTER_CNT)
        {
            // 如果未达到重复检测的次数
            speed_scan_cnt++;
            cur_speed_average_val += cur_speed; // 累加当前得到的时速(单位：km/h)

            // if (cur_speed)
            // {
            //     printf("ori speed %lu\n", cur_speed);
            // }
        }
        else
        {
            // 如果达到了重复检测的次数
            speed_scan_cnt = 0;
            cur_speed_average_val /= SPEED_SCAN_FILTER_CNT; // 时速取平均值
            fun_info.speed = cur_speed_average_val;         // 存放得到的时速
            cur_speed_average_val = 0;                      // 清空变量的值
            
#if USE_MY_DEBUG

            if (fun_info.speed != 0)
            {
                printf("cur speed %lu km/h\n", fun_info.speed);
            }

#endif

            // 限制要发送的时速:
            if (fun_info.speed > 999)
            {
                fun_info.speed = 999;
            }

            flag_get_speed = 1; //
        }
    }
}
