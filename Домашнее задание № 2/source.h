#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include "Time.h"

using namespace std;

// Задание 1

template<typename T> void Swap(T*& ptr1, T*& ptr2)
{
    T* temp = ptr1;
    ptr1 = ptr2;
    ptr2 = temp;
}

// Задание 2

template<typename T> void SortPointers(vector<T*>& pointerList)
{
    sort(pointerList.begin(), pointerList.end(), [](T* ptr1, T* ptr2) {
        return *ptr1 < *ptr2;
    });
}

// Задание 3

class WarAndPeace
{
private:
    ifstream book;
public:
    WarAndPeace(string path) { book.open(path); }
    ~WarAndPeace() { book.close(); }

    void CountFind()
    {
        Timer timer("count_if() and find()");
        book.clear();
        book.seekg(0, ios::beg);
        size_t counter = 0;
        while (!book.eof())
        {
            string input;
            getline(book, input);
            // static const string vowels = "АаЕеЁёИиОоУуЫыЭэЮюЯя";
            static const string vowels = "AaEeIiOoUu";
            auto predicate = [](char symb)
            {
                return vowels.find(symb) != string::npos;
            };
            counter += count_if(input.begin(), input.end(), predicate);
        }
        cout << "Number of vowels: " << counter << endl;
        timer.print();
        
    }

    void CountFor()
    {
        Timer timer("count_if() and for()");
        book.clear();
        book.seekg(0, ios::beg);
        size_t counter = 0;
        while (!book.eof())
        {
            string input;
            getline(book, input);
            // static const string vowels = "АаЕеЁёИиОоУуЫыЭэЮюЯя";
            static const string vowels = "AaEeIiOoUu";
            auto predicate = [](char symb)
            {
                for (auto& it : vowels)
                {
                    if (symb == it)
                        return true;
                }
                return false;
            };
            counter += count_if(input.begin(), input.end(), predicate);
        }
        cout << "Number of vowels: " << counter << endl;
        timer.print();
    }
    
    void ForFind()
    {
        Timer timer("count_if() and for()");
        book.clear();
        book.seekg(0, ios::beg);
        size_t counter = 0;
        while (!book.eof())
        {
            string input;
            getline(book, input);
            // static const string vowels = "АаЕеЁёИиОоУуЫыЭэЮюЯя";
            static const string vowels = "AaEeIiOoUu";
            for (auto& symb : input)
            {
                if (vowels.find(symb) != string::npos)
                    ++counter;
            }
        }
        cout << "Number of vowels: " << counter << endl;
        timer.print();
    }

    void ForFor()
    {
        Timer timer("count_if() and for()");
        book.clear();
        book.seekg(0, ios::beg);
        size_t counter = 0;
        while (!book.eof())
        {
            string input;
            getline(book, input);
            // static const string vowels = "АаЕеЁёИиОоУуЫыЭэЮюЯя";
            static const string vowels = "AaEeIiOoUu";
            for (auto& symb : input)
            {
                for (auto& it : vowels)
                {
                    if (symb == it)
                        ++counter;
                }
            }
        }
        cout << "Number of vowels: " << counter << endl;
        timer.print();
    }
};