#include "RAIIDeepCopyCpp03.h"
#include <memory.h>
#include <string>
#include <time.h>
#include <typeinfo>

namespace RAIIDeepCopyCpp03
{
#pragma region RAIIDeepCopyCpp03_Foo

    /// <summary>
    /// Foo constructor. (Allocates Int array resources)
    /// </summary>
    /// <param name="resourceSz"> Resource size to allocate on construction.</param>
    Foo::Foo(const size_t resourceSz) :
        _internalResourceSize(resourceSz),
        _pInternalResource(nullptr)
    {
        AllocateResource();
    }

    /// <summary>
    /// Foo destructor. (Deallocates Int array resources)
    /// </summary>
    Foo::~Foo()
    {
        DeallocateResource();
    }

    /// <summary>
    /// Foo Copy constructor. (Deep copy of resource)
    /// </summary>
    /// <param name="other">Other foo to construct from.</param>
    Foo::Foo(const Foo& other) :
        _internalResourceSize(other._internalResourceSize),
        _pInternalResource(nullptr)
    {
        // Deep copy.
        AllocateResource();
        if (other.HasValidBuffer() && HasValidBuffer())
        {
            memcpy(_pInternalResource, other._pInternalResource, (sizeof(int) * _internalResourceSize));
        }
    }

    /// <summary>
    /// Assign operator overload (Deep copy of resource)
    /// </summary>
    /// <param name="other">Other foo</param>
    /// <returns>Reference to this</returns>
    Foo& Foo::operator= (const Foo& other)
    {
        if (this != &other)
        {
            DeallocateResource();

            // Deep copy.
            _internalResourceSize = other._internalResourceSize;
            AllocateResource();
            if (other.HasValidBuffer() && HasValidBuffer())
            {
                memcpy(_pInternalResource, other._pInternalResource, (sizeof(int) * _internalResourceSize));
            }
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
            (_internalResourceSize == other._internalResourceSize))
        {
            return (memcmp(_pInternalResource, other._pInternalResource, (sizeof(int) * _internalResourceSize)) == 0);
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
        return ((_pInternalResource != nullptr) && (_internalResourceSize > 0));
    }

    /// <summary>
    /// Allocate Int resource array of size equal to internal resource size member variable. 
    /// Resource array will not be allocated when internal resource size is zero. (Invalid buffer)
    /// Fill allocated array with zeroes. 
    /// </summary>
    void Foo::AllocateResource()
    {
        if (_internalResourceSize > 0)
        {
            _pInternalResource = new int[_internalResourceSize];
            memset(_pInternalResource, 0, (sizeof(int) * _internalResourceSize));
        }
    }

    /// <summary>
    /// Deallocated any allocated resource.
    /// </summary>
    void Foo::DeallocateResource()
    {
        if (_pInternalResource != nullptr)
        {
            delete[] _pInternalResource;
            _pInternalResource = nullptr;
            _internalResourceSize = 0;
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
            for (size_t bufferIdx = 0; bufferIdx < _internalResourceSize; bufferIdx++)
            {
                _pInternalResource[bufferIdx] = rand() % _internalResourceSize;
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
            for (size_t bufferIdx = 0; bufferIdx < _internalResourceSize; bufferIdx++)
            {
                bufferToStr.append(std::to_string(_pInternalResource[bufferIdx])).append(",");
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

#pragma endregion RAIIDeepCopyCpp03_Foo

#pragma region RAIIDeepCopyCpp03_Bar

    /// <summary>
    /// Bar constructor. (Allocates char array resources)
    /// </summary>
    /// <param name="resourceSz"> Resource size to allocate on construction.</param>
    Bar::Bar(const size_t resourceSz) :
        Foo(resourceSz),
        _internalResourceSize(resourceSz),
        _pInternalResource(nullptr)
    {
        AllocateResource();
    }

    /// <summary>
    /// Bar destructor. (Deallocates char array resources)
    /// </summary>
    Bar::~Bar()
    {
        DeallocateResource();
    }

    /// <summary>
    /// Bar Copy constructor. (Deep copy of resource)
    /// </summary>
    /// <param name="other">Other bar to construct from.</param>
    Bar::Bar(const Bar& other) :
        Foo(other),
        _internalResourceSize(other._internalResourceSize),
        _pInternalResource(nullptr)
    {
        // Deep copy.
        AllocateResource();
        if (other.HasValidBuffer() && HasValidBuffer())
        {
            memcpy(_pInternalResource, other._pInternalResource, (sizeof(char) * _internalResourceSize));
        }
    }

    /// <summary>
    /// Assign operator overload (Deep copy of resource)
    /// </summary>
    /// <param name="other">Other bar</param>
    /// <returns>Reference to this</returns>
    Bar& Bar::operator= (const Bar& other)
    {
        if (this != &other)
        {
            __super::operator=(other);

            DeallocateResource();

            _internalResourceSize = other._internalResourceSize;

            // Deep copy.
            AllocateResource();
            if (other.HasValidBuffer() && HasValidBuffer())
            {
                memcpy(_pInternalResource, other._pInternalResource, (sizeof(char) * _internalResourceSize));
            }
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
            (_internalResourceSize == otherBar._internalResourceSize))
        {
            return (memcmp(_pInternalResource, otherBar._pInternalResource, (sizeof(char) * _internalResourceSize)) == 0);
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
        return ((_pInternalResource != nullptr) && (_internalResourceSize > 0));
    }

    /// <summary>
    /// Allocate Char resource array of size equal to internal resource size member variable. 
    /// Resource array will not be allocated when internal resource size is zero. (Invalid buffer)
    /// Fill allocated array with zeroes. 
    /// </summary>
    void Bar::AllocateResource()
    {
        if (_internalResourceSize > 0)
        {
            _pInternalResource = new char[_internalResourceSize];
            memset(_pInternalResource, 0, (sizeof(char) * _internalResourceSize));
        }
    }

    /// <summary>
    /// Deallocated any allocated resource.
    /// </summary>
    void Bar::DeallocateResource()
    {
        if (_pInternalResource != nullptr)
        {
            delete[] _pInternalResource;
            _pInternalResource = nullptr;
            _internalResourceSize = 0;
        }
    }

    /// <summary>
    /// Update internal char buffer with random values.
    /// </summary>
    void Bar::RandomizeInternalBuffers()
    {
        Foo::RandomizeInternalBuffers();

        if (HasValidBuffer())
        {
            srand((unsigned int)time(NULL));
            for (size_t bufferIdx = 0; bufferIdx < _internalResourceSize; bufferIdx++)
            {
                _pInternalResource[bufferIdx] = 'a' + (rand() % 26);
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
            for (size_t bufferIdx = 0; bufferIdx < _internalResourceSize; bufferIdx++)
            {
                bufferToStr.push_back(_pInternalResource[bufferIdx]);
            }
        }
        else
        {
            bufferToStr.append("Invalid buffer.");
        }

        printf("Function: %s, Values: %s \n", __FUNCTION__, bufferToStr.c_str());
    }

#pragma endregion RAIIDeepCopyCpp03_Bar

}