#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <qfile.h>
#include <qfiledialog.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    ui->setupUi(this);

    connect(ui->actionLoad, &QAction::triggered, this, &MainWindow::onFileOpen);
    connect(ui->buttonCalculate, &QPushButton::clicked, this, &MainWindow::onCalculate);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::onFileOpen() {
    QString filename = QFileDialog::getOpenFileName(this, QString(), QString(), "*.txt");
    Table table(filename.toStdString());
    ui->buttonCalculate->setEnabled(true);
    ui->actionSave->setEnabled(true);
    ui->spinArg->setEnabled(true);
    spline = std::make_unique<Spline>(table);
}


void MainWindow::onCalculate() {
    assert(spline);
    double arg = ui->spinArg->value();
    double val = spline->value(arg);
    ui->lineResult->setText(QString::number(val));
}
