#ifndef RROS_EXCEPTION_H
#define RROS_EXCEPTION_H
#include "RROS_Types.h"
// clang-format off
#define RROS_TRY    {\
                        RROS_Result RROS_error = RROS_Result_OK;

#define RROS_CATCH_BEGIN(error) RROS_CATCH_LABEL:\
                                (error) = RROS_error;

#define RROS_CATCH_END }

#define RROS_THROW(error)   RROS_error = (error);\
                            goto RROS_CATCH_LABEL
// clang-format on

#endif /*RROS_EXCEPTION_H*/