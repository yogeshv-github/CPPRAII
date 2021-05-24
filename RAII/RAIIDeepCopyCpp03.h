#pragma once
#include "DebugActions.h"

namespace RAIIDeepCopyCpp03
{
    /// <summary>
    /// Creates and manages an Integer array resource.
    /// Foo always performs deep copy of the resource and does not maintain 
    /// reference to resources from other Foo.
    /// </summary>
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
        void AllocateResource();
        void DeallocateResource();

        size_t  _internalResourceSize;
        int*    _pInternalResource;
    };

    /// <summary>
    /// Creates and manages a Char array resource in addition to Int Array resource of Foo.
    /// Bar always performs deep copy of the resource and does not maintain 
    /// reference to resources from other Bar or Foo.
    /// </summary>
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
        virtual bool Equals(Bar const& other) const;

    private:
        bool HasValidBuffer() const;
        void AllocateResource();
        void DeallocateResource();

        size_t  _internalResourceSize;
        char*   _pInternalResource;
    };
}