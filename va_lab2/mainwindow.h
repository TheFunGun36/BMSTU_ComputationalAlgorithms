#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "table.h"
#include "interpolator.h"

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
    Table table;

private slots:
    void onFileOpen();
    void onFileSave();
    void onCalculate();
};
#endif // MAINWINDOW_H
