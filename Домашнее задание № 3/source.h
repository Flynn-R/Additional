#pragma once
#include <iostream>
#include <list>
#include <array>
#include <vector>

using namespace std;

// Задание 1

void addAverage(list<float>&);
void print(list<float>&);

// Задание 2

#define SIZE 5

class Matrix
{
private:
    vector<vector<int>> matrix;
    int det(vector<vector<int>>&);
public:
    Matrix();
    void print();
    int det();
};

// Задание 3

template<class T>
class Iterator
{
private:
    T* ptr;
public:
    Iterator() = default;
    Iterator(T& val) : ptr(&val) {}
    void operator=(T val) { *ptr = val; }
    T* operator++() { return ++ptr; }
    T* operator--() { return --ptr; }
    T* operator++(T none)
    {
        T* newPtr = ptr;
        ++ptr;
        return newPtr;
    }
    T* operator--(T)
    {
        T* newPtr = ptr;
        --ptr;
        return newPtr;
    }
    T operator*() { return *ptr; }
};