#include "api_types.h"
#include "display_info_handler.h"
#include <QtNetwork/QNetworkAccessManager>
#include <memory>

#ifndef API_CALLER_H
#define API_CALLER_H

/**
 * @class API_Caller
 * @brief Handles the calling and processing of information from the API.
 *
 * @details
 * This class contains various functions that call the helldivers api and store the information;
 * The information is then handled by other functions. an instance of network manager is also stored
 * here.
 *
 */
class API_Caller : public QObject
{
public:
    API_Caller(std::shared_ptr<DisplayInfoHandler> &DIH, QObject* parent = nullptr);
    ~API_Caller() = default;

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
    std::variant<API_Types::warInfoStructT,API_Types::planetStructT> errorCheck(QJsonObject& info, API_Types::typeOfCheck type);




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
    void retrieveWarCampaign(QNetworkAccessManager &netManager);

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
    void retrieveWarInfo(QNetworkAccessManager &netManager);

    /**
     * @brief api call to
     * @link https://helldiverstrainingmanual.com/api/v1/war/status
     *
     * @details
     * calls api to retrieve information, errorchecks this informaton and then puts it into a warstatus struct
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

private:

    std::shared_ptr<DisplayInfoHandler> myDIH;

    std::shared_ptr<QList<API_Types::planetStructT>> warCampaignListPtr;

    API_Types::warInfoStructT warInfoStruct;

    const QUrl WAR_CAMPAIGN_URL = QUrl("https://helldiverstrainingmanual.com/api/v1/war/campaign");

    const QUrl WAR_INFO_URL = QUrl("https://helldiverstrainingmanual.com/api/v1/war/info");
};

#endif // API_CALLER_H
