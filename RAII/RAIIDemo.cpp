#include <stdio.h>
#include "RAIICpp03.h"

void TestRAIICpp03()
{
    RAIICpp03::Foo* foo1 = new RAIICpp03::Foo(4);
    foo1->RandomizeInternalBuffers();
    foo1->PrintInternalBuffers();

    RAIICpp03::Foo* bar1 = new RAIICpp03::Bar(1);
    bar1->RandomizeInternalBuffers();
    bar1->PrintInternalBuffers();

    RAIICpp03::Bar* bar2 = new RAIICpp03::Bar(2);
    bar2->RandomizeInternalBuffers();
    bar2->PrintInternalBuffers();

    printf("Is foo1 equal bar1 before assignment: %d \n", (*foo1 == *bar1));
    *foo1 = *bar1;
    printf("Is foo1 equal bar1 after assignment: %d \n", (*foo1 == *bar1));

    printf("Is bar1 equal bar2 before assignment: %d \n", (*bar1 == *bar2));
    *bar1 = *bar2;
    printf("Is bar1 equal bar2 after assignment: %d \n", (*bar1 == *bar2));

    RAIICpp03::Bar* bar1Casted = dynamic_cast<RAIICpp03::Bar*>(bar1);
    printf("Is casted bar1 equal bar2 before assignment: %d \n", (*bar1 == *bar2));
    *bar1Casted = *bar2;
    printf("Is casted bar1 equal bar2 after assignment: %d \n", (*bar1 == *bar2));

    delete foo1;
    delete bar1;
    delete bar2;
}

int main()
{
    TestRAIICpp03();

    getchar();

    return 0;
}