#ifndef THREAD_PROCESSES_H
#define THREAD_PROCESSES_H

#include "api_caller.h"
#include <QObject>
#include <QThread>

class Thread_Processes : public QObject
{
    Q_OBJECT
public slots:
    void warCampaignProcessor(std::shared_ptr<API_Caller> &myAPI_Caller)
    {
        QNetworkAccessManager *netManager = new QNetworkAccessManager();
        while(!isWarCampaignRunning)
        {
            myAPI_Caller->retrieveWarCampaign(*netManager);
            QThread::sleep(std::chrono::seconds(30));
        }
        delete netManager;
        emit warCampaignfinished();
    }

    void warInfoProcessor(std::shared_ptr<API_Caller> &myAPI_Caller)
    {
        QNetworkAccessManager *netManager = new QNetworkAccessManager();
        while(!isWarInfoRunning)
        {
            myAPI_Caller->retrieveWarInfo(*netManager);
            QThread::sleep(std::chrono::seconds(30));
        }
        delete netManager;
        emit warInfofinished();
    }

signals:
    void warCampaignfinished();
    void warInfofinished();

private:
    std::atomic<bool> isWarCampaignRunning = false;
    std::atomic<bool> isWarInfoRunning = false;
};
#endif // THREAD_PROCESSES_H
