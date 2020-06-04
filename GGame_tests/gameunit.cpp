#include "gameunit.h"

GameUnit::GameUnit(QWidget *parent) : QWidget(parent) {

    // Установили название виджета.
    setWindowTitle("Chest Hunter");

    // Установли иконку.......Аы.
    setWindowIcon(QIcon(":/Icon/Chest"));

    // Аы сделал бекграунд черным.
    setStyleSheet("background-color:black;");

    // Аы поставил минимальное разрешение.
    setMinimumSize(1280,640);

    // Аы поставил минимальное разрешение.
    setMaximumSize(1280,640);

    // ну чисто загрузил текстуры.
    loadTexture();

    doTextures();

    initGame();
}

void GameUnit::initGame()
{
    inGame = true;

    /* Инициализируем персонажа */
    playerX = 9*64 + 18;
    playerY = 5*64;

    direction = "L";
    current_picture = 0;

    chestsRemain = 0;
    setChests();

    timerId = startTimer(DELAY);
}

// Функция обработки события рисования на виджете.
void GameUnit::paintEvent(QPaintEvent *pEvent) {
    Q_UNUSED(pEvent);

    doDrawFloor();

    doDrawChest();

    doDrawPlayer();

    doDrawWall();
}

// Функция предзагрузки текстур.
void GameUnit::loadTexture() {

    // Забиваем текстуры.
    for (int i = 1; i <= 55; ++i) {
        imageWallmass[i].load(":/UpWalls/tile" + QString::number(i));
    }

    // Загружаем картинки для анимации движения вверх
    for (int i = 0; i <= 11; i++)
        imageUp[i].load(":/Character/Up/" + QString::number(i));

    // Загружаем картинки для анимации движения вниз
    for (int i = 0; i <= 11; i++)
        imageDown[i].load(":/Character/Down/" + QString::number(i));

    // Загружаем картинки для анимации движения влево
    for (int i = 0; i <= 7; i++)
        imageLeft[i].load(":/Character/Left/" + QString::number(i));

    // Загружаем картинки для анимации движения вправо
    for (int i = 0; i <= 7; i++)
        imageRight[i].load(":/Character/Right/" + QString::number(i));
}

void GameUnit::timerEvent(QTimerEvent *e)
{

    Q_UNUSED(e);

    if (chestsRemain == 0)
        close();

    repaint();
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
            if (gameMap[indexX][indexY] >= 48 && gameMap[indexX][indexY] <= 55) {
                gamePaint.drawImage((indexY-1) * PONUNIT, (indexX-1) * PONUNIT, imageWallmass[gameMap[indexX][indexY]]);
            }
        }
    }
}

// Функция отрисовки сундука.
void GameUnit::doDrawChest() {

    // Объект на котором мы рисуем то, что мы рисуем.(после он отображается на основном виджете)
    QPainter gamePaint(this);

    // Индексы для пробега по карте прорисовки.
    int indexX;
    int indexY;

    // Рисуем пол.
    for (indexX = 1; indexX < gameColMap.size()-1; ++indexX) {
        for (indexY = 1; indexY < gameColMap[indexX].size()-1; ++indexY) {
            if (gameColMap[indexX][indexY] == 2) {
                gamePaint.drawImage((indexY-1) * PONUNIT + 18, (indexX-1) * PONUNIT + 45, imageWallmass[55]);
            }
        }
    }
}

// Функция рисования стен.
void GameUnit::doDrawSideWall() {

    // Объект на котором мы рисуем то, что мы рисуем.(после он отображается на основном виджете)
    QPainter gamePaint(this);

    // Индексы для пробега по карте прорисовки.
    int indexX;
    int indexY;

    // Далее рисуем стенки.....
    for (indexX = 1; indexX < gameMap.size()-1; ++indexX) {
        for (indexY = 1; indexY < gameMap[indexX].size()-1; ++indexY) {
            if (gameMap[indexX][indexY] != 0 && gameMap[indexX][indexY] > 50) {
                gamePaint.drawImage((indexY-1) * PONUNIT, (indexX-1) * PONUNIT, imageWallmass[gameMap[indexX][indexY]]);
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
            if (gameMap[indexX][indexY] != 0 && gameMap[indexX][indexY] < 48) {
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

// Функция отрисовки персонажа
void GameUnit::doDrawPlayer()
{
    QPainter gamePaint (this);

    const int add = 28;

    if (direction == "U")
    {
        //qDebug() << direction << current_picture;
        gamePaint.drawImage(playerX, playerY + add, imageUp[current_picture]);
    }
    else if (direction == "D")
    {
        //qDebug() << direction << current_picture;
        gamePaint.drawImage(playerX, playerY + add, imageDown[current_picture]);
    }
    else if (direction == "L")
    {
        //qDebug() << direction << current_picture;
        gamePaint.drawImage(playerX, playerY + add, imageLeft[current_picture]);
    }
    else if (direction == "R")
    {
        //qDebug() << direction << current_picture;
        gamePaint.drawImage(playerX, playerY + add, imageRight[current_picture]);
    }
}

// Функция обработки положения стен.
// ВНИМАНИЕ. Не для слабонервных.
void GameUnit::ifElse(int index, int indey) {


    // floor
    if     (( UL == UL) && (UM != 1) && (UR == UR) &&
            ( ML == ML) && (MM != 1) && (MR == MR) &&
            ( DL == DL) && (DM == DM) && (DR == DR)) {
        gameMap[index][indey] = 50  - (qrand() % 3);
    }

    // 1
    if     (( UL == 1) && (UM == 1) && (UR == 1) &&
            ( ML == 1) && (MM == 1) && (MR == 1) &&
            ( DL == 1) && (DM == 1) && (DR == 1)) {
        gameMap[index][indey] = 1;
    }

    // 2
    if     (( UL == UL) && (UM != 1) && (UR == UR) &&
            ( ML == 1) && (MM == 1) && (MR != 1) &&
            ( DL == 1) && (DM == 1) && (DR == DR)) {
        gameMap[index][indey] = 2;
    }

    // 3
    if     (( UL == UL) && (UM != 1) && (UR == UR) &&
            ( ML == 1) && (MM == 1) && (MR != 1) &&
            ( DL != 1) && (DM == 1) && (DR == DR)) {
        gameMap[index][indey] = 3;
    }

    // 4
    if     (( UL == 1) && (UM == 1) && (UR == UR) &&
            ( ML == 1) && (MM == 1) && (MR != 1) &&
            ( DL == DL) && (DM != 1) && (DR == DR)) {
        gameMap[index][indey] = 4;
        gameMap[index + 1][indey] = 54 - (qrand() % 4);
    }

    // 5
    if     (( UL != 1) && (UM == 1) && (UR == UR) &&
            ( ML == 1) && (MM == 1) && (MR != 1) &&
            ( DL == DL) && (DM != 1) && (DR == DR)) {
        gameMap[index][indey] = 5;
        gameMap[index + 1][indey] = 54 - (qrand() % 4);
    }


    // 6
    if     (( UL == UL) && (UM == 1) && (UR == 1) &&
            ( ML != 1) && (MM == 1) && (MR == 1) &&
            ( DL == DL) && (DM != 1) && (DR == DR)) {
        gameMap[index][indey] = 6;
        gameMap[index + 1][indey] = 54 - (qrand() % 4);
    }

    // 7
    if     (( UL == UL) && (UM == 1) && (UR != 1) &&
            ( ML != 1) && (MM == 1) && (MR == 1) &&
            ( DL == DL) && (DM != 1) && (DR == DR)) {
        gameMap[index][indey] = 7;
        gameMap[index + 1][indey] = 54 - (qrand() % 4);
    }

    // 8
    if     (( UL == UL) && (UM != 1) && (UR == UR) &&
            ( ML != 1) && (MM == 1) && (MR != 1) &&
            ( DL == DL) && (DM == 1) && (DR == DR)) {
        gameMap[index][indey] = 8;
    }

    // 9
    if     (( UL == UL) && (UM != 1) && (UR == UR) &&
            ( ML != 1) && (MM == 1) && (MR == 1) &&
            ( DL == DL) && (DM != 1) && (DR == DR)) {
        gameMap[index][indey] = 9;
        gameMap[index + 1][indey] = 54 - (qrand() % 4);
    }

    // 10
    if     (( UL == UL) && (UM == 1) && (UR == UR) &&
            ( ML != 1) && (MM == 1) && (MR != 1) &&
            ( DL == DL) && (DM != 1) && (DR == DR)) {
        gameMap[index][indey] = 10;
        gameMap[index + 1][indey] = 54 - (qrand() % 4);
    }

    // 11
    if     (( UL == UL) && (UM != 1) && (UR == UR) &&
            ( ML == 1) && (MM == 1) && (MR != 1) &&
            ( DL == DL) && (DM != 1) && (DR == DR)) {
        gameMap[index][indey] = 11;
        gameMap[index + 1][indey] = 54 - (qrand() % 4);
    }

    // 12
    if     (( UL == UL) && (UM != 1) && (UR == UR) &&
            ( ML != 1) && (MM == 1) && (MR != 1) &&
            ( DL == DL) && (DM != 1) && (DR == DR)) {
        gameMap[index][indey] = 12;
        gameMap[index + 1][indey] = 54 - (qrand() % 4);
    }

    // 13
    if     (( UL != 1) && (UM == 1) && (UR == 1) &&
            ( ML == 1) && (MM == 1) && (MR == 1) &&
            ( DL == 1) && (DM == 1) && (DR == 1)) {
        gameMap[index][indey] = 13;
    }

    // 14
    if     (( UL == 1) && (UM == 1) && (UR != 1) &&
            ( ML == 1) && (MM == 1) && (MR == 1) &&
            ( DL == 1) && (DM == 1) && (DR == 1)) {
        gameMap[index][indey] = 14;
    }

    // 15
    if     (( UL != 1) && (UM == 1) && (UR != 1) &&
            ( ML == 1) && (MM == 1) && (MR == 1) &&
            ( DL == 1) && (DM == 1) && (DR == 1)) {
        gameMap[index][indey] = 15;
    }

    // 16
    if     (( UL == 1) && (UM == 1) && (UR == 1) &&
            ( ML == 1) && (MM == 1) && (MR == 1) &&
            ( DL == 1) && (DM == 1) && (DR != 1)) {
        gameMap[index][indey] = 16;
    }

    // 17
    if     (( UL != 1) && (UM == 1) && (UR == 1) &&
            ( ML == 1) && (MM == 1) && (MR == 1) &&
            ( DL == 1) && (DM == 1) && (DR != 1)) {
        gameMap[index][indey] = 17;
    }

    // 18
    if     (( UL == 1) && (UM == 1) && (UR != 1) &&
            ( ML == 1) && (MM == 1) && (MR == 1) &&
            ( DL == 1) && (DM == 1) && (DR != 1)) {
        gameMap[index][indey] = 18;
    }

    // 19
    if     (( UL != 1) && (UM == 1) && (UR != 1) &&
            ( ML == 1) && (MM == 1) && (MR == 1) &&
            ( DL == 1) && (DM == 1) && (DR != 1)) {
        gameMap[index][indey] = 19;
    }

    // 20
    if     (( UL == 1) && (UM == 1) && (UR == 1) &&
            ( ML == 1) && (MM == 1) && (MR == 1) &&
            ( DL != 1) && (DM == 1) && (DR == 1)) {
        gameMap[index][indey] = 20;
    }

    // 21
    if     (( UL != 1) && (UM == 1) && (UR == 1) &&
            ( ML == 1) && (MM == 1) && (MR == 1) &&
            ( DL != 1) && (DM == 1) && (DR == 1)) {
        gameMap[index][indey] = 21;
    }

    // 22
    if     (( UL == 1) && (UM == 1) && (UR != 1) &&
            ( ML == 1) && (MM == 1) && (MR == 1) &&
            ( DL != 1) && (DM == 1) && (DR == 1)) {
        gameMap[index][indey] = 22;
    }

    // 23
    if     (( UL != 1) && (UM == 1) && (UR != 1) &&
            ( ML == 1) && (MM == 1) && (MR == 1) &&
            ( DL != 1) && (DM == 1) && (DR == 1)) {
        gameMap[index][indey] = 23;
    }

    // 24
    if     (( UL == 1) && (UM == 1) && (UR == 1) &&
            ( ML == 1) && (MM == 1) && (MR == 1) &&
            ( DL != 1) && (DM == 1) && (DR != 1)) {
        gameMap[index][indey] = 24;
    }

    // 25
    if     (( UL != 1) && (UM == 1) && (UR == 1) &&
            ( ML == 1) && (MM == 1) && (MR == 1) &&
            ( DL != 1) && (DM == 1) && (DR != 1)) {
        gameMap[index][indey] = 25;
    }

    // 26
    if     (( UL == 1) && (UM == 1) && (UR != 1) &&
            ( ML == 1) && (MM == 1) && (MR == 1) &&
            ( DL != 1) && (DM == 1) && (DR != 1)) {
        gameMap[index][indey] = 26;
    }

    // 27
    if     (( UL != 1) && (UM == 1) && (UR != 1) &&
            ( ML == 1) && (MM == 1) && (MR == 1) &&
            ( DL != 1) && (DM == 1) && (DR != 1)) {
        gameMap[index][indey] = 27;
    }

    // 28
    if     (( UL == UL) && (UM == 1) && (UR == 1) &&
            ( ML != 1) && (MM == 1) && (MR == 1) &&
            ( DL == DL) && (DM == 1) && (DR == 1)) {
        gameMap[index][indey] = 28;
    }

    // 29
    if     (( UL == UL) && (UM == 1) && (UR != 1) &&
            ( ML != 1) && (MM == 1) && (MR == 1) &&
            ( DL == DL) && (DM == 1) && (DR == 1)) {
        gameMap[index][indey] = 29;
    }

    // 30
    if     (( UL == UL) && (UM == 1) && (UR == 1) &&
            ( ML != 1) && (MM == 1) && (MR == 1) &&
            ( DL == DL) && (DM == 1) && (DR != 1)) {
        gameMap[index][indey] = 30;
    }

    // 31
    if     (( UL == UL) && (UM == 1) && (UR != 1) &&
            ( ML != 1) && (MM == 1) && (MR == 1) &&
            ( DL == DL) && (DM == 1) && (DR != 1)) {
        gameMap[index][indey] = 31;
    }

    // 32
    if     (( UL == UL) && (UM != 1) && (UR == UR) &&
            ( ML == 1) && (MM == 1) && (MR == 1) &&
            ( DL == 1) && (DM == 1) && (DR == 1)) {
        gameMap[index][indey] = 32;
    }

    // 33
    if     (( UL == UL) && (UM != 1) && (UR == UR) &&
            ( ML == 1) && (MM == 1) && (MR == 1) &&
            ( DL == 1) && (DM == 1) && (DR != 1)) {
        gameMap[index][indey] = 33;
    }

    // 34
    if     (( UL == UL) && (UM != 1) && (UR == UR) &&
            ( ML == 1) && (MM == 1) && (MR == 1) &&
            ( DL != 1) && (DM == 1) && (DR == 1)) {
        gameMap[index][indey] = 34;
    }

    // 35
    if     (( UL == UL) && (UM != 1) && (UR == UR) &&
            ( ML == 1) && (MM == 1) && (MR == 1) &&
            ( DL != 1) && (DM == 1) && (DR != 1)) {
        gameMap[index][indey] = 35;
    }

    // 36
    if     (( UL == 1) && (UM == 1) && (UR == UR) &&
            ( ML == 1) && (MM == 1) && (MR != 1) &&
            ( DL == 1) && (DM == 1) && (DR == DR)) {
        gameMap[index][indey] = 36;
    }

    // 37
    if     (( UL == 1) && (UM == 1) && (UR == UR) &&
            ( ML == 1) && (MM == 1) && (MR != 1) &&
            ( DL != 1) && (DM == 1) && (DR == DR)) {
        gameMap[index][indey] = 37;
    }

    // 38
    if     (( UL != 1) && (UM == 1) && (UR == UR) &&
            ( ML == 1) && (MM == 1) && (MR != 1) &&
            ( DL == 1) && (DM == 1) && (DR == DR)) {
        gameMap[index][indey] = 38;
    }

    // 39
    if     (( UL != 1) && (UM == 1) && (UR == UR) &&
            ( ML == 1) && (MM == 1) && (MR != 1) &&
            ( DL != 1) && (DM == 1) && (DR == DR)) {
        gameMap[index][indey] = 39;
    }

    // 40
    if     (( UL == 1) && (UM == 1) && (UR == 1) &&
            ( ML == 1) && (MM == 1) && (MR == 1) &&
            ( DL == DL) && (DM != 1) && (DR == DR)) {
        gameMap[index][indey] = 40;
        gameMap[index + 1][indey] = 54 - (qrand() % 4);
    }

    // 41
    if     (( UL != 1) && (UM == 1) && (UR == 1) &&
            ( ML == 1) && (MM == 1) && (MR == 1) &&
            ( DL == DL) && (DM != 1) && (DR == DR)) {
        gameMap[index][indey] = 41;
        gameMap[index + 1][indey] = 54 - (qrand() % 4);
    }

    // 42
    if     (( UL == 1) && (UM == 1) && (UR != 1) &&
            ( ML == 1) && (MM == 1) && (MR == 1) &&
            ( DL == DL) && (DM != 1) && (DR == DR)) {
        gameMap[index][indey] = 42;
        gameMap[index + 1][indey] = 54 - (qrand() % 4);
    }

    // 43
    if     (( UL != 1) && (UM == 1) && (UR != 1) &&
            ( ML == 1) && (MM == 1) && (MR == 1) &&
            ( DL == DL) && (DM != 1) && (DR == DR)) {
        gameMap[index][indey] = 43;
        gameMap[index + 1][indey] = 54 - (qrand() % 4);
    }

    // 44
    if     (( UL == UL) && (UM == 1) && (UR == UR) &&
            ( ML != 1) && (MM == 1) && (MR != 1) &&
            ( DL == DL) && (DM == 1) && (DR == DR)) {
        gameMap[index][indey] = 44;
    }

    // 45
    if     (( UL == UL) && (UM != 1) && (UR == UR) &&
            ( ML == 1) && (MM == 1) && (MR == 1) &&
            ( DL == DL) && (DM != 1) && (DR == DR)) {
        gameMap[index][indey] = 45;
        gameMap[index + 1][indey] = 54 - (qrand() % 4);
    }

    // 46
    if     (( UL == UL) && (UM != 1) && (UR == UR) &&
            ( ML != 1) && (MM == 1) && (MR == 1) &&
            ( DL == DL) && (DM == 1) && (DR == 1)) {
        gameMap[index][indey] = 46;
    }

    // 47
    if     (( UL == UL) && (UM != 1) && (UR == UR) &&
            ( ML != 1) && (MM == 1) && (MR == 1) &&
            ( DL == DL) && (DM == 1) && (DR != 1)) {
        gameMap[index][indey] = 47;
    }
}

// Обработчик клавиатуры.
void GameUnit::keyPressEvent(QKeyEvent *event) {

    // Обработка выхода из приложения.
    if (event->key() == Qt::Key_Escape) {
        close();
    }

    // Если идём вверх
    if (event->key() == Qt::Key_W || event->key() == Qt::Key_Up)
    {
        direction = "U";
        // Проверяем коллизию
        if (noCollision(playerX, playerY, "U"))
            playerY -= 3;

        //qDebug() << playerY;
        (current_picture + 1 <= 11) ? current_picture += 1: current_picture = 0;
    }

    // Если идём вниз
    if (event->key() == Qt::Key_S || event->key() == Qt::Key_Down)
    {
        direction = "D";
        // Проверяем коллизию
        if (noCollision(playerX, playerY, "D"))
            playerY += 3;

        //qDebug() << playerY;
        (current_picture + 1 <= 11) ? current_picture += 1: current_picture = 0;
    }

    // Если идём влево
    if (event->key() == Qt::Key_A || event->key() == Qt::Key_Left)
    {
        direction = "L";
        // Проверяем коллизию
        if (noCollision(playerX, playerY, "L"))
            playerX -= 3;

        //qDebug() << playerX;
        (current_picture + 1 <= 7) ? current_picture += 1: current_picture = 0;
    }

    // Если идём вправо
    if (event->key() == Qt::Key_D || event->key() == Qt::Key_Right)
    {
        direction = "R";
        // Проверяем коллизию
        if (noCollision(playerX, playerY, "R"))
            playerX += 3;

        //qDebug() << playerX;
       (current_picture + 1 <= 7) ? current_picture += 1: current_picture = 0;
    }

    QWidget::keyPressEvent(event);
}

// Функция проверки на коллизию со стеной
bool GameUnit::noCollision(int x, int y, QString direction)
{
       if   (direction == "U" && gameColMap[(y-3)/64 + 1][(x+18)/64 + 1] == 1) //-40
    {
        return 0;
    }
    elif (direction == "D" && gameColMap[(y+3)/64 + 1][(x+18)/64 + 1] == 1)
    {
        return 0;
    }
    elif (direction == "L" && gameColMap[y/64 + 1][(x-3)/64 + 1] == 1)
    {
        return 0;
    }
    elif (direction == "R" && gameColMap[y/64 + 1][(x+33)/64 + 1] == 1) //+33
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

void GameUnit::setChests()
{
    while (chestsRemain != 5)
    {
        for (int i = 1; i <= gameColMap.size()-2; i++)
        {
            for (int j = 1; j <= gameColMap[i].size()-2; j++)
            {
                if (gameColMap[i][j] != 0)
                    continue;

                if (chestsRemain == 5)
                    break;

                std::uniform_int_distribution <int> distribution(0, 10000);
                int r = distribution(*QRandomGenerator::global());
                qDebug() << r;

                if (r >= 9500)
                {
                    chestsRemain++;
                    gameColMap[i][j] = 2;

                }
            }
        }
    }
}
