/******************************************************************
*   ��    ��    ��xiaoqinxing
*   ��������    ��log��ӡ�ȼ�ʵ��
*   ʹ��˵��    ��
******************************************************************/
#ifndef _DEBUG_H_
#define _DEBUG_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "stdarg.h"
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

typedef enum {
    MAIN_MODULE = 0,
    SUB_MODULE1,
    SUB_MODULE2,
    MAX_MODULE
}debug_module_t;

typedef struct {
    debug_level_t  level;
    const char     *name;
} module_debug_t;

/******************************************************************
@brief   : ģ���ӡ�궨��
@author  : xiaoqinxing
@input   ��none
@output  ��none
@detail  : 
����һ��д����#define LOGE(fmt, args...) \
    LOG(MAIN_MODULE, DBG_ERR,  fmt, ##args)
ʵ��֤�����У������ڸ�ͨ�������ǿ��Ա���ģ����ܺͱ�������й�
******************************************************************/

#define LOG(module, level, fmt, ...)  \
    debug_print(module, level, __func__, __LINE__, fmt, __VA_ARGS__);

#define LOGE(fmt, ...) LOG(MAIN_MODULE, DBG_ERR,  fmt, __VA_ARGS__)
#define LOGW(fmt, ...) LOG(MAIN_MODULE, DBG_WARN, fmt, __VA_ARGS__)
#define LOGH(fmt, ...) LOG(MAIN_MODULE, DBG_HIGH, fmt, __VA_ARGS__)
#define LOGD(fmt, ...) LOG(MAIN_MODULE, DBG_DEBUG,fmt, __VA_ARGS__)
#define LOGL(fmt, ...) LOG(MAIN_MODULE, DBG_LOW,  fmt, __VA_ARGS__)
#define LOGI(fmt, ...) LOG(MAIN_MODULE, DBG_INFO, fmt, __VA_ARGS__)


#ifdef __cplusplus
}
#endif

#endif
