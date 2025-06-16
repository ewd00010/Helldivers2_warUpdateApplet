#include <QSet>
#include <QHBoxLayout>
#include <QWidget>
#include "api_types.h"
#include "QMainWindow"

#ifndef DISPLAY_INFO_HANDLER_H
#define DISPLAY_INFO_HANDLER_H

class DisplayInfoHandler
{
public:
    DisplayInfoHandler(QMainWindow *window);

    static bool getIsPlanetDisplayed(int planetIndex);
    static bool setIsPlanetDisplayed(int planetIndex);
    static bool getIsWarDisplayed();
    static void setIsWarDisplayed();
    static bool getCurrentLayoutForm();
    static void setCurrentLayoutForm(int choice);

    void addPlanetToCurrentLayout(API_Types::warCampaignStructT planet);
    void addWarToCurrentLayout(API_Types::warInfoStructT war);

    enum CurrentLayoutForm
    {
        automaticallySet = 0,
        manuallySet = 1
    };
    static CurrentLayoutForm layoutForm;

    void setLayout();

private:
    static QSet<int> planetsCurrentlyDisplayed;
    static bool isWarDisplayed;
    QWidget *window = new QWidget;
    QHBoxLayout *planetsLayout = new QHBoxLayout(window);
    QMainWindow *myMainWindow;
};

#endif // DISPLAY_INFO_HANDLER_H
