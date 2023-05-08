#pragma once
/*
struct stats
{
    int m_copy;
    int m_compare;
    stats(int copy = 0, int compare = 0) : m_copy(copy), m_compare(compare) {}
    stats operator+(const stats &src)
    {
        this->m_compare += src.m_compare;
        this->m_copy += src.m_copy;
        return *this;
    }
    stats(const stats &src)
    {
        this->m_copy = src.m_copy;
        this->m_compare = src.m_compare;
    }
};*/
struct stats
{
    long comparison_count = 0;
    long copy_count = 0;
    stats(long copy = 0, long compare = 0) : copy_count(copy), comparison_count(compare) {}
    stats operator+(const stats &src)
    {
        this->comparison_count += src.comparison_count;
        this->copy_count += src.copy_count;
        return *this;
    }
    stats(const stats &src)
    {
        this->copy_count = src.copy_count;
        this->comparison_count = src.comparison_count;
    }
};
