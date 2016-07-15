#pragma once
#include <map>

template<typename T>
class IndexedVector : public std::map<int, T>
{
public:
    int operator += (T t) {
        int i = 0;
        while (hasKey(i))
            i++;

        (*this)[i] = t;
        return i;
    }

    bool operator -= (int key) {
        if (!hasKey(key))
            return false;

        return this->erase(key) > 0;
    }

    bool hasKey(int key) {
        for (const auto& i : (*this))
            if (i.first == key)
                return true;

        return false;
    }

    template<typename Pred>
    int indexOf(Pred p) {
        for (auto& i : (*this))
            if (p(i.second))
                return i.first;

        return -1;
    }
};
