#include "api_types.h"
#include "display_info_handler.h"
#include <qnetworkaccessmanager.h>

#ifndef API_CALLER_H
#define API_CALLER_H

class API_Caller
{
public:
    API_Caller(std::shared_ptr<DisplayInfoHandler> *DIH);
    virtual ~API_Caller() = default;

    /**
     * @brief using information from campaign api call
     *
     * @details
     * calls retrieveWarCampaign, adds planets from this call to a layout with addPlanetToCurrentLayout
     * then sets the current layout with setCurrentLayout
     */
    void useWarCampaignInfo();

    /**
     * @brief using information from warinfo api call
     *
     * @details
     */
    void useWarInfoInfo();

    /**
     * @brief Provides error checking of information from api call
     *
     * @details
     * Dependant on the type of source the information came from, we check information to ensure it exists and
     * is the right type for use within its variable,
     *
     * @param info[in] Info in Json style form
     *        type[in] The type of the source that provided info
     *
     * @return a struct with information relevant to the type passed in
     */
    std::variant<API_Types::warInfoStructT,API_Types::warCampaignStructT> errorCheck(QJsonObject& info, API_Types::typeOfCheck type);


    QNetworkAccessManager *netManager = new QNetworkAccessManager();
private:

    /**
     * @brief api call to
     * @link https://helldiverstrainingmanual.com/api/v1/war/campaign
     *
     * @details
     * calls api to retrieve information, errochecks this informaton and then puts it into a warCampaign struct
     * via the use of errorCheck with use of war campaign type argument
     *
     * @return a struct with error checked war campaign information
     */
    QList<API_Types::warCampaignStructT> retrieveWarCampaign();

    /**
     * @brief api call to
     * @link https://helldiverstrainingmanual.com/api/v1/war/info
     *
     * @details
     * calls api to retrieve information, errochecks this informaton and then puts it into a warinfo struct
     * via the use of errorCheck with use of war info type argument
     *
     * @return a struct with error checked war info information
     */
    QList<API_Types::warInfoStructT> retrieveWarInfo();

    /**
     * @brief api call to
     * @link https://helldiverstrainingmanual.com/api/v1/war/status
     *
     * @details
     * calls api to retrieve information, errochecks this informaton and then puts it into a warstatus struct
     * via the use of errorCheck with use of war status type argument
     *
     * @return a struct with error checked war status information
     */
    void retrieveWarStatus();

    /**
     * @brief api call to
     * @link https://helldiverstrainingmanual.com/api/v1/war/major-orders
     *
     * @details
     * calls api to retrieve information, errochecks this informaton and then puts it into a majororder struct
     * via the use of errorCheck with use of major order type argument
     *
     * @return a struct with error checked major order information
     */
    void retrieveMajorOrder();

    std::shared_ptr<DisplayInfoHandler> myDIH;
};

#endif // API_CALLER_H
