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
    connect(ui->ared, &QAction::toggled, this, [this](bool state) {
        graph[size_t(GraphType::natural)]->setVisible(state);
        ui->plot->replot();
    });
    connect(ui->agrn, &QAction::toggled, this, [this](bool state) {
        graph[size_t(GraphType::onlyLeft)]->setVisible(state);
        ui->plot->replot();
    });
    connect(ui->ablu, &QAction::toggled, this, [this](bool state) {
        graph[size_t(GraphType::both)]->setVisible(state);
        ui->plot->replot();
    });

    graph[size_t(GraphType::natural)] = ui->plot->addGraph();
    graph[size_t(GraphType::natural)]->setName("Естественные границы");
    graph[size_t(GraphType::natural)]->setPen(QPen(Qt::red));

    graph[size_t(GraphType::onlyLeft)] = ui->plot->addGraph();
    graph[size_t(GraphType::onlyLeft)]->setName("Левая граница мод.");
    graph[size_t(GraphType::onlyLeft)]->setPen(QPen(Qt::green));

    graph[size_t(GraphType::both)] = ui->plot->addGraph();
    graph[size_t(GraphType::both)]->setName("Обе границы мод.");
    graph[size_t(GraphType::both)]->setPen(QPen(Qt::blue));

    ui->plot->legend->setVisible(true);
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
    spline[size_t(GraphType::natural)] = std::make_unique<Spline>(table);
    spline[size_t(GraphType::onlyLeft)] = std::make_unique<Spline>(table, true);
    spline[size_t(GraphType::both)] = std::make_unique<Spline>(table, true, true);
    reGraph(QPair(table.minArg(), table.maxArg()));
}

void MainWindow::onCalculate() {
    assert(spline);
    double arg = ui->spinArg->value();
    double val = spline[ui->comboBox->currentIndex()]->value(arg);
    ui->lineResult->setText(QString::number(val));
}

void MainWindow::reGraph(QPair<double, double> range) {
    const size_t idxRange = 1000;
    QVector<double> x(idxRange);
    QVector<double> y1(idxRange);
    QVector<double> y2(idxRange);
    QVector<double> y3(idxRange);

    double step = (range.second - range.first) / idxRange;
    double xcur = range.first;
    for (size_t i = 0; i < idxRange; i++, xcur += step) {
        x[i] = xcur;
        y1[i] = spline[size_t(GraphType::natural)]->value(xcur);
        y2[i] = spline[size_t(GraphType::onlyLeft)]->value(xcur);
        y3[i] = spline[size_t(GraphType::both)]->value(xcur);
    }

    graph[size_t(GraphType::natural)]->setData(x, y1);
    graph[size_t(GraphType::onlyLeft)]->setData(x, y2);
    graph[size_t(GraphType::both)]->setData(x, y3);
    ui->plot->rescaleAxes();
    ui->plot->replot();
}
