#include "RROS.h"
#include "gtest/gtest.h"

static RROS_Result task_stub(void)
{
    return RROS_Result_OK;
}

TEST(RROS_Tests, UT_Init_ParametersCheck)
{
    RROS_Handle rros_handle;
    RROS_Task tasks[] = {
        {.task_ID = 0U,
         .task_period = 1000U,
         .task_timeout = 100,
         .task_run = NULL,
         .task_init = NULL},
        {.task_ID = 1U,
         .task_period = 1000U,
         .task_timeout = 100,
         .task_run = task_stub,
         .task_init = task_stub},
        {.task_ID = 2U,
         .task_period = 1000U,
         .task_timeout = 100,
         .task_run = task_stub,
         .task_init = NULL},
        {.task_ID = 3U,
         .task_period = 1000U,
         .task_timeout = 100,
         .task_run = NULL,
         .task_init = task_stub},
    };
    EXPECT_EQ(RROS_Result_InvalidParameters, RROS_init(NULL, NULL, 1U));
    EXPECT_EQ(RROS_Result_InvalidParameters,
              RROS_init(&rros_handle, tasks, 1U));
    EXPECT_EQ(RROS_Result_OK, RROS_init(&rros_handle, &(tasks[1]), 1U));
    EXPECT_EQ(RROS_Result_InvalidParameters,
              RROS_init(&rros_handle, &(tasks[1]), 2U));
    EXPECT_EQ(RROS_Result_InvalidParameters,
              RROS_init(&rros_handle, &(tasks[3]), 1U));
}