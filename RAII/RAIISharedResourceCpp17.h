#pragma once
#include "DebugActions.h"
#include <memory>
#include <vector>

namespace RAIISharedResourceCpp17
{
    /// <summary>
    /// Creates aand Manages an Integer array resource.
    /// Foo assign and copy support shalow copy of the shared resource and does maintain 
    /// reference to shared resources from other Foo.
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
        void AllocateResource(size_t resourceSz);
        void DeallocateResource();

        typedef std::vector<int> int_array_t;
        std::shared_ptr<int_array_t> _internalResource;
    };

    /// <summary>
    /// Creates and Manages a Char array resource in addition to Int Array resource of Foo.
    /// Bar assign and copy support shallow copy of the resource and does maintain 
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
        virtual bool Equals(Foo const& other) const;

    private:
        bool HasValidBuffer() const;
        void AllocateResource(size_t resourceSz);
        void DeallocateResource();

        typedef std::vector<char> char_array_t;
        std::shared_ptr<char_array_t> _internalResource;
    };
}