#include "source.h"

int main()
{
    std::vector<stud::Student> group;
    group.push_back(stud::Student("Arthur", "Morghan", std::nullopt, { 2, 3, 2 }));
    group.push_back(stud::Student("John", "Marston", "Morghanovych", { 5, 4, 5 }));
    group.push_back(stud::Student("Abigail", "Roberts", std::nullopt, { 3, 3, 3 }));

    stud::StudentsGroup students1(std::move(group));
    students1.Save();
    stud::StudentsGroup students2;
    students2.Open();
    return 0;
}