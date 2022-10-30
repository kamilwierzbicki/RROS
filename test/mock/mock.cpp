#include <mock.h>

extern "C" {
RROS_Result mocked_init();
RROS_Result mocked_run();
}

std::unique_ptr<Task_Mock> RROSTestFixture::_mock = nullptr;

extern "C" {
RROS_Result mocked_init()
{
    return RROS_UT::_mock->mocked_init();
}
RROS_Result mocked_run()
{
    return RROS_UT::_mock->mocked_run();
}
RROS_Result mocked_init2()
{
    return RROS_UT::_mock->mocked_init2();
}
RROS_Result mocked_run2()
{
    return RROS_UT::_mock->mocked_run2();
}
RROS_Result mocked_init3()
{
    return RROS_UT::_mock->mocked_init3();
}
RROS_Result mocked_run3()
{
    return RROS_UT::_mock->mocked_run3();
}
RROS_Result mocked_init4()
{
    return RROS_UT::_mock->mocked_init4();
}
RROS_Result mocked_run4()
{
    return RROS_UT::_mock->mocked_run4();
}
}