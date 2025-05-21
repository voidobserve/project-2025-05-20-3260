#include "battery.h"

//

// 将ad值转换为对应的电压值
// arg_adc_val ： ad值
u8 conver_adc_val_to_voltage(u16 arg_adc_val)
{
    /*
        采集到的ad值范围：0~4095
        ad值对应的电压： 0 ~ MAX_VOLTAGE_OF_BATTERY
        那么 每单位ad值对应 MAX_VOLTAGE_OF_BATTERY / 4096
    */
    return (u32)arg_adc_val * MAX_VOLTAGE_OF_BATTERY / 4096;
}

// 将电池电压转换为对应的百分比
// voltage： 0~255 ， 对应0~25.5V
u8 conver_voltage_of_battery_to_percentage(u8 voltage)
{
    // 用电池电压voltage除以MAX_VOLTAGE_OF_BATTERY，得到占比，再乘以100，得到百分比
    u32 tmp = voltage * 100 / MAX_VOLTAGE_OF_BATTERY;
    if (tmp >= 98)
    {
        // 如果电量百分比大于 98%，当作100%电量处理
        tmp = 100;
    }

    return tmp;
}

void battery_scan(void)
{
    u8 voltage_of_battery = 0;        // 存放电池电压
    u8 cur_percentage_of_battery = 0; // 存放当前电池电量百分比

    static u32 battery_scan_cnt = 0; // 记录电池电压扫描次数
    static u32 battery_scan_time_cnt = 0; // 电池扫描时间计时
    static u32 battery_val = 0; // 累加每次采集到的ad值，到了电池扫描时间时，直接求平均值

    adc_sel_pin(ADC_PIN_BATTERY);
    battery_val += adc_getval(); // 可能要防止计数溢出
    battery_scan_cnt++;
    battery_scan_time_cnt += ONE_CYCLE_TIME_MS;
    if (battery_scan_time_cnt >= BATTERY_SCAN_UPDATE_TIME_MS)
    {
        battery_val /= battery_scan_cnt; // 取平均数
        voltage_of_battery = conver_adc_val_to_voltage(battery_val);
        cur_percentage_of_battery = conver_voltage_of_battery_to_percentage(voltage_of_battery);
        battery_val = 0;           // 清空数值
        battery_scan_cnt = 0;      // 清空计数值
        battery_scan_time_cnt = 0; // 清空时间计数值

        fun_info.battery = cur_percentage_of_battery;
        fun_info.voltage_of_battery = voltage_of_battery;

#ifdef USE_MY_DEBUG
#if USE_MY_DEBUG

        // printf("cur voltage of battery : \n");

#endif
#endif

        flag_get_voltage_of_battery = 1;
        flag_get_battery = 1;
    }
}