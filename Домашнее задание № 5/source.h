#pragma once
#include <iostream>
#include <set>
#include <vector>
#include <deque>
#include <list>
#include <iterator>
#include <unordered_set>
#include <sstream>
#include <map>

using namespace std;

// Задание 1

template<typename T>
void uniqueWords(T& array)
{
    unordered_set<string> uniq(array.begin(), array.end());
    copy(uniq.begin(), uniq.end(), ostream_iterator<string>(cout, " "));
};

// Задание 2

void rogue(string&& s)
{
    auto it = s.begin();
    stringstream ss;
    ss << s;
    string temp;
    multimap<size_t, string> sentence_count;
    size_t count = 0;
    while (ss >> s)
    {
        auto it = find_if(s.begin(), s.end(),
            [](char a)
            {
                return (a == '.' || a == '?' || a == '!');
            });
        
        temp += s + ' ';
        ++count;
        if (it != s.end())
        {
            sentence_count.emplace(make_pair(count, temp));
            temp.clear();
            count = 0;
        }
    }
    for_each(sentence_count.begin(), sentence_count.end(),
        [](pair<size_t, string> sentence)
        {
            cout << sentence.second << "\tКоличество слов: " << sentence.first << endl;
        });
}