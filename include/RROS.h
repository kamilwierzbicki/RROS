#ifdef __cplusplus
extern "C" {
#endif

#include "RROS_Structs.h"
#include "RROS_TimeCounter.h"
#include "RROS_Types.h"

RROS_Result RROS_init(RROS_Handle *const pHandle, RROS_Task *const pTasks,
                      const size_t taskSize);

RROS_Result RROS_run(RROS_Handle *const pHandle);

#ifdef __cplusplus
}
#endif
