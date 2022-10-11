#include "gui.h"
#include "tabel/table.h"
#include "graphicsrectitem.h"
#include "global.h"
#include "graphicsscene.h"
#include "eventtypechenged.h"
#include "graphicsview.h"

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPushButton>
#include <QSpinBox>
#include <QLabel>
#include <QLayout>
#include <QDebug>
#include <QGraphicsRectItem>
#include <QMutexLocker>
#include <QtConcurrent/QtConcurrent>

Gui::Gui(Table *table, QWidget *parent)
    : QWidget(parent), _table(table), _scene(new GraphicsScene(this))
{
    _width = _table->columnCount();
    _height = _table->rowCount();

    initScene();

    connect(_table, &Table::sizeChanged, _scene, [this]() {
        initScene();
    });

    connect(_table, &Table::searched, this, &Gui::setPath);

    connect(_scene, &GraphicsScene::clickedItem, _table, [this](const QPointF &pointF) {
        const QPoint point = getTablePoint(pointF);
        const int row = point.x();
        const int column = point.y();
        const Cell cell = _table->cell(row, column);

        if (!_table->isStart()) {
            _table->setStart(row, column);
            if (_table->isFinish()) {
                search();
            } else {
                _isFinish = false;
                removeStartPath();
            }
        } else if (cell.type() == CellNS::Type::Start) {
            _table->setStart(-1, -1);
            removeStartPath();
        } else if (_isFinish && cell.type() == CellNS::Type::Finish) {
            _table->setFinish(-1, -1);
            _isFinish = false;
            removeStartPath();
        } else if (!_isFinish){
            _table->setFinish(row, column);
            _isFinish = _table->isFinish();
            search();
        }
    });

    connect(_scene, &GraphicsScene::setFinish, _table, [this](const QPointF &pointF) {
        const QPoint point = getTablePoint(pointF);
        const int row = point.x();
        const int column = point.y();

        if (_isFinish || !_table->isStart()
            || _table->cell(row, column).type() == CellNS::Type::Start) {
            return;
        }

        _table->setFinish(row, column);
        search();
    });

    connect(_scene, &GraphicsScene::removeFinish, _table, [this]() {
        if (_isFinish)
            return;

        _table->setFinish(-1, -1);
        removeStartPath();
    });

    connect(_table, &Table::cellChanged,
            _scene, [this](int row, int column, Cell cell) {

        _scene->sendEvent(_scene->itemAt(getScenePoint({ row, column }), QTransform()),
                          new EventTypeChenged(cell.type()));
    });


    auto pbGenerate = new QPushButton(tr("Генерировать"));
    connect(pbGenerate, &QPushButton::clicked, _table, [this]() {
        _table->reset(_height, _width);
    });

    auto sbWidth = new QSpinBox();
    sbWidth->setMinimum(0);
    sbWidth->setMaximum(MAX_COLUMN_COUNT);
    sbWidth->setValue(_width);
    connect(sbWidth, QOverload<int>::of(&QSpinBox::valueChanged), this, [this](int value){
        _width = value;
    });

    auto sbHeight = new QSpinBox();
    sbHeight->setMinimum(0);
    sbHeight->setMaximum(MAX_ROW_COUNT);
    sbHeight->setValue(_height);
    connect(sbHeight, QOverload<int>::of(&QSpinBox::valueChanged), this, [this](int value){
        _height = value;
    });

    auto tableView = new GraphicsView(_scene);
    tableView->setMouseTracking(true);

    auto layRight = new QVBoxLayout();
    layRight->addWidget(pbGenerate);
    layRight->addStretch();

    auto layUp = new QHBoxLayout();
    layUp->addWidget(tableView);
    layUp->addLayout(layRight);

    auto layDown = new QHBoxLayout();
    layDown->addWidget(new QLabel(tr("Ширина")));
    layDown->addWidget(sbWidth);
    layDown->addSpacing(100);
    layDown->addWidget(new QLabel(tr("Высота")));
    layDown->addWidget(sbHeight);
    layDown->addStretch();

    auto layMain = new QVBoxLayout(this);
    layMain->addLayout(layUp);
    layMain->addLayout(layDown);
}

void Gui::initScene()
{
    _isFinish = false;
    removeStartPath();
    _scene->clear();

    const int rowCount = _table->rowCount();
    for (int row = 0; row < rowCount; ++row) {
        const int columnount = _table->columnCount();
        for (int column = 0; column < columnount; ++column) {
            QRect rect(column * _widthCell, row * _heightCell, _widthCell, _heightCell);
            auto item = new GraphicsRectItem(rect, _table->cell(row, column).type());

            auto textItem = new QGraphicsSimpleTextItem("", item);
            textItem->setFont(QFont("Arial", 25));
            textItem->setBrush(QBrush(QColor(Qt::red)));

            _scene->addItem(item);
        }
    }
}

void Gui::setPath(const QList<QPoint> &path)
{
    removeStartPath();

    const int countLine = path.count() - 1;

    QGraphicsLineItem *parent = nullptr;

    QMutexLocker mutex(&_mutex);

    for (int i = 0; i < countLine; ++i) {
        QLineF line = QLineF(getLinePoint(path[i]), getLinePoint(path[i + 1]));
        parent = new QGraphicsLineItem(line, parent);
        parent->setPen(QPen(QColor(Qt::red)));

        if (i == 0)
            _startPath = parent;
    }
    if (_startPath)
        _scene->addItem(_startPath);
}

void Gui::removeStartPath()
{
    QMutexLocker mutex(&_mutex);
    if (!_scene->items().contains(_startPath))
        return;

    _scene->removeItem(_startPath);
    _startPath = nullptr;
}

void Gui::search()
{
    auto future = QtConcurrent::run([this]() {
        _table->search();
    });
}

QPoint Gui::getTablePoint(const QPointF &point) const
{
    const int y = qRound(point.x() / _widthCell);
    const int x = qRound(point.y() / _heightCell);
    return { x, y };
}

QPointF Gui::getScenePoint(const QPoint &point) const
{
    const double y = point.x() * _widthCell;
    const double x = point.y() * _heightCell;
    return { x, y };
}

QPointF Gui::getLinePoint(const QPoint &point) const
{
    const double y = point.x() * _widthCell + _widthCell / 2;
    const double x = point.y() * _heightCell + _heightCell / 2;
    return { x, y };
}
