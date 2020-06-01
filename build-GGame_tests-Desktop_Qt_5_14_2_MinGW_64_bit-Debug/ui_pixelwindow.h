/********************************************************************************
** Form generated from reading UI file 'pixelwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PIXELWINDOW_H
#define UI_PIXELWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_pixelWindow
{
public:
    QAction *actionExit;
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QGraphicsView *graphicsView;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *pixelWindow)
    {
        if (pixelWindow->objectName().isEmpty())
            pixelWindow->setObjectName(QString::fromUtf8("pixelWindow"));
        pixelWindow->resize(360, 251);
        actionExit = new QAction(pixelWindow);
        actionExit->setObjectName(QString::fromUtf8("actionExit"));
        centralwidget = new QWidget(pixelWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        graphicsView = new QGraphicsView(centralwidget);
        graphicsView->setObjectName(QString::fromUtf8("graphicsView"));

        verticalLayout->addWidget(graphicsView);

        pixelWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(pixelWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 360, 21));
        pixelWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(pixelWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        pixelWindow->setStatusBar(statusbar);

        retranslateUi(pixelWindow);
        QObject::connect(actionExit, SIGNAL(triggered()), pixelWindow, SLOT(close()));

        QMetaObject::connectSlotsByName(pixelWindow);
    } // setupUi

    void retranslateUi(QMainWindow *pixelWindow)
    {
        pixelWindow->setWindowTitle(QCoreApplication::translate("pixelWindow", "GGGame", nullptr));
        actionExit->setText(QCoreApplication::translate("pixelWindow", "Exit", nullptr));
    } // retranslateUi

};

namespace Ui {
    class pixelWindow: public Ui_pixelWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PIXELWINDOW_H
