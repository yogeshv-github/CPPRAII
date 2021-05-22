#include "RAIIDemo.h"
#include <memory.h>
#include <string>
#include <time.h>
#include <typeinfo>

namespace RAIIDemoCpp03
{
    /*static*/ void Test()
    {
        Foo* foo1 = new Foo(4);
        foo1->RandomizeInternalBuffers();
        foo1->PrintInternalBuffers();

        Foo* bar1 = new Bar(1);
        bar1->RandomizeInternalBuffers();
        bar1->PrintInternalBuffers();

        Bar* bar2 = new Bar(2);
        bar2->RandomizeInternalBuffers();
        bar2->PrintInternalBuffers();

        printf("Is foo1 equal bar1 before assignment: %d \n", (*foo1 == *bar1));
        *foo1 = *bar1;
        printf("Is foo1 equal bar1 after assignment: %d \n", (*foo1 == *bar1));

        printf("Is bar1 equal bar2 before assignment: %d \n", (*bar1 == *bar2));
        *bar1 = *bar2;
        printf("Is bar1 equal bar2 after assignment: %d \n", (*bar1 == *bar2));

        Bar* bar1Casted = dynamic_cast<Bar*>(bar1);
        printf("Is casted bar1 equal bar2 before assignment: %d \n", (*bar1 == *bar2));
        *bar1Casted = *bar2;
        printf("Is casted bar1 equal bar2 after assignment: %d \n", (*bar1 == *bar2));

        delete foo1;
        delete bar1;
        delete bar2;
    }

#pragma region RAIIDemoCpp03_Foo

    Foo::Foo(const size_t resourceSz) :
        _internalResourceSize(resourceSz),
        _pInternalResource(nullptr)
    {
        if (_internalResourceSize > 0)
        {
            _pInternalResource = new int[_internalResourceSize];
            memset(_pInternalResource, 0, (sizeof(int) * _internalResourceSize));
        }
    }

    Foo::~Foo()
    {
        if (_pInternalResource)
        {
            delete _pInternalResource;
        }
    }

    Foo::Foo(const Foo& other) :
        _internalResourceSize(other._internalResourceSize),
        _pInternalResource(nullptr)
    {
        // Deep copy.
        if (_internalResourceSize > 0)
        {
            _pInternalResource = new int[_internalResourceSize];
            memset(_pInternalResource, 0, (sizeof(int) * _internalResourceSize));

            if (other._pInternalResource != nullptr)
            {
                memcpy(_pInternalResource, other._pInternalResource, (sizeof(int) * _internalResourceSize));
            }
        }
    }

    Foo& Foo::operator= (const Foo& other)
    {
        if (this != &other)
        {
            if (_pInternalResource != nullptr)
            {
                delete _pInternalResource;
                _pInternalResource = nullptr;
                _internalResourceSize = 0;
            }

            // Deep copy.
            _internalResourceSize = other._internalResourceSize;
            if (_internalResourceSize > 0)
            {
                _pInternalResource = new int[_internalResourceSize];
                memset(_pInternalResource, 0, (sizeof(int) * _internalResourceSize));

                if (other._pInternalResource != nullptr)
                {
                    memcpy(_pInternalResource, other._pInternalResource, (sizeof(int) * _internalResourceSize));
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
            return (memcmp(_pInternalResource, other._pInternalResource, (sizeof(int) * _internalResourceSize)) == 0);
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
        return ((_pInternalResource != nullptr) && (_internalResourceSize > 0));
    }

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

#pragma endregion RAIIDemoCpp03_Foo

#pragma region RAIIDemoCpp03_Bar

    Bar::Bar(const size_t resourceSz) :
        Foo(resourceSz),
        _internalResourceSize(resourceSz),
        _pInternalResource(nullptr)
    {
        if (_internalResourceSize > 0)
        {
            _pInternalResource = new char[_internalResourceSize];
            memset(_pInternalResource, 0, (sizeof(char) * _internalResourceSize));
        }
    }

    Bar::~Bar()
    {
        if (_pInternalResource)
        {
            delete _pInternalResource;
        }
    }

    Bar::Bar(const Bar& other) :
        Foo(other),
        _internalResourceSize(other._internalResourceSize),
        _pInternalResource(nullptr)
    {
        // Deep copy.
        if (_internalResourceSize > 0)
        {
            _pInternalResource = new char[_internalResourceSize];
            memset(_pInternalResource, 0, (sizeof(char) * _internalResourceSize));

            if (other._pInternalResource != nullptr)
            {
                memcpy(_pInternalResource, other._pInternalResource, (sizeof(char) * _internalResourceSize));
            }
        }
    }

    Bar& Bar::operator= (const Bar& other)
    {
        if (this != &other)
        {
            if (_pInternalResource != nullptr)
            {
                delete _pInternalResource;
                _pInternalResource = nullptr;
                _internalResourceSize = 0;
            }

            // Deep copy.
            _internalResourceSize = other._internalResourceSize;
            if (_internalResourceSize > 0)
            {
                _pInternalResource = new char[_internalResourceSize];
                memset(_pInternalResource, 0, (sizeof(char) * _internalResourceSize));

                if (other._pInternalResource != nullptr)
                {
                    memcpy(_pInternalResource, other._pInternalResource, (sizeof(char) * _internalResourceSize));
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
            return (memcmp(_pInternalResource, otherBar._pInternalResource, (sizeof(char) * _internalResourceSize)) == 0);
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
        return ((_pInternalResource != nullptr) && (_internalResourceSize > 0));
    }

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
#pragma endregion RAIIDemoCpp03_Bar

}