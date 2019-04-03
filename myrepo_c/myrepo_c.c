#include "pch.h"
#include "app.h"
int main()
{
    while (1) {
        int test_state = 0;
        LOGE("\r\n«Î ‰»Î≤‚ ‘≥Ã–Ú–Ú∫≈£∫");
        scanf_s("%d", &test_state, 2);
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
            default:
                LOGE("≥¨≥ˆ∑∂Œß");
                break;
        }
    }
}