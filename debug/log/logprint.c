/******************************************************************
*   作    者    ：xiaoqinxing
*   功能描述    ：debug调试
*   使用说明    ：
******************************************************************/
#include "logprint.h"

module_debug_t debug_level[MAX_MODULE] = {
    {DBG_ERR, "MAIN"},
    {DBG_ERR, "LEAK"},
    {DBG_ERR, "COMMON"},
};

static char log_buffer[DBG_MAX_STR_LEN] = {0};
/******************************************************************
@brief   : 打印等级设置
@author  : xiaoqinxing
@input   ：需要设置的模块及其打印等级
@output  ：none
@detail  : none
******************************************************************/
void debug_level_set(debug_module_t module, debug_level_t level)
{
    debug_level[module].debug_level = level;
    return;
}

/******************************************************************
@brief   : 对传入的参数进行打印，同时防止超出打印buffer的长度
@author  : xiaoqinxing
@input   ：buffer pointer/size/pfmt/argptr
@output  ：none
@detail  : 如果超出buffer长度，则会截取前面一部分写入buffer
******************************************************************/
static void log_vsnprintf(char *pdst, unsigned int size,
                          const char *pfmt, va_list argptr)
{
    int num_chars_written = 0;

    pdst[0] = '\0';
    num_chars_written = vsnprintf(pdst, size, pfmt, argptr);

    if ((num_chars_written >= (int)size) && (size > 0))
    {
        /* Message length exceeds the buffer limit size */
        num_chars_written = size - 1;
        pdst[size - 1] = '\0';
    }
}
/******************************************************************
@brief   : 根据模块及等级进行打印
@author  : xiaoqinxing
@input   ：模块，打印等级，字符串
@output  ：none
@detail  : none
******************************************************************/

void debug_print(const debug_module_t module, const debug_level_t level,
                 const char *func, const int line, const char *format, ...)
{
    va_list args; // 申请参数列表变量
    va_start(args, format);
    log_vsnprintf(log_buffer, DBG_MAX_STR_LEN, format, args);
    va_end(args);
    printf("%s %s [%s] %d: %s\n",
           debug_level[module].name, level_to_str[level], func, line, log_buffer);
}
