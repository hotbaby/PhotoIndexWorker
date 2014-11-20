/*************************************************************************
> File Name: test.c
> Author: yy
> Mail: mengyy_linux@163.com
 ************************************************************************/

#include <stdio.h>

int test_func(const char *s)
{
    if (s == NULL)
    {
        fprintf(stderr, "param error.\n");
        return -1;
    }

    fprintf(stderr, "@@@ call test function. @@@\n");
    fprintf(stderr, "%s\n", s);

    return 0;
}
