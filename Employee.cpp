#include "Employee.h"
#include <fstream>
#include <random>
#include <ctime>

//Перегрузка операторов
std::istream& operator>>(std::istream& is, Fullname& fn) {
    std::cout << "  Фамилия: ";
    is >> fn.surname;
    std::cout << "  Имя: ";
    is >> fn.name;
    std::cout << "  Отчество: ";
    is >> fn.patronymic;
    return is;
}

std::ostream& operator<<(std::ostream& os, const Fullname& fn) {
    os << fn.surname << " " << fn.name << " " << fn.patronymic;
    return os;
}

std::istream& operator>>(std::istream& is, Employee& emp) {
    std::cout << "Введите ФИО:\n";
    is >> emp.fullname;
    std::cout << "Введите номер паспорта: ";
    is >> emp.passport;
    std::cout << "Введите телефон: ";
    is >> emp.phone;
    std::cout << "Введите возраст: ";
    is >> emp.age;
    std::cout << "Введите пол (M/F): ";
    is >> emp.gender;
    return is;
}

std::ostream& operator<<(std::ostream& os, const Employee& emp) {
    os << "ФИО: " << emp.fullname << "\n"
       << "Паспорт: " << emp.passport << "\n"
       << "Телефон: " << emp.phone << "\n"
       << "Возраст: " << emp.age << "\n"
       << "Пол: " << emp.gender << "\n";
    return os;
}

//Базовые функции
void print(const Employee* employee, size_t size) {
    for (size_t i = 0; i < size; ++i) {
        std::cout << "Сотрудник #" << i + 1 << ":\n" << employee[i] << std::endl;
    }
}

void init(Employee* employee, size_t size) {
    for (size_t i = 0; i < size; ++i) {
        std::cout << "Введите данные для сотрудника #" << i + 1 << ":\n";
        std::cin >> employee[i];
    }
}

Employee* init(size_t size) {
    Employee* arr = new Employee[size];
    init(arr, size);
    return arr;
}

//Текстовые файлы
void writeToTextFile(const Employee* employee, size_t size, const std::string& filename) {
    std::ofstream out(filename);
    if (!out) {
        std::cerr << "Ошибка открытия файла для записи: " << filename << std::endl;
        return;
    }
    out << size << "\n";
    for (size_t i = 0; i < size; ++i) {
        const Employee& emp = employee[i];
        out << emp.fullname.surname << " " << emp.fullname.name << " " << emp.fullname.patronymic << "\n";
        out << emp.passport << "\n";
        out << emp.phone << "\n";
        out << emp.age << "\n";
        out << emp.gender << "\n";
    }
    out.close();
    std::cout << "Данные записаны в текстовый файл " << filename << std::endl;
}

void readFromTextFile(Employee*& employee, size_t& size, const std::string& filename) {
    std::ifstream in(filename);
    if (!in) {
        std::cerr << "Ошибка открытия файла для чтения: " << filename << std::endl;
        return;
    }
    in >> size;
    in.ignore();
    if (employee) delete[] employee;
    employee = new Employee[size];
    for (size_t i = 0; i < size; ++i) {
        Employee& emp = employee[i];
        in >> emp.fullname.surname >> emp.fullname.name >> emp.fullname.patronymic;
        in >> emp.passport;
        in >> emp.phone;
        in >> emp.age;
        in >> emp.gender;
    }
    in.close();
    std::cout << "Данные прочитаны из текстового файла " << filename << std::endl;
}

//Бинарные файлы
void writeToBinaryFile(const Employee* employee, size_t size, const std::string& filename) {
    std::ofstream out(filename, std::ios::binary);
    if (!out) {
        std::cerr << "Ошибка открытия бинарного файла для записи: " << filename << std::endl;
        return;
    }
    out.write(reinterpret_cast<const char*>(&size), sizeof(size));
    for (size_t i = 0; i < size; ++i) {
        const Employee& emp = employee[i];
        size_t len;

        len = emp.fullname.surname.size();
        out.write(reinterpret_cast<const char*>(&len), sizeof(len));
        out.write(emp.fullname.surname.c_str(), len);

        len = emp.fullname.name.size();
        out.write(reinterpret_cast<const char*>(&len), sizeof(len));
        out.write(emp.fullname.name.c_str(), len);

        len = emp.fullname.patronymic.size();
        out.write(reinterpret_cast<const char*>(&len), sizeof(len));
        out.write(emp.fullname.patronymic.c_str(), len);

        len = emp.passport.size();
        out.write(reinterpret_cast<const char*>(&len), sizeof(len));
        out.write(emp.passport.c_str(), len);

        len = emp.phone.size();
        out.write(reinterpret_cast<const char*>(&len), sizeof(len));
        out.write(emp.phone.c_str(), len);

        out.write(reinterpret_cast<const char*>(&emp.age), sizeof(emp.age));
        out.write(&emp.gender, sizeof(emp.gender));
    }
    out.close();
    std::cout << "Данные записаны в бинарный файл " << filename << std::endl;
}

void readFromBinaryFile(Employee*& employee, size_t& size, const std::string& filename) {
    std::ifstream in(filename, std::ios::binary);
    if (!in) {
        std::cerr << "Ошибка открытия бинарного файла для чтения: " << filename << std::endl;
        return;
    }
    in.read(reinterpret_cast<char*>(&size), sizeof(size));
    if (employee) delete[] employee;
    employee = new Employee[size];
    for (size_t i = 0; i < size; ++i) {
        Employee& emp = employee[i];
        size_t len;

        in.read(reinterpret_cast<char*>(&len), sizeof(len));
        emp.fullname.surname.resize(len);
        in.read(&emp.fullname.surname[0], len);

        in.read(reinterpret_cast<char*>(&len), sizeof(len));
        emp.fullname.name.resize(len);
        in.read(&emp.fullname.name[0], len);

        in.read(reinterpret_cast<char*>(&len), sizeof(len));
        emp.fullname.patronymic.resize(len);
        in.read(&emp.fullname.patronymic[0], len);

        in.read(reinterpret_cast<char*>(&len), sizeof(len));
        emp.passport.resize(len);
        in.read(&emp.passport[0], len);

        in.read(reinterpret_cast<char*>(&len), sizeof(len));
        emp.phone.resize(len);
        in.read(&emp.phone[0], len);

        in.read(reinterpret_cast<char*>(&emp.age), sizeof(emp.age));
        in.read(&emp.gender, sizeof(emp.gender));
    }
    in.close();
    std::cout << "Данные прочитаны из бинарного файла " << filename << std::endl;
}

//Поиск
int find_element(const Employee* employee, size_t size, bool (*condition)(const Employee&)) {
    for (size_t i = 0; i < size; ++i) {
        if (condition(employee[i])) return static_cast<int>(i);
    }
    return -1;
}

Employees find_all_elements(const Employee* employee, size_t size, bool (*condition)(const Employee&)) {
    Employees result;
    int count = 0;
    for (size_t i = 0; i < size; ++i)
        if (condition(employee[i])) count++;
    result.size = count;
    result.employees = new Employee[count];
    int idx = 0;
    for (size_t i = 0; i < size; ++i)
        if (condition(employee[i]))
            result.employees[idx++] = employee[i];
    return result;
}

size_t needful_element(const Employee* employee, size_t size, bool (*comparator)(const Employee&, const Employee&)) {
    if (size == 0) return 0;
    size_t best_idx = 0;
    for (size_t i = 1; i < size; ++i) {
        if (comparator(employee[i], employee[best_idx]))
            best_idx = i;
    }
    return best_idx;
}

//Генерация случайных данных
static const std::string surnames[] = {"Иванов", "Петров", "Сидоров", "Кузнецов", "Смирнов", "Васильев", "Федоров", "Михайлов"};
static const std::string names[] = {"Иван", "Петр", "Сидор", "Алексей", "Дмитрий", "Андрей", "Сергей", "Максим"};
static const std::string patronymics[] = {"Иванович", "Петрович", "Сидорович", "Алексеевич", "Дмитриевич", "Андреевич", "Сергеевич", "Максимович"};
static const std::string woman_names[] = {"Мария", "Елена", "Ольга", "Наталья", "Анна", "Татьяна", "Ирина", "Светлана"};
static const std::string woman_patronymics[] = {"Ивановна", "Петровна", "Сидоровна", "Алексеевна", "Дмитриевна", "Андреевна", "Сергеевна", "Максимовна"};
static const std::string female_surnames[] = {"Иванова", "Петрова", "Сидорова", "Кузнецова", "Смирнова", "Васильева", "Федорова", "Михайлова"};

std::string randomStringFromArray(const std::string arr[], size_t size) {
    static std::mt19937 rng(static_cast<unsigned>(std::time(nullptr)));
    std::uniform_int_distribution<size_t> dist(0, size - 1);
    return arr[dist(rng)];
}

std::string randomPassport() {
    static std::mt19937 rng(static_cast<unsigned>(std::time(nullptr)));
    std::uniform_int_distribution<int> series(1000, 9999);
    std::uniform_int_distribution<int> number(100000, 999999);
    return std::to_string(series(rng)) + " " + std::to_string(number(rng));
}

std::string randomPhone() {
    static std::mt19937 rng(static_cast<unsigned>(std::time(nullptr)));
    std::uniform_int_distribution<int> part1(100, 999);
    std::uniform_int_distribution<int> part2(10, 99);
    std::uniform_int_distribution<int> part3(10, 99);
    return "+7(" + std::to_string(part1(rng)) + ")" + std::to_string(part2(rng)) + "-" + std::to_string(part3(rng));
}

Employee generateRandomEmployee() {
    Employee emp;
    static std::mt19937 rng(static_cast<unsigned>(std::time(nullptr)));
    std::uniform_int_distribution<int> genderDist(0, 1);
    std::uniform_int_distribution<int> ageDist(18, 70);

    bool isMale = genderDist(rng) == 0;
    emp.gender = isMale ? 'M' : 'F';
    emp.age = ageDist(rng);

    if (isMale) {
        emp.fullname.surname = randomStringFromArray(surnames, sizeof(surnames)/sizeof(surnames[0]));
        emp.fullname.name = randomStringFromArray(names, sizeof(names)/sizeof(names[0]));
        emp.fullname.patronymic = randomStringFromArray(patronymics, sizeof(patronymics)/sizeof(patronymics[0]));
    } else {
        emp.fullname.surname = randomStringFromArray(female_surnames, sizeof(female_surnames)/sizeof(female_surnames[0]));
        emp.fullname.name = randomStringFromArray(woman_names, sizeof(woman_names)/sizeof(woman_names[0]));
        emp.fullname.patronymic = randomStringFromArray(woman_patronymics, sizeof(woman_patronymics)/sizeof(woman_patronymics[0]));
    }

    emp.passport = randomPassport();
    emp.phone = randomPhone();
    return emp;
}

void fillRandom(Employee* employee, size_t size) {
    for (size_t i = 0; i < size; ++i) {
        employee[i] = generateRandomEmployee();
    }
}