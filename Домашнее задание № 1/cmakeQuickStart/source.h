#pragma once
#include <iostream>
#include <optional>
#include <tuple>
#include <vector>
#include <fstream>
#include <algorithm>

using namespace std;

// Person

struct Person
{
    string surname;
    string name;
    optional<string> patronicName;
};

ostream& operator<<(ostream&, Person&);
bool operator<(Person&, Person&);
bool operator==(Person&, Person&);

// PhoneNumber

struct PhoneNumber
{
    unsigned short countryCode;
    unsigned short cityCode;
    string number;
    optional<unsigned short> additionalNumber;
};

ostream& operator<<(ostream&, PhoneNumber&);
bool operator<(PhoneNumber&, PhoneNumber&);
bool operator==(PhoneNumber&, PhoneNumber&);

// PhoneBook

class PhoneBook
{
private:
    vector<pair<Person, PhoneNumber>> list;
public:
    PhoneBook(ifstream&);
    friend ostream& operator<<(ostream&, PhoneBook&);
    void SortByName();
    void SortByPhone();
    pair<string, PhoneNumber> GetPhoneNumber(string);
    void ChangePhoneNumber(Person, PhoneNumber);
};