#ifndef RROS_TYPES_H
#define RROS_TYPES_H
typedef enum
{
    RROS_Result_OK,
    RROS_Result_InternalError,
    RROS_Result_InvalidParameters,
    RROS_Result_TaskError,
    RROS_Result_TaskCriticalError,
    RROS_Result_TaskTimeout
} RROS_Result;
#endif /*RROS_TYPES_H*/