#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <qlabel.h>>
#include <parachutewidget.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QLabel *label = new QLabel(tr("Hello, World!"));
    ParachuteWidget *p = new ParachuteWidget(this);
    this->setCentralWidget(p);
}

MainWindow::~MainWindow()
{
    delete ui;
}
