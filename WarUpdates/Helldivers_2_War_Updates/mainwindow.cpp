#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent, std::shared_ptr<DisplayInfoHandler> *DIH, std::shared_ptr<API_Caller> *apiCaller)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , myDIH(*DIH)
    , myApiCaller(*apiCaller)
{
    ui->setupUi(this);
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

