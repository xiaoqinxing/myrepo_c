#include "app.h"
#include "logprint.h"

int main()
{
    while (1) {
        int test_state = 0;
        ALOGE("\r\n��������Գ�����ţ�");
        scanf("%d", &test_state);
        if (test_state == 0)
            exit(0);
        switch (test_state) {
            case 1:
                test1_mem_alloc();
                break;
            case 2:
                test2_log_func();
                break;
            case 3:
                test3_mem_templet_func();
                break;
            case 4:
                test4_size_read_func();
                break;
            case 5:
                test5_stack_func();
                break;
            case 6:
                test6_queue_func();
                break;
            case 7:
                test_queue_utils_func();
                break;
            default:
                ALOGE("������Χ");
                break;
        }
    }
}