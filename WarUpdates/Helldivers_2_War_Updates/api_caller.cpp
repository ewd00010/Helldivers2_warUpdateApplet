#include "api_caller.h"
#include <QUrl>
#include <QDebug>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QEventLoop>

API_Caller::API_Caller(std::shared_ptr<DisplayInfoHandler> *DIH, QObject *parent) : myDIH(*DIH) {}

void API_Caller::retrieveWarCampaign() {
    QNetworkReply *reply = netManager->get(QNetworkRequest(
        QUrl("https://helldiverstrainingmanual.com/api/v1/war/campaign")));
    warCampaignListPtr = std::make_shared<QList<API_Types::planetStructT>>();

    QEventLoop myConnectFinished;

    QObject::connect(
        reply, &QNetworkReply::finished, this,
        [&, reply]() {
            if (reply->error() == QNetworkReply::NoError) {
                QByteArray responseData = reply->readAll();
                QJsonDocument jsonDoc = QJsonDocument::fromJson(responseData);
                QJsonArray jsonArray = jsonDoc.array();

                for(const QJsonValue &planet : jsonArray) {
                    QJsonObject planetObj = planet.toObject();
                    API_Types::planetStructT warCampaignStruct = std::get<API_Types::planetStructT>(errorCheck(planetObj, API_Types::typeOfCheck::Campaign));

                    warCampaignListPtr->append(warCampaignStruct);
                }
            } else {
                qDebug() << "Error:" << reply->errorString();
            }
            reply->deleteLater();
            qDebug() << "made it";
            myConnectFinished.quit();
        });
    myConnectFinished.exec();
};

void API_Caller::useWarCampaignInfo() {
    qDebug() << "ApiCaller::useWarCampaignInfo";

    for (API_Types::planetStructT planet : *warCampaignListPtr)
    {
        if (!DisplayInfoHandler::getIsPlanetDisplayed(planet.myPlanetIndex)) {
            {
                myDIH->addPlanetToCurrentLayout(planet);
            }
        }
    }

}

QList<API_Types::warInfoStructT> API_Caller::retrieveWarInfo() {
    QNetworkReply *reply = netManager->get(QNetworkRequest(
        QUrl("https://helldiverstrainingmanual.com/api/v1/war/info")));
    QList<API_Types::warInfoStructT> warInfoList;
    auto warInfoListPtr =
        std::make_shared<QList<API_Types::warInfoStructT>>(warInfoList);

    QEventLoop myConnectFinished;
    QObject::connect(reply, &QNetworkReply::finished,
                     [&myConnectFinished, reply, warInfoListPtr, this]()
                     {
                         if (reply->error() == QNetworkReply::NoError) {
                             QByteArray responseData = reply->readAll();
                             QJsonDocument jsonDoc =
                                 QJsonDocument::fromJson(responseData);
                             QJsonObject jsonObject = jsonDoc.object();

                             const API_Types::warInfoStructT warInfoStruct =
                                 std::get<API_Types::warInfoStructT>(errorCheck(jsonObject,
                                    API_Types::typeOfCheck::WarInfo));

                             warInfoListPtr.get()->append(warInfoStruct);
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

void API_Caller::useWarInfoInfo() {
    QList<API_Types::warInfoStructT> warInfoInfo = retrieveWarInfo();

    for(API_Types::warInfoStructT& war : warInfoInfo) {
        if (!DisplayInfoHandler::getIsWarDisplayed()) {
            myDIH->addWarToCurrentLayout(war);
        }
    }
};

void API_Caller::retrieveWarStatus() {};
void API_Caller::retrieveMajorOrder() {};

std::variant<API_Types::warInfoStructT,API_Types::planetStructT> API_Caller::errorCheck(QJsonObject &info, API_Types::typeOfCheck type)
{
    API_Types::warInfoStructT warInfoStruct = API_Types::warInfoStructT();
    API_Types::planetStructT warCampaignStruct = API_Types::planetStructT();

    switch(type)
    {
    case API_Types::typeOfCheck::Campaign:
        if (info.contains("planetIndex") && info["planetIndex"].isDouble())
            warCampaignStruct.myPlanetIndex = info["planetIndex"].toInt();
        else
            qDebug() << "Missing or invalid planetIndex";

        if (info.contains("name") && info["name"].isString())
            warCampaignStruct.myPlanetName = info["name"].toString();
        else
            qDebug() << "Missing or invalid planet name";

        if (info.contains("faction") && info["faction"].isString())
            warCampaignStruct.myFactionName = info["faction"].toString();
        else
            qDebug() << "Missing or invalid faction name";

        if (info.contains("players") && info["players"].isDouble())
            warCampaignStruct.myPlayers = info["players"].toInt();
        else
            qDebug() << "Missing or invalid players";

        if (info.contains("health") && info["health"].isDouble())
            warCampaignStruct.myHealth = info["health"].toInt();
        else
            qDebug() << "Missing or invalid health";

        if (info.contains("maxHealth") && info["maxHealth"].isDouble())
            warCampaignStruct.myMaxHealth = info["maxHealth"].toInt();
        else
            qDebug() << "Missing or invalid maxHealth";

        if (info.contains("percentage") && info["percentage"].isDouble())
            warCampaignStruct.myPercentage = info["percentage"].toDouble();
        else
            qDebug() << "Missing or invalid percentage";

        if (info.contains("defense") && info["defense"].isBool())
            warCampaignStruct.myIsDefence = info["defense"].toBool();
        else
            qDebug() << "Missing or invalid defense";

        if (info.contains("majorOrder") && info["majorOrder"].isBool())
            warCampaignStruct.myIsMajorOrder = info["majorOrder"].toBool();
        else if (info.contains("majorOrder") && info["majorOrder"].isDouble())
            warCampaignStruct.myIsMajorOrder = info["majorOrder"].toInt();
        else
        {
            qDebug() << "Missing or invalid majorOrder";
        }

        if (info.contains("biome") && info["biome"].isObject()) {
            QJsonObject biomeObj = info["biome"].toObject();
            if (biomeObj.contains("slug") && biomeObj["slug"].isString())
                warCampaignStruct.myBiome = biomeObj["slug"].toString();
            else
                qDebug() << "Missing or invalid biome.slug";
        } else {
            qDebug() << "Missing or invalid biome object";
        }
        return warCampaignStruct;
        break;
    case API_Types::typeOfCheck::WarInfo:
        if (info.contains("warId") && info["warId"].isDouble())
            warInfoStruct.myWarId = info["warId"].toInt();
        else
            qDebug() << "Missing or invalid warId";

        if (info.contains("startDate") && info["endDate"].isDouble())
            warInfoStruct.myStartDate = info["startDate"].toInt();
        else
            qDebug() << "Missing or invalid planet startDate";

        if (info.contains("endDate") && info["endDate"].isDouble())
            warInfoStruct.myEndDate = info["endDate"].toInt();
        else
            qDebug() << "Missing or invalid faction endDate";
        return warInfoStruct;
        break;
    };
};
