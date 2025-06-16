/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionautomatic;
    QAction *actionmanually_add;
    QWidget *centralwidget;
    QMenuBar *menubar;
    QMenu *menuHelldivers_Campaign_Updates;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 600);
        actionautomatic = new QAction(MainWindow);
        actionautomatic->setObjectName("actionautomatic");
        actionmanually_add = new QAction(MainWindow);
        actionmanually_add->setObjectName("actionmanually_add");
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 21));
        menuHelldivers_Campaign_Updates = new QMenu(menubar);
        menuHelldivers_Campaign_Updates->setObjectName("menuHelldivers_Campaign_Updates");
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menuHelldivers_Campaign_Updates->menuAction());
        menuHelldivers_Campaign_Updates->addAction(actionautomatic);
        menuHelldivers_Campaign_Updates->addAction(actionmanually_add);
        menuHelldivers_Campaign_Updates->addSeparator();

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        actionautomatic->setText(QCoreApplication::translate("MainWindow", "Automatically add", nullptr));
        actionmanually_add->setText(QCoreApplication::translate("MainWindow", "Manually add", nullptr));
        menuHelldivers_Campaign_Updates->setTitle(QCoreApplication::translate("MainWindow", "Helldivers Campaign Updates", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
