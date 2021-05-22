#pragma once
#include "DebugActions.h"

namespace RAIIDemoCpp03
{
    void Test();

    class Foo : public DebugActions
    {
    public:
        Foo(const size_t resourceSz);
        virtual ~Foo();
        Foo(const Foo& other);
        Foo& operator= (const Foo& other);
        bool operator== (const Foo& other) const;
        bool operator!= (const Foo& other) const;

        virtual void RandomizeInternalBuffers() override;
        virtual void PrintInternalBuffers() override;

    protected:
        virtual bool Equals(Foo const& other) const;

    private:
        bool HasValidBuffer() const;

        size_t  _internalResourceSize;
        int*    _pInternalResource;
    };

    class Bar : public Foo
    {
    public:
        Bar(const size_t resourceSz);
        virtual ~Bar();
        Bar(const Bar& other);
        Bar& operator= (const Bar& other);
        bool operator== (const Bar& other) const;
        bool operator!= (const Bar& other) const;

        virtual void RandomizeInternalBuffers() override;
        virtual void PrintInternalBuffers() override;

    protected:
        virtual bool Equals(Foo const& other) const;

    private:
        bool HasValidBuffer() const;

        size_t  _internalResourceSize;
        char*   _pInternalResource;
    };
}