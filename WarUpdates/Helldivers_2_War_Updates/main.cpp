#include "mainwindow.h"
#include "api_caller.h"
#include "display_info_handler.h"
#include <QDebug>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    qDebug() << "made it past main window";
    w.myDIH = std::make_shared<DisplayInfoHandler>(&w);

    qDebug() << "made it past DIH shared";
    w.myDIH.get()->layoutForm = DisplayInfoHandler::CurrentLayoutForm::automaticallySet;
    w.myApiCaller = std::make_shared<API_Caller>(&w.myDIH);
    qDebug() << "made it past ApiCaller shared";

    w.myApiCaller->useWarCampaignInfo();
    qDebug() << "made it past warCampaignInfo";

    w.show();
    return a.exec();
}
