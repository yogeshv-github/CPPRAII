#include <stdio.h>
#include <iostream>
#include "RAIIDeepCopyCpp03.h"
#include "RAIIDeepCopyCpp17.h" 

using namespace std;

void TestRAIICpp03()
{
    RAIIDeepCopyCpp03::Foo* foo1 = new RAIIDeepCopyCpp03::Foo(4);
    foo1->RandomizeInternalBuffers();
    foo1->PrintInternalBuffers();

    RAIIDeepCopyCpp03::Foo* bar1 = new RAIIDeepCopyCpp03::Bar(1);
    bar1->RandomizeInternalBuffers();
    bar1->PrintInternalBuffers();

    RAIIDeepCopyCpp03::Bar* bar2 = new RAIIDeepCopyCpp03::Bar(2);
    bar2->RandomizeInternalBuffers();
    bar2->PrintInternalBuffers();

    cout <<"    Is foo1 equal bar1 before *foo1 = *bar1: " << (*foo1 == *bar1) << endl;
    *foo1 = *bar1;
    cout <<"    Is foo1 equal bar1 after *foo1 = *bar1: " << (*foo1 == *bar1) << endl;

    cout <<"    Is bar1 equal bar2 before *bar1 = *bar2: " << (*bar1 == *bar2) << endl;
    *bar1 = *bar2;
    cout <<"    Is bar1 equal bar2 after *bar1 = *bar2: " << (*bar1 == *bar2) << endl;

    RAIIDeepCopyCpp03::Bar* bar1Casted = dynamic_cast<RAIIDeepCopyCpp03::Bar*>(bar1);
    if (bar1Casted != nullptr)
    {
        cout <<"    Is casted bar1 equal bar2 before *bar1Casted = *bar2: " << (*bar1 == *bar2) << endl;
        *bar1Casted = *bar2;
        cout <<"    Is casted bar1 equal bar2 after *bar1Casted = *bar2: " << (*bar1 == *bar2) << endl;
    }

    delete foo1;
    delete bar1;
    delete bar2;
}

void TestRAIICpp17()
{
    RAIIDeepCopyCpp17::Foo* foo1 = new RAIIDeepCopyCpp17::Foo(4);
    foo1->RandomizeInternalBuffers();
    foo1->PrintInternalBuffers();

    RAIIDeepCopyCpp17::Foo* bar1 = new RAIIDeepCopyCpp17::Bar(1);
    bar1->RandomizeInternalBuffers();
    bar1->PrintInternalBuffers();

    RAIIDeepCopyCpp17::Bar* bar2 = new RAIIDeepCopyCpp17::Bar(2);
    bar2->RandomizeInternalBuffers();
    bar2->PrintInternalBuffers();

    cout <<"    Is foo1 equal bar1 before *foo1 = *bar1: " << (*foo1 == *bar1) << endl;
    *foo1 = *bar1;
    cout <<"    Is foo1 equal bar1 after *foo1 = *bar1: " << (*foo1 == *bar1) << endl;

    cout <<"    Is bar1 equal bar2 before *bar1 = *bar2: " << (*bar1 == *bar2) << endl;
    *bar1 = *bar2;
    cout <<"    Is bar1 equal bar2 after *bar1 = *bar2: " << (*bar1 == *bar2) << endl;

    RAIIDeepCopyCpp17::Bar* bar1Casted = dynamic_cast<RAIIDeepCopyCpp17::Bar*>(bar1);
    if (bar1Casted != nullptr)
    {
        cout <<"    Is casted bar1 equal bar2 before *bar1Casted = *bar2: " << (*bar1 == *bar2) << endl;
        *bar1Casted = *bar2;
        cout <<"    Is casted bar1 equal bar2 after *bar1Casted = *bar2: " << (*bar1 == *bar2) << endl;
    }

    delete foo1;
    delete bar1;
    delete bar2;
}

int main()
{
    cout << "****************  Test RAIICpp03 Start ****************" << endl;
    TestRAIICpp03();
    cout << "****************  Test RAIICpp03 End ****************" << endl << endl;

    cout << "****************  Test RAIICpp17 Start ****************" << endl;
    TestRAIICpp17();
    cout << "****************  Test RAIICpp17 End ****************" << endl << endl;

    getchar();

    return 0;
}