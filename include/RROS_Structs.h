#ifndef RROS_STRUCTS_H
#define RROS_STRUCTS_H

#include "RROS_Types.h"
#include <stdbool.h>
#include <stdint.h>

typedef struct
{
    uint32_t task_ID;
    uint32_t task_period;
    uint32_t task_timeout;
    RROS_Result (*task_run)(void);
    RROS_Result (*task_init)(void);
    uint32_t _lastRunTime;
} RROS_Task;

typedef struct
{
    uint32_t task_ID;
    uint32_t taskErrorCode;
    uint32_t errorTime;
} RROS_ErrorHandle;

typedef struct
{
    RROS_Task *tasks;
    size_t numOfTasks;
    bool initialized;
    RROS_ErrorHandle error;
} RROS_Handle;

#endif /*RROS_STRUCTS_H*/