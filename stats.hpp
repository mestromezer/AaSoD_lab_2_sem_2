#pragma once
struct stats
{
    int m_copy;
    int m_compare;
    stats(int copy = 0, int compare = 0) : m_copy(copy), m_compare(compare) {}
    stats(const stats &src)
    {
        this->m_copy = src.m_copy;
        this->m_compare = src.m_compare;
    }
};