#include "source.h"


// Person

ostream& operator<<(ostream& out, Person& p)
{
    out << p.surname << ' ' << p.name;
    if (p.patronicName.has_value())
        out << ' ' << p.patronicName.value();
    return out;
}

bool operator<(Person& p1, Person& p2)
{
    if (p1.patronicName.has_value() && p2.patronicName.has_value())
    {
        return
        {
            tie(p1.surname, p1.name, p1.patronicName) <
            tie(p2.surname, p2.name, p2.patronicName)
        };
    }
    return tie(p1.surname, p1.name) < tie(p2.surname, p2.name);
}

bool operator==(Person& p1, Person& p2)
{
    if (p1.patronicName.has_value() && p2.patronicName.has_value())
    {
        return
        {
            tie(p1.surname, p1.name, p1.patronicName) ==
            tie(p2.surname, p2.name, p2.patronicName)
        };
    }
    return tie(p1.surname, p1.name) == tie(p2.surname, p2.name);
}

// PhoneNumber

ostream& operator<<(ostream& out, PhoneNumber& nmb)
{
    out << '+' << nmb.countryCode;
    out << '(' << nmb.cityCode << ')';
    out << nmb.number;
    if (nmb.additionalNumber.has_value())
        out << ' ' << nmb.additionalNumber.value();
    return out;
}

bool operator<(PhoneNumber& nmb1, PhoneNumber& nmb2)
{
    if (nmb1.additionalNumber.has_value() && nmb2.additionalNumber.has_value())
    {
        return
        {
            tie(nmb1.countryCode, nmb1.cityCode, nmb1.number, nmb1.additionalNumber) <
            tie(nmb2.countryCode, nmb2.cityCode, nmb2.number, nmb2.additionalNumber)
        };
    }
    return
    {
        tie(nmb1.countryCode, nmb1.cityCode, nmb1.number) <
        tie(nmb2.countryCode, nmb2.cityCode, nmb2.number)
    };
}

bool operator==(PhoneNumber& nmb1, PhoneNumber& nmb2)
{
    if (nmb1.additionalNumber.has_value() && nmb2.additionalNumber.has_value())
    {
        return
        {
            tie(nmb1.countryCode, nmb1.cityCode, nmb1.number, nmb1.additionalNumber) ==
            tie(nmb2.countryCode, nmb2.cityCode, nmb2.number, nmb2.additionalNumber)
        };
    }
    return
    {
        tie(nmb1.countryCode, nmb1.cityCode, nmb1.number) ==
        tie(nmb2.countryCode, nmb2.cityCode, nmb2.number)
    };
}

// PhoneBook

PhoneBook::PhoneBook(ifstream& input)
{
    while (!input.eof())
    {
        Person p;
        PhoneNumber nmb;
        string entry;
        getline(input, entry);

        string::iterator it = entry.begin();
        for (; *it != ' '; ++it)
            p.surname.push_back(*it);
        for (++it; *it != ' '; ++it)
            p.name.push_back(*it);
        if (*(it + 1) != '+')
        {
            string helper;
            for (++it; *it != ' '; ++it)
                helper.push_back(*it);
            p.patronicName.emplace(helper);
        }
        else
            p.patronicName = nullopt;

        ++it;
        nmb.countryCode = 0;
        for (++it; *it != '('; ++it)
        {
            nmb.countryCode *= 10;
            nmb.countryCode += *it - '0';
        }
        nmb.cityCode = 0;
        for (++it; *it != ')'; ++it)
        {
            nmb.cityCode *= 10;
            nmb.cityCode += *it - '0';
        }
        for (++it; *it != ' ' && *it != '\000'; ++it)
            nmb.number.push_back(*it);
        if (*it == ' ')
        {
            nmb.additionalNumber.emplace(0);
            for (++it; *it != '\000'; ++it)
            {
                nmb.additionalNumber.value() *= 10;
                nmb.additionalNumber.value() += *it - '0';
            }
        }

        list.push_back(make_pair(p, nmb));
    }
}

ostream& operator<<(ostream& out, PhoneBook& book)
{
    for (auto& it : book.list)
        out << it.first << ' ' << it.second << endl;
    return out;
}

void PhoneBook::SortByName()
{
    auto comparator = [](pair<Person, PhoneNumber>& p1, pair<Person, PhoneNumber>& p2)
    {
        if (p1.first.surname != p2.first.surname)
            return p1.first.surname < p2.first.surname;
        else if (p1.first.name != p2.first.name)
            return p1.first.name < p2.first.name;
        else if (p1.first.patronicName && p2.first.patronicName)
            return p1.first.patronicName < p2.first.patronicName;
        else
            return false;
    };
    sort(list.begin(), list.end(), comparator);
}

void PhoneBook::SortByPhone()
{
    auto comparator = [](pair<Person, PhoneNumber>& nmb1, pair<Person, PhoneNumber>& nmb2)
    {
        if (nmb1.second.countryCode != nmb2.second.countryCode)
            return nmb1.second.countryCode < nmb2.second.countryCode;
        else if (nmb1.second.cityCode != nmb2.second.cityCode)
            return nmb1.second.cityCode < nmb2.second.cityCode;
        else if (nmb1.second.number != nmb2.second.number)
            return nmb1.second.number < nmb2.second.number;
        else
            return nmb1.second.additionalNumber < nmb2.second.additionalNumber;
    };
    sort(list.begin(), list.end(), comparator);
}

pair<string, PhoneNumber> PhoneBook::GetPhoneNumber(string surname)
{
    size_t count = 0;
    PhoneNumber found;
    for (auto& it : list)
    {
        if (it.first.surname == surname)
        {
            ++count;
            found = it.second;
        }
    }

    if (count == 1)
        return make_pair(""s, found);
    else if (count < 1)
        return make_pair("not found"s, found);
    else
        return make_pair("found more than 1", found);
}

void PhoneBook::ChangePhoneNumber(Person p, PhoneNumber nmb)
{
    for (auto& it : list)
    {
        if (it.first == p)
        {
            it.second.countryCode = nmb.countryCode;
            it.second.cityCode = nmb.cityCode;
            it.second.number = nmb.number;
            if (nmb.additionalNumber)
                it.second.additionalNumber.emplace(nmb.additionalNumber.value());
        }
    }
}