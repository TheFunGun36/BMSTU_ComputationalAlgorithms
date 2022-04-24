#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <qpair.h>
#include <memory>
#include "qcustomplot.h"
#include "spline.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    std::unique_ptr<Spline> spline[3];

    QCPGraph *graph[3];
    enum class GraphType {
        natural,
        onlyLeft,
        both
    };

private slots:
    void onFileOpen();
    void onCalculate();
    void reGraph(QPair<double, double> range);
};
#endif // MAINWINDOW_H
