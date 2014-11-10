#ifndef INDEXEDVECTOR_HPP
#define INDEXEDVECTOR_HPP

#include <boost/optional.hpp>
#include <map>

template<typename T>
class IndexedVector : public std::map<int, T>
{
public:
	int operator += (T t) {
		int i = 0;
		while (doesKeyExist(i))
			i++;

		(*this)[i] = t;
		return i;
	}

	bool operator -= (int key) {
		if (!doesKeyExist(key))
			return false;

		return this->erase(key) > 0;
	}

	bool doesKeyExist(int key) {
		for (const auto& i : (*this)) {
			if (i.first == key)
				return true;
		}

		return false;
	}

	template<typename Pred>
	boost::optional<int> index_of(Pred p) {
		for (auto& i : (*this)) {
			if (p(i.second))
				return i.first;
		}

		return nullptr;
	}
};

#endif
