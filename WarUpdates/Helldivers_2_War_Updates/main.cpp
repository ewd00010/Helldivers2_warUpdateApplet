#include "mainwindow.h"
#include "api_caller.h"
#include "display_info_handler.h"
#include "thread_processes.h"
#include <QDebug>
#include <QApplication>
#include <QNetworkProxy>
#include <QNetworkreply>
#include <QThread>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    qDebug() << "main window";

    w.myDIH = std::make_shared<DisplayInfoHandler>(&w);
    qDebug() << "DIH shared";

    w.myApiCaller = std::make_shared<API_Caller>(w.myDIH);
    qDebug() << "ApiCaller shared";

    w.myThreadProcesses = std::make_shared<Thread_Processes>();
    qDebug() << "ThreadProcesses shared";
    QNetworkAccessManager *netManager = new QNetworkAccessManager;

    w.myApiCaller->retrieveWarCampaign(*netManager);
    w.myApiCaller->retrieveWarInfo(*netManager);

    w.myApiCaller->useWarCampaignInfo();
    w.myApiCaller->useWarInfoInfo();

    w.CampaignCallerThread = std::make_shared<QThread>();

    w.myThreadProcesses->moveToThread(w.CampaignCallerThread.get());

    Thread_Processes::connect(w.CampaignCallerThread.get(), &QThread::started, [&](){w.myThreadProcesses->warCampaignProcessor(w.myApiCaller);});

    Thread_Processes::connect(w.myThreadProcesses.get(), &Thread_Processes::warCampaignfinished, w.CampaignCallerThread.get(), &QThread::quit);

    w.CampaignCallerThread->start();

    Thread_Processes::connect(w.CampaignCallerThread.get(), &QThread::started, [&](){w.myThreadProcesses->warInfoProcessor(w.myApiCaller);});

    Thread_Processes::connect(w.myThreadProcesses.get(), &Thread_Processes::warInfofinished, w.CampaignCallerThread.get(), &QThread::quit);

    w.CampaignCallerThread->start();

    w.show();
    return a.exec();
}

/**
    {
        //myDIH->updatePlanetLayout()
    }

    {
        //myDIH->updateWarLayout()
    }

    will need to do the coding for the functions above.

    need to implement selecting amount of planets to show, over the old manually option.

    at somepoint i will make a config file and reader, to allow for tweaking off start up
    options.

    code also cut down on the total amount of buttons by making them dynamically change
    function based on state.
*/
