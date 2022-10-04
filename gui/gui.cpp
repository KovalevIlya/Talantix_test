#include "gui.h"
#include "tabel/table.h"

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPushButton>
#include <QSpinBox>
#include <QLabel>
#include <QLayout>

Gui::Gui(Table *table, QWidget *parent)
    : QWidget(parent), _table(table), _scene(new QGraphicsScene(this))
{
    initScene();
    connect(_table, &Table::sizeChanged, _scene, [this]() {
        initScene();
    });

    auto pbGenerate = new QPushButton(tr("Генерировать"));
    connect(pbGenerate, &QPushButton::clicked, _table, [this]() {
        _table->reset(_width, _height);
    });

    auto sbWidth = new QSpinBox();
    sbWidth->setMinimum(0);
    connect(sbWidth, QOverload<int>::of(&QSpinBox::valueChanged), this, [this](int value){
        _width = value;
    });

    auto sbHeight = new QSpinBox();
    sbHeight->setMinimum(0);
    connect(sbHeight, QOverload<int>::of(&QSpinBox::valueChanged), this, [this](int value){
        _height = value;
    });

    auto layRight = new QVBoxLayout();
    layRight->addWidget(pbGenerate);
    layRight->addStretch();

    auto layUp = new QHBoxLayout();
    layUp->addWidget(new QGraphicsView(_scene));
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
    _scene->clear();
    const int rowCount = _table->rowCount();
    for (int row = 0; row < rowCount; ++row) {
        const int columnount = _table->columnCount();
        for (int column = 0; column < columnount; ++column) {
            QRect rect(column * _widthCell, row * _heightCell, _widthCell, _heightCell);
            QBrush brush = _table->cell(row, column).type() == Cell::Type::Close
                    ? QBrush(Qt::DiagCrossPattern)
                    : QBrush();

            _scene->addRect(rect, QPen(), brush);
        }
    }
}
