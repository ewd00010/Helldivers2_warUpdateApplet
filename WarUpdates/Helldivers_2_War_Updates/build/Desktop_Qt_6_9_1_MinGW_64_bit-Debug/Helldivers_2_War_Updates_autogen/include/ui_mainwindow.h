/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
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
    QAction *action_Automatically_add;
    QAction *action_Manually_add;
    QAction *actionClear_all_planets;
    QAction *actionClear_a_planet;
    QWidget *centralwidget;
    QMenuBar *menubar;
    QMenu *menuHelldivers_Campaign_Updates;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 600);
        action_Automatically_add = new QAction(MainWindow);
        action_Automatically_add->setObjectName("action_Automatically_add");
        action_Manually_add = new QAction(MainWindow);
        action_Manually_add->setObjectName("action_Manually_add");
        actionClear_all_planets = new QAction(MainWindow);
        actionClear_all_planets->setObjectName("actionClear_all_planets");
        actionClear_a_planet = new QAction(MainWindow);
        actionClear_a_planet->setObjectName("actionClear_a_planet");
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 25));
        menuHelldivers_Campaign_Updates = new QMenu(menubar);
        menuHelldivers_Campaign_Updates->setObjectName("menuHelldivers_Campaign_Updates");
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menuHelldivers_Campaign_Updates->menuAction());
        menuHelldivers_Campaign_Updates->addSeparator();
        menuHelldivers_Campaign_Updates->addAction(action_Automatically_add);
        menuHelldivers_Campaign_Updates->addAction(action_Manually_add);
        menuHelldivers_Campaign_Updates->addSeparator();
        menuHelldivers_Campaign_Updates->addAction(actionClear_all_planets);
        menuHelldivers_Campaign_Updates->addAction(actionClear_a_planet);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        action_Automatically_add->setText(QCoreApplication::translate("MainWindow", "Automatically add", nullptr));
        action_Manually_add->setText(QCoreApplication::translate("MainWindow", "Manually add", nullptr));
        actionClear_all_planets->setText(QCoreApplication::translate("MainWindow", "Clear all planets", nullptr));
        actionClear_a_planet->setText(QCoreApplication::translate("MainWindow", "Clear a planet", nullptr));
        menuHelldivers_Campaign_Updates->setTitle(QCoreApplication::translate("MainWindow", "Helldivers Campaign Updates", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
