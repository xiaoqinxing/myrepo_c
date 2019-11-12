/******************************************************************
*   作    者    ：xiaoqinxing
*   功能描述    ：功能函数实例
*   使用说明    ：
******************************************************************/
#include "pch.h"
#include "app.h"
#include "pthread.h"

void test1_mem_alloc() {
    LOGE("测试程序");
    Invrec *a;
    /*
    **注意了，由于动态分配的内存需要释放，如果将这个指针进行了运算
    **free的时候就会出问题，另外如果运算了，其他地方进行引用，也容易
    **出现找错内存块的问题。
    */
    a = create_subassy_record(3);
    //将参与运算的指针保护起来。
    SUBASSYPART *new_part = a->info.subassy->part;
    strcpy(new_part->partno, "hello world");
    printf("%p\r\n", new_part);
    new_part++;
    strcpy(new_part->partno, "this is my");
    printf("%p\r\n", new_part);
    new_part++;
    //注意此处如果拷贝的数据超过数组长度，内存溢出
    strcpy(new_part->partno, "first function");
    printf("%p\r\n", new_part);
    printf("%s\r\n", new_part->partno);
    //注意这里的a没有被释放，因为他是在函数中调用free
    //只是对a的拷贝进行了修改
    //discard_inventory_record(a);
    discard_inventory_record(&a);
    printf("回收后的地址%p\r\n", a);
    //注意这里如果引用释放后的指针会出问题
    //如果引用NULL指向的数也会出问题，这些编译器都检查不出来
    //printf("回收后的指针地址2%p\r\n", a->info.subassy);
}

void test2_log_func() {
    LOGE("测试程序");
    version_print();
    LOGE("OK");
    LOGD("%s", "hello");
    SETLOG(MAIN_MODULE, DBG_DEBUG);
    LOGD("%s", "hello2");
    LOGI("%s", "DSFASDJKHFKL ASHJDLFIHKSDFDSLKAJFKLJASDLKJFK");
    uint32_t a = 10, b = 11;
    //由于a和b都是无符号整数，相减之后还是无符号整数，肯定是大于等于0的
    //因此这个地方是有问题的，需要注意，最好写成if(a>b)
    if (a - b >= 0)
        LOGE("a = %d,b = %d,但a - b却判断为 > 0", a, b);
    LOGE("如果直接对a-b打印：%d，但是", a - b);
}

/******************************************************************
@brief   : 动态内存模板测试程序
@author  : xiaoqinxing
@input   ：none
@output  ：none
@detail  : none
******************************************************************/
typedef struct {
    BufferContext mem;
    int rc;
}IntBufferContext;

//注意这里形参传入的是BufferContext,因为这里只是指向的地址
static int MyDoubleTest(BufferContext *pBuf) {
    IntBufferContext *p = (IntBufferContext *)pBuf;
    int a = 10;
    pBuf->pBuf = &a;
    //对void类型指针操作，首先要强制类型转换
    p->rc = *(int*)(p->mem.pBuf)*2;
}

void test3_mem_templet_func() {
    LOGE("测试程序");
    int p;
    IntBufferContext membuffer = {{ NULL,sizeof(int),MyDoubleTest }, 0};
    //注意这里传入的是IntBufferContext
    MemBuffer(&membuffer);
    LOGE("%d", membuffer.rc);
}

/******************************************************************
@brief   : 文件操作模板测试程序
@author  : xiaoqinxing
@input   ：文件名（加路径）
@output  ：文件大小
@detail  : none
******************************************************************/
//这里的SizeGetContext可以看做是继承了FileAccessorContext;并增加了
//一个返回值
typedef struct {
    FileAccessorContext base;
    long size;
}SizeGetContext;

static long file_size(FileAccessorContext *p, FILE *fp) {
    SizeGetContext *pThis = (SizeGetContext *)p;
    pThis->size = -1;
    if (fseek(fp, 0, SEEK_END) == 0)
        pThis->size = ftell(fp);
}

void test4_size_read_func() {
    char filename[50];
    LOGE("测试程序");
    LOGE("请输入文件名：");
    scanf_s("%s", filename, 50);
    SizeGetContext ctx = { {filename,"rb",file_size},0 };
    if (!FileAccess(&ctx)) {
        LOGE("文件长度为%d个字节", ctx.size);
    }
    else
        perror("ERROR:");
}
/******************************************************************
@brief   : 单链表实现动态堆栈
@author  : xiaoqinxing
@input   ：none
@output  ：none
@detail  : none
******************************************************************/
void test5_stack_func() {
    Stack *tmp = create_stack();
    LOGE("创建一个堆栈，并判断是否为空-%d", tmp->is_empty(tmp));
    tmp->set_length(tmp, 3);
    LOGE("设置堆栈长度为3");
    for (int j = 0; j < 2; j++) {
        for (int i = 0; i < 6; i++) {
            tmp->push(tmp, i);
            LOGE("after push,top is %d", tmp->top(tmp));
        }
        for (int i = 0; i < 5; i++) {
            LOGE("pop time:%d value = %d", i + 1, tmp->pop(tmp));
        }
    }
    destroy_stack(tmp);
    LOGE("销毁堆栈后堆栈指针为%p", tmp);
}
/******************************************************************
@brief   : 单链表实现队列
@author  : xiaoqinxing
@input   ：none
@output  ：none
@detail  : none
******************************************************************/
void test6_queue_func() {
    Queue *tmp = create_queue();
    LOGE("创建一个队列，并判断是否为空-%d", tmp->is_empty(tmp));
    tmp->set_length(tmp, 5);
    LOGE("设置队列长度为5");
    for (int j = 0; j < 2; j++) {
        for (int i = 0; i < 10; i++) {
            LOGE("enqueue:%d", i);
            tmp->enqueue(tmp, i);
        }
        for (int i = 0; i < 8; i++) {
            LOGE("dequeue time:%d value = %d", i + 1, tmp->dequeue(tmp));
        }
    }
    destroy_queue(tmp);
    LOGE("销毁队列后队列指针为%p", tmp);
}
/******************************************************************
@brief   : 文件拷贝模板实例
@author  : xiaoqinxing
@input   ：none
@output  ：none
@detail  : 如果多次进行资源的处理，比如先获取资源大小，申请内存，再
           读取，需要打开文件两次，可以将大小存在SizeGetContext中，
           又叫上下文。将打开文件的操作分离，放在process之中
******************************************************************/
