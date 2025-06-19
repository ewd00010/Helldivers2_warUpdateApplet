#include "display_info_handler.h"
#include <QLabel>
#include <QProgressBar>
#include <QGroupBox>
#include <QVBoxLayout>

QSet<int> DisplayInfoHandler::planetsCurrentlyDisplayed;

bool DisplayInfoHandler::isWarDisplayed;

DisplayInfoHandler::CurrentLayoutForm DisplayInfoHandler::layoutForm;

DisplayInfoHandler::DisplayInfoHandler(QMainWindow *mainWindow) : myMainWindow(mainWindow) {}

bool DisplayInfoHandler::getIsPlanetDisplayed(int planetIndex)
{
    return DisplayInfoHandler::planetsCurrentlyDisplayed.contains(planetIndex);
};

bool DisplayInfoHandler::setIsPlanetDisplayed(int planetIndex)
{
    if(!DisplayInfoHandler::planetsCurrentlyDisplayed.contains(planetIndex))
    {
        DisplayInfoHandler::planetsCurrentlyDisplayed.insert(planetIndex);
        return true;
    }
    return false;
};

void DisplayInfoHandler::addWarToCurrentLayout(API_Types::warInfoStructT war){};

void DisplayInfoHandler::addPlanetToCurrentLayout(API_Types::warCampaignStructT planet)
{
    if(!getIsPlanetDisplayed(planet.myPlanetIndex))
    {
        setIsPlanetDisplayed(planet.myPlanetIndex);
        QGroupBox* planetGroupBox = new QGroupBox(planet.myPlanetName, DisplayInfoHandler::window);
        planetGroupBox->setGeometry(40, 50, 241, 481);

        // Create layout for labels
        QVBoxLayout* textLayout = new QVBoxLayout;

        QLabel* playerCountLabel = new QLabel("Player Count: " + QString::number(planet.myPlayers));
        QLabel* healthLabel = new QLabel("Health: " + QString::number(planet.myHealth));
        QString campaignType = planet.myIsDefence ? "Defensive" : "Offensive";
        QLabel* campaignTypeLabel = new QLabel("Campaign Type: " + campaignType);
        QLabel* majorOrderLabel = new QLabel("Major Order: " + QVariant(planet.myIsMajorOrder).toString());
        QLabel* biomeLabel = new QLabel("Biome: " + planet.myBiome);

        textLayout->addWidget(playerCountLabel);
        textLayout->addWidget(healthLabel);
        textLayout->addWidget(campaignTypeLabel);
        textLayout->addWidget(majorOrderLabel);
        textLayout->addWidget(biomeLabel);

        QWidget* textContainer = new QWidget;
        textContainer->setGeometry(10, 30, 221, 161);
        textContainer->setLayout(textLayout);

        // Create Progress Bars
        QProgressBar* progressBar1 = new QProgressBar;
        progressBar1->setGeometry(10, 200, 71, 271);
        progressBar1->setValue(planet.myPercentage);
        progressBar1->setOrientation(Qt::Vertical);
        progressBar1->setAlignment(Qt::AlignCenter);
        progressBar1->setInvertedAppearance(false);

        QProgressBar* progressBar2 = new QProgressBar;
        progressBar2->setGeometry(140, 200, 71, 271);
        progressBar2->setValue(0);
        progressBar2->setOrientation(Qt::Vertical);
        progressBar2->setAlignment(Qt::AlignCenter);
        progressBar2->setInvertedAppearance(true);

        // Layout to organize everything inside QGroupBox
        QVBoxLayout* mainLayout = new QVBoxLayout;
        mainLayout->addWidget(textContainer);
        mainLayout->addWidget(progressBar1);
        mainLayout->addWidget(progressBar2);

        planetGroupBox->setLayout(mainLayout);
        planetsLayout->addWidget(planetGroupBox);
        planetsInLayout->append(planetGroupBox);
    }
};

void DisplayInfoHandler::setPlanetLayout()
{
    window->setLayout(planetsLayout);
    myMainWindow->setCentralWidget(window);
};

bool DisplayInfoHandler::getIsWarDisplayed()
{
    return DisplayInfoHandler::isWarDisplayed;
};

void DisplayInfoHandler::setIsWarDisplayed()
{
    DisplayInfoHandler::isWarDisplayed = !DisplayInfoHandler::isWarDisplayed;
}

bool DisplayInfoHandler::getCurrentLayoutForm()
{
    return DisplayInfoHandler::layoutForm;
};

void DisplayInfoHandler::setCurrentLayoutForm(int choice)
{
    switch(choice)
    {
    case 0:
        DisplayInfoHandler::layoutForm = DisplayInfoHandler::CurrentLayoutForm::manuallySet;
        break;
    case 1:
        DisplayInfoHandler::layoutForm = DisplayInfoHandler::CurrentLayoutForm::automaticallySet;
        break;
    }
};

void DisplayInfoHandler::clearPlanetsDisplayed()
{
    planetsCurrentlyDisplayed.clear();
};

void DisplayInfoHandler::clearPlanetLayout()
{
    qDebug() << "called clearPlanetLayout";

    for(QGroupBox *planet : *planetsInLayout)
    {
        planetsLayout->removeWidget(planet);
        planet->hide();
        planet->deleteLater();
    }

    window->setLayout(planetsLayout);
    myMainWindow->setCentralWidget(window);
};
