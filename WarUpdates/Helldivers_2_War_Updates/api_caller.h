#include "api_types.h"
#include "display_info_handler.h"

#ifndef API_CALLER_H
#define API_CALLER_H

class API_Caller
{
public:
    API_Caller(std::shared_ptr<DisplayInfoHandler> *DIH);

    void useWarCampaignInfo();
    void useWarInfoInfo();

private:
    QList<API_Types::warCampaignStructT> retrieveWarCampaign();
    QList<API_Types::warInfoStructT> retrieveWarInfo();
    void retrieveWarStatus();
    void retrieveMajorOrder();
    std::shared_ptr<DisplayInfoHandler> myDIH;
};

#endif // API_CALLER_H
