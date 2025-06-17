#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QAction *myAction = new QAction(tr("&Do Something"), this);
    connect(myAction, &QAction::triggered, this, &MainWindow::on_actionClear_all_planets_triggered);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionClear_all_planets_triggered()
{
    myDIH->clearPlanetLayout();
    myDIH->clearPlanetsDisplayed();
}

