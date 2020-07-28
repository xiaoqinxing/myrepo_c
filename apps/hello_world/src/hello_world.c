#include "stdio.h"
#include "logprint.h"
void main()
{
    LOGE(MAIN_MODULE, "hello world %s", "haha");
    LOGE(LEAK_DEBUG_MODULE, "OK");
    ALOGH("let's printf some log");
    version_print();
    printf("hello world\n");
    return;
}