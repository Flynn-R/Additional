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
    matrix.reserve(SIZE);
    for (size_t i = 0; i < SIZE; ++i)
    {
        matrix[i].reserve(SIZE);
        for (size_t j = 0; j < SIZE; ++j)
            matrix[i].push_back(rand() % 100);
    }
}

void Matrix::print()
{
    for (size_t i = 0; i < SIZE; ++i)
    {
        for (size_t j = 0; j < SIZE; ++j)
            cout << matrix[i][j] << ' ';
        cout << endl;
    }
}

int Matrix::det()
{
    if (matrix.size() == 1)
        return matrix[0][0];
    return det(matrix);
}

int Matrix::det(vector<vector<int>>& minor)
{
    int res = 0;
    if (minor.size() == 1)
        return minor[0][0];
    size_t size = minor[0].size();
    vector<vector<int>> newMinor(size - 1, vector<int>(size - 1));
    for (size_t i = 0; i < size; ++i)
    {
        for (size_t j = 1; j < size; ++j)
        {
            size_t m = 0;
            for (size_t k = 0; k < size; ++k)
            {
                if (i != k)
                    newMinor[j - 1][m++] = minor[j][k];
            }
        }
        if (i % 2 == 0)
            res += minor[0][i] * det(newMinor);
        else
            res -= minor[0][i] * det(newMinor);
    }
    return res;
}