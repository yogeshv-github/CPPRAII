#include "RAIIDeepCopyCpp17.h"
#include <memory.h>
#include <string>
#include <time.h>
#include <typeinfo>

namespace RAIIDeepCopyCpp17
{
#pragma region RAIIDeepCopyCpp17_Foo

    Foo::Foo(const size_t resourceSz) :
        _internalResourceSize(resourceSz),
        _internalResource(nullptr)
    {
        if (_internalResourceSize > 0)
        {
            _internalResource = std::make_unique<int[]>(_internalResourceSize);
            memset(_internalResource.get(), 0, (sizeof(int) * _internalResourceSize));
        }
    }

    Foo::~Foo()
    {
        if (_internalResource != nullptr)
        {
            _internalResource.reset(nullptr);
        }
    }

    Foo::Foo(const Foo& other) :
        _internalResourceSize(other._internalResourceSize),
        _internalResource(nullptr)
    {
        // Deep copy.
        if (_internalResourceSize > 0)
        {
            _internalResource = std::make_unique<int[]>(_internalResourceSize);
            memset(_internalResource.get(), 0, (sizeof(int) * _internalResourceSize));

            if (other._internalResource != nullptr)
            {
                memcpy(_internalResource.get(), other._internalResource.get(), (sizeof(int) * _internalResourceSize));
            }
        }
    }

    Foo& Foo::operator= (const Foo& other)
    {
        if (this != &other)
        {
            if (_internalResource != nullptr)
            {
                _internalResource.reset(nullptr);
                _internalResourceSize = 0;
            }

            // Deep copy.
            _internalResourceSize = other._internalResourceSize;
            if (_internalResourceSize > 0)
            {
                _internalResource = std::make_unique<int[]>(_internalResourceSize);
                memset(_internalResource.get(), 0, (sizeof(int) * _internalResourceSize));

                if (other._internalResource != nullptr)
                {
                    memcpy(_internalResource.get(), other._internalResource.get(), (sizeof(int) * _internalResourceSize));
                }
            }
        }

        return (*this);
    }

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
            return (memcmp(_internalResource.get(), other._internalResource.get(), (sizeof(int) * _internalResourceSize)) == 0);
        }

        return false;
    }

    bool Foo::operator== (const Foo& other) const
    {
        return this->Equals(other);
    }

    bool Foo::operator!= (const Foo& other) const
    {
        return !(*this == other);
    }

    bool Foo::HasValidBuffer() const
    {
        return ((_internalResource != nullptr) && (_internalResourceSize > 0));
    }

    void Foo::RandomizeInternalBuffers() 
    {
        if (HasValidBuffer())
        {
            srand((unsigned int)time(NULL));
            for (size_t bufferIdx = 0; bufferIdx < _internalResourceSize; bufferIdx++)
            {
                _internalResource.get()[bufferIdx] = rand() % _internalResourceSize;
            }
        }
    }

    void Foo::PrintInternalBuffers()
    {
        std::string bufferToStr;
        if (HasValidBuffer())
        {
            for (size_t bufferIdx = 0; bufferIdx < _internalResourceSize; bufferIdx++)
            {
                bufferToStr.append(std::to_string(_internalResource.get()[bufferIdx])).append(",");
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

#pragma endregion RAIIDeepCopyCpp17_Foo

#pragma region RAIIDeepCopyCpp17_Bar

    Bar::Bar(const size_t resourceSz) :
        Foo(resourceSz),
        _internalResourceSize(resourceSz),
        _internalResource(nullptr)
    {
        if (_internalResourceSize > 0)
        {
            _internalResource = std::make_unique<char[]>(_internalResourceSize);
            memset(_internalResource.get(), 0, (sizeof(char) * _internalResourceSize));
        }
    }

    Bar::~Bar()
    {
        if (_internalResource != nullptr)
        {
            _internalResource.reset(nullptr);
        }
    }

    Bar::Bar(const Bar& other) :
        Foo(other),
        _internalResourceSize(other._internalResourceSize),
        _internalResource(nullptr)
    {
        // Deep copy.
        if (_internalResourceSize > 0)
        {
            _internalResource = std::make_unique<char[]>(_internalResourceSize);
            memset(_internalResource.get(), 0, (sizeof(char) * _internalResourceSize));

            if (other._internalResource != nullptr)
            {
                memcpy(_internalResource.get(), other._internalResource.get(), (sizeof(char) * _internalResourceSize));
            }
        }
    }

    Bar& Bar::operator= (const Bar& other)
    {
        if (this != &other)
        {
            if (_internalResource != nullptr)
            {
                _internalResource.reset(nullptr);
                _internalResourceSize = 0;
            }

            // Deep copy.
            _internalResourceSize = other._internalResourceSize;
            if (_internalResourceSize > 0)
            {
                _internalResource = std::make_unique<char[]>(_internalResourceSize);
                memset(_internalResource.get(), 0, (sizeof(char) * _internalResourceSize));

                if (other._internalResource != nullptr)
                {
                    memcpy(_internalResource.get(), other._internalResource.get(), (sizeof(char) * _internalResourceSize));
                }
            }
        }

        return (*this);
    }

    bool Bar::Equals(Foo const& other) const
    {
        if (typeid(*this) != typeid(other))
        {
            return false;
        }

        if (!Foo::Equals(other))
        {
            return false;
        }

        auto otherBar = static_cast<Bar const&>(other);
        if (HasValidBuffer() &&
            otherBar.HasValidBuffer() &&
            (_internalResourceSize == otherBar._internalResourceSize))
        {
            return (memcmp(_internalResource.get(), otherBar._internalResource.get(), (sizeof(char) * _internalResourceSize)) == 0);
        }

        return false;
    }

    bool Bar::operator==(const Bar& other) const
    {
        return this->Equals(other);
    }

    bool Bar::operator!=(const Bar& other) const
    {
        return !(*this == other);
    }

    bool Bar::HasValidBuffer() const
    {
        return ((_internalResource != nullptr) && (_internalResourceSize > 0));
    }

    void Bar::RandomizeInternalBuffers()
    {
        Foo::RandomizeInternalBuffers();

        if (HasValidBuffer())
        {
            srand((unsigned int)time(NULL));
            for (size_t bufferIdx = 0; bufferIdx < _internalResourceSize; bufferIdx++)
            {
                _internalResource.get()[bufferIdx] = 'a' + (rand() % 26);
            }
        }
    }

    void Bar::PrintInternalBuffers()
    {
        Foo::PrintInternalBuffers();

        std::string bufferToStr;
        if (HasValidBuffer())
        {
            for (size_t bufferIdx = 0; bufferIdx < _internalResourceSize; bufferIdx++)
            {
                bufferToStr.push_back(_internalResource.get()[bufferIdx]);
            }
        }
        else
        {
            bufferToStr.append("Invalid buffer.");
        }

        printf("Function: %s, Values: %s \n", __FUNCTION__, bufferToStr.c_str());
    }
#pragma endregion RAIIDeepCopyCpp17_Bar

}