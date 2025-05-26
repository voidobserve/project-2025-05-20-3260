#include "fuel_capacity.h"

volatile u32 fuel_capacity_scan_cnt = 0; // 扫描时间计数，在1ms定时器中断中累加
volatile u32 fuel_adc_val = 0;
volatile u32 fuel_adc_scan_cnt = 0; // 在更新时间到来前，记录adc扫描的次数

volatile u8 fuel_percent = 0xFF;

// static volatile u8 last_fuel_percent = 0xFF; // 记录上一次检测到的油量百分比

void fuel_capacity_scan(void)
{
    adc_sel_pin(ADC_PIN_FUEL); // 内部至少占用1ms
    adc_val = adc_getval();
    // printf("fuel adc %u \n", adc_val);

    fuel_adc_val += adc_val;
    fuel_adc_scan_cnt++;

    // fuel_capacity_scan_cnt += ONE_CYCLE_TIME_MS;
    if (fuel_capacity_scan_cnt >= FUEL_CAPACITY_SCAN_TIME_MS)
    {
        // 如果到了扫描更新时间，
        // bit flag_is_update_percent = 1; // 是否更新百分比,0--不更新,1--更新
        fuel_capacity_scan_cnt = 0;
        fuel_adc_val /= fuel_adc_scan_cnt; // 求出扫描时间内得到的ad平均值
        fuel_adc_scan_cnt = 0;
        // printf("fuel adc val %lu \n", fuel_adc_val);


#ifdef USE_MY_DEBUG
#if USE_MY_DEBUG
        // printf("fuel adc val %lu \n", fuel_adc_val);
#endif // #if USE_MY_DEBUG
#endif // #ifdef USE_MY_DEBUG

        // 先确定油量百分比的大致范围：
        if (fuel_adc_val < FUEL_MAX_ADC_VAL + (FUEL_90_PERCENT_ADC_VAL - FUEL_MAX_ADC_VAL) / 3)
        {
            fuel_percent = 100;
        }
        else if (fuel_adc_val < (FUEL_90_PERCENT_ADC_VAL - (FUEL_90_PERCENT_ADC_VAL - FUEL_MAX_ADC_VAL) / 3))
        {
            fuel_percent = 90;
        }
        else if (fuel_adc_val < (FUEL_80_PERCENT_ADC_VAL - (FUEL_80_PERCENT_ADC_VAL - FUEL_90_PERCENT_ADC_VAL) / 3))
        {
            fuel_percent = 80;
        }
        else if (fuel_adc_val < (FUEL_70_PERCENT_ADC_VAL - (FUEL_70_PERCENT_ADC_VAL - FUEL_80_PERCENT_ADC_VAL) / 3))
        {
            fuel_percent = 70;
        }
        else if (fuel_adc_val < (FUEL_60_PERCENT_ADC_VAL - (FUEL_60_PERCENT_ADC_VAL - FUEL_70_PERCENT_ADC_VAL) / 3))
        {
            fuel_percent = 60;
        }
        else if (fuel_adc_val < (FUEL_50_PERCENT_ADC_VAL - (FUEL_50_PERCENT_ADC_VAL - FUEL_60_PERCENT_ADC_VAL) / 3))
        {
            fuel_percent = 50;
        }
        else if (fuel_adc_val < (FUEL_40_PERCENT_ADC_VAL - (FUEL_40_PERCENT_ADC_VAL - FUEL_50_PERCENT_ADC_VAL) / 3))
        {
            fuel_percent = 40;
        }
        else if (fuel_adc_val < (FUEL_30_PERCENT_ADC_VAL - (FUEL_30_PERCENT_ADC_VAL - FUEL_40_PERCENT_ADC_VAL) / 3))
        {
            fuel_percent = 30;
        }
        else if (fuel_adc_val < (FUEL_20_PERCENT_ADC_VAL - (FUEL_20_PERCENT_ADC_VAL - FUEL_30_PERCENT_ADC_VAL) / 3))
        {
            fuel_percent = 20;
        }
        else if (fuel_adc_val < (FUEL_10_PERCENT_ADC_VAL - (FUEL_10_PERCENT_ADC_VAL - FUEL_20_PERCENT_ADC_VAL) / 3))
        {
            fuel_percent = 10;
        }
        else
        {
            fuel_percent = 0;
        }

#ifdef USE_MY_DEBUG
#if USE_MY_DEBUG
        // printf("fuel percent nearly %bu\n", fuel_percent);
#endif // #if USE_MY_DEBUG
#endif // #ifdef USE_MY_DEBUG

        // 再根据死区限制油量百分比
        if (fuel_adc_val > FUEL_MIN_ADC_VAL - ((FUEL_MIN_ADC_VAL - FUEL_10_PERCENT_ADC_VAL) / 3))
        {
            // 0%油量
            fuel_percent = 0;
        }
        else if (fuel_adc_val < (FUEL_10_PERCENT_ADC_VAL + (FUEL_MIN_ADC_VAL - FUEL_10_PERCENT_ADC_VAL) / 3) &&
                 fuel_adc_val > FUEL_10_PERCENT_ADC_VAL - (FUEL_10_PERCENT_ADC_VAL - FUEL_20_PERCENT_ADC_VAL) / 3)
        {
            // 10%油量
            fuel_percent = 10;
        }
        else if (fuel_adc_val < (FUEL_20_PERCENT_ADC_VAL + (FUEL_10_PERCENT_ADC_VAL - FUEL_20_PERCENT_ADC_VAL) / 3) &&
                 fuel_adc_val > FUEL_20_PERCENT_ADC_VAL - (FUEL_20_PERCENT_ADC_VAL - FUEL_30_PERCENT_ADC_VAL) / 3)
        {
            // 20%油量
            fuel_percent = 20;
        }
        else if (fuel_adc_val < (FUEL_30_PERCENT_ADC_VAL + (FUEL_20_PERCENT_ADC_VAL - FUEL_30_PERCENT_ADC_VAL) / 3) &&
                 fuel_adc_val > FUEL_30_PERCENT_ADC_VAL - (FUEL_30_PERCENT_ADC_VAL - FUEL_40_PERCENT_ADC_VAL) / 3)
        {
            // 30%油量
            fuel_percent = 30;
        }
        else if (fuel_adc_val < (FUEL_40_PERCENT_ADC_VAL + (FUEL_30_PERCENT_ADC_VAL - FUEL_40_PERCENT_ADC_VAL) / 3) &&
                 fuel_adc_val > FUEL_40_PERCENT_ADC_VAL - (FUEL_40_PERCENT_ADC_VAL - FUEL_50_PERCENT_ADC_VAL) / 3)
        {
            // 40%油量
            fuel_percent = 40;
        }
        else if (fuel_adc_val < (FUEL_50_PERCENT_ADC_VAL + (FUEL_40_PERCENT_ADC_VAL - FUEL_50_PERCENT_ADC_VAL) / 3) &&
                 fuel_adc_val > FUEL_50_PERCENT_ADC_VAL - (FUEL_50_PERCENT_ADC_VAL - FUEL_60_PERCENT_ADC_VAL) / 3)
        {
            // 50%油量
            fuel_percent = 50;
        }

        else if (fuel_adc_val < (FUEL_60_PERCENT_ADC_VAL + (FUEL_50_PERCENT_ADC_VAL - FUEL_60_PERCENT_ADC_VAL) / 3) &&
                 fuel_adc_val > FUEL_60_PERCENT_ADC_VAL - (FUEL_60_PERCENT_ADC_VAL - FUEL_70_PERCENT_ADC_VAL) / 3)
        {
            // 60%油量
            fuel_percent = 60;
        }
        else if (fuel_adc_val < (FUEL_70_PERCENT_ADC_VAL + (FUEL_60_PERCENT_ADC_VAL - FUEL_70_PERCENT_ADC_VAL) / 3) &&
                 fuel_adc_val > FUEL_70_PERCENT_ADC_VAL - (FUEL_70_PERCENT_ADC_VAL - FUEL_80_PERCENT_ADC_VAL) / 3)
        {
            // 70%油量
            fuel_percent = 70;
        }
        else if (fuel_adc_val < (FUEL_80_PERCENT_ADC_VAL + (FUEL_70_PERCENT_ADC_VAL - FUEL_80_PERCENT_ADC_VAL) / 3) &&
                 fuel_adc_val > FUEL_80_PERCENT_ADC_VAL - (FUEL_80_PERCENT_ADC_VAL - FUEL_90_PERCENT_ADC_VAL) / 3)
        {
            // 80%油量
            fuel_percent = 80;
        }
        else if (fuel_adc_val < (FUEL_90_PERCENT_ADC_VAL + (FUEL_80_PERCENT_ADC_VAL - FUEL_90_PERCENT_ADC_VAL) / 3) &&
                 fuel_adc_val > FUEL_90_PERCENT_ADC_VAL - (FUEL_90_PERCENT_ADC_VAL - FUEL_MAX_ADC_VAL) / 3)
        {
            // 90%油量
            fuel_percent = 90;
        }
        else if (fuel_adc_val < (FUEL_MAX_ADC_VAL + ((FUEL_90_PERCENT_ADC_VAL - FUEL_MAX_ADC_VAL) / 3)))
        {
            // 100%油量
            fuel_percent = 100;
        }
        else
        {
            // 如果检测到的ad值不在死区范围内,不更新油量
            // flag_is_update_percent = 0;
        }


        // printf("fuel percent %bu\n", fuel_percent);
#ifdef USE_MY_DEBUG
#if USE_MY_DEBUG
        // printf("fuel percent %bu\n", fuel_percent);
#endif // #if USE_MY_DEBUG
#endif // #ifdef USE_MY_DEBUG

        fun_info.fuel = fuel_percent;
        fuel_adc_val = 0xFF;
        flag_get_fuel = 1;
    } // if (fuel_capacity_scan_cnt >= FUEL_CAPACITY_SCAN_TIME_MS)
}
