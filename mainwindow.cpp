#include "mainwindow.h"
#include "tabel/table.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    auto table = new Table(5, 5);
    qDebug() << table->search();
    exit(0);
}

MainWindow::~MainWindow()
{
}

