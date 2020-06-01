#ifndef GAMEUNIT_H
#define GAMEUNIT_H

#include <QWidget>
#include <QPaintEvent>
#include <QVector>
#include <QKeyEvent>
#include <QImage>
#include <QPainter>
#include <QDebug>

using ull = unsigned long long;

static const int PONUNIT = 64;

class GameUnit : public QWidget
{
    Q_OBJECT
public:
    explicit GameUnit(QWidget *parent = nullptr);

    // Массивчич идентификаторов спрайтов.
    QVector<QVector<int>> gameMap = {
        {15,39,23,39,23,39,39,39,39,23,39,23,39,39,19,15,39,39,39,19},
        {35,52,43,50,43,53,50,50,52,9,50,43,52,50,05,03,52,50,52,27},
        {35,00,43,00,6,44,02,00,00,53,00,43,00,00,53,52,00,7,00,27},
        {35,00,43,00,50,53,6,44,44,10,00,9,00,8,44,44,44,4,00,27},
        {35,00,43,00,7,00,52,50,53,50,00,50,00,50,53,50,50,52,00,27},
        {35,00,9,00,9,00,7,00,11,00,11,00,8,44,10,00,8,44,44,20},
        {35,00,50,00,52,00,43,00,50,00,52,00,50,53,50,00,52,52,53,27},
        {35,00,8,44,10,00,43,00,8,44,10,00,11,00,8,44,44,10,00,27},
        {35,00,53,52,50,00,43,00,53,52,50,00,53,00,50,52,50,53,00,27},
        {13,31,31,31,31,31,14,31,31,31,31,31,31,31,31,31,31,31,31,12}
    };

private:

    // Массив спарйтов.
    QImage imageWallmass[60];

    bool fullScreenPointer = true;
    void keyPressEvent(QKeyEvent *event);
    void paintEvent(QPaintEvent *pEvent);
    void loadTexture();
    void doDraw();
};

#endif // GAMEUNIT_H
