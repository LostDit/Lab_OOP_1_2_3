// Employee.h
#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <iostream>
#include <string>
#include <vector>

struct Fullname {
    std::string surname;
    std::string name;
    std::string patronymic;
};

struct Employee {
    Fullname fullname;
    std::string passport;
    std::string phone;
    unsigned int age;
    char gender; // 'M' или 'F'
};

struct Employees {
    Employee* employees = nullptr;
    int size = 0;
};

// Перегрузка операторов
std::istream& operator>>(std::istream& is, Fullname& fn);
std::ostream& operator<<(std::ostream& os, const Fullname& fn);
std::istream& operator>>(std::istream& is, Employee& emp);
std::ostream& operator<<(std::ostream& os, const Employee& emp);

// Функции для работы с массивом
void print(const Employee* employee, size_t size);
void init(Employee* employee, size_t size);
Employee* init(size_t size);

// Работа с текстовыми файлами
void writeToTextFile(const Employee* employee, size_t size, const std::string& filename);
void readFromTextFile(Employee*& employee, size_t& size, const std::string& filename);

// Работа с бинарными файлами
void writeToBinaryFile(const Employee* employee, size_t size, const std::string& filename);
void readFromBinaryFile(Employee*& employee, size_t& size, const std::string& filename);

// Поиск
int find_element(const Employee* employee, size_t size, bool (*condition)(const Employee&));
Employees find_all_elements(const Employee* employee, size_t size, bool (*condition)(const Employee&));
size_t needful_element(const Employee* employee, size_t size, bool (*comparator)(const Employee&, const Employee&));

// Генерация случайных данных
Employee generateRandomEmployee();
void fillRandom(Employee* employee, size_t size);

//Перегрузки для вектора
void print(const std::vector<Employee>& vec);
void init(std::vector<Employee>& vec);
void writeToTextFile(const std::vector<Employee>& vec, const std::string& filename);
void readFromTextFile(std::vector<Employee>& vec, const std::string& filename);
void writeToBinaryFile(const std::vector<Employee>& vec, const std::string& filename);
void readFromBinaryFile(std::vector<Employee>& vec, const std::string& filename);

int find_element(const std::vector<Employee>& vec, bool (*condition)(const Employee&));
Employees find_all_elements(const std::vector<Employee>& vec, bool (*condition)(const Employee&));
size_t needful_element(const std::vector<Employee>& vec, bool (*comparator)(const Employee&, const Employee&));

void fillRandom(std::vector<Employee>& vec, size_t size);

#endif