#ifndef GUI_H
#define GUI_H

#include <QWidget>
#include <QMutex>

class Table;
class GraphicsScene;
class QGraphicsItem;

/// Основной виджет
class Gui : public QWidget
{
    Q_OBJECT
public:
    /// Конструктор
    /// \param table Лабиринт
    /// \param parent Родительский объект
    explicit Gui(Table *table, QWidget *parent = nullptr);

    /// Инициализировать сцену
    void initScene();
    /// Установить путь на сцену
    /// \param Путь
    Q_SLOT void setPath(const QList<QPoint> &path);
    /// Удалить элемент начала пути
    /// \note Так же удалится весть путь, зависимы от элемента
    void removeStartPath();
    /// Начать поиск пути
    void search();

    /// Получить индекс в координатах лабиринта
    /// \param point Индекс в координатах сцены
    /// \return Индекс в координатах лабиринта
    QPoint getTablePoint(const QPointF &point) const;
    /// Получить индекс в координатах сцены
    /// \param pointИндекс в координатах лабиринта
    /// \return Индекс в координатах сцены
    QPointF getScenePoint(const QPoint &point) const;
    /// Получить индекс пути в координатах сцены
    /// \param point Индекс пути в координатах лабиринта
    /// \return Индекс пути в координатах сцены
    QPointF getLinePoint(const QPoint &point) const;

private:
    Table* _table; ///< Лабиринт
    GraphicsScene* _scene; ///< Сцена
    QGraphicsItem *_startPath = nullptr; ///< Элемент начала пути
    QMutex _mutex; ///< Мьютекс

    bool _isFinish = false; ///< Флаг установки окончательного конца пути

    int _width = 0; ///< Ширина лабиринта указанная пользователем
    int _height = 0; ///< Высота лабиринта указанная пользователем

    const int _widthCell = 50; ///< Ширина отображаемой клетки
    const int _heightCell = 50; ///< Высота отображаемой клетки
};

#endif // GUI_H
