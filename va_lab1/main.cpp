#include <iostream>
#include <string>
#include "table.h"
#include "newtonpolynomial.h"

int main() {
    setlocale(LC_ALL, "Russian");
    using namespace std;

    Table table;
    string filename;
    cout << "������� ��� �����, �� �������� ����� �������������� ��������\n>";
    cin >> filename;
    table.loadFromFile(filename);
    cout << "�������� �������:" << endl;
    cout << table << endl;
    
    double value;
    cout << "������� ���������������� �������� (x)\n>";
    cin >> value;

    int power;
    cout << "������� ������� �������� �������\n";
    cout << "(���-�� ����� ����� �������������� ��� ���������� ����� ��� �������� ������)\n>";
    cin >> power;

    table.cutElementsAround(value, power + 1);
    cout << "������������ ����:" << endl;
    cout << table << endl;

    cout << "����� �������\n";
    Polynomial newton(table);
    cout << "������� �������������:" << endl;
    newton.getTableStream(cout);
    cout << "������������ ��������: " << newton.calculate(value);

    cout << "--------------------\n";
    
    cout << "����� ������\n";
    table.duple();
    Polynomial hermite(table);
    table.unDuple();
    cout << "������� �������������:" << endl;
    hermite.getTableStream(cout);
    cout << "������������ ��������: " << hermite.calculate(value);

    cout << "--------------------\n";
    
    cout << "������� �������� ��� �������� ������������\n>";
    cin >> value;
    table.swapXY();
    Polynomial newtonRev(table);
    cout << "������� �������������:" << endl;
    newtonRev.getTableStream(cout);
    cout << "������������ ��������: " << newtonRev.calculate(value);

    return 0;
}
