#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <windows.h>
using namespace std;

struct Route {
    char startPoint[50];
    char endPoint[50];
    int routeNumber;
};

void CreateRoutesFile(char* filename);
void PrintRouteByNumber(char* filename, int routeNumber);
void SortRoutesFile(char* filename);
void PrintAllRoutes(char* filename);
void AddRoutesToFile(char* filename);

void CreateRoutesFile(char* filename) {
    ofstream fout(filename, ios::binary);
    if (!fout) {
        cout << "Помилка створення файлу!" << endl;
        return;
    }

    char ch; // відповідь користувача
    do {
        Route route;
        cin.ignore();
        cout << "Введіть початковий пункт: ";
        cin.getline(route.startPoint, 50);
        cout << "Введіть кінцевий пункт: ";
        cin.getline(route.endPoint, 50);
        cout << "Введіть номер маршруту: ";
        cin >> route.routeNumber;

        fout.write(reinterpret_cast<char*>(&route), sizeof(Route));

        cout << "Додати ще маршрут? (y/n): ";
        cin >> ch;
    } while (ch == 'y' || ch == 'Y');

    fout.close();
    cout << "Дані збережено у файл: " << filename << endl;
}

void PrintRouteByNumber(char* filename, int routeNumber) {
    ifstream fin(filename, ios::binary); // Відкриваємо файл для зчитування
    if (!fin) {
        cout << "Помилка відкриття файлу для читання!" << endl;
        return;
    }

    Route route; // Структура для зчитування
    bool found = false;

    while (fin.read(reinterpret_cast<char*>(&route), sizeof(Route))) { // Читаємо запис
        if (route.routeNumber == routeNumber) { // Перевірка за номером
            cout << "=============================================================" << endl;
            cout << "|  Початковий пункт  |  Кінцевий пункт  |  Номер маршруту   |" << endl;
            cout << "=============================================================" << endl;
            cout << "| " << setw(19) << left << route.startPoint
                << "| " << setw(17) << left << route.endPoint
                << "| " << setw(17) << left << route.routeNumber << " |" << endl;
            cout << "=============================================================" << endl;
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "Маршрут із номером " << routeNumber << " не знайдено." << endl;
    }

    fin.close();
}


void SortRoutesFile(char* filename) {
    fstream file(filename, ios::binary | ios::in | ios::out);
    if (!file) {
        cout << "Помилка відкриття файлу!" << endl;
        return;
    }

    // Визначення розміру файлу та кількості записів
    file.seekg(0, ios::end);
    int fileSize = file.tellg();
    int recordCount = fileSize / sizeof(Route);
    file.seekg(0, ios::beg);

    for (int i = 1; i < recordCount; i++) {
        for (int j = 0; j < recordCount - i; j++) {
            // Зчитування двох сусідніх записів
            Route a, b;
            file.seekg(j * sizeof(Route), ios::beg);
            file.read(reinterpret_cast<char*>(&a), sizeof(Route));
            file.read(reinterpret_cast<char*>(&b), sizeof(Route));

            // Порівняння та обмін, якщо необхідно
            if (a.routeNumber > b.routeNumber) {
                // Повернення до позиції для запису
                file.seekp(j * sizeof(Route), ios::beg);
                file.write(reinterpret_cast<char*>(&b), sizeof(Route));
                file.write(reinterpret_cast<char*>(&a), sizeof(Route));
            }
        }
    }

    file.close();
    cout << "Маршрути відсортовано за номером." << endl;
}


void PrintAllRoutes(char* filename) {
    ifstream fin(filename, ios::binary); // Відкриваємо файл для зчитування
    if (!fin) {
        cout << "Помилка відкриття файлу для читання!" << endl;
        return;
    }

    Route route; // Структура для зчитування
    cout << "=============================================================" << endl;
    cout << "|  Початковий пункт  |  Кінцевий пункт  |  Номер маршруту   |" << endl;
    cout << "=============================================================" << endl;

    while (fin.read(reinterpret_cast<char*>(&route), sizeof(Route))) { // Читаємо запис
        // Виводимо дані на екран
        cout << "| " << setw(19) << left << route.startPoint
            << "| " << setw(17) << left << route.endPoint
            << "| " << setw(17) << left << route.routeNumber << " |" << endl;
    }

    cout << "=============================================================" << endl;
    fin.close();
}


void AddRoutesToFile(char* filename) {
    ofstream fout(filename, ios::binary | ios::app);
    if (!fout) {
        cout << "Помилка відкриття файлу для додавання!" << endl;
        return;
    }

    char ch;
    do {
        Route route;
        cin.ignore();
        cout << "Введіть початковий пункт: ";
        cin.getline(route.startPoint, 50);
        cout << "Введіть кінцевий пункт: ";
        cin.getline(route.endPoint, 50);
        cout << "Введіть номер маршруту: ";
        cin >> route.routeNumber;

        fout.write(reinterpret_cast<char*>(&route), sizeof(Route));

        cout << "Додати ще маршрут? (y/n): ";
        cin >> ch;
    } while (ch == 'y' || ch == 'Y');

    fout.close();
    cout << "Дані додано до файлу: " << filename << endl;
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251); 

    char filename[100];
    cout << "Введіть ім'я файлу: ";
    cin >> filename;

    int menuItem;
    do {
        cout << endl;
        cout << "Оберіть дію:" << endl;
        cout << " [1] - Створити файл маршрутів" << endl;
        cout << " [2] - Вивести маршрут за номером" << endl;
        cout << " [3] - Сортувати маршрути у файлі" << endl;
        cout << " [4] - Вивести всі маршрути" << endl;
        cout << " [5] - Додати маршрути до файлу" << endl;
        cout << " [0] - Вихід" << endl;
        cout << "Ваш вибір: ";
        cin >> menuItem;

        switch (menuItem) {
        case 1:
            CreateRoutesFile(filename);
            break;
        case 2: {
            int routeNumber;
            cout << "Введіть номер маршруту: ";
            cin >> routeNumber;
            PrintRouteByNumber(filename, routeNumber);
            break;
        }
        case 3:
            SortRoutesFile(filename);
            break;
        case 4:
            PrintAllRoutes(filename);
            break;
        case 5: 
            AddRoutesToFile(filename);
            break;
        case 0:
            cout << "Вихід з програми." << endl;
            break;
        default:
            cout << "Невірний вибір. Спробуйте ще раз." << endl;
        }
    } while (menuItem != 0);

    return 0;
}
