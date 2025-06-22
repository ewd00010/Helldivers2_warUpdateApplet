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
    QNetworkReply *reply = w.myApiCaller->netManager->get(QNetworkRequest(
        QUrl("https://helldiverstrainingmanual.com/api/v1/war/campaign")));

    w.show();
    return a.exec();
}
