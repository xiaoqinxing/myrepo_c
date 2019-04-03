/******************************************************************
*   ��    ��    ��xiaoqinxing
*   ��������    �����ܺ���ʵ��
*   ʹ��˵��    ��
******************************************************************/
#include "pch.h"
#include "app.h"
#include "invendor.h"
#include "stack.h"
void test1_mem_alloc() {
    LOGE("���Գ���");
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
    LOGE("���Գ���");
    version_print();
    LOGE("OK");
    LOGD("%s", "hello");
    SETLOG(MAIN_MODULE, DBG_DEBUG);
    LOGD("%s", "hello2");
    LOGI("%s", "DSFASDJKHFKL ASHJDLFIHKSDFDSLKAJFKLJASDLKJFK");
    uint32_t a = 10, b = 11;
    //����a��b�����޷������������֮�����޷����������϶��Ǵ��ڵ���0��
    //�������ط���������ģ���Ҫע�⣬���д��if(a>b)
    if (a - b >= 0)
        LOGE("a = %d,b = %d,��a - bȴ�ж�Ϊ > 0", a, b);
    LOGE("���ֱ�Ӷ�a-b��ӡ��%d������", a - b);
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
static int MyDoubleTest(BufferContext *pBuf) {
    IntBufferContext *p = (IntBufferContext *)pBuf;
    int a = 10;
    pBuf->pBuf = &a;
    //��void����ָ�����������Ҫǿ������ת��
    p->rc = *(int*)(p->mem.pBuf)*2;
}

void test3_mem_templet_func() {
    LOGE("���Գ���");
    int p;
    IntBufferContext membuffer = {{ NULL,sizeof(int),MyDoubleTest }, 0};
    //ע�����ﴫ�����IntBufferContext
    MemBuffer(&membuffer);
    LOGE("%d", membuffer.rc);
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

static long file_size(FileAccessorContext *p, FILE *fp) {
    SizeGetContext *pThis = (SizeGetContext *)p;
    pThis->size = -1;
    if (fseek(fp, 0, SEEK_END) == 0)
        pThis->size = ftell(fp);
}

void test4_size_read_func() {
    char filename[50];
    LOGE("���Գ���");
    LOGE("�������ļ�����");
    scanf_s("%s", filename, 50);
    SizeGetContext ctx = { {filename,"rb",file_size},0 };
    if (!FileAccess(&ctx)) {
        LOGE("�ļ�����Ϊ%d���ֽ�", ctx.size);
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
    LOGE("����һ����ջ�����ж��Ƿ�Ϊ��-%d", tmp->is_empty(tmp));
    tmp->push(tmp, 1);
    LOGE("PUSH 1:%d", tmp->top(tmp));
    tmp->push(tmp, 2);
    LOGE("PUSH 2:%d", tmp->top(tmp));
    tmp->pop(tmp);
    LOGE("POP:%d", tmp->top(tmp));
    destroy_stack(tmp);
    LOGE("%p", tmp);
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
