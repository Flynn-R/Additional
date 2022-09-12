#pragma once
#include <iostream>
#include <optional>
#include <tuple>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

struct Person
{
    string surname, name;
    optional<string> patronicName;
    friend ostream& operator<<(ostream&, Person&);
    friend bool operator<(Person&, Person&);
    friend bool operator==(Person&, Person&);
};

struct PhoneNumber
{
    int country, city;
    string number;
    optional<int> additional;
    friend ostream& operator<<(ostream&, PhoneNumber&);
    friend ostream& operator<<(ostream&, optional<PhoneNumber>);
    friend bool operator<(PhoneNumber&, PhoneNumber&);
    friend bool operator==(PhoneNumber&, PhoneNumber&);
};

class PhoneBook
{
private:
    vector<pair<Person, PhoneNumber>> list;
public:
    PhoneBook(ifstream&);
    void SortByName();
    void SortByPhone();
    pair<string, optional<PhoneNumber>> GetPhoneNumber(string);
    void ChangePhoneNumber(Person, PhoneNumber);
    friend ostream& operator<<(ostream&, PhoneBook&);
};