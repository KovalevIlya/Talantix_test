#include "mainwindow.h"
#include "tabel/table.h"
#include "gui/gui.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    auto table = new Table(0, 0, this);
    setCentralWidget(new Gui(table, this));
}

MainWindow::~MainWindow()
{

}

