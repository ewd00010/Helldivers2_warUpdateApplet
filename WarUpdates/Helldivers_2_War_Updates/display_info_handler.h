#include <QSet>
#include <QHBoxLayout>
#include <QWidget>
#include <QGroupBox>
#include <QMainWindow>
#include "api_types.h"

#ifndef DISPLAY_INFO_HANDLER_H
#define DISPLAY_INFO_HANDLER_H

/**
 * @class DisplayInfoHandler
 * @brief Manages what is displayed.
 *
 * @details
 * This class contains information to what is currently display on screen; It
 * allows for getting and setting of indivudal planets and wars, append them
 * to the current layout and keeping a log of what is displayed. It also allows
 * for clearing of the current layout.
 *
 */
class DisplayInfoHandler
{
public:
    DisplayInfoHandler(QMainWindow *window);
    ~DisplayInfoHandler()= default;

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
    static void clearAllPlanetsDisplayed();

    /**
    * @brief clear A planet from the current list of displayed planet ids
    *
    * @param planetIndex[in] the planet to check for
    *
    * @return true if it is removed from the id list, false if it was not in the list
    */
    static bool clearSomePlanetDisplayed(const int planetIndex[]);

    /**
    * @brief adds planet to currenty displayed layout
    *
    * @param planet info struct to be added to layout
    */
    void addPlanetToCurrentLayout(API_Types::planetStructT& planet);

    /**
    * @brief clears the planet layout
    */
    void clearPlanetLayout();

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
    * @brief adds war to currenty displayed layout
    *
    * @param war info struct to be added to layout
    */
    void addWarLayoutToCurrentLayout(API_Types::warInfoStructT&);

    /**
    * @brief adds pwar to currenty displayed layout
    *
    * @param war info struct to be added
    */
    void addWarToCurrentLayout(API_Types::warInfoStructT& war);

    /**
    * @brief clears the war layout
    */
    void clearWarLayout();

private:
    static QSet<int> planetsCurrentlyDisplayed;
    static bool isWarDisplayed;

    QWidget *window;
    QHBoxLayout *planetsLayout;
    QHBoxLayout *warLayout;
    QVector<QGroupBox*> *planetsInLayout;
    QMainWindow *myMainWindow;
    QVBoxLayout* mainVLayout;
};

#endif // DISPLAY_INFO_HANDLER_H
