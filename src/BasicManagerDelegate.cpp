#include "BasicManagerDelegate.hpp"

void BasicManagerDelegate::setIndex(int index)
{
    m_index = index;
}

const int BasicManagerDelegate::index() const
{
    return m_index;
}
