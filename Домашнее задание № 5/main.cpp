#include "source.h"

int main()
{
    setlocale(LC_ALL, "Russian");
    // Задание 1
    {
        cout << "Задание 1" << endl;
        list<string> ls { "hello", "world", "world", "good" };
        vector<string> v { "hello", "world", "world", "good" };
        deque<string> deq { "hello", "world", "world", "good" };
        cout << "List: ";
        uniqueWords<list<string>>(ls);
        cout << endl;
        cout << "Vector: ";
        uniqueWords<vector<string>>(v);
        cout << endl;
        cout << "Deque: ";
        uniqueWords<deque<string>>(deq);
        cout << endl;
    }

    // Задание 2
    {
        cout << "задание 2" << endl;
        cout << "Введите текст. Для окончания ввода нажмите 'Enter'." << endl;
        string str;
        getline(cin, str);
        rogue(move(str));
        cout << endl;
    }

    return 0;
}