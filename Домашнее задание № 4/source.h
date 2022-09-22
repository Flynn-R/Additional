#pragma once
#include <iostream>
#include <algorithm>
#include <vector>
#include <list>
#include <deque>
#include <numeric>

using namespace std;

// Задание 1

template<typename T, typename U> void insert_sorted(T& array, U&& value)
{
    auto it = lower_bound(begin(array), end(array), value);
    array.insert(it, value);
}

template<typename T> void print(T& array)
{
    copy(begin(array), end(array), ostream_iterator<double> { cout, "\t"});
    cout << endl;
}

// Задание 2

double error(vector<double> analog, vector<int>& digital)
{
    auto it = digital.begin();
    transform(analog.begin(), analog.end(), analog.begin(),
    [&](double a) { return (a - *it) * (a - *it++); });
    return accumulate(analog.begin(), analog.end(), static_cast<double>(0));
}