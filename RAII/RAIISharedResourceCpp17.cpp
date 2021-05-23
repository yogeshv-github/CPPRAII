#include "RAIISharedResourceCpp17.h"
#include <memory.h>
#include <string>
#include <time.h>
#include <typeinfo>

namespace RAIISharedResourceCpp17
{
#pragma region RAIISharedResourceCpp17_Foo

    Foo::Foo(const size_t resourceSz) :
        _internalResource(nullptr)
    {
        AllocateResource(resourceSz);
    }

    Foo::~Foo()
    {
        DeallocateResource();
    }

    Foo::Foo(const Foo& other) :
        _internalResource(other._internalResource)
    {}

    Foo& Foo::operator= (const Foo& other)
    {
        if (this != &other)
        {
            _internalResource = other._internalResource;
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
            (_internalResource->size() == other._internalResource->size()))
        {
            return (_internalResource == other._internalResource);
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
        return (_internalResource != nullptr);
    }

    void Foo::AllocateResource(size_t resourceSz)
    {
        if (resourceSz > 0)
        {
            _internalResource = std::make_shared<int_array_t>();
            _internalResource->resize(resourceSz);
        }
    }

    void Foo::DeallocateResource()
    {
        if (_internalResource != nullptr)
        {
            _internalResource->clear();
            _internalResource.reset();
        }
    }

    void Foo::RandomizeInternalBuffers() 
    {
        if (HasValidBuffer())
        {
            srand((unsigned int)time(NULL));
            const size_t resSz = _internalResource->size();
            for (size_t bufferIdx = 0; bufferIdx < resSz; bufferIdx++)
            {
                const int randomVal = (rand() % resSz);
                auto resBuffer = *_internalResource;
                resBuffer[bufferIdx] = randomVal;
            }
        }
    }

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

    Bar::Bar(const size_t resourceSz) :
        Foo(resourceSz),
        _internalResource(nullptr)
    {
        AllocateResource(resourceSz);
    }

    Bar::~Bar()
    {
        DeallocateResource();
    }

    Bar::Bar(const Bar& other) :
        Foo(other),
        _internalResource(other._internalResource)
    {}

    Bar& Bar::operator= (const Bar& other)
    {
        if (this != &other)
        {
            _internalResource = other._internalResource;
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
            (_internalResource->size() == otherBar._internalResource->size()))
        {
            return (_internalResource == otherBar._internalResource);
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
        return (_internalResource != nullptr);
    }

    void Bar::AllocateResource(size_t resourceSz)
    {
        if (resourceSz > 0)
        {
            _internalResource = std::make_shared<char_array_t>();
            _internalResource->resize(resourceSz);
        }
    }

    void Bar::DeallocateResource()
    {
        if (_internalResource != nullptr)
        {
            _internalResource->clear();
            _internalResource.reset();
        }
    }

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
                auto resBuffer = *_internalResource;
                resBuffer[bufferIdx] = randomVal;
            }
        }
    }

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