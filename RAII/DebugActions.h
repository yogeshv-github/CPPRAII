#pragma once

class DebugActions
{
public:
    virtual void RandomizeInternalBuffers() = 0;
    virtual void PrintInternalBuffers() = 0;
};
