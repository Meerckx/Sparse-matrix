#include <iostream>
#include "graph.h"

using namespace std;

const int vertices = 5;                             //�������� ������
const int arcs = 4;                                 //�������� ���

int main() {
    setlocale(LC_ALL, "Russian");

    string addressIn = "D:\\Programming\\Projects\\MAI\\Practice\\in.txt";
    string addressOut = "D:\\Programming\\Projects\\MAI\\Practice\\out.txt";

    cout << "��� �� ������ ������� �������?\n";
    cout << "1 - ������ �������\n" << "2 - ������� �� �����\n";
    cout << "��� �����: ";

    int choice;
    cin >> choice;

    switch(choice) {
    case 1: {
        Graph crs(vertices, arcs);
        Graph crsR = reachability(crs);
        cout << "\n��� �� ������ ������� ������� ������������?\n";
        cout << "1 - � ���������\n" << "2 - � �����\n";
        cout << "��� �����: ";

        cin >> choice;

        switch(choice) {
        case 1:
            crsR.output();
            break;
        case 2:
            crsR.fileOutput(addressOut);
            break;
        }

        break;
    }
    case 2: {
        Graph crs(addressIn, vertices, arcs);
        Graph crsR = reachability(crs);
        cout << "\n��� �� ������ ������� ������� ������������?\n";
        cout << "1 - � ���������\n" << "2 - � �����\n";
        cout << "��� �����: ";

        cin >> choice;

        switch(choice) {
        case 1:
            crsR.output();
            break;
        case 2:
            crsR.fileOutput(addressOut);
            break;
        }
        break;
    }
    }


    return 0;
}
