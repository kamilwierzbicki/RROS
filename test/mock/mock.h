#include "RROS.h"
#include <gmock/gmock.h>

extern "C" {
RROS_Result mocked_init();
RROS_Result mocked_run();
RROS_Result mocked_init2();
RROS_Result mocked_run2();
RROS_Result mocked_init3();
RROS_Result mocked_run3();
RROS_Result mocked_init4();
RROS_Result mocked_run4();
}

class Task_Mock
{
  public:
    virtual ~Task_Mock()
    {}

    MOCK_METHOD0(mocked_init, RROS_Result());
    MOCK_METHOD0(mocked_run, RROS_Result());
    MOCK_METHOD0(mocked_init2, RROS_Result());
    MOCK_METHOD0(mocked_run2, RROS_Result());
    MOCK_METHOD0(mocked_init3, RROS_Result());
    MOCK_METHOD0(mocked_run3, RROS_Result());
    MOCK_METHOD0(mocked_init4, RROS_Result());
    MOCK_METHOD0(mocked_run4, RROS_Result());
};

class RROSTestFixture : public ::testing::Test
{
  public:
    RROSTestFixture()
    {
        _mock.reset(new ::testing::NiceMock<Task_Mock>());
    }
    ~RROSTestFixture()
    {
        _mock.reset();
    }

  protected:
    static void SetUpTestCase()
    {}

    virtual void SetUp()
    {}
    virtual void TearDown()
    {}

  public:
    static std::unique_ptr<Task_Mock> _mock;
};

class RROS_UT : public RROSTestFixture
{
  public:
    RROS_UT()
    {}
    static void invokeTimerCallback(uint32_t num)
    {
        for (uint32_t i = 0; i < num; i++)
        {
            RROS_timeCounterCallback();
        }
    }
};