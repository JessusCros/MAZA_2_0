#include "gameunit.h"

GameUnit::GameUnit(QWidget *parent) : QWidget(parent) {

    // Аы сделал бекграунд черным.
    setStyleSheet("background-color:black;");

    // Аы поставил минимальное разрешение.
    setMinimumSize(1280,640);


    // ну чисто загрузил текстуры.
    loadTexture();

    //Отрисовал..... Появились сомнения насчет работы этой функции.....
    doDraw();
}


// Обработчик клавиатуры.
void GameUnit::keyPressEvent(QKeyEvent *event) {\

    // Обработка выхода из приложения.
    if (event->key() == Qt::Key_Escape) {
        close();
    }

    // Обработка смены режима экрана.
    if (event->key() == Qt::Key_F11) {
        if(fullScreenPointer) {
            setWindowState(Qt::WindowFullScreen);
            fullScreenPointer = !fullScreenPointer;
        } else {
            setWindowState(Qt::WindowNoState);
            fullScreenPointer = !fullScreenPointer;
        }
    }

    // Место где Диса будет ставить перемещение персонажа.
    // .........................................................................................................

    // что-то написал для проверки работы гитаa

}

// Функция обработки событи рисования на виджете.
void GameUnit::paintEvent(QPaintEvent *pEvent) {
    Q_UNUSED(pEvent);

    doDraw();
}

// Функция предзагрузки текстур.
void GameUnit::loadTexture() {

    // Забиваем текстуры до 99, т.к в шаблоне стоит 0, а всем менять имя не хочу.
    for (int i = 64;i <= 99; ++i) {
        imageWallmass[i - 64].load(":/UpWalls/tile0" + QString::number(i));
    }

    // Забиваем текстуры после 99.
    for (int i = 100;i <= 117; ++i) {
        imageWallmass[i - 64].load(":/UpWalls/tile" + QString::number(i));
    }

}

//Функция рисования карты.
void GameUnit::doDraw() {

    // Объект на котором мы рисуем то, что мы рисуем.(после он отображается на основном виджете)
    QPainter gamePaint(this);

    // Индексы для пробега по карте прорисовки.
    int indexX;
    int indexY;

    // Сначала рисеум пол, чтобы потом он был на заднем плане.
    for (indexX = 0;indexX < gameMap.size(); ++indexX) {
        for (indexY = 0;indexY < gameMap[indexX].size(); ++indexY) {
            gamePaint.drawImage(indexY * PONUNIT, indexX * PONUNIT, imageWallmass[49 - (qrand() % 3)]);
        }
    }

    // Место где Диса будет рисовать персонажа................................................................

    // Далее рисуем стенки.....
    for (indexX = 0;indexX < gameMap.size(); ++indexX) {
        for (indexY = 0;indexY < gameMap[indexX].size(); ++indexY) {
            if(gameMap[indexX][indexY] != 0) {
                gamePaint.drawImage(indexY * PONUNIT, indexX * PONUNIT, imageWallmass[gameMap[indexX][indexY]]);
            }
        }
    }
}

