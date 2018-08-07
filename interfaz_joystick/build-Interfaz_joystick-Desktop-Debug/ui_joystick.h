/********************************************************************************
** Form generated from reading UI file 'joystick.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_JOYSTICK_H
#define UI_JOYSTICK_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Joystick
{
public:
    QWidget *centralWidget;
    QLabel *label;
    QLabel *b_1;
    QLabel *b_2;
    QLabel *b_A;
    QLabel *b_B;
    QLabel *b_Y;
    QLabel *b_X;
    QLabel *d_pad;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *Joystick)
    {
        if (Joystick->objectName().isEmpty())
            Joystick->setObjectName(QString::fromUtf8("Joystick"));
        Joystick->resize(614, 435);
        centralWidget = new QWidget(Joystick);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(0, -20, 631, 441));
        label->setPixmap(QPixmap(QString::fromUtf8(":/iconos/fondo.jpg")));
        b_1 = new QLabel(centralWidget);
        b_1->setObjectName(QString::fromUtf8("b_1"));
        b_1->setGeometry(QRect(180, 270, 91, 91));
        b_1->setPixmap(QPixmap(QString::fromUtf8(":/iconos/WiiU_1.png")));
        b_1->setScaledContents(true);
        b_2 = new QLabel(centralWidget);
        b_2->setObjectName(QString::fromUtf8("b_2"));
        b_2->setGeometry(QRect(290, 270, 91, 91));
        b_2->setPixmap(QPixmap(QString::fromUtf8(":/iconos/WiiU_2.png")));
        b_2->setScaledContents(true);
        b_A = new QLabel(centralWidget);
        b_A->setObjectName(QString::fromUtf8("b_A"));
        b_A->setGeometry(QRect(460, 220, 91, 91));
        b_A->setPixmap(QPixmap(QString::fromUtf8(":/iconos/WiiU_A.png")));
        b_A->setScaledContents(true);
        b_B = new QLabel(centralWidget);
        b_B->setObjectName(QString::fromUtf8("b_B"));
        b_B->setGeometry(QRect(520, 160, 91, 91));
        b_B->setPixmap(QPixmap(QString::fromUtf8(":/iconos/WiiU_B.png")));
        b_B->setScaledContents(true);
        b_Y = new QLabel(centralWidget);
        b_Y->setObjectName(QString::fromUtf8("b_Y"));
        b_Y->setGeometry(QRect(460, 100, 91, 91));
        b_Y->setPixmap(QPixmap(QString::fromUtf8(":/iconos/WiiU_Y.png")));
        b_Y->setScaledContents(true);
        b_X = new QLabel(centralWidget);
        b_X->setObjectName(QString::fromUtf8("b_X"));
        b_X->setGeometry(QRect(400, 160, 91, 91));
        b_X->setPixmap(QPixmap(QString::fromUtf8(":/iconos/WiiU_X.png")));
        b_X->setScaledContents(true);
        d_pad = new QLabel(centralWidget);
        d_pad->setObjectName(QString::fromUtf8("d_pad"));
        d_pad->setGeometry(QRect(10, 130, 181, 171));
        d_pad->setPixmap(QPixmap(QString::fromUtf8(":/iconos/centro.png")));
        d_pad->setScaledContents(true);
        Joystick->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(Joystick);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 614, 27));
        Joystick->setMenuBar(menuBar);
        mainToolBar = new QToolBar(Joystick);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        Joystick->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(Joystick);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        Joystick->setStatusBar(statusBar);

        retranslateUi(Joystick);

        QMetaObject::connectSlotsByName(Joystick);
    } // setupUi

    void retranslateUi(QMainWindow *Joystick)
    {
        Joystick->setWindowTitle(QApplication::translate("Joystick", "Joystick", 0, QApplication::UnicodeUTF8));
        label->setText(QString());
        b_1->setText(QString());
        b_2->setText(QString());
        b_A->setText(QString());
        b_B->setText(QString());
        b_Y->setText(QString());
        b_X->setText(QString());
        d_pad->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class Joystick: public Ui_Joystick {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_JOYSTICK_H
