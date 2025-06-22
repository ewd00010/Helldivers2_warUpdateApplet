#include <QSet>
#include <QHBoxLayout>
#include <QWidget>
#include <QGroupBox>
#include "api_types.h"
#include "QMainWindow"

#ifndef DISPLAY_INFO_HANDLER_H
#define DISPLAY_INFO_HANDLER_H

/**
 * @class DisplayInfoHandler
 * @brief Manages what is displayed.
 *
 * @details
 * this class contains information to what is currently display on screen; It
 * allows for getting and setting of indivudal planets and wars, append them
 * to the current layout and keeping a log of what is displayed. It also allows
 * for clearing of the current layout.
 *
 */
class DisplayInfoHandler
{
public:
    DisplayInfoHandler(QMainWindow *window);

    /**
    * @brief returns if the planet passed in is displayed
    *
    * @param planetIndex[in] the planet to check for
    *
    * @return if the planet is displayed
    */
    static bool getIsPlanetDisplayed(const int& planetIndex);

    /**
    * @brief sets the planet passed in to be displayed
    *
    * @param planetIndex[in] the planet to set as displayed
    *
    * @return true if it is now being displayed, false if it is already displayed
    */
    static bool setIsPlanetDisplayed(const int& planetIndex);

    /**
    * @brief clear ALL planets from the current list of displayed planet ids
    */
    static void clearPlanetsDisplayed();

    /**
    * @brief clear A planet from the current list of displayed planet ids
    *
    * @param planetIndex[in] the planet to check for
    *
    * @return true if it is removed from the id list, false if it was not in the list
    */
    static bool clearAPlanetDisplayed(const int& planetIndex);

    /**
    * @brief checks if we are displaying war information
    *
    * @return true if the war is displayed currently
    */
    static bool getIsWarDisplayed();

    /**
    * @brief sets tracker for if war info is currently being displayed
    */
    static void setIsWarDisplayed();

    /**
    * @brief get the current layout form
    *
    * @return the layourform we are currently under
    */
    static bool getCurrentLayoutForm();

    /**
    * @brief set the current layout form
    *
    * @param the layout form we want to use
    */
    static void setCurrentLayoutForm(const int& choice);

    /**
    * @brief adds planet to currenty displayed layout
    *
    * @param planet info struct to be added to layout
    */
    void addPlanetToCurrentLayout(API_Types::warCampaignStructT& planet);

    void addWarLayoutToCurrentLayout(API_Types::warInfoStructT&);

    /**
    * @brief clears the planet layout
    */
    void clearPlanetLayout();

    /**
    * @brief adds pwar to currenty displayed layout
    *
    * @param war info struct to be added
    */
    void addWarToCurrentLayout(API_Types::warInfoStructT& war);

    enum CurrentLayoutForm
    {
        automaticallySet = 0,
        manuallySet = 1
    };
    static CurrentLayoutForm layoutForm;

    /**
    * @brief sets the current planet layout to be used by the main window
    */
    void setPlanetLayout();

    /**
    * @brief sets the current war layout to be used by the main window
    */
    void setWarLayout();


    /*!
    * @todo next session, will need to look at how i'm handling layouts,
    * and will program in war layout(probably with modifications to planet
    * layout)
    *
    * also I will need to make my api cals work with callback handlers, otherwise
    * QEventExec will block signals making my api calls time out
    */



private:
    static QSet<int> planetsCurrentlyDisplayed;
    static bool isWarDisplayed;

    QWidget *window = new QWidget;
    QHBoxLayout *planetsLayout = new QHBoxLayout(window);
    QVector<QGroupBox*> *planetsInLayout = new QVector<QGroupBox*>();
    QMainWindow *myMainWindow;
};

#endif // DISPLAY_INFO_HANDLER_H
