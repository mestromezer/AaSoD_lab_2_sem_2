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

stats comb_sort(vector<int> *data)
{
    int c_copy = 0;
    int c_comp = 0;

    double factor = 1.2473309;   // фактор уменьшения
    int step = data->size() - 1; // шаг сортировки

    // Последняя итерация цикла, когда step==1 эквивалентна одному проходу сортировки пузырьком
    while (step >= 1)
    {
        for (int i = 0; i + step < data->size(); i++)
        {
            if (data->at(i) > data->at(i + step))
            {
                std::swap(data->at(i), data->at(i + step));
            }
        }
        step /= factor;
    }

    return stats(c_copy, c_comp);
}

stats quickSort(vector<int> *v, int low, int high, stats c = stats())
{
    int i = low;
    int j = high;
    int pivot = v->at((i + j) / 2);
    int temp;

    while (i <= j)
    {
        while (++c.m_compare && v->at(i) < pivot)
            i++;
        while (++c.m_compare && v->at(j) > pivot)
            j--;
        if (i <= j)
        {
            temp = v->at(i);
            v->at(i) = v->at(j);
            v->at(j) = temp;
            i++;
            j--;
            c.m_copy++;
        }
    }
    if (j > low)
        c = quickSort(v, low, j);
    if (i < high)
        c = quickSort(v, i, high);

    return c;
}

stats insertion_sort(vector<int> *v)
{
    int c_copy = 0;
    int c_comp = 0;
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