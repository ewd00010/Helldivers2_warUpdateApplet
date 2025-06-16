#include "mainwindow.h"
#include "api_caller.h"
#include "display_info_handler.h"
#include <QDebug>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    std::unique_ptr<DisplayInfoHandler> DIH = std::make_unique<DisplayInfoHandler>(&w);
    DIH.get()->layoutForm = DisplayInfoHandler::CurrentLayoutForm::automaticallySet;
    std::unique_ptr<API_Caller> apiCaller = std::make_unique<API_Caller>(*DIH);
    apiCaller->useWarCampaignInfo();
    qDebug() << "\n showing \n";
    w.show();
    return a.exec();
}
