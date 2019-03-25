/******************************************************************
*   ��    ��    ��xiaoqinxing
*   ��������    ��debug����
*   ʹ��˵��    ��
******************************************************************/
#include "pch.h"
#include "debug.h"

module_debug_t debug_level[MAX_MODULE] = { 
    {DBG_ERR,"<MAIN>"},
    {DBG_ERR,"<SUB1>"},
    {DBG_ERR,"<SUB2>"},
};
static char log_buffer[DBG_MAX_STR_LEN] = { 0 };
/******************************************************************
@brief   : ��ӡ�ȼ�����
@author  : xiaoqinxing
@input   ����Ҫ���õ�ģ�鼰���ӡ�ȼ�
@output  ��none
@detail  : none
******************************************************************/

void debug_level_set(debug_module_t module, debug_level_t level) {
    switch (module)
    {
        case MAIN_MODULE:
            debug_level[MAIN_MODULE].debug_level = level;
        break;
        case SUB_MODULE1:
            debug_level[SUB_MODULE1].debug_level = level;
        break;
        case SUB_MODULE2:
            debug_level[SUB_MODULE1].debug_level = level;
        break;
    default:
        break;
    }
}

/******************************************************************
@brief   : �Դ���Ĳ������д�ӡ��ͬʱ��ֹ������ӡbuffer�ĳ���
@author  : xiaoqinxing
@input   ��buffer pointer/size/pfmt/argptr
@output  ��none
@detail  : �������buffer���ȣ�����ȡǰ��һ����д��buffer
******************************************************************/

static void log_vsnprintf(char* pdst, unsigned int size,
    const char* pfmt, va_list argptr) {
    int num_chars_written = 0;

    pdst[0] = '\0';
    num_chars_written = vsnprintf(pdst, size, pfmt, argptr);

    if ((num_chars_written >= (int)size) && (size > 0)) {
        /* Message length exceeds the buffer limit size */
        num_chars_written = size - 1;
        pdst[size - 1] = '\0';
    }
}
/******************************************************************
@brief   : ����ģ�鼰�ȼ����д�ӡ
@author  : xiaoqinxing
@input   ��ģ�飬��ӡ�ȼ����ַ���
@output  ��none
@detail  : none
******************************************************************/

void debug_print(const debug_module_t module, const debug_level_t level,
    const char *func, const int line, const char * format, ...) {
    va_list args;          // ��������б����
    va_start(args, format);
    log_vsnprintf(log_buffer, DBG_MAX_STR_LEN, format, args);
    va_end(args);
    printf("%s [%s] %d: %s\n", \
        debug_level[module].name, func, line, log_buffer);
}
