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

    w.show();
    return a.exec();
}

/**
    and add functionality to adding wars manually (could also make automatic only show planets
    with progress or more than x players), add some bool that states if anything has changed in
    layouts since their last automatic call, to use as guard to further calling of the same info,
    therefore same layout
*/
