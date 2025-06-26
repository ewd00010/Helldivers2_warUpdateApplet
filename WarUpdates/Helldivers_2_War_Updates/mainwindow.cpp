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
    QAction *autoAdd = new QAction(tr("&Automatically add planets"), this);
    QAction *manuallyAdd = new QAction(tr("&Manually add Planets"), this);
    QAction *warInfoAdd = new QAction(tr("&Add war info"), this);
    QAction *clearWarInfo = new QAction(tr("&Clear war info"), this);
    connect(clearAll, &QAction::triggered, this, &MainWindow::on_actionClear_all_planets_triggered);
    connect(autoAdd, &QAction::triggered, this, &MainWindow::on_action_Automatically_add_triggered);
    connect(manuallyAdd, &QAction::triggered, this, &MainWindow::on_action_Manually_add_triggered);
    connect(warInfoAdd, &QAction::triggered, this, &MainWindow::on_actionAdd_war_info_triggered);
    connect(clearWarInfo, &QAction::triggered, this, &MainWindow::on_actionClear_war_info_triggered);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionClear_all_planets_triggered()
{
    qDebug() << "MainWindow::on_actionClear_all_planets_triggered()";
    myDIH->clearPlanetLayout();
    myDIH->clearPlanetsDisplayed();
    setFixedSize(BASE_WIDTH, BASE_HEIGHT);
    setMinimumSize(QSize(0, 0));
    setMaximumSize(MAX_WIDTH, MAX_HEIGHT);
}


void MainWindow::on_action_Automatically_add_triggered()
{
    qDebug() << "MainWindow::on_action_Automatically_add_triggered()";
    myApiCaller->useWarCampaignInfo();
}


void MainWindow::on_action_Manually_add_triggered()
{

}


void MainWindow::on_actionAdd_war_info_triggered()
{
    qDebug() << "MainWindow::on_actionAdd_war_info_triggered()";
    myApiCaller->useWarInfoInfo();
}


void MainWindow::on_actionClear_war_info_triggered()
{
    qDebug() << "MainWindow::on_actionClear_war_info_triggered()";
    myDIH->clearWarLayout();
}

