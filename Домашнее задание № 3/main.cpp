#include "source.h"

int main()
{
    // задание 1
    {
        cout << "Задание 1" << endl;
        list<float> test { 2.5, 4, 4.5, 10.5, 6 };
        print(test);

        addAverage(test);
        print(test);
        cout << endl;
    }

    // Задание 2
    {
        cout << "Задание 2" << endl;
        Matrix matrix;
        matrix.print();
        cout << "Определитель: " << matrix.det();
        cout << endl << endl;
    }

    // Задание 3
    {
        cout << "Задание 3" << endl;
        int v[4] { 1, 2, 3, 4 };
        for (Iterator<int> it : v)
            cout << *it << ' ';
        cout << endl;
        vector<int> vec { 1, 2, 3, 4 };
        for (Iterator<int> it : vec)
            cout << *it << ' ';
        cout << endl;
    }

    return 0;
}