/******************************************************************
*   作    者    ：xiaoqinxing
*   功能描述    ：提供一个稳定的，可以用作消息队列的数据结构，考虑了多线程的影响
*   使用说明    ：参考高通代码
******************************************************************/
#ifndef __QUEUE_UTILS_H__
#define __QUEUE_UTILS_H__
#include "pthread.h"
// Camera dependencies
#include "list_utils.h"
/**
 * 自定义查找队列中是否有数据匹配的函数
 * 用于仅刷新特定节点，或者仅dequeue特定节点
 */
typedef bool (*match_fn_data)(void *data, void *user_data, void *match_data);

/**
 * 内存释放函数回调
 * 将data进行释放的回调函数
 * user_data一般是进行函数调用的(可选)
 */
typedef void (*release_data_fn)(void* data, void *user_data);

/**
 * 匹配函数回调
 * 判断*data以及*user_data是否和某个特定的数匹配
 * 仅用于刷新特定节点上
 */
typedef bool (*match_fn)(void *data, void *user_data);

class QueueUtils {
public:
    QueueUtils();
    //这个用户数据有什么用？
    QueueUtils(release_data_fn data_rel_fn, void *user_data);
    virtual ~QueueUtils();
    void init();
    bool enqueue(void *data);
    bool enqueueWithPriority(void *data);
    /* This call will put queue into uninitialized state.
     * Need to call init() in order to use the queue again */
    void flush();
    void flushNodes(match_fn match);
    void flushNodes(match_fn_data match, void *spec_data);
    //需要注意dequeue的时候输出的是个指针，如果那个值被销毁了就很危险，或者被篡改了就不是原来的值了
    void* dequeue(bool bFromHead = true);
    void* dequeue(match_fn_data match, void *spec_data);
    void* peek();
    bool isEmpty();
    int getCurrentSize() {return m_size;}
private:
    typedef struct {
        struct list_utils list;
        void* data;
    } camera_q_node;

    camera_q_node m_head; // dummy head
    int m_size;
    bool m_active;
    pthread_mutex_t m_lock;
    release_data_fn m_dataFn;
    void * m_userData;
};

#endif /* __QCAMERA_QUEUE_H__ */
