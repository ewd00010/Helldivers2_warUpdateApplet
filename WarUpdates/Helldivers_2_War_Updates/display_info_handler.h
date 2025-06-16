#include <QSet>
#include <QHBoxLayout>
#include <QWidget>
#include <QGroupBox>
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
    static void clearPlanetsDisplayed();
    static void clearAPlanetDisplayed(int planetIndex);

    static bool getIsWarDisplayed();
    static void setIsWarDisplayed();
    static bool getCurrentLayoutForm();
    static void setCurrentLayoutForm(int choice);


    void addPlanetToCurrentLayout(API_Types::warCampaignStructT planet);
    void clearPlanetLayout();
    void addWarToCurrentLayout(API_Types::warInfoStructT war);

    enum CurrentLayoutForm
    {
        automaticallySet = 0,
        manuallySet = 1
    };
    static CurrentLayoutForm layoutForm;

    void setPlanetLayout();

private:
    static QSet<int> planetsCurrentlyDisplayed;
    static bool isWarDisplayed;

    QWidget *window = new QWidget;
    QHBoxLayout *planetsLayout = new QHBoxLayout(window);
    QVector<QGroupBox*> *planetsInLayout = new QVector<QGroupBox*>();
    QMainWindow *myMainWindow;
};

#endif // DISPLAY_INFO_HANDLER_H
