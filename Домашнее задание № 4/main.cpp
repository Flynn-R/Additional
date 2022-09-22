#include "source.h"

int main()
{
    // Задание 1
    {
        cout << "Задание 1" << endl;
        vector<int> v(10);
        generate(v.begin(), v.end(), []() { return rand() % 100; });
        print(v);
        sort(v.begin(), v.end());
        print(v);
        insert_sorted(v, 24);
        print(v);
        insert_sorted(v, 24);
        insert_sorted(v, 212);
        insert_sorted(v, 0);
        print(v);
        cout << endl;
    }

    // Задание 2
    {
        cout << "Задание 2" << endl;
        vector<double> a(10);
        generate(a.begin(), a.end(),
        []() { return static_cast<double>(rand() % 100) / 10; });
        print(a);
        vector<int> b(10);
        transform(a.begin(), a.end(), b.begin(),
        [](double i) { return static_cast<int>(i);});
        print(b);

        cout << "Error: " << error(a, b) << endl;
    }

    return 0;
}