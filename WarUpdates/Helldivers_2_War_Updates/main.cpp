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

    w.show();
    return a.exec();
}

/**
    useWarInfoInfo still needs a minor update to store info in a object. easy win.

    need to thread retrieving info for them to be called every 30-300 seconds.

    need to implement selecting amount of planets to show, over the old manually option.

    at somepoint i will make a config file and reader, to allow for tweaking off start up
    options.

    code also cut down on the total amount of buttons by making them dynamically change
    function based on state.
*/
