#include "mainwindow.h"
#include "tabel/table.h"
#include "gui/gui.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    qRegisterMetaType<QList<QPoint>>("QList<QPoint>");

    auto table = new Table(0, 0, this);
    auto gui = new Gui(table, this);
    gui->setMouseTracking(true);

    setCentralWidget(gui);

    setMouseTracking(this);

    table->reset(5, 5);
}

MainWindow::~MainWindow()
{

}

