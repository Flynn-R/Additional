#pragma once
#include <iostream>
#include <optional>
#include <vector>
#include <fstream>
#include <numeric>
#include <sstream>
#include <string>

// Задание 2

namespace stud
{
    class FullName
    {
        friend class Student;
        friend class StudentsGroup;
    private:
        std::string name;
        std::string surname;
        std::optional<std::string> patronic;

        friend bool operator==(const FullName& fname1, const FullName& fname2)
        {
            bool res = (fname1.name == fname2.name) && (fname1.surname == fname2.surname);
            if (!fname1.patronic.has_value() || !fname2.patronic.has_value())
                return res;
            return res && (fname1.patronic.value() == fname2.patronic.value());
        }
    public:
        FullName() = default;
        FullName(const std::string&& n, const std::string&& sn, const std::optional<std::string>&& p = std::nullopt)
        {
            name = n;
            surname = sn;
            if (p != std::nullopt)
                patronic = p.value();
        }
    };

    class Student
    {
        friend class StudentsGroup;
    private:
        FullName fname;
        std::vector<unsigned short> grades;
        float average;
    public:
        Student() = default;
        Student(const std::string&& n, const std::string&& sn, const std::optional<std::string>&& p, std::vector<unsigned short>&& g)
        {
            fname = std::move(FullName(std::move(n), std::move(sn), std::move(p)));
            grades = std::move(g);
        }
    };

    class IRepository
    {
        virtual void Open() = 0; // бинарная десериализация в файл
        virtual void Save() = 0; // бинарная сериализация в файл
    };

    class IMethods
    {
        virtual double GetAverageScore(const FullName& name) = 0;
        virtual std::string GetAllInfo(const FullName& name) = 0;
        virtual std::string GetAllInfo() = 0;
    };

    // Задание 3

    class StudentsGroup : public IRepository, IMethods
    {
    private:
        std::vector<Student> group;
    public:
        StudentsGroup() = default;
        StudentsGroup(const std::vector<Student>&& gp) : group(gp) {}

        double GetAverageScore(const FullName& name) override
        {
            for (auto& student : group)
            {
                if (student.fname == name)
                    return static_cast<double>(accumulate(student.grades.begin(), student.grades.end(), 0)) / student.grades.size();
            }
            return 0;
        }

        std::string GetAllInfo(const FullName& name) override
        {
            std::string result = "";
            for (auto& student : group)
            {
                if (student.fname == name)
                {
                    result += student.fname.name + " " + student.fname.surname;
                    if (student.fname.patronic.has_value())
                        result += " " + student.fname.patronic.value();
                    
                    result += "\n";

                    for (auto it = student.grades.begin(); it != student.grades.end(); ++it)
                    {
                        std::ostringstream ss;
                        ss << *it << ((it == student.grades.end() - 1) ? "\n" : " ");
                        result += ss.str();
                    }
                    
                    student.average = GetAverageScore(student.fname);
                    std::ostringstream ss;
                    ss << student.average;
                    result += ss.str() + "\n=============\n";
                }
            }
            return result;
        }

        std::string GetAllInfo() override
        {
            std::string result = "";
            for (auto& student : group)
                result += GetAllInfo(student.fname);
            return result;
        }

        void Open() override
        {
            std::ifstream input("/home/pierre/serialized.bin", std::ios::binary);
            std::string buffer;
            buffer.resize(1024);
            input.read(buffer.data(), buffer.size());
            buffer.resize(input.gcount());
            input.close();

            std::istringstream iss(buffer);
            std::string probe;
            while(std::getline(iss, probe))
            {
                Student st;
                {
                    std::stringstream ss;
                    ss << probe;
                    ss >> probe;
                    st.fname.name = probe;
                    ss >> probe;
                    st.fname.surname = probe;
                    if (!ss.eof())
                    {
                        ss >> probe;
                        st.fname.patronic = probe;
                    }
                }

                std::getline(iss, probe);
                {
                    std::stringstream ss;
                    ss << probe;
                    while(ss >> probe)
                        st.grades.push_back(std::stoi(probe));
                }

                group.push_back(st);

                std::getline(iss, probe);
                std::getline(iss, probe);
            }

            std::ofstream output("./deserialized.txt");
            output << GetAllInfo();
            output.close();
        }

        void Save() override
        {
            std::string buffer = GetAllInfo();
            std::ofstream output("./serialized.bin", std::ios::binary);
            output.write(buffer.c_str(), buffer.size());
            output.close();
        }
    };
}