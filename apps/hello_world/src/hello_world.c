#include "stdio.h"
#include "logprint.h"
#include "version.h"
void main()
{
    LOGE("hello world %s\n", "haha");
    LOGE("OK");
    version_print();
    printf("hello world\n");
    return;
}