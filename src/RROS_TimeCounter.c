
/*------------------------------------------------------*/
/* ---------------------Includes----------------------- */
/*------------------------------------------------------*/
#include "RROS_TimeCounter.h"
#include <stdatomic.h>
/*------------------------------------------------------*/
/* ----------------Function Prototypes----------------- */
/*------------------------------------------------------*/
/* Global functions*/
uint32_t RROS_getCurrentTime(void);
void RROS_timeCounterCallback(void);
void RROS_TimeCounterInit(void);
/* Static functions*/
/*------------------------------------------------------*/
/* ----------------Function Definitions---------------- */
/*------------------------------------------------------*/

atomic_uint_fast32_t timeCounter = 0U;

void RROS_TimeCounterInit(void)
{
    timeCounter = 0U;
}

uint32_t RROS_getCurrentTime(void)
{
    return timeCounter;
}
void RROS_timeCounterCallback(void)
{
    timeCounter++;
}