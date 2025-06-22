#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    resize(BASE_WIDTH, BASE_HEIGHT);
    setMaximumWidth(MAX_WIDTH);
    setMaximumHeight(MAX_HEIGHT);
    QAction *clearAll = new QAction(tr("&Clear the Screen of Planets"), this);
    QAction *autoAdd = new QAction(tr("&Clear the Screen of Planets"), this);
    QAction *manuallyAdd = new QAction(tr("&Clear the Screen of Planets"), this);
    connect(clearAll, &QAction::triggered, this, &MainWindow::on_actionClear_all_planets_triggered);
    connect(autoAdd, &QAction::triggered, this, &MainWindow::on_action_Automatically_add_triggered);
    connect(manuallyAdd, &QAction::triggered, this, &MainWindow::on_action_Manually_add_triggered);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionClear_all_planets_triggered()
{
    myDIH->clearPlanetLayout();
    myDIH->clearPlanetsDisplayed();
    setFixedSize(BASE_WIDTH, BASE_HEIGHT);
    setMinimumSize(QSize(0, 0));
    setMaximumSize(MAX_WIDTH, MAX_HEIGHT);
}


void MainWindow::on_action_Automatically_add_triggered()
{
    myApiCaller->useWarCampaignInfo();
    qDebug() << "warCampaignInfo";
}


void MainWindow::on_action_Manually_add_triggered()
{

}

