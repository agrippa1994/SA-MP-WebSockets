#ifndef BASICMANAGERDELEGATE_HPP
#define BASICMANAGERDELEGATE_HPP

class BasicManagerDelegate
{
    int m_index = -1;

public:
    void setIndex(int index);
    const int index() const;
};

#endif
