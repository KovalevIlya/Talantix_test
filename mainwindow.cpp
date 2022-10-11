#include "mainwindow.h"
#include "global.h"
#include "tabel/table.h"
#include "gui/gui.h"

#include <QSettings>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    qRegisterMetaType<QList<QPoint>>("QList<QPoint>");

    _settings = new QSettings("./settings/Settings.ini", QSettings::IniFormat, this);
    QByteArray geometry = _settings->value("Gui/geometry", QByteArray()).toByteArray();
    if (!geometry.isEmpty())
        restoreGeometry(geometry);

    int rowCount = _settings->value("row_count", 5).toInt();
    int columnCount = _settings->value("column_count", 5).toInt();
    if (rowCount < 0 || rowCount > MAX_ROW_COUNT
        || columnCount < 0 || columnCount > MAX_COLUMN_COUNT) {
        qWarning() << tr("Некорректно указаны параметры таблицы в настройках!");

        rowCount = 5;
        columnCount = 5;
    }

    _table = new Table(rowCount, columnCount, this);
    auto gui = new Gui(_table, this);

    setCentralWidget(gui);
}

MainWindow::~MainWindow()
{
    _settings->setValue("Gui/geometry", saveGeometry());
    _settings->setValue("row_count", _table->rowCount());
    _settings->setValue("column_count", _table->columnCount());
}

