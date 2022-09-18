#include "source.h"

// Задание 1

void addAverage(list<float>& list)
{
    float average = 0;
    for (auto& val : list)
        average += val;
    list.push_back(average / list.size());
}

void print(list<float>& list)
{
    for (auto& it : list)
        cout << it << ' ';
    cout << endl;
}

// Задание 2

Matrix::Matrix()
{
    
}