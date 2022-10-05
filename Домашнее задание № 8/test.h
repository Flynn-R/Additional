#pragma once
#include "source.h"
#include <gtest/gtest.h>

// Задание 2

class TestStudentsGroup : public testing::Test
{
protected:
    stud::StudentsGroup* students;
    
    void SetUp() override
    {
        std::vector<stud::Student> group;
        group.push_back(stud::Student("Arthur", "Morghan", std::nullopt, { 2, 3, 2 }));
        group.push_back(stud::Student("John", "Marston", "Morghanovych", { 5, 4, 5 }));
        group.push_back(stud::Student("Abigail", "Roberts", std::nullopt, { 3, 3, 3 }));
        students = new stud::StudentsGroup(std::move(group));
    }

    void TearDown() override
    {
        delete students;
    }
};

TEST_F(TestStudentsGroup, GetAverage)
{
    ASSERT_NEAR(students->GetAverageScore(stud::FullName("Arthur", "Morghan")), 2.3, 0.04);
    ASSERT_NEAR(students->GetAverageScore(stud::FullName("John", "Marston", "Morghanovych")), 4.6, 0.07);
    ASSERT_NEAR(students->GetAverageScore(stud::FullName("Abigail", "Roberts")), 3, 0);

}

TEST_F(TestStudentsGroup, GetInfo)
{
    ASSERT_STREQ("Arthur Morghan\n2 3 2\n2.33333\n=============\n", 
                 students->GetAllInfo(stud::FullName("Arthur", "Morghan")).c_str());
    ASSERT_STREQ("John Marston Morghanovych\n5 4 5\n4.66667\n=============\n",
                 students->GetAllInfo(stud::FullName("John", "Marston", "Morghanovych")).c_str());
    ASSERT_STREQ("Abigail Roberts\n3 3 3\n3\n=============\n",
                 students->GetAllInfo(stud::FullName("Abigail", "Roberts")).c_str());
}