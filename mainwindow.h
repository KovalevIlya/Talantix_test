#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QSettings;
class Table;

/// Класс главного окна
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /// Конструктор
    /// \param parent Родительский объект
    MainWindow(QWidget *parent = nullptr);
    /// Деструктор
    ~MainWindow();

private:
    QSettings *_settings; ///< Настройки
    Table *_table; ///< Лабиринта
};
#endif // MAINWINDOW_H
