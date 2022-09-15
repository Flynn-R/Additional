#include "source.h"

int main()
{
    // Задание 1
    /*{
        char a = 'A';
        char b = 'B';

        char* ptrA = &a;
        char* ptrB = &b;

        cout << "Before Swap():" << endl;
        cout << a << ' ' << b << endl;
        cout << *ptrA << ' ' << *ptrB << endl;

        Swap<char>(ptrA, ptrB);

        cout << "After Swap():" << endl;
        cout << a << ' ' << b << endl;
        cout << *ptrA << ' ' << *ptrB << endl;
    }*/

    // Задание 2
    /*{
        int a = 2, b = 1, c = 3;
        int* ptrA = &a;
        int* ptrB = &b;
        int* ptrC = &c;

        vector<int*> list { ptrA, ptrB, ptrC };

        cout << "Before SortPointers():" << endl;
        cout << *list[0] << ' ' << *list[1] << ' ' << *list[2] << endl;

        SortPointers(list);

        cout << "After SortPointers():" << endl;
        cout << *list[0] << ' ' << *list[1] << ' ' << *list[2] << endl;
    }*/

    // Задание 3
    {
        WarAndPeace book("/home/pierre/test.txt");
        book.CountFind();
        book.CountFor();
        book.ForFind();
        book.ForFor();
    }

    return 0;
}