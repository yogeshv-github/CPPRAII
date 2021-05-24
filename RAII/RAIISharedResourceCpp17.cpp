#include "RAIISharedResourceCpp17.h"
#include <memory.h>
#include <string>
#include <time.h>
#include <typeinfo>

#include <iostream>
using namespace std;

namespace RAIISharedResourceCpp17
{
#pragma region RAIISharedResourceCpp17_Foo

    /// <summary>
    /// Foo constructor. (Allocates Int array resources)
    /// </summary>
    /// <param name="resourceSz"> Resource size to allocate on construction.</param>
    Foo::Foo(const size_t resourceSz) :
        _internalResource(nullptr)
    {
        AllocateResource(resourceSz);
    }

    /// <summary>
    /// Foo destructor. (Deallocates Int array resources, reference count reduces for shallow copy)
    /// </summary>
    Foo::~Foo()
    {
        DeallocateResource();
    }

    /// <summary>
    /// Foo Copy constructor. (Shallow copy of shared resource, reference count increments.)
    /// </summary>
    /// <param name="other">Other foo to construct from.</param>
    Foo::Foo(const Foo& other) :
        _internalResource(other._internalResource)
    {}

    /// <summary>
    /// Assign operator overload (Shallow copy of shared resource, reference count increments.)
    /// </summary>
    /// <param name="other">Other foo</param>
    /// <returns>Reference to this</returns>
    Foo& Foo::operator= (const Foo& other)
    {
        if (this != &other)
        {
            _internalResource = other._internalResource;
        }

        return (*this);
    }

    /// <summary>
    /// Equality check. (Compares resources correctly)
    /// </summary>
    /// <param name="other"></param>
    /// <returns>True, on equal, false otherwise.</returns>
    bool Foo::Equals(Foo const& other) const
    {
        if (typeid(*this) != typeid(other))
        {
            return false;
        }

        if (HasValidBuffer() && 
            other.HasValidBuffer() &&
            (_internalResource->size() == other._internalResource->size()))
        {
            return (_internalResource == other._internalResource);
        }

        return false;
    }

    /// <summary>
    /// Equality operator overload to correctly compare resource.
    /// </summary>
    /// <param name="other"></param>
    /// <returns>True on equal, false otherwise.</returns>
    bool Foo::operator== (const Foo& other) const
    {
        return this->Equals(other);
    }

    /// <summary>
    /// Inequality operator overload to correctly compare resource.
    /// </summary>
    /// <param name="other"></param>
    /// <returns>True when resources are not equal, false otherwise.</returns>
    bool Foo::operator!= (const Foo& other) const
    {
        return !(*this == other);
    }

    /// <summary>
    /// Is local foo buffer valid?
    /// </summary>
    /// <returns>True, when non-zero resource is allocated, false otherwise.</returns>
    bool Foo::HasValidBuffer() const
    {
        return (_internalResource != nullptr);
    }

    /// <summary>
    /// Allocate Int resource array of size equal to internal resource size member variable. 
    /// Resource array will not be allocated when internal resource size is zero. (Invalid buffer)
    /// Fill allocated array with zeroes. 
    /// </summary>
    void Foo::AllocateResource(size_t resourceSz)
    {
        if (resourceSz > 0)
        {
            _internalResource = std::make_shared<int_array_t>();
            _internalResource->resize(resourceSz);
        }
    }

    /// <summary>
    /// Deallocated any allocated resource.
    /// </summary>
    void Foo::DeallocateResource()
    {
        if (_internalResource != nullptr)
        {
            _internalResource->clear();
            _internalResource.reset();
        }
    }

    /// <summary>
    /// Update internal int buffer with random values.
    /// </summary>
    void Foo::RandomizeInternalBuffers() 
    {
        if (HasValidBuffer())
        {
            srand((unsigned int)time(NULL));
            const size_t resSz = _internalResource->size();
            for (size_t bufferIdx = 0; bufferIdx < resSz; bufferIdx++)
            {
                const int randomVal = (rand() % resSz);
                _internalResource->at(bufferIdx) = randomVal;
            }
        }
    }

    /// <summary>
    /// Print internal buffer for debugging purpose.
    /// </summary>
    void Foo::PrintInternalBuffers()
    {
        std::string bufferToStr;
        if (HasValidBuffer())
        {
            for (auto resourceElement : *_internalResource)
            {
                bufferToStr.append(std::to_string(resourceElement)).append(",");
            }

            if (bufferToStr.back() == ',')
            {
                bufferToStr.pop_back();
            }
        }
        else
        {
            bufferToStr.append("Invalid buffer.");
        }

        printf("Function: %s, Values: %s \n", __FUNCTION__, bufferToStr.c_str());
    }

#pragma endregion RAIISharedResourceCpp17_Foo

#pragma region RAIISharedResourceCpp17_Bar

    /// <summary>
    /// Bar constructor. (Allocates Char array resources)
    /// </summary>
    /// <param name="resourceSz"> Resource size to allocate on construction.</param>
    Bar::Bar(const size_t resourceSz) :
        Foo(resourceSz),
        _internalResource(nullptr)
    {
        AllocateResource(resourceSz);
    }

    /// <summary>
    /// Bar destructor. (Deallocates char array resources)
    /// </summary>
    Bar::~Bar()
    {
        DeallocateResource();
    }

    /// <summary>
    /// Bar Copy constructor. (Shallow copy of resource)
    /// </summary>
    /// <param name="other">Other bar to construct from.</param>
    Bar::Bar(const Bar& other) :
        Foo(other),
        _internalResource(other._internalResource)
    {}

    /// <summary>
    /// Assign operator overload (Shalow copy of resource)
    /// </summary>
    /// <param name="other">Other bar</param>
    /// <returns>Reference to this</returns>
    Bar& Bar::operator= (const Bar& other)
    {
        if (this != &other)
        {
            __super::operator=(other);

            _internalResource = other._internalResource;
        }

        return (*this);
    }

    /// <summary>
    /// Equality check. (Compares resources correctly)
    /// </summary>
    /// <param name="other"></param>
    /// <returns>True, on equal, false otherwise.</returns>
    bool Bar::Equals(Foo const& other) const
    {
        if (typeid(*this) != typeid(other))
        {
            return false;
        }

        if (!__super::Equals(other))
        {
            return false;
        }

        auto otherBar = static_cast<Bar const&>(other);
        if (HasValidBuffer() &&
            otherBar.HasValidBuffer() &&
            (_internalResource->size() == otherBar._internalResource->size()))
        {
            return (_internalResource == otherBar._internalResource);
        }

        return false;
    }

    /// <summary>
    /// Equality operator overload to correctly compare resource.
    /// </summary>
    /// <param name="other"></param>
    /// <returns>True on equal, false otherwise.</returns>
    bool Bar::operator==(const Bar& other) const
    {
        return this->Equals(other);
    }

    /// <summary>
    /// Inequality operator overload to correctly compare resource.
    /// </summary>
    /// <param name="other"></param>
    /// <returns>True when resources are not equal, false otherwise.</returns>
    bool Bar::operator!=(const Bar& other) const
    {
        return !(*this == other);
    }

    /// <summary>
    /// Is local bar buffer valid?
    /// </summary>
    /// <returns>True, when non-zero resource is allocated, false otherwise.</returns>
    bool Bar::HasValidBuffer() const
    {
        return (_internalResource != nullptr);
    }

    /// <summary>
    /// Allocate Char resource array of size equal to internal resource size member variable. 
    /// Resource array will not be allocated when internal resource size is zero. (Invalid buffer)
    /// Fill allocated array with zeroes. 
    /// </summary>
    void Bar::AllocateResource(size_t resourceSz)
    {
        if (resourceSz > 0)
        {
            _internalResource = std::make_shared<char_array_t>();
            _internalResource->resize(resourceSz);
        }
    }

    /// <summary>
    /// Deallocated any allocated resource.
    /// </summary>
    void Bar::DeallocateResource()
    {
        if (_internalResource != nullptr)
        {
            _internalResource->clear();
            _internalResource.reset();
        }
    }

    /// <summary>
    /// Update internal int buffer with random values.
    /// </summary>
    void Bar::RandomizeInternalBuffers()
    {
        Foo::RandomizeInternalBuffers();

        if (HasValidBuffer())
        {
            srand((unsigned int)time(NULL));
            const size_t resSz = _internalResource->size();
            for (size_t bufferIdx = 0; bufferIdx < resSz; bufferIdx++)
            {
                const char randomVal = 'a' + (rand() % 26);
                _internalResource->at(bufferIdx) = randomVal;
            }
        }
    }

    /// <summary>
    /// Print internal buffer for debugging purpose.
    /// </summary>
    void Bar::PrintInternalBuffers()
    {
        Foo::PrintInternalBuffers();

        std::string bufferToStr;
        if (HasValidBuffer())
        {
            for (auto resourceElement : *_internalResource)
            {
                bufferToStr.push_back(resourceElement);
            }
        }
        else
        {
            bufferToStr.append("Invalid buffer.");
        }

        printf("Function: %s, Values: %s \n", __FUNCTION__, bufferToStr.c_str());
    }
#pragma endregion RAIISharedResourceCpp17_Bar

}