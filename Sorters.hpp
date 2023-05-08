#pragma once

#include "stats.hpp"

#define EXIT_SUCCESS 0
#define GOLDEN_RATIO 1.61803398875
#include <iterator>
#include <iostream>
#include <vector>
#include <math.h>

using namespace std;

size_t lcg()
{
    static size_t x = 0;
    x = (1021 * x + 24631) % 100;
    return x;
}

vector<int> *random_vector(int size)
{
    vector<int> *v = new vector<int>(size);
    for (int i = 0; i < size; i++)
    {
        v->at(i) = lcg();
    }
    return v;
}

stats comb_sort(vector<int> *data)
{
    long c_copy = 0;
    long c_comp = 0;

    double factor = 1.2473309;
    int step = data->size() - 1;
    while (step >= 1)
    {
        for (int i = 0; i + step < data->size(); i++)
        {
            if (++c_comp && data->at(i) > data->at(i + step))
            {
                std::swap(data->at(i), data->at(i + step));
                c_copy++;
            }
        }
        step /= factor;
    }

    return stats(c_copy, c_comp);
}

void quickSort(vector<int> *v, int low, int high, stats *c)
{
    int i = low;
    int j = high;
    int pivo = v->at((i + j) / 2);
    int temp;

    while (i <= j)
    {
        while (++c->comparison_count && v->at(i) < pivo)
            i++;
        while (++c->comparison_count && v->at(j) > pivo)
            j--;
        if (i <= j)
        {
            temp = v->at(i);
            v->at(i) = v->at(j);
            v->at(j) = temp;
            i++;
            j--;
            c->copy_count++;
        }
    }
    if (j > low)
        quickSort(v, low, j, c);
    if (i < high)
        quickSort(v, i, high, c);

    // return c;
}

stats start_quickSort(vector<int> *v)
{
    stats *Counter = new stats;

    quickSort(v, 0, v->size() - 1, Counter);

    stats res(*Counter);

    delete Counter;

    return res;
}

stats insertion_sort(vector<int> *v)
{
    long c_copy = 0;
    long c_comp = 0;
    for (int i = 1; i < v->size(); i++)
    {
        int id = i;
        while (++c_comp && id > 0 && v->at(id) < v->at(id - 1))
        {
            int tmp = v->at(id);
            v->at(id) = v->at(id - 1);
            v->at(id - 1) = tmp;
            id--;
            c_copy++;
        }
    }

    return stats(c_copy, c_comp);
}