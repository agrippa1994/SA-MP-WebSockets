#ifndef UTILS_HPP
#define UTILS_HPP

#include <boost/optional.hpp>
#include <string>

#define DISABLE_CPY_CTOR(X) \
    X(const X&) = delete; \
    X& operator=(const X&) = delete;

#define DISABLE_MOV_CTOR(X) \
    X(X&&) = delete;

#define DISABLE_CPY_MOV_CTOR(X) DISABLE_CPY_CTOR(X) DISABLE_MOV_CTOR(X)

template<typename T>
using Optional = boost::optional<T>;

#endif
