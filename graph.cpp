#include "graph.h"

using namespace std;

Graph::Graph(int vertices, int arcs) {                          //Конструктор
    m_vertices = vertices;
    m_arcs = arcs;
    values = new int[arcs];
    iColumns = new int[arcs];
    quantityElements = new int[vertices + 1];

    cout << "Значения: ";
    for(int i = 0; i < arcs; i++)                            //Ввод массива значений
        cin >> values[i];

    cout << "Индексы столбцов: ";
    for(int i = 0; i < arcs; i++)                            //Ввод массива индексов столбцов
        cin >> iColumns[i];

    cout << "Кол-во элементов по строкам: ";
    for(int i = 0; i <= vertices; i++)                        //Ввод массива кол-ва элементов по строкам
        cin >> quantityElements[i];
}

Graph::Graph(int vertices) {                                    //Конструктор единичной матрицы
    m_vertices = vertices;
    m_arcs = vertices;
    values = new int[vertices];
    iColumns = new int[vertices];
    quantityElements = new int[vertices + 1]();

    for(int i = 0; i < vertices; i++)                            //Зполнение массива значений
        values[i] = 1;

    for(int i = 0; i < vertices; i++)                            //Зполнение массива индексов столбцов
        iColumns[i] = i;

    for(int i = 0; i <= vertices; i++)                           //Зполнение массива кол-ва элементов по строкам
        quantityElements[i] = i;
}

Graph::Graph(string address, int vertices, int arcs) {          //Конструктор для чтения из файла
    ifstream file(address);         //Открываем файл для чтения

    if(file.is_open()){             //Проверяем, удалось ли открыть файл
        string str;

        m_vertices = vertices;
        m_arcs = arcs;
        values = new int[arcs]();
        iColumns = new int[arcs]();
        quantityElements = new int[vertices + 1]();

        cout << "Значения: ";
        for(int i = 0; i < arcs; i++){                                  //Зполнение массива значений
            file >> str;
            for(int j = 0; str[j] != '\0'; j++){                        //Считываем поэлементно каждое число и записываем в массив поразрядно,
                values[i] = values[i] * 10 + (str[j] - '0');            //попутно конвертируя char в int
            }
            cout << values[i] << " ";
        }

        cout << "\nИндексы столбцов: ";
        for(int i = 0; i < arcs; i++){                                  //Зполнение массива индексов столбцов
            file >> str;
            for(int j = 0; str[j] != '\0'; j++){
                iColumns[i] = iColumns[i] * 10 + (str[j] - '0');
            }
            cout << iColumns[i] << " ";
        }

        cout << "\nКол-во элементов по строкам: ";
        for(int i = 0; i <= vertices; i++){                             //Зполнение массива кол-ва элементов по строкам
            file >> str;
            for(int j = 0; str[j] != '\0'; j++){
                quantityElements[i] = quantityElements[i] * 10 + (str[j] - '0');
            }
            cout << quantityElements[i] << " ";
        }

        file.close();               //Закрываем файл
    }
    else {                                      //Если файл не открылся изначально, то выводим сообщение об ошибке
        cerr << "Error: file could not be opened";
    }
}

Graph::Graph(int vertices, int finalArcs, int *tmpValues, int *tmpIColumns, int *tmpQuantityElements) {     //Конструктор c доп. параметрами
    m_vertices = vertices;
    m_arcs = finalArcs;
    values = new int[finalArcs];
    iColumns = new int[finalArcs];
    quantityElements = new int[vertices + 1];

    for(int i = 0; i < finalArcs; i++)                            //Ввод массива значений
        values[i] = tmpValues[i];

    for(int i = 0; i < finalArcs; i++)                            //Ввод массива индексов столбцов
        iColumns[i] = tmpIColumns[i];

    for(int i = 0; i <= vertices; i++)                            //Ввод массива кол-ва элементов по строкам
        quantityElements[i] = tmpQuantityElements[i];

    delete [] tmpValues;
    delete [] tmpIColumns;
    delete [] tmpQuantityElements;
}

Graph::Graph(const Graph &crs) {                             //Конструктор копирования
    m_vertices = crs.m_vertices;
    m_arcs = crs.m_arcs;
    values = new int[m_arcs];
    iColumns = new int[m_arcs];
    quantityElements = new int[m_vertices + 1];

    for(int i = 0; i < m_arcs; i++)                                 //Копирование массива значений
        values[i] = crs.values[i];

    for(int i = 0; i < m_arcs; i++)                                 //Копирование массива индексов столбцов
        iColumns[i] = crs.iColumns[i];

    for(int i = 0; i <= m_vertices; i++)                            //Копирование массива кол-ва элементов по строкам
        quantityElements[i] = crs.quantityElements[i];
}

Graph transpose(const Graph &crs) {                          //Транспонирование
    int count = 0;                                          //Счётчик кол-ва элементов построчно
    int vertices = crs.m_vertices;
    int arcs = crs.m_arcs;
    int tmpIndex = 0;                                       //Индекс записи элементов в новый массив
    int *tmpValues = new int[crs.m_arcs];                   //Создание временных массивов
    int *tmpIColumns = new int[crs.m_arcs];
    int *tmpQuantityElements = new int[crs.m_vertices + 1]();

    for(int i = 0; i < vertices; i++){                                                      //Перебираем индексы вершин
        for(int currentArc = 0; currentArc < arcs; currentArc++){                           //Проходимся по каждой дуге
            if(crs.iColumns[currentArc] == i){                                              //Если значение элемента массива iColumns = данной вершине,
                tmpValues[tmpIndex] = crs.values[currentArc];                               //то записываем значение этого элемента в новый массив.
                for(int indexCount = 0; indexCount < vertices; indexCount++)                //Добавляем новый счётчик индексов QuantityElements и ищем
                    if((currentArc + 1) > crs.quantityElements[indexCount] && (currentArc + 1) <= crs.quantityElements[indexCount + 1]) //строку, в
                        tmpIColumns[tmpIndex] = indexCount;                                 //которой находится значение элемента этого шага.
                tmpIndex++;                                 //Переходим к следующему шагу
                count++;
            }
        }
        tmpQuantityElements[i + 1] += count;                //Записываем количество элементов в новый массив
    }
    return Graph(vertices, arcs, tmpValues, tmpIColumns, tmpQuantityElements);
}

void adding(int* &crs, int n, int size) {                    //Добавление элемента в конец массива
    int *tmpCrs = new int[size + 1];                //Создаём новый массив на 1 больше

    for(int i = 0; i < size; i++)                   //Копируем значения
        tmpCrs[i] = crs[i];
    tmpCrs[size] = n;                               //Добавляем новое

    delete [] crs;                                  //Удаляем старый массив

    crs = tmpCrs;                                   //Указываем на новый массив
    tmpCrs = nullptr;                               //Нулевой указатель
}

Graph& Graph::operator=(const Graph &crs) {                  //Оператор присваивания
    m_vertices = crs.m_vertices;
    m_arcs = crs.m_arcs;
    values = new int[m_arcs];
    iColumns = new int[m_arcs];
    quantityElements = new int[m_vertices + 1];

    for(int i = 0; i < m_arcs; i++)                                 //Копирование массива значений
        values[i] = crs.values[i];

    for(int i = 0; i < m_arcs; i++)                                 //Копирование массива индексов столбцов
        iColumns[i] = crs.iColumns[i];

    for(int i = 0; i <= m_vertices; i++)                            //Копирование массива кол-ва элементов по строкам
        quantityElements[i] = crs.quantityElements[i];

    return *this;
}

Graph operator+(const Graph &crs1, const Graph &crs2) {      //Оператор сложения
    int maxArcs = crs1.m_arcs;                               //Поиск максимального кол-ва дуг
    if(crs1.m_arcs < crs2.m_arcs)
        maxArcs = crs2.m_arcs;
    int vertices = crs1.m_vertices;                          //Сохранение кол-ва вершин в отдельную переменную

    int *tmpValues = new int[maxArcs * 2];                   //Создание временных массивов
    int *tmpIColumns = new int[maxArcs * 2];
    int *tmpQuantityElements = new int[vertices + 1]();

    int leftItems{0}, rightItems{0};                         //Создание счётчиков, отвечающих за индексы суммируемых эл-ов из левой и правой матриц
    int tmpQuantity{0};                                      //Создание счётчика ненулевых элементов для третьего массива

    for(int i = 1; i <= vertices; i++){                                                         //Проходимся по всем элементам, кроме i = 0
        while(leftItems < crs1.quantityElements[i] && rightItems < crs2.quantityElements[i]){   //Если индексы суммируемых эллементов меньше значения
            if(crs1.iColumns[leftItems] < crs2.iColumns[rightItems]){                           //текущего элемента массива ненулевых элементов, то
                tmpValues[tmpQuantity] = crs1.values[leftItems];                                //запускаем цикл, в котором определяем значения
                tmpIColumns[tmpQuantity] = crs1.iColumns[leftItems];                            //элементов наших временных массивов из leftItems
                leftItems++;                                                                    //Переходим к следующему левому индексу
                tmpQuantity++;                                                                  //Увеличиваем кол-во ненулевых элементов в строке
            }
            else if(crs1.iColumns[leftItems] > crs2.iColumns[rightItems]){                      //Теперь, если значение элемента левого массива iColums
                tmpValues[tmpQuantity] = crs2.values[rightItems];                               //больше правого, то определяем значения элементов
                tmpIColumns[tmpQuantity] = crs2.iColumns[rightItems];                           //временных массивов из rightItems
                rightItems++;                                                                   //Переходим к следующему правому индексу
                tmpQuantity++;                                                                  //Увеличиваем кол-во ненулевых элементов в строке
            }
            else {                                                                              //Если хотим сложить элементы с одинаковыми коор-ми,
                tmpValues[tmpQuantity] = crs1.values[leftItems] + crs2.values[rightItems];      //то суммируем значения values
                tmpIColumns[tmpQuantity] = crs1.iColumns[leftItems];
                leftItems++;
                rightItems++;
                tmpQuantity++;
            }
        }
        while(leftItems < crs1.quantityElements[i]){                            //Если в левой строке остались элементы, по которым мы не проходили,
            tmpValues[tmpQuantity] = crs1.values[leftItems];                    //то в отдельном цикле делаем это и определяем соответствующие
            tmpIColumns[tmpQuantity] = crs1.iColumns[leftItems];                //значения, определённые ранее
            leftItems++;
            tmpQuantity++;
        }
        while(rightItems < crs2.quantityElements[i]){                           //Если в правой строке остались элементы, по которым не проходили...
            tmpValues[tmpQuantity] = crs2.values[rightItems];
            tmpIColumns[tmpQuantity] = crs2.iColumns[rightItems];
            rightItems++;
            tmpQuantity++;
        }
        tmpQuantityElements[i] = tmpQuantity;                                   //Записываем значение tmpQuantity на i-ом шаге в массив ненулевых эл-ов
    }

    int finalArcs = tmpQuantityElements[vertices];                              //Итоговое кол-во дуг после сложения

    return Graph(vertices, finalArcs, tmpValues, tmpIColumns, tmpQuantityElements);         //Возвращаем полученные значения в новый конструктор
}

Graph operator*(const Graph &crs1, const Graph &crs2) {      //Оператор умножения
    int *tmpValues = new int[0];                    //Создание временных массивов
    int *tmpIColumns = new int[0];
    int *tmpQuantityElements = new int[crs1.m_vertices + 1]();

    int vertices = crs1.m_vertices;

    int sum;                                        //Сумма одного умножения строки на столбец
    int count = 0;                                  //Количество ненулевых элементов в результате умножений одной строки
    int shift = 0;                                  //Счётчик продвижения по массивам значений и индексам столбцов

    Graph crsTranspose = transpose(crs2);           //Транспонируем правую матрицу

    for(int leftRows = 1; leftRows <= vertices; leftRows++){                 //Проходимся по строкам левой и правой матриц. После чего
        for(int rightRows = 1; rightRows <= vertices; rightRows++){          //проходимся по каждому столбцу, и если индексы столбцов совпадают,
            sum = 0;                                                         //то в сумму записываем произведение данных элементов
            for(int leftColumns = crs1.quantityElements[leftRows - 1]; leftColumns < crs1.quantityElements[leftRows]; leftColumns++){
                for(int rightColumns = crsTranspose.quantityElements[rightRows - 1]; rightColumns < crsTranspose.quantityElements[rightRows]; rightColumns++){
                    if(crs1.iColumns[leftColumns] == crsTranspose.iColumns[rightColumns]){
                        sum += crs1.values[leftColumns] * crsTranspose.values[rightColumns];        //Если элемент нашёлся, то прерываем последний цикл и
                        break;                                                                      //переходим к следующему шагу
                    }
                }
            }
            if(sum){                                                //Если сумма после перебора строки второй матрицы ненулевая, то добавляем
                adding(tmpValues, sum, shift);                      //необходимые элементы в массивы, а также увеличиваем счётчики
                adding(tmpIColumns, rightRows - 1, shift);
                shift++;
                count++;
            }
        }
        tmpQuantityElements[leftRows] += count;                     //Записываем количество элементов в новый массив
    }
    int finalArcs = tmpQuantityElements[vertices];                  //Итоговое кол-во дуг

    return Graph(vertices, finalArcs, tmpValues, tmpIColumns, tmpQuantityElements);         //Возвращаем полученные значения в новый конструктор
}

void Graph::output() const {                                 //Вывод
    cout << "Значения: ";
    for(int i = 0; i < m_arcs; i++)                          //Вывод массива значений
        cout << Graph::values[i] << " ";

    cout << "\nИндексы столбцов: ";
    for(int i = 0; i < m_arcs; i++)                          //Вывод массива индексов столбцов
        cout << Graph::iColumns[i] << " ";

    cout << "\nКол-во элементов по строкам: ";
    for(int i = 0; i <= m_vertices; i++)                      //Вывод массива кол-ва элементов по строкам
        cout << Graph::quantityElements[i] << " ";
}

void Graph::fileOutput(string address) const {               //Вывод в файл
    ofstream file(address);                 //Открываем файл для записи

    if(file.is_open()){                     //Проверяем, удалось ли открыть файл

        file << values[0];                      //Записываем массив значений
        for(int i = 1; i < m_arcs; i++)         //Для того, чтобы избежать лишних пробелов, сначала выводим первый элемент, а потом уже все остальные
            file << " " << values[i];
        file << '\n';                           //Переходим на новую строку

        file << iColumns[0];                    //Записываем массив индексов столбцов
        for(int i = 1; i < m_arcs; i++)
            file << " " << iColumns[i];
        file << '\n';

        file << quantityElements[0];            //Записываем массив кол-ва элементов по строкам
        for(int i = 1; i <= m_vertices; i++)
            file << " " << quantityElements[i];

        file.close();                           //Закрываем файл
    }
    else {                                      //Если файл не открылся изначально, то выводим сообщение об ошибке
        cerr << "Error: file could not be opened";
    }
}

Graph reachability(const Graph &crs) {                  //Нахождение матрицы достижимости
    Graph powCrs(crs.m_vertices);
    Graph rCrs(crs.m_vertices);

    for(int i = 1; i < crs.m_vertices; i++){            //Необходимые арифмитические действия для нахождения матрицы достижимости
        powCrs = powCrs * crs;
        rCrs = rCrs + powCrs;
    }

    int arcs = rCrs.m_arcs;
    int *tmpValues = new int[arcs];                    //Создание временных массивов
    int *tmpIColumns = new int[arcs];
    int *tmpQuantityElements = new int[crs.m_vertices]();

    for(int i = 0; i < arcs; i++)                            //Ввод массива значений
        tmpValues[i] = rCrs.values[i];

    for(int i = 0; i < arcs; i++)                            //Ввод массива индексов столбцов
        tmpIColumns[i] = rCrs.iColumns[i];

    for(int i = 0; i <= crs.m_vertices; i++)                            //Ввод массива кол-ва элементов по строкам
        tmpQuantityElements[i] = rCrs.quantityElements[i];

    return Graph(crs.m_vertices, arcs, tmpValues, tmpIColumns, tmpQuantityElements);
}

Graph::~Graph() {                                            //Деструктор
    delete [] Graph::values;
    delete [] Graph::iColumns;
    delete [] Graph::quantityElements;
}
