#include "display_info_handler.h"
#include <QLabel>
#include <QProgressBar>
#include <QGroupBox>
#include <QVBoxLayout>
#include "api_caller.h"


DisplayInfoHandler::DisplayInfoHandler(QMainWindow *mainWindow) : myMainWindow(mainWindow) {}

QSet<int> DisplayInfoHandler::planetsCurrentlyDisplayed;

bool DisplayInfoHandler::isWarDisplayed;

DisplayInfoHandler::CurrentLayoutForm DisplayInfoHandler::layoutForm;

bool DisplayInfoHandler::getIsPlanetDisplayed(const int& planetIndex)
{
    return planetsCurrentlyDisplayed.contains(planetIndex);
};

bool DisplayInfoHandler::setIsPlanetDisplayed(const int& planetIndex)
{
    if(!planetsCurrentlyDisplayed.contains(planetIndex))
    {
        planetsCurrentlyDisplayed.insert(planetIndex);
        return true;
    }
    return false;
};

void DisplayInfoHandler::addWarToCurrentLayout(API_Types::warInfoStructT& war){};

void DisplayInfoHandler::addPlanetToCurrentLayout(API_Types::warCampaignStructT& planet)
{
    if(!getIsPlanetDisplayed(planet.myPlanetIndex))
    {
        setIsPlanetDisplayed(planet.myPlanetIndex);
        QGroupBox* planetGroupBox = new QGroupBox(planet.myPlanetName, window);
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
    return isWarDisplayed;
};

void DisplayInfoHandler::setIsWarDisplayed()
{
    isWarDisplayed = !isWarDisplayed;
}

bool DisplayInfoHandler::getCurrentLayoutForm()
{
    return layoutForm;
};

void DisplayInfoHandler::setCurrentLayoutForm(const int& choice)
{
    switch(choice)
    {
    case 0:
        layoutForm = CurrentLayoutForm::manuallySet;
        break;
    case 1:
        layoutForm = CurrentLayoutForm::automaticallySet;
        break;
    }
};

void DisplayInfoHandler::clearPlanetsDisplayed()
{
    planetsCurrentlyDisplayed.clear();
};

void DisplayInfoHandler::clearPlanetLayout()
{
    qDebug() << "DisplayInfoHandler::clearPlanetLayout";

    for(QGroupBox *planet : *planetsInLayout)
    {
        planetsLayout->removeWidget(planet);
        delete planet;
    }
    planetsInLayout->clear();

    window->setLayout(planetsLayout);
    myMainWindow->setCentralWidget(window);
};
