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
RROS_Result RROS_init(const RROS_Handle *pHandle, const RROS_Task *pTasks,
                      const size_t taskSize);
/* Static functions*/
static RROS_Result RROS_validateTask(const RROS_Task *pTask);
/*------------------------------------------------------*/
/* ----------------Function Definitions---------------- */
/*------------------------------------------------------*/

RROS_Result RROS_init(const RROS_Handle *pHandle, const RROS_Task *pTasks,
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
            if (res != RROS_Result_OK)
            {
                RROS_THROW(taskResult);
            }

            res = pTasks->task_init();
            if (res != RROS_Result_OK)
            {
                RROS_THROW(taskResult);
            }
        }
    }
    RROS_CATCH_BEGIN(res)
    {}
    RROS_CATCH_END
    return res;
}

RROS_Result RROS_run(const RROS_Handle *pHandle, const RROS_Task *pTasks,
                     const size_t tasksSize)
{
    RROS_Result res = RROS_Result_OK;
    RROS_TRY
    {
        if ((pHandle == NULL) != (pTasks == NULL))
        {
            RROS_THROW(RROS_Result_InvalidParameters);
        }
        uint32_t currentTime = RROS_getCurrentTime();
        for (uint32_t taskIndex = 0U; taskIndex < tasksSize; taskIndex++)
        {
            if (currentTime > pTasks->task_period)
            {}
            uint32_t taskStartTime = RROS_getCurrentTime();
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