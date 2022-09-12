#include "source.h"

int main()
{
    setlocale(LC_ALL, "Russian");
    ifstream file("~/Документы/C++: сложные моменты/Домашнее задание № 1/PhoneBook.txt"); // путь к файлу PhoneBook.txt
    PhoneBook book(file);
    cout << book;
    cout << "------SortByPhone-------" << endl;
    book.SortByPhone();
    cout << book;
    cout << "------SortByName--------" << endl;
    book.SortByName();
    cout << book;
    cout << "-----GetPhoneNumber-----" << endl;
    // лямбда функция, которая принимает фамилию и выводит номер телефона этого человека, либо строку с ошибкой
    auto print_phone_number = [&book](const string& surname)
    {
        cout << surname << "\t";
        auto answer = book.GetPhoneNumber(surname);
        if (get<0>(answer).empty())
            cout << get<1>(answer);
        else
            cout << get<0>(answer);
        cout << endl;
    };
    // вызовы лямбды
    // print_phone_number("Ivanov");
    print_phone_number("Иванов");
    // print_phone_number("Petrov");
    print_phone_number("Петров");
    cout << "----ChangePhoneNumber----" << endl;
    // book.ChangePhoneNumber(Person{ "Kotov", "Vasilii", "Eliseevich" },
    // PhoneNumber{7, 123, "15344458", nullopt});
    book.ChangePhoneNumber(Person{ "Котов", "Василий", "Елисеевич" },
    PhoneNumber{7, 123, "15344458", nullopt});
    // book.ChangePhoneNumber(Person{ "Mironova", "Margarita", "Vladimirovna" },
    // PhoneNumber{ 16, 465, "9155448", 13 });
    book.ChangePhoneNumber(Person{ "Миронова", "Маргарита", "Владимировна" },
    PhoneNumber{ 16, 465, "9155448", 13 });
    cout << book;
    return 0;
}