/******************************************************************
*   作    者    ：xiaoqinxing
*   功能描述    ：
*   使用说明    ：
******************************************************************/
#ifndef  __CMD_THREAD_H_
#define  __CMD_THREAD_H_

#ifdef __cplusplus
extern "C" {
#endif
#include "pch.h"
#include "pthread.h"
#include "queue.h"
typedef enum
{
    CMD_TYPE_NONE = -1,
    CMD_TYPE_START_DATA_PROC,
    CMD_TYPE_STOP_DATA_PROC,
    CMD_TYPE_DO_NEXT_JOB,
    CMD_TYPE_EXIT,
    CMD_TYPE_TIMEOUT,
    CMD_TYPE_MAX
} cmd_type_t;

//为什么这里要加一个struct定义？
typedef struct {
    cmd_type_t cmd;
} cmd_t;

typedef struct {
    int val;
    pthread_mutex_t mutex;
    pthread_cond_t cond;
} cmd_semaphore_t;

typedef struct CmdThread
{
    int32_t (*launch)(struct CmdThread *cmd_thread_obj, void *(*start_routine)(void *), void* user_data);
    int32_t (*setName)(struct CmdThread *cmd_thread_obj, const char* name);
    int32_t (*sendCmd)(struct CmdThread *cmd_thread_obj, cmd_type_t cmd, uint8_t sync_cmd, uint8_t priority);
    cmd_type_t (*getCmd)(struct CmdThread *cmd_thread_obj);
    Queue *cmd_queue;             /* cmd queue */
    pthread_t cmd_pid;           /* cmd thread ID */
    cmd_semaphore_t cmd_sem;     /* semaphore for cmd thread */
    cmd_semaphore_t sync_sem;    /* semaphore for synchronized call signal */
}CmdThread;

void cmd_sem_init(cmd_semaphore_t *s, int n);
void cmd_sem_post(cmd_semaphore_t *s);
int cmd_sem_wait(cmd_semaphore_t *s);
void cmd_sem_destroy(cmd_semaphore_t *s);

CmdThread *CmdThreadInit(void);
int32_t CmdThreadLaunch(struct CmdThread *cmd_thread_obj, void *(*start_routine)(void *), void* user_data);
int32_t CmdThreadExit(struct CmdThread *cmd_thread_obj);
int32_t CmdThreadSendCmd(struct CmdThread *cmd_thread_obj, cmd_type_t cmd, uint8_t sync_cmd, uint8_t priority);
cmd_type_t CmdThreadGetCmd(struct CmdThread *cmd_thread_obj);


#ifdef __cplusplus
}
#endif

#endif
