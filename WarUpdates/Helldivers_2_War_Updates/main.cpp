#include "mainwindow.h"
#include "api_caller.h"
#include "display_info_handler.h"
#include <QDebug>
#include <QApplication>
#include <QNetworkProxy>
#include <qnetworkreply.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    qDebug() << "main window";
    w.myDIH = std::make_shared<DisplayInfoHandler>(&w);

    qDebug() << "DIH shared";

    w.myApiCaller = std::make_shared<API_Caller>(&w.myDIH);
    qDebug() << "ApiCaller shared";

    w.myApiCaller->netManager->setProxy(QNetworkProxy::NoProxy);

    w.myApiCaller->retrieveWarCampaign();
    w.myApiCaller->retrieveWarInfo();

    w.myApiCaller->useWarCampaignInfo();
    w.myApiCaller->useWarInfoInfo();

    std::thread CampaignCallerThread = std::thread(&API_Caller::campaignCallerThreadFunction, w.myApiCaller);
    CampaignCallerThread.detach();

    std::thread WarInfoCallerThread = std::thread(&API_Caller::warInfoCallerThreadFunction, w.myApiCaller);
    CampaignCallerThread.detach();

    w.show();
    return a.exec();
}

/**
    will need to convert current std::thread usage, to QThread.

    need to implement selecting amount of planets to show, over the old manually option.

    at somepoint i will make a config file and reader, to allow for tweaking off start up
    options.

    code also cut down on the total amount of buttons by making them dynamically change
    function based on state.
*/
