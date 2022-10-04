#pragma once
#include <iostream>
#include <thread>
#include <mutex>
#include <vector>

using namespace std;

// Задание 1

mutex mx;

void pcout()
{
    lock_guard lg(mx);
    cout << "This is thread #";
    this_thread::sleep_for(1s);
    cout << this_thread::get_id();
    this_thread::sleep_for(1s);
    cout << endl;
}

// Задание 2

size_t prime(size_t i, size_t& progress)
{
    progress = 1;
    vector<size_t> primes { 2 };
    size_t temp = 2;
    while (progress != i)
    {
        for (vector<size_t>::iterator it = primes.begin(); it != primes.end(); ++it)
        {
            if (temp % *it == 0)
            {
                ++temp;
                it = primes.begin() - 1;

            }
            else if (it == primes.end() - 1)
            {
                primes.push_back(temp);
                break;
            }
        }
        ++progress;
    }
    return *(primes.end() - 1);
}

// Задание 3

void owner(vector<int>& items)
{
    while (true)
    {
        this_thread::sleep_for(1s);
        items.push_back(rand() % 100);
    }
}

void thief(vector<int>& items)
{
    while (true)
    {
        this_thread::sleep_for(500ms);
        if (!items.empty())
            items.erase(max_element(items.begin(), items.end()));
    }
}

void print(vector<int>& items)
{
    copy(items.begin(), items.end(), ostream_iterator<int>{cout, " "});
    cout << endl;
}