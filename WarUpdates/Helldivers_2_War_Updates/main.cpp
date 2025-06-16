#include "mainwindow.h"
#include "api_caller.h"
#include "display_info_handler.h"
#include <QDebug>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.myDIH = std::make_shared<DisplayInfoHandler>(&w);
    w.myDIH.get()->layoutForm = DisplayInfoHandler::CurrentLayoutForm::automaticallySet;
    w.myApiCaller = std::make_shared<API_Caller>(&w.myDIH);
    w.myApiCaller->useWarCampaignInfo();
    w.show();
    return a.exec();
}
