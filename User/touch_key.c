#include "touch_key.h"

/*
    标志位，触摸按键的扫描周期是否到来
    由定时器中断置位，扫描函数中判断该标志位的状态，再决定是否要进行按键扫描
*/
volatile bit flag_is_touch_key_scan_circle_arrived;

/**
 * @brief __is_double_click() 判断是否有双击同一个触摸按键,内部最长延时时间：DETECT_DOUBLE_CLICK_INTERVAL
 *
 * @param touch_key_id_const
 * @return u8 0--没有双击同一个触摸按键，1--双击了同一个触摸按键
 */
u8 __is_double_click(const u32 touch_key_id_const)
{
    u8 i = 0;                   // 循环计数值
    volatile u32 touch_key = 0; // 存放每次检测到的按键

    for (; i < DETECT_DOUBLE_CLICK_INTERVAL; i++)
    {
        delay_ms(1);
        __tk_scan();
        touch_key = __tk_key_flag;

        if (touch_key_id_const == touch_key)
        {
            // 如果检测到是同一个按键按下，说明是双击
            return 1; // 双击了同一个触摸按键，返回1
        }
    }

    return 0; // 没有双击同一个触摸按键，返回0
}

// 使用touch_key之前，先调用官方提供的触摸模块的初始化函数 tk_param_init();
void touch_key_scan(void)
{

#if 1
    // static volatile u8 filter_cnt = 0; // 按键消抖使用到的变量
    volatile u32 touch_key = 0;                   // __tk_key_flag 单次按键标志
    static volatile u32 touch_key_last = 0;                // 用于存放长按时，对应的按键
    static volatile u32 touch_time_cnt = 0;       // 长按计数值
    static volatile u8 touch_key_scan_status = 0; // 非阻塞的按键扫描函数中，使用的状态机

    if (0 == flag_is_touch_key_scan_circle_arrived)
    {
        // 如果扫描周期没有到来，不执行按键扫描
        return;
    }

    flag_is_touch_key_scan_circle_arrived = 0;

    WDT_KEY = WDT_KEY_VAL(0xAA); // 喂狗并清除 wdt_pending
    /* 按键扫描函数 */
    __tk_scan();                 // 使用了库里面的接口（闭源库）
    WDT_KEY = WDT_KEY_VAL(0xAA); // 喂狗并清除 wdt_pending
    touch_key = __tk_key_flag;   // __tk_key_flag 单次按键标志

    if (TOUCH_KEY_SCAN_STATUS_NONE == touch_key_scan_status) // 未检测到按键时
    {
        // 如果有按键按下（并且之前扫描到的不是长按）

        // 判断是否为长按：

        if (touch_key_last == 0) // 如果之前未检测到按键
        {
            touch_key_last = touch_key;
        }
        else if (touch_key_last == touch_key)
        {
            // 如果上次检测到的按键与此次的按键相等，说明按键还未松开
            touch_time_cnt += (TOUCH_KEY_SCAN_CIRCLE_TIMES);

            if (touch_time_cnt >= LONG_PRESS_TIME_THRESHOLD_MS)
            {
                // 如果长按超过了设置的长按时间
                // 跳转到长按处理
                touch_time_cnt = 0; // 清除长按时间计数
                // printf("long press\n");
                touch_key_scan_status = TOUCH_KEY_SCAN_STATUS_IS_HANDLE_LONG_PRESS;
            }
        }
        else
        {
            // 如果上次检测到的按键与此次的按键不相等，并且上次检测到的按键不等于0
            // touch_time_cnt = 0; // 清除长按时间计数（可以留到收尾处理）

            // 跳转到短按处理
            touch_key_scan_status = TOUCH_KEY_SCAN_STATUS_IS_HANDLE_SHORT_PRESS;

            // printf("short press\n");
        }

        // delay_ms(1); //
    }

    if (TOUCH_KEY_SCAN_STATUS_IS_HANDLE_SHORT_PRESS == touch_key_scan_status)
    {
        // 如果是正在处理短按
        bit flag_is_double_click = 0; // 标志位，是否有按键双击

        if (TOUCH_KEY_ID_1 == touch_key_last)
        {
            // 如果KEY1被触摸
            flag_is_double_click = __is_double_click(touch_key_last);
            if (flag_is_double_click)
            {
                // 如果有按键双击
                printf("k1 double press\n");
#if USE_MY_DEBUG
                printf("k1 double press\n");
#endif
                // send_status_keyval(KEY_PRESS_DOUBLECLICK, TOUCH_KEY1); // 发送带有状态的键值
            }
            else
            {
                // 如果没有按键双击，说明是短按
                printf("k1 press\n");
#if USE_MY_DEBUG
                printf("k1 press\n");
#endif
                // send_status_keyval(KEY_PRESS_SHORT, TOUCH_KEY1); // 发送带有状态的键值
            }

            touch_key_scan_status = TOUCH_KEY_SCAN_STATUS_IS_WAIT_SHORT_PRESS_RELEASE; // 等待按键松开
        }
        else if (TOUCH_KEY_ID_2 == touch_key_last)
        {
            // 如果KEY2被触摸
            flag_is_double_click = __is_double_click(touch_key_last);
            if (flag_is_double_click)
            {
                // 如果有按键双击
                printf("k2 double press\n");
#if USE_MY_DEBUG
                printf("k2 double press\n");
#endif
                // send_status_keyval(KEY_PRESS_DOUBLECLICK, TOUCH_KEY2); // 发送带有状态的键值
            }
            else
            {
                // 如果没有按键双击，说明是短按
                printf("k2 press\n");
#if USE_MY_DEBUG
                printf("k2 press\n");
#endif
                // send_status_keyval(KEY_PRESS_SHORT, TOUCH_KEY2); // 发送带有状态的键值
            }

            touch_key_scan_status = TOUCH_KEY_SCAN_STATUS_IS_WAIT_SHORT_PRESS_RELEASE; // 等待按键松开
        }
    }

    if (TOUCH_KEY_SCAN_STATUS_IS_HANDLE_LONG_PRESS == touch_key_scan_status)
    {
        // 处理长按
        if (TOUCH_KEY_ID_1 == touch_key)
        {
            // 如果KEY1被触摸
            printf("k1 long press\n");
#if USE_MY_DEBUG
            printf("k1 long press\n");
#endif
            // send_status_keyval(KEY_PRESS_LONG, TOUCH_KEY1);
        }
        else if (TOUCH_KEY_ID_2 == touch_key)
        {
            // 如果KEY2被触摸
            printf("k2 long press\n");
#if USE_MY_DEBUG
            printf("k2 long press\n");
#endif
            // send_status_keyval(KEY_PRESS_LONG, TOUCH_KEY2);
        }

        touch_key_scan_status = TOUCH_KEY_SCAN_STATUS_IS_HANDLE_HOLD_PRESS; // 跳转到长按持续
    }

    if (TOUCH_KEY_SCAN_STATUS_IS_HANDLE_HOLD_PRESS == touch_key_scan_status)
    {
        // 处理长按持续

        if (touch_key_last == touch_key)
        {
            touch_time_cnt += TOUCH_KEY_SCAN_CIRCLE_TIMES;
            if (TOUCH_KEY_ID_1 == touch_key)
            {
                if (touch_time_cnt >= HOLD_PRESS_TIME_THRESHOLD_MS)
                {
                    touch_time_cnt = 0;
                    printf("k1 continue press\n");
#if USE_MY_DEBUG
                    printf("k1 continue press\n");
#endif
                    // send_status_keyval(KEY_PRESS_CONTINUE, TOUCH_KEY1);
                }
            }
            else if (TOUCH_KEY_ID_2 == touch_key)
            {
                if (touch_time_cnt >= HOLD_PRESS_TIME_THRESHOLD_MS)
                {
                    touch_time_cnt = 0;
                    printf("k2 continue press\n");
#if USE_MY_DEBUG
                    printf("k2 continue press\n");
#endif
                    // send_status_keyval(KEY_PRESS_CONTINUE, TOUCH_KEY2);
                }
            }

            // delay_ms(1);
        }
        else
        {
            // 如果之前检测到的按键与当前检测到的按键不一致，
            // 说明 可能松开了手 或是 一只手按住了原来的按键另一只手按了其他按键

            // 跳转到等待长按松开
            touch_key_scan_status = TOUCH_KEY_SCAN_STATUS_IS_WAIT_LONG_PRESS_RELEASE;
        }
    }

    if ((TOUCH_KEY_SCAN_STATUS_IS_WAIT_LONG_PRESS_RELEASE == touch_key_scan_status) ||
        (TOUCH_KEY_SCAN_STATUS_IS_WAIT_SHORT_PRESS_RELEASE == touch_key_scan_status))
    {
        // 如果是等待按键松开
        static volatile u16 loose_cnt = 0; // 存放松手计数值

        if (touch_key == 0)
        {
            loose_cnt += TOUCH_KEY_SCAN_CIRCLE_TIMES;
            delay_ms(1);
        }
        else
        {
            // 只要有一次检测到按键，说明没有松开手
            loose_cnt = 0;
        }

        if (loose_cnt >= LOOSE_PRESS_CNT_MS) // 这里的比较值需要注意，不能大于变量类型对应的最大值
        {
            loose_cnt = 0; // 清空松手计数
            // 如果 xx ms内没有检测到按键按下，说明已经松开手

            if (TOUCH_KEY_SCAN_STATUS_IS_WAIT_LONG_PRESS_RELEASE == touch_key_scan_status)
            {
                if (TOUCH_KEY_ID_1 == touch_key_last)
                {
                    printf("k1 long press loose\n");
#if USE_MY_DEBUG
                    printf("k1 long press loose\n");
#endif
                    // send_status_keyval(KEY_PRESS_LOOSE, TOUCH_KEY1);
                }
                else if (TOUCH_KEY_ID_2 == touch_key_last)
                {
                    printf("k2 long press loose\n");
#if USE_MY_DEBUG
                    printf("k2 long press loose\n");
#endif
                    // send_status_keyval(KEY_PRESS_LOOSE, TOUCH_KEY2);
                }
            }

            touch_key_scan_status = TOUCH_KEY_SCAN_STATUS_IS_END; // 跳转到收尾处理
        }
    }

    if (TOUCH_KEY_SCAN_STATUS_IS_END == touch_key_scan_status)
    {
        // 收尾处理
        touch_key = 0;
        touch_key_last = 0;
        touch_time_cnt = 0;

        touch_key_scan_status = TOUCH_KEY_SCAN_STATUS_NONE;
    }
#endif
}

// void touch_key_handle(void)
// {
// }
