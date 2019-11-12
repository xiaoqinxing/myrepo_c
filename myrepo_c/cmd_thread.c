/******************************************************************
*   作    者    ：xiaoqinxing
*   功能描述    ：
*   使用说明    ：
******************************************************************/
#include "pch.h"
#include "pthread.h"
#include "cmd_thread.h"
#define CMD_THREAD_QUEUE_LENGTH 10

void cmd_sem_init(cmd_semaphore_t *s, int n)
{
#ifdef SEM_INIT_USE_FUNC
    //用函数的方法初始化
    pthread_condattr_t cond_attr;

    pthread_condattr_init(&cond_attr);
    pthread_condattr_setclock(&cond_attr, CLOCK_MONOTONIC);

    pthread_mutex_init(&(s->mutex), NULL);
    pthread_cond_init(&(s->cond), &cond_attr);
    pthread_condattr_destroy(&cond_attr);
    s->val = n;
#else
    //用宏结构常量初始化
    s->cond = PTHREAD_COND_INITIALIZER;
    s->mutex = PTHREAD_MUTEX_INITIALIZER;
    s->val = n;
#endif
}

//发送信号量
void cmd_sem_post(cmd_semaphore_t *s)
{
    pthread_mutex_lock(&(s->mutex));
    s->val++;
    pthread_cond_signal(&(s->cond));
    pthread_mutex_unlock(&(s->mutex));
}

//等待信号量
int cmd_sem_wait(cmd_semaphore_t *s)
{
    int rc = 0;
    pthread_mutex_lock(&(s->mutex));
    while (s->val == 0)
        rc = pthread_cond_wait(&(s->cond), &(s->mutex));
    s->val--;
    pthread_mutex_unlock(&(s->mutex));
    return rc;
}


/******************************************************************
@brief   : 销毁信号量
@author  : xiaoqinxing
@input   ：none
@output  ：none
@detail  : 注意还需要用FREE将申请的cmd_semaphore_t空间释放。
******************************************************************/
void cmd_sem_destroy(cmd_semaphore_t *s)
{
    pthread_mutex_destroy(&(s->mutex));
    pthread_cond_destroy(&(s->cond));
    s->val = 0;
}


/******************************************************************
@brief   : launch cmd thread
@author  : xiaoqinxing
@input   ：none
@output  ：none
@detail  : 注意函数形参的写法
******************************************************************/
int32_t CmdThreadLaunch(CmdThread *cmd_thread_obj, void *(*start_routine)(void *),
    void* user_data)
{
    /* launch the thread */
    pthread_create(&cmd_thread_obj->cmd_pid,
        NULL,
        start_routine,
        user_data);
    return NO_ERR;
}

/******************************************************************
@brief   : none
@author  : xiaoqinxing
@input   ：dwThreadID = -1,在当前线程下设置名字
@output  ：none
@detail  : none
******************************************************************/
//typedef struct tagTHREADNAME_INFO
//{
//    DWORD dwType; // must be 0x1000
//    LPCSTR szName; // pointer to name (in user addr space)
//    DWORD dwThreadID; // thread ID (-1=caller thread)
//    DWORD dwFlags; // reserved for future use, must be zero
//} THREADNAME_INFO;
//void CmdThreadSetName(DWORD dwThreadID, LPCSTR szThreadName)
//{
//    THREADNAME_INFO info;
//    info.dwType = 0x1000;
//    info.szName = szThreadName;
//    info.dwThreadID = dwThreadID;
//    info.dwFlags = 0;
//
//    __try
//    {
//        RaiseException(0x406D1388, 0, sizeof(info) / sizeof(DWORD), (DWORD*)&info);
//    }
//    __except (EXCEPTION_CONTINUE_EXECUTION)
//    {
//    }
//}


/******************************************************************
@brief   : send a command to the Cmd Thread
@author  : xiaoqinxing
@input   ：cmd     : command to be executed.
           sync_cmd: flag to indicate if this is a synchorinzed cmd. 
           If true, this call will wait until signal is set after the
           command is completed.
           priority: flag to indicate if this is a cmd with priority.
           If true, the cmd will be enqueued to the head with priority.
@output  ：none
@detail  : none
******************************************************************/
int32_t CmdThreadSendCmd(CmdThread *cmd_thread_obj, cmd_type_t cmd,
    uint8_t sync_cmd, uint8_t priority){
    Queue *cmd_queue_tmp = cmd_thread_obj->cmd_queue;
    if (priority) {
        cmd_queue_tmp->enqueueWithPriority(cmd_queue_tmp, cmd);
    }
    else
        cmd_queue_tmp->enqueue(cmd_queue_tmp, cmd);

    cmd_sem_post(&cmd_thread_obj->cmd_sem);

    /* if is a sync call, need to wait until it returns */
    if (sync_cmd) {
        cmd_sem_wait(&cmd_thread_obj->sync_sem);
    }
    return NO_ERR;
}

//获取CmdQueue
cmd_type_t CmdThreadGetCmd(CmdThread *cmd_thread_obj)
{
    return cmd_thread_obj->cmd_queue->dequeue(cmd_thread_obj->cmd_queue);
}

int32_t CmdThreadExit(CmdThread *cmd_thread_obj)
{
    int32_t rc = NO_ERR;

    if (cmd_thread_obj->cmd_pid.p == NULL) {
        return rc;
    }

    rc = cmd_thread_obj->sendCmd(cmd_thread_obj, CMD_TYPE_EXIT, 0, 1);
    if (NO_ERR != rc) {
        LOGE("Error during exit, rc = %d", rc);
        return rc;
    }

    /* wait until cmd thread exits */
    if (pthread_join(cmd_thread_obj->cmd_pid, NULL) != 0) {
        LOGD("pthread dead already\n");
    }
    cmd_thread_obj->cmd_pid.p = NULL;
    FREE(cmd_thread_obj);
    return rc;
}

/******************************************************************
@brief   : cmd thread init
@author  : xiaoqinxing
@input   ：none
@output  ：none
@detail  : none
******************************************************************/
CmdThread *CmdThreadInit(void) {
    CmdThread* cmd_thread_obj = MALLOC(1, CmdThread);
    cmd_thread_obj->cmd_pid.p = NULL;
    cmd_sem_init(&cmd_thread_obj->sync_sem, 0);
    cmd_sem_init(&cmd_thread_obj->cmd_sem, 0);
    cmd_thread_obj->launch = CmdThreadLaunch;
    cmd_thread_obj->sendCmd = CmdThreadSendCmd;
    cmd_thread_obj->getCmd = CmdThreadGetCmd;
    cmd_thread_obj->cmd_queue->set_length(cmd_thread_obj->cmd_queue, 
        CMD_THREAD_QUEUE_LENGTH);
    //cmd_thread_obj->setName = CmdThreadSetName;
}
//延迟工作程序
void *deferredWorkRoutine(void *obj)
{
    int running = 1;
    int ret;
    uint8_t is_active = FALSE;
    int32_t job_status = 0;

    HardwareInterface *pme = (HardwareInterface *)obj;
    CmdThread *cmdThread = &pme->mDeferredWorkThread;
    //cmdThread->setName("CAM_defrdWrk");

    do {
        do {
            ret = cam_sem_wait(&cmdThread->cmd_sem);
            if (ret != 0 && errno != EINVAL) {
                LOGE("cam_sem_wait error (%s)",
                    strerror(errno));
                return NULL;
            }
        } while (ret != 0);

        // we got notified about new cmd avail in cmd queue
        cmd_type_t cmd = cmdThread->getCmd(cmdThread);
        LOGD("cmd: %d", cmd);
        switch (cmd) {
        case CMD_TYPE_START_DATA_PROC:
            LOGH("start data proc");
            is_active = TRUE;
            break;
        case CMD_TYPE_STOP_DATA_PROC:
            LOGH("stop data proc");
            is_active = FALSE;
            // signal cmd is completed
            cam_sem_post(&cmdThread->sync_sem);
            break;
        case CMD_TYPE_DO_NEXT_JOB:
        {
            DefWork *dw =
                reinterpret_cast<DefWork *>(pme->mCmdQueue.dequeue());

            if (NULL == dw) {
                LOGE("Invalid deferred work");
                break;
            }

            switch (dw->cmd) {
            case CMD_DEF_ALLOCATE_BUFF:
            {
                QCameraChannel * pChannel = dw->args.allocArgs.ch;

                if (NULL == pChannel) {
                    LOGE("Invalid deferred work channel");
                    job_status = BAD_VALUE;
                    break;
                }

                cam_stream_type_t streamType = dw->args.allocArgs.type;
                LOGH("Deferred buffer allocation started for stream type: %d",
                    streamType);

                uint32_t iNumOfStreams = pChannel->getNumOfStreams();
                QCameraStream *pStream = NULL;
                for (uint32_t i = 0; i < iNumOfStreams; ++i) {
                    pStream = pChannel->getStreamByIndex(i);

                    if (NULL == pStream) {
                        job_status = BAD_VALUE;
                        break;
                    }

                    if (pStream->isTypeOf(streamType)) {
                        if (pStream->allocateBuffers()) {
                            LOGE("Error allocating buffers !!!");
                            job_status = NO_MEMORY;
                            pme->sendEvtNotify(CAMERA_MSG_ERROR,
                                CAMERA_ERROR_UNKNOWN, 0);
                        }
                        break;
                    }
                }
            }
            break;
            case CMD_DEF_PPROC_START:
            {
                int32_t ret = pme->getDefJobStatus(pme->mInitPProcJob);
                if (ret != NO_ERROR) {
                    job_status = ret;
                    LOGE("PPROC Start failed");
                    pme->sendEvtNotify(CAMERA_MSG_ERROR,
                        CAMERA_ERROR_UNKNOWN, 0);
                    break;
                }
                QCameraChannel * pChannel = dw->args.pprocArgs;
                assert(pChannel);

                if (pme->m_postprocessor.start(pChannel) != NO_ERROR) {
                    LOGE("cannot start postprocessor");
                    job_status = BAD_VALUE;
                    pme->sendEvtNotify(CAMERA_MSG_ERROR,
                        CAMERA_ERROR_UNKNOWN, 0);
                }
            }
            break;
            case CMD_DEF_METADATA_ALLOC:
            {
                int32_t ret = pme->getDefJobStatus(pme->mParamAllocJob);
                if (ret != NO_ERROR) {
                    job_status = ret;
                    LOGE("Metadata alloc failed");
                    pme->sendEvtNotify(CAMERA_MSG_ERROR,
                        CAMERA_ERROR_UNKNOWN, 0);
                    break;
                }
                pme->mMetadataMem = new QCameraMetadataStreamMemory(
                    QCAMERA_ION_USE_CACHE);

                if (pme->mMetadataMem == NULL) {
                    LOGE("Unable to allocate metadata buffers");
                    job_status = BAD_VALUE;
                    pme->sendEvtNotify(CAMERA_MSG_ERROR,
                        CAMERA_ERROR_UNKNOWN, 0);
                }
                else {
                    int32_t rc = pme->mMetadataMem->allocate(
                        dw->args.metadataAllocArgs.bufferCnt,
                        dw->args.metadataAllocArgs.size);
                    if (rc < 0) {
                        delete pme->mMetadataMem;
                        pme->mMetadataMem = NULL;
                    }
                }
            }
            break;
            case CMD_DEF_CREATE_JPEG_SESSION:
            {
                QCameraChannel * pChannel = dw->args.pprocArgs;
                assert(pChannel);

                int32_t ret = pme->getDefJobStatus(pme->mReprocJob);
                if (ret != NO_ERROR) {
                    job_status = ret;
                    LOGE("Jpeg create failed");
                    break;
                }

                if (pme->m_postprocessor.createJpegSession(pChannel)
                    != NO_ERROR) {
                    LOGE("cannot create JPEG session");
                    job_status = UNKNOWN_ERROR;
                    pme->sendEvtNotify(CAMERA_MSG_ERROR,
                        CAMERA_ERROR_UNKNOWN, 0);
                }
            }
            break;
            case CMD_DEF_PPROC_INIT:
            {
                int32_t rc = NO_ERROR;

                jpeg_encode_callback_t jpegEvtHandle =
                    dw->args.pprocInitArgs.jpeg_cb;
                void* user_data = dw->args.pprocInitArgs.user_data;
                QCameraPostProcessor *postProcessor =
                    &(pme->m_postprocessor);
                uint32_t cameraId = pme->mCameraId;
                cam_capability_t *capability =
                    gCamCapability[cameraId];
                cam_padding_info_t padding_info;
                cam_padding_info_t& cam_capability_padding_info =
                    capability->padding_info;

                if (!pme->mJpegClientHandle) {
                    rc = pme->initJpegHandle();
                    if (rc != NO_ERROR) {
                        LOGE("Error!! creating JPEG handle failed");
                        job_status = UNKNOWN_ERROR;
                        pme->sendEvtNotify(CAMERA_MSG_ERROR,
                            CAMERA_ERROR_UNKNOWN, 0);
                        break;
                    }
                }
                LOGH("mJpegClientHandle : %d", pme->mJpegClientHandle);

                rc = postProcessor->setJpegHandle(&pme->mJpegHandle,
                    &pme->mJpegMpoHandle,
                    pme->mJpegClientHandle);
                if (rc != 0) {
                    LOGE("Error!! set JPEG handle failed");
                    job_status = UNKNOWN_ERROR;
                    pme->sendEvtNotify(CAMERA_MSG_ERROR,
                        CAMERA_ERROR_UNKNOWN, 0);
                    break;
                }

                /* get max pic size for jpeg work buf calculation*/
                rc = postProcessor->init(jpegEvtHandle, user_data);

                if (rc != NO_ERROR) {
                    LOGE("cannot init postprocessor");
                    job_status = UNKNOWN_ERROR;
                    pme->sendEvtNotify(CAMERA_MSG_ERROR,
                        CAMERA_ERROR_UNKNOWN, 0);
                    break;
                }

                // update padding info from jpeg
                postProcessor->getJpegPaddingReq(padding_info);
                if (cam_capability_padding_info.width_padding <
                    padding_info.width_padding) {
                    cam_capability_padding_info.width_padding =
                        padding_info.width_padding;
                }
                if (cam_capability_padding_info.height_padding <
                    padding_info.height_padding) {
                    cam_capability_padding_info.height_padding =
                        padding_info.height_padding;
                }
                if (cam_capability_padding_info.plane_padding !=
                    padding_info.plane_padding) {
                    cam_capability_padding_info.plane_padding =
                        mm_stream_calc_lcm(
                            cam_capability_padding_info.plane_padding,
                            padding_info.plane_padding);
                }
                if (cam_capability_padding_info.offset_info.offset_x
                    != padding_info.offset_info.offset_x) {
                    cam_capability_padding_info.offset_info.offset_x =
                        mm_stream_calc_lcm(
                            cam_capability_padding_info.offset_info.offset_x,
                            padding_info.offset_info.offset_x);
                }
                if (cam_capability_padding_info.offset_info.offset_y
                    != padding_info.offset_info.offset_y) {
                    cam_capability_padding_info.offset_info.offset_y =
                        mm_stream_calc_lcm(
                            cam_capability_padding_info.offset_info.offset_y,
                            padding_info.offset_info.offset_y);
                }
            }
            break;
            case CMD_DEF_PARAM_ALLOC:
            {
                int32_t rc = NO_ERROR;
                if (pme->isDualCamera()) {
                    rc = pme->mParameters.allocate(MM_CAMERA_MAX_CAM_CNT);
                }
                else {
                    rc = pme->mParameters.allocate();
                }
                // notify routine would not be initialized by this time.
                // So, just update error job status
                if (rc != NO_ERROR) {
                    job_status = rc;
                    LOGE("Param allocation failed");
                    break;
                }
            }
            break;
            case CMD_DEF_PARAM_INIT:
            {
                int32_t rc = pme->getDefJobStatus(pme->mParamAllocJob);
                if (rc != NO_ERROR) {
                    job_status = rc;
                    LOGE("Param init failed");
                    pme->sendEvtNotify(CAMERA_MSG_ERROR,
                        CAMERA_ERROR_UNKNOWN, 0);
                    break;
                }

                uint32_t camId = pme->mCameraId;
                cam_capability_t * cap = gCamCapability[camId];

                if (pme->mCameraHandle == NULL) {
                    LOGE("Camera handle is null");
                    job_status = BAD_VALUE;
                    pme->sendEvtNotify(CAMERA_MSG_ERROR,
                        CAMERA_ERROR_UNKNOWN, 0);
                    break;
                }

                // Now PostProc need calibration data as initialization
                // time for jpeg_open and calibration data is a
                // get param for now, so params needs to be initialized
                // before postproc init
                rc = pme->mParameters.init(cap,
                    pme->mCameraHandle,
                    pme, pme->m_pFovControl);
                if (rc != 0) {
                    job_status = UNKNOWN_ERROR;
                    LOGE("Parameter Initialization failed");
                    pme->sendEvtNotify(CAMERA_MSG_ERROR,
                        CAMERA_ERROR_UNKNOWN, 0);
                    break;
                }

                // Get related cam calibration only in
                // dual camera mode
                if ((pme->getRelatedCamSyncInfo()->sync_control ==
                    CAM_SYNC_RELATED_SENSORS_ON) || pme->isDualCamera()) {
                    rc = pme->mParameters.getRelatedCamCalibration(
                        &(pme->mJpegMetadata.otp_calibration_data));
                    LOGD("Dumping Calibration Data Version Id %f rc %d",
                        pme->mJpegMetadata.otp_calibration_data.calibration_format_version,
                        rc);
                    if (rc != 0) {
                        job_status = UNKNOWN_ERROR;
                        LOGE("getRelatedCamCalibration failed");
                        pme->sendEvtNotify(CAMERA_MSG_ERROR,
                            CAMERA_ERROR_UNKNOWN, 0);
                        break;
                    }
                    pme->m_bRelCamCalibValid = true;
                }

                pme->mJpegMetadata.sensor_mount_angle =
                    cap->sensor_mount_angle;
                pme->mJpegMetadata.default_sensor_flip = FLIP_NONE;

                pme->mParameters.setMinPpMask(
                    cap->qcom_supported_feature_mask);
                pme->mExifParams.debug_params =
                    (mm_jpeg_debug_exif_params_t *)
                    malloc(sizeof(mm_jpeg_debug_exif_params_t));
                if (!pme->mExifParams.debug_params) {
                    LOGE("Out of Memory. Allocation failed for "
                        "3A debug exif params");
                    job_status = NO_MEMORY;
                    pme->sendEvtNotify(CAMERA_MSG_ERROR,
                        CAMERA_ERROR_UNKNOWN, 0);
                    break;
                }
                memset(pme->mExifParams.debug_params, 0,
                    sizeof(mm_jpeg_debug_exif_params_t));
            }
            break;
            case CMD_DEF_GENERIC:
            {
                BackgroundTask *bgTask = dw->args.genericArgs;
                job_status = bgTask->bgFunction(bgTask->bgArgs);
            }
            break;
            default:
                LOGE("Incorrect command : %d", dw->cmd);
            }

            pme->dequeueDeferredWork(dw, job_status);
        }
        break;
        case CMD_TYPE_EXIT:
            running = 0;
            break;
        default:
            break;
        }
    } while (running);

    return NULL;
}