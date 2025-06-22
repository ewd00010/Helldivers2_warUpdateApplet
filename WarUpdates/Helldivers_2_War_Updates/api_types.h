#include <QString>
#include <QDebug>

#pragma once

class API_Types
{
public:
    /**
     * @brief The warCampaignStructT type
     *
     * @details contains information from api call to campaign
     */
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

    /**
     * @brief The warInfoStructT type
     *
     * @details contains information from api call to warInfo
     */
    struct warInfoStructT
    {
        int myWarId;
        int myStartDate;
        int myEndDate;
    };

    /**
     * @brief The planetStatusStructT type
     *
     * @details contains information from api call to planetStatus
     */
    struct planetStatusStructT
    {
        int health;
        int players;
        double regenPerSecond;
    };

    /**
     * @brief The warStatusStructT type
     *
     * @details contains information from api call to warStatus
     */
    struct warStatusStructT
    {
        int warId;
        int time;
        double impactMultiplier;
        planetStatusStructT myplanetStatusStruct;
    };

    /**
     * @brief The majorOrderStructT type
     *
     * @details contains information from api call to majorOrder
     */
    struct majorOrderStructT
    {
        QString overrideBrief;
        QString taskDescription;
        int planetIds[];
    };

    /**
     * @brief the Type of check need to do be for a api call
     *
     * @details used within a switch case, to determine what information needs to be checked
     *
     * @see APICaller::errorCheck
     */
    enum typeOfCheck
    {
        Campaign = 0,
        WarInfo = 1
    };
};
