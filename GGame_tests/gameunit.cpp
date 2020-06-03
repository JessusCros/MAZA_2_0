#include "gameunit.h"

GameUnit::GameUnit(QWidget *parent) : QWidget(parent) {

    // Аы сделал бекграунд черным.
    setStyleSheet("background-color:black;");

    // Аы поставил минимальное разрешение.
    setMinimumSize(1280,640);

    // Аы поставил минимальное разрешение.
    setMaximumSize(1280,640);

    // ну чисто загрузил текстуры.
    loadTexture();

    doTextures();
}


// Обработчик клавиатуры.
void GameUnit::keyPressEvent(QKeyEvent *event) {

    // Обработка выхода из приложения.
    if (event->key() == Qt::Key_Escape) {
        close();
    }
}

// Функция обработки событи рисования на виджете.
void GameUnit::paintEvent(QPaintEvent *pEvent) {
    Q_UNUSED(pEvent);

    doDrawFloor();

    doDrawWall();
}

// Функция предзагрузки текстур.
void GameUnit::loadTexture() {

    // Забиваем текстуры.
    for (int i = 1; i <= 54; ++i) {
        imageWallmass[i].load(":/UpWalls/tile" + QString::number(i));
    }
}

// Функция рисование пола.
void GameUnit::doDrawFloor() {

    // Объект на котором мы рисуем то, что мы рисуем.(после он отображается на основном виджете)
    QPainter gamePaint(this);

    // Индексы для пробега по карте прорисовки.
    int indexX;
    int indexY;

    // Рисуем пол.
    for (indexX = 1; indexX < gameMap.size()-1; ++indexX) {
        for (indexY = 1; indexY < gameMap[indexX].size()-1; ++indexY) {
            if (gameMap[indexX][indexY] == 0) {
                gamePaint.drawImage((indexY-1) * PONUNIT, (indexX-1) * PONUNIT, imageWallmass[50  - (qrand() % 3)]);
            }
        }
    }

}
// Функция рисования стен.
void GameUnit::doDrawWall() {

    // Объект на котором мы рисуем то, что мы рисуем.(после он отображается на основном виджете)
    QPainter gamePaint(this);

    // Индексы для пробега по карте прорисовки.
    int indexX;
    int indexY;

    // Далее рисуем стенки.....
    for (indexX = 1; indexX < gameMap.size()-1; ++indexX) {
        for (indexY = 1; indexY < gameMap[indexX].size()-1; ++indexY) {
            if (gameMap[indexX][indexY] != 0) {
                gamePaint.drawImage((indexY-1) * PONUNIT, (indexX-1) * PONUNIT, imageWallmass[gameMap[indexX][indexY]]);
            }
        }
    }
}

// Функция обработки текстур.
void GameUnit::doTextures() {

    int index;
    int indey;

    QDebug dbg(QtDebugMsg);

    for (index = 1; index < gameColMap.size()-1; index++) {
        for (indey = 1; indey < gameColMap[index].size()-1; indey++) {
            ifElse(index,indey);
        }
    }

}

// Функция обработки положения стен.
// ВНИМАНИЕ. Не для слабонервных.
void GameUnit::ifElse(int index, int indey) {

    // 1
    if     (( UL == 1) && (UM == 1) && (UR == 1) &&
            ( ML == 1) && (MM == 1) && (MR == 1) &&
            ( DL == 1) && (DM == 1) && (DR == 1)) {
        gameMap[index][indey] = 1;
    }

    // 2
    if     (( UL == UL) && (UM == 0) && (UR == UR) &&
            ( ML == 1) && (MM == 1) && (MR == 0) &&
            ( DL == 1) && (DM == 1) && (DR == DR)) {
        gameMap[index][indey] = 2;
    }

    // 3
    if     (( UL == UL) && (UM == 0) && (UR == UR) &&
            ( ML == 1) && (MM == 1) && (MR == 0) &&
            ( DL == 0) && (DM == 1) && (DR == DR)) {
        gameMap[index][indey] = 3;
    }

    // 4
    if     (( UL == 1) && (UM == 1) && (UR == UR) &&
            ( ML == 1) && (MM == 1) && (MR == 0) &&
            ( DL == DL) && (DM == 0) && (DR == DR)) {
        gameMap[index][indey] = 4;
        gameMap[index + 1][indey] = 54 - (qrand() % 4);
    }

    // 5
    if     (( UL == 0) && (UM == 1) && (UR == UR) &&
            ( ML == 1) && (MM == 1) && (MR == 0) &&
            ( DL == DL) && (DM == 0) && (DR == DR)) {
        gameMap[index][indey] = 5;
        gameMap[index + 1][indey] = 54 - (qrand() % 4);
    }


    // 6
    if     (( UL == UL) && (UM == 1) && (UR == 1) &&
            ( ML == 0) && (MM == 1) && (MR == 1) &&
            ( DL == DL) && (DM == 0) && (DR == DR)) {
        gameMap[index][indey] = 6;
        gameMap[index + 1][indey] = 54 - (qrand() % 4);
    }

    // 7
    if     (( UL == UL) && (UM == 1) && (UR == 0) &&
            ( ML == 0) && (MM == 1) && (MR == 1) &&
            ( DL == DL) && (DM == 0) && (DR == DR)) {
        gameMap[index][indey] = 7;
        gameMap[index + 1][indey] = 54 - (qrand() % 4);
    }

    // 8
    if     (( UL == UL) && (UM == 0) && (UR == UR) &&
            ( ML == 0) && (MM == 1) && (MR == 0) &&
            ( DL == DL) && (DM == 1) && (DR == DR)) {
        gameMap[index][indey] = 8;
    }

    // 9
    if     (( UL == UL) && (UM == 0) && (UR == UR) &&
            ( ML == 0) && (MM == 1) && (MR == 1) &&
            ( DL == DL) && (DM == 0) && (DR == DR)) {
        gameMap[index][indey] = 9;
        gameMap[index + 1][indey] = 54 - (qrand() % 4);
    }

    // 10
    if     (( UL == UL) && (UM == 1) && (UR == UR) &&
            ( ML == 0) && (MM == 1) && (MR == 0) &&
            ( DL == DL) && (DM == 0) && (DR == DR)) {
        gameMap[index][indey] = 10;
        gameMap[index + 1][indey] = 54 - (qrand() % 4);
    }

    // 11
    if     (( UL == UL) && (UM == 0) && (UR == UR) &&
            ( ML == 1) && (MM == 1) && (MR == 0) &&
            ( DL == DL) && (DM == 0) && (DR == DR)) {
        gameMap[index][indey] = 11;
        gameMap[index + 1][indey] = 54 - (qrand() % 4);
    }

    // 12
    if     (( UL == UL) && (UM == 0) && (UR == UR) &&
            ( ML == 0) && (MM == 1) && (MR == 0) &&
            ( DL == DL) && (DM == 0) && (DR == DR)) {
        gameMap[index][indey] = 12;
        gameMap[index + 1][indey] = 54 - (qrand() % 4);
    }

    // 13
    if     (( UL == 0) && (UM == 1) && (UR == 1) &&
            ( ML == 1) && (MM == 1) && (MR == 1) &&
            ( DL == 1) && (DM == 1) && (DR == 1)) {
        gameMap[index][indey] = 13;
    }

    // 14
    if     (( UL == 1) && (UM == 1) && (UR == 0) &&
            ( ML == 1) && (MM == 1) && (MR == 1) &&
            ( DL == 1) && (DM == 1) && (DR == 1)) {
        gameMap[index][indey] = 14;
    }

    // 15
    if     (( UL == 0) && (UM == 1) && (UR == 0) &&
            ( ML == 1) && (MM == 1) && (MR == 1) &&
            ( DL == 1) && (DM == 1) && (DR == 1)) {
        gameMap[index][indey] = 15;
    }

    // 16
    if     (( UL == 1) && (UM == 1) && (UR == 1) &&
            ( ML == 1) && (MM == 1) && (MR == 1) &&
            ( DL == 1) && (DM == 1) && (DR == 0)) {
        gameMap[index][indey] = 16;
    }

    // 17
    if     (( UL == 0) && (UM == 1) && (UR == 1) &&
            ( ML == 1) && (MM == 1) && (MR == 1) &&
            ( DL == 1) && (DM == 1) && (DR == 0)) {
        gameMap[index][indey] = 17;
    }

    // 18
    if     (( UL == 1) && (UM == 1) && (UR == 0) &&
            ( ML == 1) && (MM == 1) && (MR == 1) &&
            ( DL == 1) && (DM == 1) && (DR == 0)) {
        gameMap[index][indey] = 18;
    }

    // 19
    if     (( UL == 0) && (UM == 1) && (UR == 0) &&
            ( ML == 1) && (MM == 1) && (MR == 1) &&
            ( DL == 1) && (DM == 1) && (DR == 0)) {
        gameMap[index][indey] = 19;
    }

    // 20
    if     (( UL == 1) && (UM == 1) && (UR == 1) &&
            ( ML == 1) && (MM == 1) && (MR == 1) &&
            ( DL == 0) && (DM == 1) && (DR == 1)) {
        gameMap[index][indey] = 20;
    }

    // 21
    if     (( UL == 0) && (UM == 1) && (UR == 1) &&
            ( ML == 1) && (MM == 1) && (MR == 1) &&
            ( DL == 0) && (DM == 1) && (DR == 1)) {
        gameMap[index][indey] = 21;
    }

    // 22
    if     (( UL == 1) && (UM == 1) && (UR == 0) &&
            ( ML == 1) && (MM == 1) && (MR == 1) &&
            ( DL == 0) && (DM == 1) && (DR == 1)) {
        gameMap[index][indey] = 22;
    }

    // 23
    if     (( UL == 0) && (UM == 1) && (UR == 0) &&
            ( ML == 1) && (MM == 1) && (MR == 1) &&
            ( DL == 0) && (DM == 1) && (DR == 1)) {
        gameMap[index][indey] = 23;
    }

    // 24
    if     (( UL == 1) && (UM == 1) && (UR == 1) &&
            ( ML == 1) && (MM == 1) && (MR == 1) &&
            ( DL == 0) && (DM == 1) && (DR == 0)) {
        gameMap[index][indey] = 24;
    }

    // 25
    if     (( UL == 0) && (UM == 1) && (UR == 1) &&
            ( ML == 1) && (MM == 1) && (MR == 1) &&
            ( DL == 0) && (DM == 1) && (DR == 0)) {
        gameMap[index][indey] = 25;
    }

    // 26
    if     (( UL == 1) && (UM == 1) && (UR == 0) &&
            ( ML == 1) && (MM == 1) && (MR == 1) &&
            ( DL == 0) && (DM == 1) && (DR == 0)) {
        gameMap[index][indey] = 26;
    }

    // 27
    if     (( UL == 0) && (UM == 1) && (UR == 0) &&
            ( ML == 1) && (MM == 1) && (MR == 1) &&
            ( DL == 0) && (DM == 1) && (DR == 0)) {
        gameMap[index][indey] = 27;
    }

    // 28
    if     (( UL == UL) && (UM == 1) && (UR == 1) &&
            ( ML == 0) && (MM == 1) && (MR == 1) &&
            ( DL == DL) && (DM == 1) && (DR == 1)) {
        gameMap[index][indey] = 28;
    }

    // 29
    if     (( UL == UL) && (UM == 1) && (UR == 0) &&
            ( ML == 0) && (MM == 1) && (MR == 1) &&
            ( DL == DL) && (DM == 1) && (DR == 1)) {
        gameMap[index][indey] = 29;
    }

    // 30
    if     (( UL == UL) && (UM == 1) && (UR == 1) &&
            ( ML == 0) && (MM == 1) && (MR == 1) &&
            ( DL == DL) && (DM == 1) && (DR == 0)) {
        gameMap[index][indey] = 30;
    }

    // 31
    if     (( UL == UL) && (UM == 1) && (UR == 0) &&
            ( ML == 0) && (MM == 1) && (MR == 1) &&
            ( DL == DL) && (DM == 1) && (DR == 0)) {
        gameMap[index][indey] = 31;
    }

    // 32
    if     (( UL == UL) && (UM == 0) && (UR == UR) &&
            ( ML == 1) && (MM == 1) && (MR == 1) &&
            ( DL == 1) && (DM == 1) && (DR == 1)) {
        gameMap[index][indey] = 32;
    }

    // 33
    if     (( UL == UL) && (UM == 0) && (UR == UR) &&
            ( ML == 1) && (MM == 1) && (MR == 1) &&
            ( DL == 1) && (DM == 1) && (DR == 0)) {
        gameMap[index][indey] = 33;
    }

    // 34
    if     (( UL == UL) && (UM == 0) && (UR == UR) &&
            ( ML == 1) && (MM == 1) && (MR == 1) &&
            ( DL == 0) && (DM == 1) && (DR == 1)) {
        gameMap[index][indey] = 34;
    }

    // 35
    if     (( UL == UL) && (UM == 0) && (UR == UR) &&
            ( ML == 1) && (MM == 1) && (MR == 1) &&
            ( DL == 0) && (DM == 1) && (DR == 0)) {
        gameMap[index][indey] = 35;
    }

    // 36
    if     (( UL == 1) && (UM == 1) && (UR == UR) &&
            ( ML == 1) && (MM == 1) && (MR == 0) &&
            ( DL == 1) && (DM == 1) && (DR == DR)) {
        gameMap[index][indey] = 36;
    }

    // 37
    if     (( UL == 1) && (UM == 1) && (UR == UR) &&
            ( ML == 1) && (MM == 1) && (MR == 0) &&
            ( DL == 0) && (DM == 1) && (DR == DR)) {
        gameMap[index][indey] = 37;
    }

    // 38
    if     (( UL == 0) && (UM == 1) && (UR == UR) &&
            ( ML == 1) && (MM == 1) && (MR == 0) &&
            ( DL == 1) && (DM == 1) && (DR == DR)) {
        gameMap[index][indey] = 38;
    }

    // 39
    if     (( UL == 0) && (UM == 1) && (UR == UR) &&
            ( ML == 1) && (MM == 1) && (MR == 0) &&
            ( DL == 0) && (DM == 1) && (DR == DR)) {
        gameMap[index][indey] = 39;
    }

    // 40
    if     (( UL == 1) && (UM == 1) && (UR == 1) &&
            ( ML == 1) && (MM == 1) && (MR == 1) &&
            ( DL == DL) && (DM == 0) && (DR == DR)) {
        gameMap[index][indey] = 40;
        gameMap[index + 1][indey] = 54 - (qrand() % 4);
    }

    // 41
    if     (( UL == 0) && (UM == 1) && (UR == 1) &&
            ( ML == 1) && (MM == 1) && (MR == 1) &&
            ( DL == DL) && (DM == 0) && (DR == DR)) {
        gameMap[index][indey] = 41;
        gameMap[index + 1][indey] = 54 - (qrand() % 4);
    }

    // 42
    if     (( UL == 1) && (UM == 1) && (UR == 0) &&
            ( ML == 1) && (MM == 1) && (MR == 1) &&
            ( DL == DL) && (DM == 0) && (DR == DR)) {
        gameMap[index][indey] = 42;
        gameMap[index + 1][indey] = 54 - (qrand() % 4);
    }

    // 43
    if     (( UL == 0) && (UM == 1) && (UR == 0) &&
            ( ML == 1) && (MM == 1) && (MR == 1) &&
            ( DL == DL) && (DM == 0) && (DR == DR)) {
        gameMap[index][indey] = 43;
        gameMap[index + 1][indey] = 54 - (qrand() % 4);
    }

    // 44
    if     (( UL == UL) && (UM == 1) && (UR == UR) &&
            ( ML == 0) && (MM == 1) && (MR == 0) &&
            ( DL == DL) && (DM == 1) && (DR == DR)) {
        gameMap[index][indey] = 44;
    }

    // 45
    if     (( UL == UL) && (UM == 0) && (UR == UR) &&
            ( ML == 1) && (MM == 1) && (MR == 1) &&
            ( DL == DL) && (DM == 0) && (DR == DR)) {
        gameMap[index][indey] = 45;
        gameMap[index + 1][indey] = 54 - (qrand() % 4);
    }

    // 46
    if     (( UL == UL) && (UM == 0) && (UR == UR) &&
            ( ML == 0) && (MM == 1) && (MR == 1) &&
            ( DL == DL) && (DM == 1) && (DR == 1)) {
        gameMap[index][indey] = 46;
    }

    // 47
    if     (( UL == UL) && (UM == 0) && (UR == UR) &&
            ( ML == 0) && (MM == 1) && (MR == 1) &&
            ( DL == DL) && (DM == 1) && (DR == 0)) {
        gameMap[index][indey] = 47;
    }
}
