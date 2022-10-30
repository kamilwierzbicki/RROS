/*------------------------------------------------------*/
/* ---------------------Includes----------------------- */
/*------------------------------------------------------*/
#include "RROS.h"
#include "RROS_Exception.h"
#include "RROS_Utils.h"
/*------------------------------------------------------*/
/* ----------------Function Prototypes----------------- */
/*------------------------------------------------------*/
/* Global functions*/
RROS_Result RROS_init(RROS_Handle *const pHandle, RROS_Task *const pTasks,
                      const size_t taskSize);
/* Static functions*/
static RROS_Result RROS_validateTask(const RROS_Task *pTask);
static void RROS_StoreErrorEvent(RROS_Handle *pHandle, uint32_t taskID,
                                 RROS_Result errorCode, uint32_t errorTime);

static RROS_Result RROS_runTask(RROS_Handle *pHandle, RROS_Task *pTask);
/*------------------------------------------------------*/
/* ----------------Function Definitions---------------- */
/*------------------------------------------------------*/

RROS_Result RROS_init(RROS_Handle *const pHandle, RROS_Task *const pTasks,
                      size_t tasksSize)
{
    RROS_Result res = RROS_Result_OK;
    RROS_TRY
    {
        if ((pHandle == NULL) || (pTasks == NULL))
        {
            RROS_THROW(RROS_Result_InvalidParameters);
        }

        for (uint32_t taskIndex = 0U; taskIndex < tasksSize; taskIndex++)
        {
            RROS_Result taskResult = RROS_Result_OK;
            taskResult = RROS_validateTask(&(pTasks[taskIndex]));
            if (taskResult != RROS_Result_OK)
            {
                RROS_THROW(taskResult);
            }
            pTasks[taskIndex]._lastRunTime = 0U;
            taskResult = pTasks[taskIndex].task_init();
            if (taskResult != RROS_Result_OK)
            {
                RROS_THROW(taskResult);
            }
        }
        pHandle->numOfTasks = tasksSize;
        pHandle->tasks = pTasks;
    }
    RROS_CATCH_BEGIN(res)
    {}
    RROS_CATCH_END
    return res;
}

RROS_Result RROS_run(RROS_Handle *const pHandle)
{
    RROS_Result res = RROS_Result_OK;
    RROS_TRY
    {
        if (pHandle == NULL || pHandle->tasks == NULL)
        {
            RROS_THROW(RROS_Result_InvalidParameters);
        }
        RROS_Task *pTasks = pHandle->tasks;
        size_t tasksNum = pHandle->numOfTasks;
        uint32_t currentTime = RROS_getCurrentTime();
        for (uint32_t taskIndex = 0U; taskIndex < tasksNum; taskIndex++)
        {
            if (currentTime >=
                pTasks[taskIndex].task_period + pTasks[taskIndex]._lastRunTime)
            {
                RROS_Result taskResult =
                    RROS_runTask(pHandle, &(pTasks[taskIndex]));

                if (taskResult != RROS_Result_OK &&
                    taskResult != RROS_Result_TaskError)
                {
                    RROS_THROW(taskResult);
                }
            }
        }
    }
    RROS_CATCH_BEGIN(res)
    {}
    RROS_CATCH_END;
    return res;
}

static RROS_Result RROS_validateTask(const RROS_Task *pTask)
{
    RROS_Result res = RROS_Result_OK;
    RROS_TRY
    {
        if (pTask == NULL)
        {
            RROS_THROW(RROS_Result_InvalidParameters);
        }

        if ((pTask->task_run == NULL) || (pTask->task_init == NULL))
        {
            RROS_THROW(RROS_Result_InvalidParameters);
        }
    }
    RROS_CATCH_BEGIN(res)
    {}
    RROS_CATCH_END
    return res;
}

static void RROS_StoreErrorEvent(RROS_Handle *pHandle, uint32_t taskID,
                                 RROS_Result errorCode, uint32_t errorTime)
{
    pHandle->error.errorTime = errorTime;
    pHandle->error.task_ID = taskID;
    pHandle->error.taskErrorCode = errorCode;
}

static RROS_Result RROS_runTask(RROS_Handle *pHandle, RROS_Task *pTask)
{
    RROS_Result res = RROS_Result_OK;
    RROS_TRY
    {
        uint32_t taskStartTime = RROS_getCurrentTime();
        uint32_t taskEndTime = 0U;
        RROS_Result taskResult = RROS_Result_OK;
        pTask->_lastRunTime = taskStartTime;
        taskResult = pTask->task_run();
        taskEndTime = RROS_getCurrentTime();
        switch (taskResult)
        {
        case RROS_Result_TaskCriticalError:
            RROS_StoreErrorEvent(pHandle, pTask->task_ID, taskResult,
                                 taskEndTime);
            RROS_THROW(taskResult);
            break;
        case RROS_Result_TaskError:
            RROS_StoreErrorEvent(pHandle, pTask->task_ID, taskResult,
                                 taskEndTime);
            break;

        default:
            break;
        }
        if (taskEndTime - taskStartTime >
            pTask->task_timeout) // TODO: Overflow protection
        {
            RROS_StoreErrorEvent(pHandle, pTask->task_ID,
                                 RROS_Result_TaskTimeout, taskEndTime);
            RROS_THROW(RROS_Result_TaskTimeout);
        }
    }
    RROS_CATCH_BEGIN(res)
    {}
    RROS_CATCH_END
    return res;
}