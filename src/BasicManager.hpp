#ifndef BASICMANAGER_HPP
#define BASICMANAGER_HPP

#include "IndexedVector.hpp"
#include "Utils.hpp"

#include <memory>
#include <type_traits>

template<typename T, typename Enabler = void>
class BasicManager;

template<typename T>
class BasicManager<T, typename std::enable_if<std::is_base_of<class BasicManagerDelegate, T>::value>::type>
{
    typedef std::shared_ptr<T> Ptr;
    IndexedVector<Ptr> m_container;

public:
    template<typename ...Args>
    int create(Args&&... p)
    {
        auto ptr = std::make_shared<T>(p...);

        int index = m_container += ptr;
        ptr->setIndex(index);

        return index;
    }

    bool destroy(int index)
    {
        return m_container -= index;
    }

    Optional<Ptr> operator[](int index)
    {
        try
        {
            return m_container.at(index);
        }
        catch(...)
        {
            return nullptr;
        }
    }

    void clear()
    {
        m_container.clear();
    }
};

#endif
