#include "RROS.h"
#include "mock.h"
#include "gtest/gtest.h"

static RROS_Result task_stub(void)
{
    return RROS_Result_OK;
}
RROS_Handle rros_handle;
TEST_F(RROS_UT, UT_Init_ParametersCheck)
{

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

TEST_F(RROS_UT, UT_Init_allInitFunctionsInvoked)
{
    RROS_Task tasks[] = {{.task_ID = 0U,
                          .task_period = 1000U,
                          .task_timeout = 100,
                          .task_run = mocked_run,
                          .task_init = mocked_init},
                         {.task_ID = 1U,
                          .task_period = 1000U,
                          .task_timeout = 100,
                          .task_run = mocked_run,
                          .task_init = mocked_init},
                         {.task_ID = 2U,
                          .task_period = 1000U,
                          .task_timeout = 100,
                          .task_run = mocked_run,
                          .task_init = mocked_init},
                         {.task_ID = 3U,
                          .task_period = 1000U,
                          .task_timeout = 100,
                          .task_run = mocked_run,
                          .task_init = mocked_init}};
    EXPECT_CALL(*_mock, mocked_init)
        .Times(4)
        .WillRepeatedly(testing::Return(RROS_Result_OK));

    EXPECT_EQ(RROS_Result_OK, RROS_init(&rros_handle, tasks, 4U));
}

TEST_F(RROS_UT, UT_Init_OneInitFunctionReturnsError)
{
    RROS_Task tasks[] = {{.task_ID = 0U,
                          .task_period = 1000U,
                          .task_timeout = 100,
                          .task_run = mocked_run,
                          .task_init = mocked_init},
                         {.task_ID = 1U,
                          .task_period = 1000U,
                          .task_timeout = 100,
                          .task_run = mocked_run,
                          .task_init = mocked_init},
                         {.task_ID = 2U,
                          .task_period = 1000U,
                          .task_timeout = 100,
                          .task_run = mocked_run,
                          .task_init = mocked_init},
                         {.task_ID = 3U,
                          .task_period = 1000U,
                          .task_timeout = 100,
                          .task_run = mocked_run,
                          .task_init = mocked_init}};
    EXPECT_CALL(*_mock, mocked_init)
        .Times(2)
        .WillOnce(testing::Return(RROS_Result_OK))
        .WillOnce(testing::Return(RROS_Result_TaskError));

    EXPECT_EQ(RROS_Result_TaskError, RROS_init(&rros_handle, tasks, 2U));
}

TEST_F(RROS_UT, UT_Init_RunTest)
{
    RROS_Task tasks[] = {{.task_ID = 0U,
                          .task_period = 1U,
                          .task_timeout = 100,
                          .task_run = mocked_run,
                          .task_init = mocked_init},
                         {.task_ID = 1U,
                          .task_period = 2U,
                          .task_timeout = 100,
                          .task_run = mocked_run2,
                          .task_init = mocked_init2},
                         {.task_ID = 2U,
                          .task_period = 3U,
                          .task_timeout = 100,
                          .task_run = mocked_run3,
                          .task_init = mocked_init3},
                         {.task_ID = 3U,
                          .task_period = 4U,
                          .task_timeout = 100,
                          .task_run = mocked_run4,
                          .task_init = mocked_init4}};
    EXPECT_CALL(*_mock, mocked_init).WillOnce(testing::Return(RROS_Result_OK));
    EXPECT_CALL(*_mock, mocked_init2).WillOnce(testing::Return(RROS_Result_OK));
    EXPECT_CALL(*_mock, mocked_init3).WillOnce(testing::Return(RROS_Result_OK));
    EXPECT_CALL(*_mock, mocked_init4).WillOnce(testing::Return(RROS_Result_OK));
    EXPECT_EQ(RROS_Result_OK, RROS_init(&rros_handle, tasks, 4U));
    invokeTimerCallback(4);
    EXPECT_CALL(*_mock, mocked_run).WillOnce(testing::Return(RROS_Result_OK));
    EXPECT_CALL(*_mock, mocked_run2).WillOnce(testing::Return(RROS_Result_OK));
    EXPECT_CALL(*_mock, mocked_run3).WillOnce(testing::Return(RROS_Result_OK));
    EXPECT_CALL(*_mock, mocked_run4).WillOnce(testing::Return(RROS_Result_OK));

    EXPECT_EQ(RROS_Result_OK, RROS_run(&rros_handle));

    invokeTimerCallback(1);

    EXPECT_CALL(*_mock, mocked_run).WillOnce(testing::Return(RROS_Result_OK));

    EXPECT_EQ(RROS_Result_OK, RROS_run(&rros_handle));

    invokeTimerCallback(1);

    EXPECT_CALL(*_mock, mocked_run).WillOnce(testing::Return(RROS_Result_OK));
    EXPECT_CALL(*_mock, mocked_run2).WillOnce(testing::Return(RROS_Result_OK));

    EXPECT_EQ(RROS_Result_OK, RROS_run(&rros_handle));
}

TEST_F(RROS_UT, UT_Init_TaskExceedsTimeout)
{
    RROS_Task tasks[] = {{.task_ID = 0U,
                          .task_period = 1U,
                          .task_timeout = 100,
                          .task_run = mocked_run,
                          .task_init = mocked_init},
                         {.task_ID = 1U,
                          .task_period = 2U,
                          .task_timeout = 100,
                          .task_run = mocked_run2,
                          .task_init = mocked_init2},
                         {.task_ID = 2U,
                          .task_period = 3U,
                          .task_timeout = 2,
                          .task_run = mocked_run3,
                          .task_init = mocked_init3},
                         {.task_ID = 3U,
                          .task_period = 4U,
                          .task_timeout = 100,
                          .task_run = mocked_run4,
                          .task_init = mocked_init4}};
    EXPECT_CALL(*_mock, mocked_init).WillOnce(testing::Return(RROS_Result_OK));
    EXPECT_CALL(*_mock, mocked_init2).WillOnce(testing::Return(RROS_Result_OK));
    EXPECT_CALL(*_mock, mocked_init3).WillOnce(testing::Return(RROS_Result_OK));
    EXPECT_CALL(*_mock, mocked_init4).WillOnce(testing::Return(RROS_Result_OK));
    EXPECT_EQ(RROS_Result_OK, RROS_init(&rros_handle, tasks, 4U));
    invokeTimerCallback(4);
    EXPECT_CALL(*_mock, mocked_run).WillOnce(testing::Return(RROS_Result_OK));
    EXPECT_CALL(*_mock, mocked_run2).WillOnce(testing::Return(RROS_Result_OK));
    EXPECT_CALL(*_mock, mocked_run3).WillOnce(testing::Return(RROS_Result_OK));
    EXPECT_CALL(*_mock, mocked_run4).WillOnce(testing::Return(RROS_Result_OK));

    EXPECT_EQ(RROS_Result_OK, RROS_run(&rros_handle));

    invokeTimerCallback(1);

    EXPECT_CALL(*_mock, mocked_run).WillOnce(testing::Return(RROS_Result_OK));

    EXPECT_EQ(RROS_Result_OK, RROS_run(&rros_handle));

    invokeTimerCallback(2);
    EXPECT_CALL(*_mock, mocked_run).WillOnce(testing::Return(RROS_Result_OK));
    EXPECT_CALL(*_mock, mocked_run2).WillOnce(testing::Return(RROS_Result_OK));
    EXPECT_CALL(*_mock, mocked_run3)
        .WillOnce(testing::DoAll(testing::InvokeWithoutArgs([]() {
                                     RROS_UT::invokeTimerCallback(1000);
                                 }),
                                 testing::Return(RROS_Result_OK)));

    EXPECT_EQ(RROS_Result_TaskTimeout, RROS_run(&rros_handle));
    EXPECT_EQ(rros_handle.error.task_ID, 2);
}