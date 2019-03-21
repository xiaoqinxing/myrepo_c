/******************************************************************
*   作    者    ：xiaoqinxing
*   功能描述    ：版本信息控制
*   使用说明    ：
******************************************************************/
#include "pch.h"
#include "stdlib.h"


/******************************************************************
@brief   : 版本信息
@author  : xiaoqinxing
@input   ：none
@output  ：none
@detail  : none
******************************************************************/
void version_print(void)
{
    uint8_t year[5] = { '\0' };
    uint8_t mon[3] = { '\0' };
    uint8_t day[3] = { '\0' };

    uint8_t firmware_year = 0;
    uint8_t firmware_mon = 0;
    uint8_t firmware_day = 0;
    year[0] = BUILD_YEAR_CH2;
    year[1] = BUILD_YEAR_CH3;

    mon[0] = BUILD_MONTH_CH0;
    mon[1] = BUILD_MONTH_CH1;

    day[0] = BUILD_DAY_CH0;
    day[1] = BUILD_DAY_CH1;

    printf("Version :%s\r\n", FUZZER_VERSION);
    printf("Compile time: %s-%s-%s\r\n", year, mon, day);
}