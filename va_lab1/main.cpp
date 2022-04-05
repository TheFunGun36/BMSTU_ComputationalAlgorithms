#include <iostream>
#include <string>
#include "table.h"
#include "newtonpolynomial.h"

int main() {
    setlocale(LC_ALL, "Russian");
    using namespace std;

    Table table;
    string filename;
    cout << "Введите имя файла, из которого будет осуществляться загрузка\n>";
    cin >> filename;
    table.loadFromFile(filename);
    cout << "Исходная таблица:" << endl;
    cout << table << endl;
    
    double value;
    cout << "Введите аппроксимируемый аргумент (x)\n>";
    cin >> value;

    int power;
    cout << "Введите степень полинома Ньютона\n";
    cout << "(это-же число будет использоваться как количество узлов для полинома Эрмита)\n>";
    cin >> power;

    table.cutElementsAround(value, power + 1);
    cout << "Используемые узлы:" << endl;
    cout << table << endl;

    cout << "Метод Ньютона\n";
    Polynomial newton(table);
    cout << "Таблица коэффициентов:" << endl;
    newton.getTableStream(cout);
    cout << "Рассчитанное значение: " << newton.calculate(value);

    cout << "--------------------\n";
    
    cout << "Метод Эрмита\n";
    table.duple();
    Polynomial hermite(table);
    table.unDuple();
    cout << "Таблица коэффициентов:" << endl;
    hermite.getTableStream(cout);
    cout << "Рассчитанное значение: " << hermite.calculate(value);

    cout << "--------------------\n";
    
    cout << "Введите значение для обратной интерполяции\n>";
    cin >> value;
    table.swapXY();
    Polynomial newtonRev(table);
    cout << "Таблица коэффициентов:" << endl;
    newtonRev.getTableStream(cout);
    cout << "Рассчитанное значение: " << newtonRev.calculate(value);

    return 0;
}
