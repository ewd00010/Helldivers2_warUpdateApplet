#include <QString>
#include <QDebug>

#pragma once

/**
 * @class API_Types
 * @brief Type store for API stuff
 *
 * @details
 * This class contains several structs and enums that contain information for common objects and
 * states.
 *
 *@see api_caller.h
 */
class API_Types
{
public:

    ~API_Types() = default;
    /**
     * @brief The planetStructT type
     *
     * @details contains information from api call to campaign
     *
     * @see API_Caller::retrieveWarCampaign
     */
    struct planetStructT
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
     *
     * @see API_Caller::retrieveWarinfo
     */
    struct warInfoStructT
    {
        int myWarId;
        int myStartDate;
        int myEndDate;
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
