#pragma once
#define NUM_OF_TEST 10
#include "../Sorters.hpp"
#include <vector>
#include <iostream>
#include <fstream>
#include <thread>
#include <future>

using namespace std;

typedef stats (*sorter)(vector<int> *);

struct KeyVal
{
    string Key;
    sorter Val;
    KeyVal(string Key, sorter Val) : Key(Key), Val(Val) {}
};

stats count_rand(int i, KeyVal pair)
{
    stats AvgRandom;
    for (int j = 0; j < 100; j++)
    {
        vector<int> *v = random_vector(i);
        AvgRandom = AvgRandom + pair.Val(v);
        delete v;
    }
    return AvgRandom;
}

stats count_sorted(int i, KeyVal pair)
{
    stats AvgSorted;
    vector<int> *v = new vector<int>(i);
    for (int j = 0; j < i; j++)
        v->push_back(j);
    AvgSorted = AvgSorted + pair.Val(v);
    delete v;
    return AvgSorted;
}

stats count_reversed(int i, KeyVal pair)
{
    stats AvgReversed;
    vector<int> *v = new vector<int>(i);
    for (int j = i; j > 0; j--)
        v->push_back(j);
    AvgReversed = AvgReversed + pair.Val(v);
    delete v;
    return AvgReversed;
}
void test()
{
    auto start = chrono::steady_clock::now();
    ofstream dump;
    dump.open("../TEST_FILES/test.txt");

    vector<KeyVal> keyvals;
    keyvals.push_back(KeyVal("comb sort", comb_sort));
    keyvals.push_back(KeyVal("quick sort", start_quickSort));
    keyvals.push_back(KeyVal("insertion sort", insertion_sort));

    for (auto pair : keyvals)
    {
        int coef = 1000;
        for (int i = 1000; i <= NUM_OF_TEST * 1000; i += coef)
        {
            stats AvgRandom = count_rand(i, pair);
            if (i == 10000)
            {
                coef = 25000;
                i = 25000;
            }
            cout << pair.Key << '\t' << i << '\t' << "Copy:" << AvgRandom.copy_count / NUM_OF_TEST << '\t' << "Compare:" << AvgRandom.comparison_count / NUM_OF_TEST << endl;
            dump << i << ';' << AvgRandom.copy_count / NUM_OF_TEST << ';' << AvgRandom.comparison_count / NUM_OF_TEST << endl;
        }

        vector<future<stats>> vec;

        coef = 25000;
        vec.push_back(async(&count_rand, coef, pair));

        coef = 50000;
        vec.push_back(async(&count_rand, coef, pair));

        coef = 75000;
        vec.push_back(async(&count_rand, coef, pair));

        coef = 100000;
        vec.push_back(async(&count_rand, coef, pair));

        vector<stats> AR;

        AR.push_back(vec[0].get());
        AR.push_back(vec[1].get());
        AR.push_back(vec[2].get());
        AR.push_back(vec[3].get());

        for (int i = 0; i < 4; i++)
        {
            cout << pair.Key << '\t' << (i + 1) * 25000 << '\t' << "Copy:" << AR[i].copy_count / NUM_OF_TEST << '\t' << "Compare:" << AR[i].comparison_count / NUM_OF_TEST << endl;
            dump << (i + 1) * 25000 << ';' << AR[i].copy_count / NUM_OF_TEST << ';' << AR[i].comparison_count / NUM_OF_TEST << endl;
        }

        vec.clear();
        AR.clear();

        coef = 1000;

        for (int i = 1000; i <= NUM_OF_TEST * 1000; i += coef)
        {
            stats AvgSorted = count_sorted(i, pair);
            if (i == 10000)
            {
                coef = 25000;
                i = 25000;
            }
            cout << pair.Key << '\t' << i << '\t' << "Copy:" << AvgSorted.copy_count / NUM_OF_TEST << '\t' << "Compare:" << AvgSorted.comparison_count / NUM_OF_TEST << endl;
            dump << i << ';' << AvgSorted.copy_count / NUM_OF_TEST << ';' << AvgSorted.comparison_count / NUM_OF_TEST << endl;
        }

        coef = 25000;
        vec.push_back(async(&count_sorted, coef, pair));

        coef = 50000;
        vec.push_back(async(&count_sorted, coef, pair));

        coef = 75000;
        vec.push_back(async(&count_sorted, coef, pair));

        coef = 100000;
        vec.push_back(async(&count_sorted, coef, pair));

        AR.push_back(vec[0].get());
        AR.push_back(vec[1].get());
        AR.push_back(vec[2].get());
        AR.push_back(vec[3].get());

        for (int i = 0; i < 4; i++)
        {
            cout << pair.Key << '\t' << (i + 1) * 25000 << '\t' << "Copy:" << AR[i].copy_count / NUM_OF_TEST << '\t' << "Compare:" << AR[i].comparison_count / NUM_OF_TEST << endl;
            dump << (i + 1) * 25000 << ';' << AR[i].copy_count / NUM_OF_TEST << ';' << AR[i].comparison_count / NUM_OF_TEST << endl;
        }

        vec.clear();
        AR.clear();

        /*for (int i = 1000; i <= NUM_OF_TEST * 1000; i += coef)
        {
            stats AvgSorted = count_sorted(i, pair);
            if (i == 10000)
            {
                coef = 25000;
                i = 25000;
            }
            cout << pair.Key << '\t' << i << '\t' << "Copy:" << AvgSorted.copy_count / NUM_OF_TEST << '\t' << "Compare:" << AvgSorted.comparison_count / NUM_OF_TEST << endl;
            dump << i << ';' << AvgSorted.copy_count / NUM_OF_TEST << ';' << AvgSorted.comparison_count / NUM_OF_TEST << ';' << endl;
        }*/

        coef = 1000;

        for (int i = 1000; i <= NUM_OF_TEST * 1000; i += coef)
        {
            stats AvgSorted = count_reversed(i, pair);
            if (i == 10000)
            {
                coef = 25000;
                i = 25000;
            }
            cout << pair.Key << '\t' << i << '\t' << "Copy:" << AvgSorted.copy_count / NUM_OF_TEST << '\t' << "Compare:" << AvgSorted.comparison_count / NUM_OF_TEST << endl;
            dump << i << ';' << AvgSorted.copy_count / NUM_OF_TEST << ';' << AvgSorted.comparison_count / NUM_OF_TEST << endl;
        }

        coef = 25000;
        vec.push_back(async(&count_reversed, coef, pair));

        coef = 50000;
        vec.push_back(async(&count_reversed, coef, pair));

        coef = 75000;
        vec.push_back(async(&count_reversed, coef, pair));

        coef = 100000;
        vec.push_back(async(&count_reversed, coef, pair));

        AR.push_back(vec[0].get());
        AR.push_back(vec[1].get());
        AR.push_back(vec[2].get());
        AR.push_back(vec[3].get());

        for (int i = 0; i < 4; i++)
        {
            cout << pair.Key << '\t' << (i + 1) * 25000 << '\t' << "Copy:" << AR[i].copy_count / NUM_OF_TEST << '\t' << "Compare:" << AR[i].comparison_count / NUM_OF_TEST << endl;
            dump << (i + 1) * 25000 << ';' << AR[i].copy_count / NUM_OF_TEST << ';' << AR[i].comparison_count / NUM_OF_TEST << endl;
        }

        vec.clear();
        AR.clear();
    }
    auto end = chrono::steady_clock::now();

    dump << "Tests time in seconds: "
         << chrono::duration_cast<chrono::hours>(end - start).count()
         << " sec";
}