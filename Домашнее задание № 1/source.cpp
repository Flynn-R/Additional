#include "source.h"

//Person

ostream& operator<<(ostream& out, Person& p)
{
    out << p.surname << " " << p.name;
    if (p.patronicName)
        out << " " << p.patronicName.value();
    out << endl;
    return out;
}

bool operator<(Person& p1, Person& p2)
{
    if (!p1.patronicName || !p2.patronicName)
        return  tie(p1.surname, p1.name) < tie(p2.surname, p2.name) ;
    return tie(p1.surname, p1.name, p1.patronicName) < tie(p2.surname, p2.name, p2.patronicName);
}

bool operator==(Person& p1, Person& p2)
{
    if (!p1.patronicName || !p2.patronicName)
        return tie(p1.surname, p1.name) == tie(p2.surname, p2.name);
    return tie(p1.surname, p1.name, p1.patronicName) == tie(p2.surname, p2.name, p2.patronicName);
}

// Phone Number

ostream& operator<<(ostream& out, PhoneNumber& nmb)
{
    out << '+' << nmb.country << '(' << nmb.city << ')' << nmb.number;
    if (nmb.additional)
        out << ' ' << nmb.additional.value();
    out << endl;
    return out;
}

ostream& operator<<(ostream& out, optional<PhoneNumber> nmb)
{
    out << nmb.value_or(0);
    return out;
}

bool operator<(PhoneNumber& nmb1, PhoneNumber& nmb2)
{
    if (!nmb1.additional || !nmb2.additional)
        return  tie(nmb1.country, nmb1.city, nmb1.number) < tie(nmb2.country, nmb2.city, nmb2.number) ;
    return tie(nmb1.country, nmb1.city, nmb1.number, nmb1.additional) < tie(nmb2.country, nmb2.city, nmb2.number, nmb2.additional);
}

bool operator==(PhoneNumber& nmb1, PhoneNumber& nmb2)
{
    if (!nmb1.additional || !nmb2.additional)
        return  tie(nmb1.country, nmb1.city, nmb1.number) == tie(nmb2.country, nmb2.city, nmb2.number) ;
    return tie(nmb1.country, nmb1.city, nmb1.number, nmb1.additional) == tie(nmb2.country, nmb2.city, nmb2.number, nmb2.additional);
}

// PhoneBook

PhoneBook::PhoneBook(ifstream& input)
{
    while (!input.eof())
    {
        Person p;
        PhoneNumber nmb;
        input >> p.surname >> p.name;
        string entry;
        input >> entry;
        if (entry[0] == '+')
            p.patronicName = nullopt;
        else
        {
            p.patronicName = entry;
            input >> entry;
        }
        nmb.country = 0;
        size_t j = 1;
        for (; entry[j] != '('; ++j)
            nmb.country = nmb.country * 10 + entry[j];
        nmb.city = 0;
        for (++j; entry[j] != ')'; ++j)
            nmb.city = nmb.city * 10 + entry[j];
        while(entry[j] != '\0' || entry[j] != '\n')
        {
            nmb.number.push_back(entry[j++]);
            if (entry[j] == '\n')
                nmb.additional = nullopt;
            else
            {
                input >> entry;
                size_t k = 0, temp = 0;
                while (entry[k] != '\n')
                    temp = temp * 10 + entry[k++];
                nmb.additional = temp;
            }
        }

        list.push_back(make_pair(p, nmb));
    }
}

ostream& operator<<(ostream& out, PhoneBook& book)
{
    for (auto& it : book.list)
    {
        out << it.first << ' ';
        out << it.second << ' ' << endl;
    }
    return out;
}

void PhoneBook::SortByName()
{
    auto compare = [](pair<Person, PhoneNumber> p1, pair<Person, PhoneNumber> p2)
    {
        return p1.first < p2.first;
    };
    sort(list.begin(), list.end(), compare);
}

void PhoneBook::SortByPhone()
{
    auto compare = [](pair<Person, PhoneNumber> p1, pair<Person, PhoneNumber> p2)
    {
        return p1.second < p2.second;
    };
    sort(list.begin(), list.end(), compare);
}

pair<string, optional<PhoneNumber>> PhoneBook::GetPhoneNumber(string surname)
{
    size_t count = 0;
    optional<PhoneNumber> nmb;
    for (auto& it : list)
    {
        if (surname == it.first.surname)
        {
            ++count;
            nmb = it.second;
        }
    }

    if (count == 1)
        return { make_pair(""s, nmb) };
    else if (count == 0)
        return { make_pair("Not found", nmb) };
    else
        return { make_pair("Found more than 1", nmb) };
}

void PhoneBook::ChangePhoneNumber(Person p, PhoneNumber nmb)
{
    for (auto& it : list)
    {
        if (it.first == p)
            it.second = nmb;
    }
}