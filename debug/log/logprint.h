/******************************************************************
*   作    者    ：xiaoqinxing
*   功能描述    ：log打印等级实现
*   使用说明    ：
******************************************************************/
#ifndef _DEBUG_H_
#define _DEBUG_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "stdarg.h"
#include "stdio.h"
#define DBG_MAX_STR_LEN 64

typedef enum {
    DBG_NONE  = 0,
    DBG_ERR   = 1,
    DBG_WARN  = 2,
    DBG_HIGH  = 3,
    DBG_DEBUG = 4,
    DBG_LOW   = 5,
    DBG_INFO  = 6
}debug_level_t;

static const char *level_to_str[] = {
    "",        /* DBG_NONE  */
    "<E>", /* DBG_ERR   */
    "<W>", /* DBG_WARN  */
    "<H>", /* DBG_HIGH  */
    "<D>", /* DBG_DEBUG */
    "<L>", /* DBG_LOW   */
    "<I>"  /* DBG_INFO  */
};
typedef enum {
    MAIN_MODULE = 0,
    LEAK_DEBUG_MODULE,
    COMMON_MODULE,
    MAX_MODULE
}debug_module_t;

typedef struct {
    debug_level_t  debug_level;
    const char     *name;
} module_debug_t;

/******************************************************************
@brief   : 模块打印宏定义
@author  : xiaoqinxing
@input   ：none
@output  ：none
@detail  : 
另有一种写法是#define LOGE(fmt, args...) \
    LOG(MAIN_MODULE, DBG_ERR,  fmt, ##args)
实验证明不行，但是在高通代码中是可以编译的，可能和编译规则有关
将判断放在函数之前，可以减少为打印函数分配栈的时间和空间
******************************************************************/
extern module_debug_t debug_level[MAX_MODULE];

#define LOG(module, level, fmt, args...)                                       \
{                                                                          \
    if (debug_level[module].debug_level >= level) {                        \
        debug_print(module, level, __func__, __LINE__, fmt, ##args);  \
    }                                                                      \
}
#define LOGE(module, fmt, args...) LOG(module, DBG_ERR,  fmt, ##args)
#define LOGW(module, fmt, args...) LOG(module, DBG_WARN, fmt, ##args)
#define LOGH(module, fmt, args...) LOG(module, DBG_HIGH, fmt, ##args)
#define LOGD(module, fmt, args...) LOG(module, DBG_DEBUG,fmt, ##args)
#define LOGL(module, fmt, args...) LOG(module, DBG_LOW,  fmt, ##args)
#define LOGI(module, fmt, args...) LOG(module, DBG_INFO, fmt, ##args)

#define ALOGE(fmt, args...) LOG(MAIN_MODULE, DBG_ERR,  fmt, ##args)
#define ALOGW(fmt, args...) LOG(MAIN_MODULE, DBG_WARN, fmt, ##args)
#define ALOGH(fmt, args...) LOG(MAIN_MODULE, DBG_HIGH, fmt, ##args)
#define ALOGD(fmt, args...) LOG(MAIN_MODULE, DBG_DEBUG,fmt, ##args)
#define ALOGL(fmt, args...) LOG(MAIN_MODULE, DBG_LOW,  fmt, ##args)
#define ALOGI(fmt, args...) LOG(MAIN_MODULE, DBG_INFO, fmt, ##args)

#define SETLOG(module, level) debug_level_set(module, level)
void debug_print(const debug_module_t module, const debug_level_t level,
                 const char *func, const int line, const char *format, ...);
void debug_level_set(debug_module_t module, debug_level_t level);
void version_print(void);

#ifdef __cplusplus
}
#endif

#endif
