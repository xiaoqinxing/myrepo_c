/******************************************************************
*   ��    ��    ��xiaoqinxing
*   ��������    �����ܺ���ʵ��
*   ʹ��˵��    ��
******************************************************************/
#include "app.h"
#include "pthread.h"
#include "logprint.h"
#include "alloc.h"
#include "queue_utils.h"
#include "string.h"

void test1_mem_alloc() {
    ALOGE("���Գ���");
    Invrec *a;
    /*
    **ע���ˣ����ڶ�̬������ڴ���Ҫ�ͷţ���������ָ�����������
    **free��ʱ��ͻ�����⣬������������ˣ������ط��������ã�Ҳ����
    **�����Ҵ��ڴ������⡣
    */
    a = create_subassy_record(3);
    //�����������ָ�뱣��������
    SUBASSYPART *new_part = a->info.subassy->part;
    strcpy(new_part->partno, "hello world");
    printf("%p\r\n", new_part);
    new_part++;
    strcpy(new_part->partno, "this is my");
    printf("%p\r\n", new_part);
    new_part++;
    //ע��˴�������������ݳ������鳤�ȣ��ڴ����
    strcpy(new_part->partno, "first function");
    printf("%p\r\n", new_part);
    printf("%s\r\n", new_part->partno);
    //ע�������aû�б��ͷţ���Ϊ�����ں����е���free
    //ֻ�Ƕ�a�Ŀ����������޸�
    //discard_inventory_record(a);
    discard_inventory_record(&a);
    printf("���պ�ĵ�ַ%p\r\n", a);
    //ע��������������ͷź��ָ��������
    //�������NULLָ�����Ҳ������⣬��Щ����������鲻����
    //printf("���պ��ָ���ַ2%p\r\n", a->info.subassy);
}

void test2_log_func() {
    ALOGE("���Գ���");
    version_print();
    ALOGE("OK");
    ALOGD("%s", "hello");
    SETLOG(MAIN_MODULE, DBG_DEBUG);
    ALOGD("%s", "hello2");
    ALOGI("%s", "DSFASDJKHFKL ASHJDLFIHKSDFDSLKAJFKLJASDLKJFK");
    uint32_t a = 10, b = 11;
    //����a��b�����޷������������֮�����޷����������϶��Ǵ��ڵ���0��
    //�������ط���������ģ���Ҫע�⣬���д��if(a>b)
    if (a - b >= 0)
        ALOGE("a = %d,b = %d,��a - bȴ�ж�Ϊ > 0", a, b);
    ALOGE("���ֱ�Ӷ�a-b��ӡ��%d������", a - b);
}

/******************************************************************
@brief   : ��̬�ڴ�ģ����Գ���
@author  : xiaoqinxing
@input   ��none
@output  ��none
@detail  : none
******************************************************************/
typedef struct {
    BufferContext mem;
    int rc;
}IntBufferContext;

//ע�������βδ������BufferContext,��Ϊ����ֻ��ָ��ĵ�ַ
void MyDoubleTest(BufferContext *pBuf) {
    IntBufferContext *p = (IntBufferContext *)pBuf;
    int a = 10;
    pBuf->pBuf = &a;
    //��void����ָ�����������Ҫǿ������ת��
    p->rc = *(int*)(p->mem.pBuf)*2;
}

void test3_mem_templet_func() {
    ALOGE("���Գ���");
    int p;
    IntBufferContext membuffer = {{ NULL,sizeof(int),MyDoubleTest }, 0};
    //ע�����ﴫ�����IntBufferContext
    MemBuffer((BufferContext*)&membuffer);
    ALOGE("%d", membuffer.rc);
}

/******************************************************************
@brief   : �ļ�����ģ����Գ���
@author  : xiaoqinxing
@input   ���ļ�������·����
@output  ���ļ���С
@detail  : none
******************************************************************/
//�����SizeGetContext���Կ����Ǽ̳���FileAccessorContext;��������
//һ������ֵ
typedef struct {
    FileAccessorContext base;
    long size;
}SizeGetContext;

void file_size(FileAccessorContext *p, FILE *fp) {
    SizeGetContext *pThis = (SizeGetContext *)p;
    pThis->size = -1;
    if (fseek(fp, 0, SEEK_END) == 0)
        pThis->size = ftell(fp);
}

void test4_size_read_func() {
    char filename[50];
    ALOGE("���Գ���");
    ALOGE("�������ļ�����");
    scanf("%s", filename);
    SizeGetContext ctx = { {filename,"rb",file_size},0 };
    if (!FileAccess((FileAccessorContext*)&ctx)) {
        ALOGE("�ļ�����Ϊ%d���ֽ�", ctx.size);
    }
    else
        perror("ERROR:");
}
/******************************************************************
@brief   : ������ʵ�ֶ�̬��ջ
@author  : xiaoqinxing
@input   ��none
@output  ��none
@detail  : none
******************************************************************/
void test5_stack_func() {
    Stack *tmp = create_stack();
    ALOGE("����һ����ջ�����ж��Ƿ�Ϊ��-%d", tmp->is_empty(tmp));
    tmp->set_length(tmp, 3);
    ALOGE("���ö�ջ����Ϊ3");
    for (int j = 0; j < 2; j++) {
        for (int i = 0; i < 6; i++) {
            tmp->push(tmp, i);
            ALOGE("after push,top is %d", tmp->top(tmp));
        }
        for (int i = 0; i < 5; i++) {
            ALOGE("pop time:%d value = %d", i + 1, tmp->pop(tmp));
        }
    }
    destroy_stack(tmp);
    ALOGE("���ٶ�ջ���ջָ��Ϊ%p", tmp);
}
/******************************************************************
@brief   : ������ʵ�ֶ���
@author  : xiaoqinxing
@input   ��none
@output  ��none
@detail  : none
******************************************************************/
void test6_queue_func() {
    Queue *tmp = create_queue();
    ALOGE("����һ�����У����ж��Ƿ�Ϊ��-%d", tmp->is_empty(tmp));
    tmp->set_length(tmp, 5);
    ALOGE("���ö��г���Ϊ5");
    for (int j = 0; j < 2; j++) {
        for (int i = 0; i < 10; i++) {
            ALOGE("enqueue:%d", i);
            tmp->enqueue(tmp, i);
        }
        for (int i = 0; i < 8; i++) {
            ALOGE("dequeue time:%d value = %d", i + 1, tmp->dequeue(tmp));
        }
    }
    destroy_queue(tmp);
    ALOGE("���ٶ��к����ָ��Ϊ%p", tmp);
}
/******************************************************************
@brief   : �ļ�����ģ��ʵ��
@author  : xiaoqinxing
@input   ��none
@output  ��none
@detail  : �����ν�����Դ�Ĵ��������Ȼ�ȡ��Դ��С�������ڴ棬��
           ��ȡ����Ҫ���ļ����Σ����Խ���С����SizeGetContext�У�
           �ֽ������ġ������ļ��Ĳ������룬����process֮��
******************************************************************/

/******************************************************************
@brief   : ��Ϣ����ʵ��
@author  : xiaoqinxing
@input   ��none
@output  ��none
@detail  : 1. enqueue��dequeue�洢�Ķ�������ָ�룬��������ʵ������
              ���ÿ��ȡ�����ݣ�ע���ͷţ�
           2. flush���ʣ�µ�û���ͷŵ����ݶ��ͷŵ�����˱��붨���ͷŻص�����
           3. ÿ��flush֮�������Ҫʹ�ã���Ҫ����init
******************************************************************/
void release_data(void* data, void *user_data){
    FREE(data);
}

void test_queue_utils_func(){
    QueueUtils *tmp = new QueueUtils(release_data,nullptr);
    int *input,*output;
    ALOGE("����һ�����У����ж��Ƿ�Ϊ��-%d", tmp->isEmpty());
    for (int j = 0; j < 2; j++) {
        for (int i = 0; i < 100; i++) {
            ALOGE("enqueue:%d", i);
            input = MALLOC(1,int);
            *input = i;
            tmp->enqueue(input);
        }
        for (int i = 0; i < 80; i++) {
            output = (int*)(tmp->dequeue(false));
            ALOGE("dequeue time:%d value = %d", i + 1, *output);
            FREE(output);
        }
    }
    ALOGE("dequeue len = %d", tmp->getCurrentSize());
    tmp->flush();
    ALOGE("dequeue len = %d", tmp->getCurrentSize());
    tmp->init();
    for (int j = 0; j < 2; j++) {
        for (int i = 0; i < 100; i++) {
            ALOGE("enqueue:%d", i);
            input = MALLOC(1,int);
            *input = i;
            tmp->enqueue(input);
        }
        for (int i = 0; i < 80; i++) {
            output = (int*)(tmp->dequeue(false));
            ALOGE("dequeue time:%d value = %d", i + 1, *output);
            FREE(output);
        }
    }
    delete tmp;
    ALOGE("���ٶ��к����ָ��Ϊ%p", tmp);
}