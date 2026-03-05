#include <iostream>
#include <vector>
#include <limits>
#include <fstream>
#include "Employee.cpp"

#ifdef _WIN32
#include <windows.h>
#endif

int safeInputInt(const std::string& prompt, int minVal, int maxVal) {
    int value;
    while (true) {
        std::cout << prompt;
        std::cin >> value;
        if (std::cin.fail() || value < minVal || value > maxVal) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Ошибка! Введите число от " << minVal << " до " << maxVal << ".\n";
        } else {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            break;
        }
    }
    return value;
}

bool is_woman(const Employee& emp) {
    return emp.gender == 'F' || emp.gender == 'f';
}

bool is_female_pensioner(const Employee& emp) {
    return is_woman(emp) && emp.age >= 60;
}

bool younger_woman_comparator(const Employee& a, const Employee& b) {
    if (!is_woman(a) && !is_woman(b)) return false;
    if (!is_woman(a)) return false;
    if (!is_woman(b)) return true;
    return a.age < b.age;
}

void clearInput() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void printMenu();

int main() {
#ifdef _WIN32
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
#endif

    std::vector<Employee> employees;
    int choice;

    do {
        printMenu();
        std::cin >> choice;
        clearInput();

        switch (choice) {
        case 1:
            init(employees);
            std::cout << "Массив создан.\n";
            break;

        case 2:
            if (employees.empty())
                std::cout << "Массив пуст.\n";
            else
                print(employees);
            break;

        case 3:
            if (employees.empty())
                std::cout << "Нет данных для записи.\n";
            else
                writeToTextFile(employees, "output.txt");
            break;

        case 4:
            if (employees.empty())
                std::cout << "Нет данных для записи.\n";
            else
                writeToBinaryFile(employees, "output.bin");
            break;

        case 5:
            readFromTextFile(employees, "input.txt");
            if (!employees.empty())
                std::cout << "Данные загружены в программу.\n";
            break;

        case 6:
            readFromBinaryFile(employees, "input.bin");
            if (!employees.empty())
                std::cout << "Данные загружены в программу.\n";
            break;

        case 7: {
            if (employees.empty()) {
                std::cout << "Массив пуст.\n";
                break;
            }
            Employees women = find_all_elements(employees, is_woman);
            if (women.size == 0)
                std::cout << "Женщины не найдены.\n";
            else {
                std::cout << "Список женщин:\n";
                print(women.employees, women.size);
            }
            delete[] women.employees;
            break;
        }

        case 8: {
            if (employees.empty()) {
                std::cout << "Массив пуст.\n";
                break;
            }
            size_t idx = needful_element(employees, younger_woman_comparator);
            if (!is_woman(employees[idx])) {
                std::cout << "Женщины отсутствуют.\n";
            } else {
                std::cout << "Самая молодая женщина:\n" << employees[idx] << std::endl;
            }
            break;
        }

        case 9: {
            if (employees.empty()) {
                std::cout << "Массив пуст.\n";
                break;
            }
            int res = find_element(employees, is_female_pensioner);
            if (res != -1)
                std::cout << "В фирме работают женщины-пенсионеры.\n";
            else
                std::cout << "Женщин-пенсионеров нет.\n";
            break;
        }

        case 10: {
            Employee emp;
            std::cout << "Введите данные нового сотрудника:\n";
            std::cin >> emp;
            employees.push_back(emp);
            std::cout << "Сотрудник добавлен.\n";
            break;
        }

        case 11: {
            if (employees.empty()) {
                std::cout << "Массив пуст.\n";
                break;
            }
            size_t idx;
            std::cout << "Введите индекс сотрудника для редактирования (1.." << employees.size() << "): ";
            std::cin >> idx;
            clearInput();
            if (idx < 1 || idx > employees.size()) {
                std::cout << "Неверный индекс.\n";
                break;
            }
            std::cout << "Текущие данные:\n" << employees[idx - 1];
            std::cout << "Введите новые данные:\n";
            std::cin >> employees[idx - 1];
            std::cout << "Данные обновлены.\n";
            break;
        }

        case 12: {
            if (employees.empty()) {
                std::cout << "Массив пуст.\n";
                break;
            }
            size_t idx;
            std::cout << "Введите индекс сотрудника для удаления (1.." << employees.size() << "): ";
            std::cin >> idx;
            clearInput();
            if (idx < 1 || idx > employees.size()) {
                std::cout << "Неверный индекс.\n";
                break;
            }
            employees.erase(employees.begin() + idx - 1);
            std::cout << "Сотрудник удалён.\n";
            break;
        }

        case 13: {
            size_t n = safeInputInt("Введите количество сотрудников для генерации: ", 1, 100);
            fillRandom(employees, n);
            std::cout << "Сгенерировано " << n << " случайных сотрудников.\n";
            break;
        }

        case 14: {
            std::ifstream test("output.txt");
            if (!test) {
                std::cout << "Файл output.txt не найден. Сначала запишите данные (пункт 3).\n";
                break;
            }
            test.close();

            std::vector<Employee> temp;
            readFromTextFile(temp, "output.txt");
            if (!temp.empty()) {
                std::cout << "Содержимое файла output.txt:\n";
                print(temp);
            }
            break;
        }

        case 15: {
            std::ifstream test("output.bin", std::ios::binary);
            if (!test) {
                std::cout << "Файл output.bin не найден. Сначала запишите данные (пункт 4).\n";
                break;
            }
            test.close();

            std::vector<Employee> temp;
            readFromBinaryFile(temp, "output.bin");
            if (!temp.empty()) {
                std::cout << "Содержимое файла output.bin:\n";
                print(temp);
            }
            break;
        }

        case 0:
            std::cout << "Выход из программы.\n";
            break;

        default:
            std::cout << "Неверный выбор, повторите.\n";
        }
    } while (choice != 0);

    return 0;
}

void printMenu() {
    std::cout << "\n========== МЕНЮ ==========\n";
    std::cout << "1. Создать массив сотрудников с клавиатуры\n";
    std::cout << "2. Вывести список сотрудников на экран\n";
    std::cout << "3. Записать массив в текстовый файл (output.txt)\n";
    std::cout << "4. Записать массив в бинарный файл (output.bin)\n";
    std::cout << "5. Прочитать массив из текстового файла (input.txt)\n";
    std::cout << "6. Прочитать массив из бинарного файла (input.bin)\n";
    std::cout << "7. Задание 1: вывести список женщин\n";
    std::cout << "8. Задание 2: найти самую молодую женщину\n";
    std::cout << "9. Задание 3: проверить наличие женщин-пенсионеров\n";
    std::cout << "10. Добавить сотрудника\n";
    std::cout << "11. Редактировать сотрудника по индексу\n";
    std::cout << "12. Удалить сотрудника по индексу\n";
    std::cout << "13. Сгенерировать случайных сотрудников\n";
    std::cout << "14. Прочитать данные из output.txt и вывести на экран\n";
    std::cout << "15. Прочитать данные из output.bin и вывести на экран\n";
    std::cout << "0. Выход\n";
    std::cout << "Ваш выбор: ";
}