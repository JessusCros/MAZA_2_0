#include "gameunit.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    GameUnit ggame;

    ggame.show();

    return a.exec();
}
