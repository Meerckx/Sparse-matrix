#include "graph.h"

using namespace std;

Graph::Graph(int vertices, int arcs) {                          //�����������
    m_vertices = vertices;
    m_arcs = arcs;
    values = new int[arcs];
    iColumns = new int[arcs];
    quantityElements = new int[vertices + 1];

    cout << "��������: ";
    for(int i = 0; i < arcs; i++)                            //���� ������� ��������
        cin >> values[i];

    cout << "������� ��������: ";
    for(int i = 0; i < arcs; i++)                            //���� ������� �������� ��������
        cin >> iColumns[i];

    cout << "���-�� ��������� �� �������: ";
    for(int i = 0; i <= vertices; i++)                        //���� ������� ���-�� ��������� �� �������
        cin >> quantityElements[i];
}

Graph::Graph(int vertices) {                                    //����������� ��������� �������
    m_vertices = vertices;
    m_arcs = vertices;
    values = new int[vertices];
    iColumns = new int[vertices];
    quantityElements = new int[vertices + 1]();

    for(int i = 0; i < vertices; i++)                            //��������� ������� ��������
        values[i] = 1;

    for(int i = 0; i < vertices; i++)                            //��������� ������� �������� ��������
        iColumns[i] = i;

    for(int i = 0; i <= vertices; i++)                           //��������� ������� ���-�� ��������� �� �������
        quantityElements[i] = i;
}

Graph::Graph(string address, int vertices, int arcs) {          //����������� ��� ������ �� �����
    ifstream file(address);         //��������� ���� ��� ������

    if(file.is_open()){             //���������, ������� �� ������� ����
        string str;

        m_vertices = vertices;
        m_arcs = arcs;
        values = new int[arcs]();
        iColumns = new int[arcs]();
        quantityElements = new int[vertices + 1]();

        cout << "��������: ";
        for(int i = 0; i < arcs; i++){                                  //��������� ������� ��������
            file >> str;
            for(int j = 0; str[j] != '\0'; j++){                        //��������� ����������� ������ ����� � ���������� � ������ ����������,
                values[i] = values[i] * 10 + (str[j] - '0');            //������� ����������� char � int
            }
            cout << values[i] << " ";
        }

        cout << "\n������� ��������: ";
        for(int i = 0; i < arcs; i++){                                  //��������� ������� �������� ��������
            file >> str;
            for(int j = 0; str[j] != '\0'; j++){
                iColumns[i] = iColumns[i] * 10 + (str[j] - '0');
            }
            cout << iColumns[i] << " ";
        }

        cout << "\n���-�� ��������� �� �������: ";
        for(int i = 0; i <= vertices; i++){                             //��������� ������� ���-�� ��������� �� �������
            file >> str;
            for(int j = 0; str[j] != '\0'; j++){
                quantityElements[i] = quantityElements[i] * 10 + (str[j] - '0');
            }
            cout << quantityElements[i] << " ";
        }

        file.close();               //��������� ����
    }
    else {                                      //���� ���� �� �������� ����������, �� ������� ��������� �� ������
        cerr << "Error: file could not be opened";
    }
}

Graph::Graph(int vertices, int finalArcs, int *tmpValues, int *tmpIColumns, int *tmpQuantityElements) {     //����������� c ���. �����������
    m_vertices = vertices;
    m_arcs = finalArcs;
    values = new int[finalArcs];
    iColumns = new int[finalArcs];
    quantityElements = new int[vertices + 1];

    for(int i = 0; i < finalArcs; i++)                            //���� ������� ��������
        values[i] = tmpValues[i];

    for(int i = 0; i < finalArcs; i++)                            //���� ������� �������� ��������
        iColumns[i] = tmpIColumns[i];

    for(int i = 0; i <= vertices; i++)                            //���� ������� ���-�� ��������� �� �������
        quantityElements[i] = tmpQuantityElements[i];

    delete [] tmpValues;
    delete [] tmpIColumns;
    delete [] tmpQuantityElements;
}

Graph::Graph(const Graph &crs) {                             //����������� �����������
    m_vertices = crs.m_vertices;
    m_arcs = crs.m_arcs;
    values = new int[m_arcs];
    iColumns = new int[m_arcs];
    quantityElements = new int[m_vertices + 1];

    for(int i = 0; i < m_arcs; i++)                                 //����������� ������� ��������
        values[i] = crs.values[i];

    for(int i = 0; i < m_arcs; i++)                                 //����������� ������� �������� ��������
        iColumns[i] = crs.iColumns[i];

    for(int i = 0; i <= m_vertices; i++)                            //����������� ������� ���-�� ��������� �� �������
        quantityElements[i] = crs.quantityElements[i];
}

Graph transpose(const Graph &crs) {                          //����������������
    int count = 0;                                          //������� ���-�� ��������� ���������
    int vertices = crs.m_vertices;
    int arcs = crs.m_arcs;
    int tmpIndex = 0;                                       //������ ������ ��������� � ����� ������
    int *tmpValues = new int[crs.m_arcs];                   //�������� ��������� ��������
    int *tmpIColumns = new int[crs.m_arcs];
    int *tmpQuantityElements = new int[crs.m_vertices + 1]();

    for(int i = 0; i < vertices; i++){                                                      //���������� ������� ������
        for(int currentArc = 0; currentArc < arcs; currentArc++){                           //���������� �� ������ ����
            if(crs.iColumns[currentArc] == i){                                              //���� �������� �������� ������� iColumns = ������ �������,
                tmpValues[tmpIndex] = crs.values[currentArc];                               //�� ���������� �������� ����� �������� � ����� ������.
                for(int indexCount = 0; indexCount < vertices; indexCount++)                //��������� ����� ������� �������� QuantityElements � ����
                    if((currentArc + 1) > crs.quantityElements[indexCount] && (currentArc + 1) <= crs.quantityElements[indexCount + 1]) //������, �
                        tmpIColumns[tmpIndex] = indexCount;                                 //������� ��������� �������� �������� ����� ����.
                tmpIndex++;                                 //��������� � ���������� ����
                count++;
            }
        }
        tmpQuantityElements[i + 1] += count;                //���������� ���������� ��������� � ����� ������
    }
    return Graph(vertices, arcs, tmpValues, tmpIColumns, tmpQuantityElements);
}

void adding(int* &crs, int n, int size) {                    //���������� �������� � ����� �������
    int *tmpCrs = new int[size + 1];                //������ ����� ������ �� 1 ������

    for(int i = 0; i < size; i++)                   //�������� ��������
        tmpCrs[i] = crs[i];
    tmpCrs[size] = n;                               //��������� �����

    delete [] crs;                                  //������� ������ ������

    crs = tmpCrs;                                   //��������� �� ����� ������
    tmpCrs = nullptr;                               //������� ���������
}

Graph& Graph::operator=(const Graph &crs) {                  //�������� ������������
    m_vertices = crs.m_vertices;
    m_arcs = crs.m_arcs;
    values = new int[m_arcs];
    iColumns = new int[m_arcs];
    quantityElements = new int[m_vertices + 1];

    for(int i = 0; i < m_arcs; i++)                                 //����������� ������� ��������
        values[i] = crs.values[i];

    for(int i = 0; i < m_arcs; i++)                                 //����������� ������� �������� ��������
        iColumns[i] = crs.iColumns[i];

    for(int i = 0; i <= m_vertices; i++)                            //����������� ������� ���-�� ��������� �� �������
        quantityElements[i] = crs.quantityElements[i];

    return *this;
}

Graph operator+(const Graph &crs1, const Graph &crs2) {      //�������� ��������
    int maxArcs = crs1.m_arcs;                               //����� ������������� ���-�� ���
    if(crs1.m_arcs < crs2.m_arcs)
        maxArcs = crs2.m_arcs;
    int vertices = crs1.m_vertices;                          //���������� ���-�� ������ � ��������� ����������

    int *tmpValues = new int[maxArcs * 2];                   //�������� ��������� ��������
    int *tmpIColumns = new int[maxArcs * 2];
    int *tmpQuantityElements = new int[vertices + 1]();

    int leftItems{0}, rightItems{0};                         //�������� ���������, ���������� �� ������� ����������� ��-�� �� ����� � ������ ������
    int tmpQuantity{0};                                      //�������� �������� ��������� ��������� ��� �������� �������

    for(int i = 1; i <= vertices; i++){                                                         //���������� �� ���� ���������, ����� i = 0
        while(leftItems < crs1.quantityElements[i] && rightItems < crs2.quantityElements[i]){   //���� ������� ����������� ���������� ������ ��������
            if(crs1.iColumns[leftItems] < crs2.iColumns[rightItems]){                           //�������� �������� ������� ��������� ���������, ��
                tmpValues[tmpQuantity] = crs1.values[leftItems];                                //��������� ����, � ������� ���������� ��������
                tmpIColumns[tmpQuantity] = crs1.iColumns[leftItems];                            //��������� ����� ��������� �������� �� leftItems
                leftItems++;                                                                    //��������� � ���������� ������ �������
                tmpQuantity++;                                                                  //����������� ���-�� ��������� ��������� � ������
            }
            else if(crs1.iColumns[leftItems] > crs2.iColumns[rightItems]){                      //������, ���� �������� �������� ������ ������� iColums
                tmpValues[tmpQuantity] = crs2.values[rightItems];                               //������ �������, �� ���������� �������� ���������
                tmpIColumns[tmpQuantity] = crs2.iColumns[rightItems];                           //��������� �������� �� rightItems
                rightItems++;                                                                   //��������� � ���������� ������� �������
                tmpQuantity++;                                                                  //����������� ���-�� ��������� ��������� � ������
            }
            else {                                                                              //���� ����� ������� �������� � ����������� ����-��,
                tmpValues[tmpQuantity] = crs1.values[leftItems] + crs2.values[rightItems];      //�� ��������� �������� values
                tmpIColumns[tmpQuantity] = crs1.iColumns[leftItems];
                leftItems++;
                rightItems++;
                tmpQuantity++;
            }
        }
        while(leftItems < crs1.quantityElements[i]){                            //���� � ����� ������ �������� ��������, �� ������� �� �� ���������,
            tmpValues[tmpQuantity] = crs1.values[leftItems];                    //�� � ��������� ����� ������ ��� � ���������� ���������������
            tmpIColumns[tmpQuantity] = crs1.iColumns[leftItems];                //��������, ����������� �����
            leftItems++;
            tmpQuantity++;
        }
        while(rightItems < crs2.quantityElements[i]){                           //���� � ������ ������ �������� ��������, �� ������� �� ���������...
            tmpValues[tmpQuantity] = crs2.values[rightItems];
            tmpIColumns[tmpQuantity] = crs2.iColumns[rightItems];
            rightItems++;
            tmpQuantity++;
        }
        tmpQuantityElements[i] = tmpQuantity;                                   //���������� �������� tmpQuantity �� i-�� ���� � ������ ��������� ��-��
    }

    int finalArcs = tmpQuantityElements[vertices];                              //�������� ���-�� ��� ����� ��������

    return Graph(vertices, finalArcs, tmpValues, tmpIColumns, tmpQuantityElements);         //���������� ���������� �������� � ����� �����������
}

Graph operator*(const Graph &crs1, const Graph &crs2) {      //�������� ���������
    int *tmpValues = new int[0];                    //�������� ��������� ��������
    int *tmpIColumns = new int[0];
    int *tmpQuantityElements = new int[crs1.m_vertices + 1]();

    int vertices = crs1.m_vertices;

    int sum;                                        //����� ������ ��������� ������ �� �������
    int count = 0;                                  //���������� ��������� ��������� � ���������� ��������� ����� ������
    int shift = 0;                                  //������� ����������� �� �������� �������� � �������� ��������

    Graph crsTranspose = transpose(crs2);           //������������� ������ �������

    for(int leftRows = 1; leftRows <= vertices; leftRows++){                 //���������� �� ������� ����� � ������ ������. ����� ����
        for(int rightRows = 1; rightRows <= vertices; rightRows++){          //���������� �� ������� �������, � ���� ������� �������� ���������,
            sum = 0;                                                         //�� � ����� ���������� ������������ ������ ���������
            for(int leftColumns = crs1.quantityElements[leftRows - 1]; leftColumns < crs1.quantityElements[leftRows]; leftColumns++){
                for(int rightColumns = crsTranspose.quantityElements[rightRows - 1]; rightColumns < crsTranspose.quantityElements[rightRows]; rightColumns++){
                    if(crs1.iColumns[leftColumns] == crsTranspose.iColumns[rightColumns]){
                        sum += crs1.values[leftColumns] * crsTranspose.values[rightColumns];        //���� ������� �������, �� ��������� ��������� ���� �
                        break;                                                                      //��������� � ���������� ����
                    }
                }
            }
            if(sum){                                                //���� ����� ����� �������� ������ ������ ������� ���������, �� ���������
                adding(tmpValues, sum, shift);                      //����������� �������� � �������, � ����� ����������� ��������
                adding(tmpIColumns, rightRows - 1, shift);
                shift++;
                count++;
            }
        }
        tmpQuantityElements[leftRows] += count;                     //���������� ���������� ��������� � ����� ������
    }
    int finalArcs = tmpQuantityElements[vertices];                  //�������� ���-�� ���

    return Graph(vertices, finalArcs, tmpValues, tmpIColumns, tmpQuantityElements);         //���������� ���������� �������� � ����� �����������
}

void Graph::output() const {                                 //�����
    cout << "��������: ";
    for(int i = 0; i < m_arcs; i++)                          //����� ������� ��������
        cout << Graph::values[i] << " ";

    cout << "\n������� ��������: ";
    for(int i = 0; i < m_arcs; i++)                          //����� ������� �������� ��������
        cout << Graph::iColumns[i] << " ";

    cout << "\n���-�� ��������� �� �������: ";
    for(int i = 0; i <= m_vertices; i++)                      //����� ������� ���-�� ��������� �� �������
        cout << Graph::quantityElements[i] << " ";
}

void Graph::fileOutput(string address) const {               //����� � ����
    ofstream file(address);                 //��������� ���� ��� ������

    if(file.is_open()){                     //���������, ������� �� ������� ����

        file << values[0];                      //���������� ������ ��������
        for(int i = 1; i < m_arcs; i++)         //��� ����, ����� �������� ������ ��������, ������� ������� ������ �������, � ����� ��� ��� ���������
            file << " " << values[i];
        file << '\n';                           //��������� �� ����� ������

        file << iColumns[0];                    //���������� ������ �������� ��������
        for(int i = 1; i < m_arcs; i++)
            file << " " << iColumns[i];
        file << '\n';

        file << quantityElements[0];            //���������� ������ ���-�� ��������� �� �������
        for(int i = 1; i <= m_vertices; i++)
            file << " " << quantityElements[i];

        file.close();                           //��������� ����
    }
    else {                                      //���� ���� �� �������� ����������, �� ������� ��������� �� ������
        cerr << "Error: file could not be opened";
    }
}

Graph reachability(const Graph &crs) {                  //���������� ������� ������������
    Graph powCrs(crs.m_vertices);
    Graph rCrs(crs.m_vertices);

    for(int i = 1; i < crs.m_vertices; i++){            //����������� �������������� �������� ��� ���������� ������� ������������
        powCrs = powCrs * crs;
        rCrs = rCrs + powCrs;
    }

    int arcs = rCrs.m_arcs;
    int *tmpValues = new int[arcs];                    //�������� ��������� ��������
    int *tmpIColumns = new int[arcs];
    int *tmpQuantityElements = new int[crs.m_vertices]();

    for(int i = 0; i < arcs; i++)                            //���� ������� ��������
        tmpValues[i] = rCrs.values[i];

    for(int i = 0; i < arcs; i++)                            //���� ������� �������� ��������
        tmpIColumns[i] = rCrs.iColumns[i];

    for(int i = 0; i <= crs.m_vertices; i++)                            //���� ������� ���-�� ��������� �� �������
        tmpQuantityElements[i] = rCrs.quantityElements[i];

    return Graph(crs.m_vertices, arcs, tmpValues, tmpIColumns, tmpQuantityElements);
}

Graph::~Graph() {                                            //����������
    delete [] Graph::values;
    delete [] Graph::iColumns;
    delete [] Graph::quantityElements;
}
