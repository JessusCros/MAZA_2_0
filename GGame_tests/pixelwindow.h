#ifndef PIXELWINDOW_H
#define PIXELWINDOW_H

#define PGINT 64
#define POLIGONCONSTMAX_X 1280
#define POLIGONCONSTMAX_Y 640

#include <QMainWindow>
#include <QKeyEvent>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsEllipseItem>
#include <QImage>
#include <QPalette>
#include <vector>

QT_BEGIN_NAMESPACE
namespace Ui { class pixelWindow; }
QT_END_NAMESPACE

class pixelWindow : public QMainWindow {
    Q_OBJECT

public:
    pixelWindow(QWidget *parent = nullptr);
    ~pixelWindow();
protected:
    QGraphicsScene* scene;
    QGraphicsRectItem* rectangel;

    std::vector<std::vector<int>> gameMap = {
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,0,1,0,0,0,0,1,0,0,0,0,1,0,1,1,1,1,1,1},
        {1,0,1,0,1,1,0,1,0,1,1,0,1,0,1,1,0,1,0,1},
        {1,0,1,0,0,0,0,0,0,1,0,0,1,0,0,1,0,1,0,1},
        {1,0,1,1,1,0,1,1,0,0,0,1,1,0,0,0,0,0,0,1},
        {1,0,1,0,0,0,0,1,1,1,0,1,1,0,1,1,1,0,1,1},
        {1,0,0,0,1,1,0,1,0,1,0,0,0,0,0,0,0,0,0,1},
        {1,0,1,0,0,0,0,1,0,1,0,1,1,1,1,0,0,1,0,1},
        {1,0,1,1,1,1,1,1,0,1,0,1,1,0,1,1,1,0,0,1},
        {1,0,0,0,0,0,0,0,0,1,0,1,1,0,0,0,0,0,1,1},
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
    };

    void keyPressEvent(QKeyEvent *event);
private:
    Ui::pixelWindow *ui;
};

#endif // PIXELWINDOW_H
