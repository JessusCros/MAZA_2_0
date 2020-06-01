#include "pixelwindow.h"
#include "ui_pixelwindow.h"
#include <QDebug>
#include <QRegion>

pixelWindow::pixelWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::pixelWindow) {
    ui->setupUi(this);

    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);

    QPalette pal;
    pal.setColor(QPalette::Background, Qt::black);

    this->setAutoFillBackground(true);
    this->setPalette(pal);


    QBrush blueBrush(Qt::blue);
    QPen blackPen(Qt::black);
    blackPen.setWidth(2);

    int index;
    int indey;

    // Draw Map.
    for(index = 0; index < (int)gameMap.size(); ++index) {
        for(indey = 0; indey < (int)gameMap[index].size(); ++indey) {
            if (gameMap[index][indey] == 1)
                scene->addRect(indey * PGINT,index * PGINT,PGINT,PGINT,blackPen,blueBrush);
        }
    }
}

pixelWindow::~pixelWindow() {
    delete ui;
    delete scene;
}

void pixelWindow::keyPressEvent(QKeyEvent *event) {
    if(event->key() == Qt::Key_Escape) {
     this->close();
    }
}

