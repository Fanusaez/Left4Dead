#include "acutest.h"

void testExample(void)
{
    int a = 1;
    TEST_CHECK(a == 1);
}

TEST_LIST = {
        {"Testing tests xd", testExample},
        {NULL, NULL}
};
