#include "source.h"

int main()
{
    setlocale(LC_ALL, "Russian");
    
    ifstream file("/home/pierre/PhoneBook.txt");
    PhoneBook book(file);

    cout << book;
}