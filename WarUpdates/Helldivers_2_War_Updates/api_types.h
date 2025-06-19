#include <QString>
#include <QDebug>

#ifndef API_TYPES_H
#define API_TYPES_H


class API_Types
{
public:
    struct warCampaignStructT
    {
        int myPlanetIndex;
        QString myPlanetName;
        QString myFactionName;
        int myPlayers;
        int myHealth;
        int myMaxHealth;
        double myPercentage;
        bool myIsDefence;
        bool myIsMajorOrder;
        QString myBiome;
    };

    struct warInfoStructT
    {
        warInfoStructT(int warId,
                       int startDate,
                       int endDate) : myWarId(warId), myStartDate(startDate), myEndDate(endDate) {}
        int myWarId;
        int myStartDate;
        int myEndDate;
    };

    struct planetStatusStructT
    {
        int health;
        double regenPerSecond;
        int players;
    } planetStatusStruct;

    struct warStatusStructT
    {
        int warId;
        int time;
        double impactMultiplier;
        planetStatusStructT myplanetStatusStruct;
    } warStatusStruct;

    struct majorOrderStructT
    {
        QString overrideBrief;
        QString taskDescription;
        int planetIds[];
    } majorOrderStruct;

    enum typeOfCheck
    {
        Campaign = 0
    };
};

#endif // API_TYPES_H
