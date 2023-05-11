#include "acutest.h"
#include <cstdlib>
#include <cstddef>


void test_example(void)
{
    void* mem;
    int a, b;

    mem = malloc(10);
    TEST_CHECK(mem != NULL);

    mem = realloc(mem, 20);
    TEST_CHECK(mem != NULL);
}

TEST_LIST = {
        {"serialize_issue_broadcast",   test_example},
        {NULL,                          NULL}
};