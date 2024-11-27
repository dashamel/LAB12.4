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
        cout << "������� ��������� �����!" << endl;
        return;
    }

    char ch; // ������� �����������
    do {
        Route route;
        cin.ignore();
        cout << "������ ���������� �����: ";
        cin.getline(route.startPoint, 50);
        cout << "������ ������� �����: ";
        cin.getline(route.endPoint, 50);
        cout << "������ ����� ��������: ";
        cin >> route.routeNumber;

        fout.write(reinterpret_cast<char*>(&route), sizeof(Route));

        cout << "������ �� �������? (y/n): ";
        cin >> ch;
    } while (ch == 'y' || ch == 'Y');

    fout.close();
    cout << "��� ��������� � ����: " << filename << endl;
}

void PrintRouteByNumber(char* filename, int routeNumber) {
    ifstream fin(filename, ios::binary); // ³�������� ���� ��� ����������
    if (!fin) {
        cout << "������� �������� ����� ��� �������!" << endl;
        return;
    }

    Route route; // ��������� ��� ����������
    bool found = false;

    while (fin.read(reinterpret_cast<char*>(&route), sizeof(Route))) { // ������ �����
        if (route.routeNumber == routeNumber) { // �������� �� �������
            cout << "=============================================================" << endl;
            cout << "|  ���������� �����  |  ʳ������ �����  |  ����� ��������   |" << endl;
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
        cout << "������� �� ������� " << routeNumber << " �� ��������." << endl;
    }

    fin.close();
}


void SortRoutesFile(char* filename) {
    fstream file(filename, ios::binary | ios::in | ios::out);
    if (!file) {
        cout << "������� �������� �����!" << endl;
        return;
    }

    // ���������� ������ ����� �� ������� ������
    file.seekg(0, ios::end);
    int fileSize = file.tellg();
    int recordCount = fileSize / sizeof(Route);
    file.seekg(0, ios::beg);

    for (int i = 1; i < recordCount; i++) {
        for (int j = 0; j < recordCount - i; j++) {
            // ���������� ���� ������ ������
            Route a, b;
            file.seekg(j * sizeof(Route), ios::beg);
            file.read(reinterpret_cast<char*>(&a), sizeof(Route));
            file.read(reinterpret_cast<char*>(&b), sizeof(Route));

            // ��������� �� ����, ���� ���������
            if (a.routeNumber > b.routeNumber) {
                // ���������� �� ������� ��� ������
                file.seekp(j * sizeof(Route), ios::beg);
                file.write(reinterpret_cast<char*>(&b), sizeof(Route));
                file.write(reinterpret_cast<char*>(&a), sizeof(Route));
            }
        }
    }

    file.close();
    cout << "�������� ����������� �� �������." << endl;
}


void PrintAllRoutes(char* filename) {
    ifstream fin(filename, ios::binary); // ³�������� ���� ��� ����������
    if (!fin) {
        cout << "������� �������� ����� ��� �������!" << endl;
        return;
    }

    Route route; // ��������� ��� ����������
    cout << "=============================================================" << endl;
    cout << "|  ���������� �����  |  ʳ������ �����  |  ����� ��������   |" << endl;
    cout << "=============================================================" << endl;

    while (fin.read(reinterpret_cast<char*>(&route), sizeof(Route))) { // ������ �����
        // �������� ��� �� �����
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
        cout << "������� �������� ����� ��� ���������!" << endl;
        return;
    }

    char ch;
    do {
        Route route;
        cin.ignore();
        cout << "������ ���������� �����: ";
        cin.getline(route.startPoint, 50);
        cout << "������ ������� �����: ";
        cin.getline(route.endPoint, 50);
        cout << "������ ����� ��������: ";
        cin >> route.routeNumber;

        fout.write(reinterpret_cast<char*>(&route), sizeof(Route));

        cout << "������ �� �������? (y/n): ";
        cin >> ch;
    } while (ch == 'y' || ch == 'Y');

    fout.close();
    cout << "��� ������ �� �����: " << filename << endl;
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251); 

    char filename[100];
    cout << "������ ��'� �����: ";
    cin >> filename;

    int menuItem;
    do {
        cout << endl;
        cout << "������ ��:" << endl;
        cout << " [1] - �������� ���� ��������" << endl;
        cout << " [2] - ������� ������� �� �������" << endl;
        cout << " [3] - ��������� �������� � ����" << endl;
        cout << " [4] - ������� �� ��������" << endl;
        cout << " [5] - ������ �������� �� �����" << endl;
        cout << " [0] - �����" << endl;
        cout << "��� ����: ";
        cin >> menuItem;

        switch (menuItem) {
        case 1:
            CreateRoutesFile(filename);
            break;
        case 2: {
            int routeNumber;
            cout << "������ ����� ��������: ";
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
            cout << "����� � ��������." << endl;
            break;
        default:
            cout << "������� ����. ��������� �� ���." << endl;
        }
    } while (menuItem != 0);

    return 0;
}
