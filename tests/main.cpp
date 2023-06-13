#include <gtest/gtest.h>

int main()
{
    // initialize the time zone for testing
    char env[20];
    strcpy(env, "TZ=UTC-8");
    putenv(env);
    tzset();
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}
