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
    w.myDIH.get()->layoutForm = DisplayInfoHandler::CurrentLayoutForm::manuallySet;

    w.myApiCaller = std::make_shared<API_Caller>(&w.myDIH);
    qDebug() << "ApiCaller shared";

    w.myApiCaller->netManager->setProxy(QNetworkProxy::NoProxy);

    w.show();
    return a.exec();
}

/**
    next time will need to add more doxygen, add a functionality to clear war info button,
    and add functionality to adding wars manually (could also make automatic only show planets
    with progress or more than x players)
*/
