#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QLabel>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QLabel *label = new QLabel(tr("Hello, World!"));
    this->setCentralWidget(label);
}

MainWindow::~MainWindow()
{
    delete ui;
}
