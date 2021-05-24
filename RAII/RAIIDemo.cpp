#include <stdio.h>
#include <iostream>

#include "RAIIUnitTests.h"

using namespace std;

int main()
{
    RAIIUnitTests ut;
    ut.TestRAIICpp03();
    ut.TestRAIICpp17();
    ut.TestRAIISharedResourceCpp17();

    const int brk = getchar();
    return (brk != 0);
}