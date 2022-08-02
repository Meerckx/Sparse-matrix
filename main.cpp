#include <iostream>
#include "graph.h"

using namespace std;

const int vertices = 5;                             //Создание вершин
const int arcs = 4;                                 //Создание дуг

int main() {
    setlocale(LC_ALL, "Russian");

    string addressIn = "D:\\Programming\\Projects\\MAI\\Practice\\in.txt";
    string addressOut = "D:\\Programming\\Projects\\MAI\\Practice\\out.txt";

    cout << "Как вы хотите считать матрицу?\n";
    cout << "1 - Ввести вручную\n" << "2 - Считать из файла\n";
    cout << "Ваш выбор: ";

    int choice;
    cin >> choice;

    switch(choice) {
    case 1: {
        Graph crs(vertices, arcs);
        Graph crsR = reachability(crs);
        cout << "\nГде вы хотите увидеть матрицу достижимости?\n";
        cout << "1 - В терминале\n" << "2 - В файле\n";
        cout << "Ваш выбор: ";

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
        cout << "\nГде вы хотите увидеть матрицу достижимости?\n";
        cout << "1 - В терминале\n" << "2 - В файле\n";
        cout << "Ваш выбор: ";

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
