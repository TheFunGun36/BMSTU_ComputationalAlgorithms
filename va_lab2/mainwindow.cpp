#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "file.h"
#include <qmessagebox.h>
#include <qfiledialog.h>
#include <qdebug.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , table() {
    ui->setupUi(this);
    ui->statusbar->showMessage("Таблица не загружена", -1);

    connect(ui->actionLoad, &QAction::triggered, this, &MainWindow::onFileOpen);
    connect(ui->actionSave, &QAction::triggered, this, &MainWindow::onFileSave);
    connect(ui->buttonCalculate, &QPushButton::clicked, this, &MainWindow::onCalculate);
}

MainWindow::~MainWindow() {
    delete ui;
}


void MainWindow::onFileOpen() {
    QString filename = QFileDialog::getOpenFileName(this, QString(), QString(), "*.txt");
    table = File::loadTable(filename.toStdString());
    ui->buttonCalculate->setEnabled(true);
    ui->actionSave->setEnabled(true);
    ui->spinPowerX->setEnabled(true);
    ui->spinPowerY->setEnabled(true);
    ui->spinPowerZ->setEnabled(true);
    ui->spinX->setEnabled(true);
    ui->spinY->setEnabled(true);
    ui->spinZ->setEnabled(true);
}


void MainWindow::onFileSave() {
    QString filename = QFileDialog::getSaveFileName(this, QString(), QString(), "*.txt");
    File::saveTable(filename.toStdString(), table);
}

void MainWindow::onCalculate() {
    try {
        std::vector<size_t> powers(3);
        powers[0] = ui->spinPowerZ->value();
        powers[1] = ui->spinPowerY->value();
        powers[2] = ui->spinPowerX->value();
        Interpolator interp(table, powers);
        std::vector<double> args(3);
        args[0] = ui->spinZ->value();
        args[1] = ui->spinY->value();
        args[2] = ui->spinX->value();
        double result = interp.value(args);
        ui->lineResult->setText(QString::number(result));
    }
    catch (const char *e) {
        QMessageBox::critical(this, "Ошибка", e);
    }
}
