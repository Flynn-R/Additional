#pragma once
#include <iostream>
#include <list>
#include <vector>

using namespace std;

// Задание 1

void addAverage(list<float>&);
void print(list<float>&);

// Задание 2

class Matrix
{
private:
    vector<vector<int>> matrix;
public:
    Matrix();
    void print();
    int det();
    int det(vector<vector<int>>);
};