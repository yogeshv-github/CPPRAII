#pragma once

/// <summary>
/// Interface to enable tracing.
/// </summary>
class DebugActions
{
public:
    virtual void RandomizeInternalBuffers() = 0;
    virtual void PrintInternalBuffers() = 0;
};
