#ifndef GRAPH_H
#define GRAPH_H
#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
using namespace std;

class Graph {
private:
    int m_vertices;                     //Кол-во вершин
    int m_arcs;                         //Кол-во дуг
    int *values;                        //Массив значений
    int *iColumns;                      //Массив индексов столбцов
    int *quantityElements;              //Массив количества элементов по строкам
public:
    Graph(int vertices, int arcs);                                                                      //Конструктор
    Graph(int vertices);                                                                                //Конструктор для единичной матрицы
    Graph(string address, int vertices, int arcs);                                                      //Конструктор для считывания из файла
    Graph(int vertices, int finalArcs, int *tmpValues, int *tmpIColumns, int *tmpQuantityElements);     //Конструктор для возврата объекта из функции
    Graph(const Graph &crs);                                                                            //Конструктор копирования
    ~Graph();                                                                                           //Деструктор
    void output() const;                                                                                //Вывод на экран
    void fileOutput(string address) const;                                                              //Вывод в файл
    void adding(int* &crs, int n, int size);                                                            //Добавление элемента в конец массива
    friend Graph transpose(const Graph &crs);                                                           //Транспонирование
    friend Graph operator+(const Graph &crs1, const Graph &crs2);                                       //Оператор сложения
    friend Graph operator*(const Graph &crs1, const Graph &crs2);                                       //Оператор умножения
    Graph& operator=(const Graph &crs);                                                                 //Оператор присваивания
    friend Graph reachability(const Graph &crs);                                                        //Нахождение матрицы достижимости
};

#endif // GRAPH_H
