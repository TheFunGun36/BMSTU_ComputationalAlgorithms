#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    ui->setupUi(this);
    ui->statusbar->showMessage("Таблица не загружена", -1);
}

MainWindow::~MainWindow() {
    delete ui;
}

