#include "api_caller.h"
#include <QUrl>
#include <QDebug>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <qforeach.h>
#include <QEventLoop>

API_Caller::API_Caller(DisplayInfoHandler DIH) : myDIH(DIH) {}

QList<API_Types::warCampaignStructT> API_Caller::retrieveWarCampaign()
{
    QNetworkAccessManager *netManager = new QNetworkAccessManager();
    QNetworkReply *reply = netManager->get(QNetworkRequest(QUrl("https://helldiverstrainingmanual.com/api/v1/war/campaign")));
    QList<API_Types::warCampaignStructT> warCampaignList;
    auto warCampaignVectorPtr = std::make_shared<QList<API_Types::warCampaignStructT>>(warCampaignList);

    QEventLoop myConnectFinished;
    QObject::connect(reply, &QNetworkReply::finished, [&myConnectFinished, reply, warCampaignVectorPtr]()
    {
        if (reply->error() == QNetworkReply::NoError)
        {
            QByteArray responseData = reply->readAll();
            QJsonDocument jsonDoc = QJsonDocument::fromJson(responseData);
            QJsonArray jsonArray = jsonDoc.array();

            foreach(const QJsonValue &planet, jsonArray)
            {
                const QJsonObject planetObj = planet.toObject();

                API_Types::warCampaignStructT warCampaignStruct(planetObj.find("planetIndex")->toInt(),planetObj.find("name")->toString(),
                planetObj.find("faction")->toString(), planetObj.find("players")->toInt(), planetObj.find("health")->toInt(), planetObj.find("maxHealth")->toInt(),
                planetObj.find("percentage")->toDouble(), planetObj.find("defense")->toBool(), planetObj.find("majorOrder")->toBool(),
                planetObj.find("biome")->toObject().find("slug")->toString());

                warCampaignVectorPtr.get()->append(warCampaignStruct);
            }
        }
        else
        {
            qDebug() << "Error:" << reply->errorString();
        }
        reply->deleteLater();
        myConnectFinished.quit();
    });
    myConnectFinished.exec();
    return *warCampaignVectorPtr.get();
};

void API_Caller::useWarCampaignInfo()
{
    QList<API_Types::warCampaignStructT> campaignInfo =  API_Caller::retrieveWarCampaign();

    foreach(const API_Types::warCampaignStructT planet, campaignInfo)
    {
        if(!DisplayInfoHandler::getIsPlanetDisplayed(planet.myPlanetIndex))
        {
            myDIH.addPlanetToCurrentLayout(planet);
        }
    }
    myDIH.setLayout();
}

QList<API_Types::warInfoStructT> API_Caller::retrieveWarInfo()
{
    QNetworkAccessManager *netManager = new QNetworkAccessManager();
    QNetworkReply *reply = netManager->get(QNetworkRequest(QUrl("https://helldiverstrainingmanual.com/api/v1/war/info")));
    QList<API_Types::warInfoStructT> warInfoList;
    auto warInfoListPtr = std::make_shared<QList<API_Types::warInfoStructT>>(warInfoList);

    QEventLoop myConnectFinished;
    QObject::connect(reply, &QNetworkReply::finished, [&myConnectFinished, reply, warInfoListPtr]()
                     {
                         if (reply->error() == QNetworkReply::NoError)
                         {
                             QByteArray responseData = reply->readAll();
                             QJsonDocument jsonDoc = QJsonDocument::fromJson(responseData);
                             QJsonArray jsonArray = jsonDoc.array();

                             foreach(const QJsonValue &war, jsonArray)
                             {
                                 const QJsonObject warObj = war.toObject();

                                 API_Types::warInfoStructT warInfoStruct(warObj.find("warId")->toInt(), warObj.find("startDate")->toInt(), warObj.find("endDate")->toInt());

                                 warInfoListPtr.get()->append(warInfoStruct);
                             }
                         }
                         else
                         {
                             qDebug() << "Error:" << reply->errorString();
                         }
                         reply->deleteLater();
                         myConnectFinished.quit();
                     });
    myConnectFinished.exec();
    return *warInfoListPtr.get();
};

void API_Caller::useWarInfoInfo()
{
    QList<API_Types::warInfoStructT> warInfoInfo =  API_Caller::retrieveWarInfo();

    foreach(const API_Types::warInfoStructT war, warInfoInfo)
    {
        if(!DisplayInfoHandler::getIsWarDisplayed())
        {
            myDIH.addWarToCurrentLayout(war);
        }
    }
    myDIH.setLayout();
};


void API_Caller::retrieveWarStatus(){};
void API_Caller::retrieveMajorOrder(){};
