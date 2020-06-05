#ifndef GAMEUNIT_H
#define GAMEUNIT_H

#define UL gameColMap[index-1][indey-1]
#define UM gameColMap[index-1][indey]
#define UR gameColMap[index-1][indey+1]
#define ML gameColMap[index][indey-1]
#define MM gameColMap[index][indey]
#define MR gameColMap[index][indey+1]
#define DL gameColMap[index+1][indey-1]
#define DM gameColMap[index+1][indey]
#define DR gameColMap[index+1][indey+1]
#define ER 1
#define elif else if


#include <QWidget>
#include <QPaintEvent>
#include <QVector>
#include <QKeyEvent>
#include <QImage>
#include <QPainter>
#include <QDebug>
#include <QString>
#include <QTime>
#include <QIcon>
#include <QRandomGenerator>

using ull = unsigned long long;

static const int PONUNIT = 64;

class GameUnit : public QWidget
{
    Q_OBJECT
public:
    explicit GameUnit(QWidget *parent = nullptr);

    /* Массивчич колизий* игры
     * В колизии входят:
     * 1) Стены - (1);
     * 2) Сундуки - (2);
     * 3) Нууу и пол.. - (0);
     */
    QVector<QVector<int>> gameColMap = {
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,1,0,1,0,1,0,1,0,0,1,0,0,0,0,1,1,0,0,0,1,1},
        {1,1,0,1,0,0,0,0,0,0,0,1,1,0,0,0,0,0,1,0,1,1},
        {1,1,0,1,0,1,0,1,0,1,0,0,0,0,1,1,1,1,1,0,1,1},
        {1,1,0,1,1,1,0,1,0,1,0,1,0,0,0,0,0,0,0,0,1,1},
        {1,1,0,1,0,1,0,1,0,1,0,1,0,1,1,1,0,1,1,1,1,1},
        {1,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
        {1,1,1,0,1,1,0,1,0,1,1,1,0,1,0,1,1,1,1,0,1,1},
        {1,1,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    };


    // Массивчич идентификаторов спрайтов.
    // Он строится относительно Массивича колизий.
    QVector<QVector<int>> gameMap = {
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
    };

private:

    /* Массив спрайтов
       Просто массив для хранениения текстурок карты */
    QImage imageWallmass[60];

    /* Картинки для анимации движений */
    QImage imageUp[12];    // Вверх
    QImage imageDown[12];  // Вниз
    QImage imageLeft[8];   // Влево
    QImage imageRight[8];  // Вправо


    /* Координаты и направление движения игрока */
    int playerX;           // Координата персонажа по Х
    int playerY;           // Координата персонажа по Y
    QString direction;     // Напавление движения персонажа
    int current_picture;   // Текущая картинка для отображения анимации

    /* Служебные переменные для игрового процесса */
    int timerId;           // Нужен для запуска таймера
    const int DELAY = 17;  // Задержка частоты обновления игрового экрана
    int chestsRemain;      // Сколько сундуков осталось на поле


    /* Событие обработчик значений с клавиатуры */
    void keyPressEvent(QKeyEvent *event);

    /* Функция отрисовки камеры.(Насколько я понял, эта херня нужна,
       чтобы можно было обрабатывать то что на виджете рисуется что - то) */
    void paintEvent(QPaintEvent *pEvent);

    /* Функция загрузки текстур в массив картинок */
    void loadTexture();

    /* Функция, инициализирующая игру */
    void initGame();

    /* Таймер, нужный для формирования игрового цикла */
    void timerEvent(QTimerEvent *e);

    /* Функция, расставляющая сундуки на карте */
    void setChests();

    /* Функция отрисовки карты */
    void doDrawWall();

    /* Функция отрисовки пола */
    void doDrawFloor();

    /* Функция отрисовки боковых стен */
    void doDrawSideWall();

    /* Функция отрисовки сундуков */
    void doDrawChest();

    /* Функция сама отрисовывающая карту */
    void doTextures();

    /* Функция отрисовки персонажа */
    void doDrawPlayer();

    /* Функция проверки вероятных расположений */
    void ifElse(int index, int indey);

    /* Функция проверки на коллизию со стеной */
    bool noCollision(int x, int y, QString direction);

    /* Функция проверки сундука в данной клетке 64х64 */
    bool hereChest(int x, int y);

    /* Функция показа текста завершения игры */
    void doDrawEndText();
};

#endif // GAMEUNIT_H
