#include "display_info_handler.h"
#include <QLabel>
#include <QProgressBar>
#include <QGroupBox>
#include <QVBoxLayout>
#include "api_caller.h"


DisplayInfoHandler::DisplayInfoHandler(QMainWindow *mainWindow) : myMainWindow(mainWindow)
{
    window = new QWidget;

    mainVLayout = new QVBoxLayout;
    warLayout = new QHBoxLayout;
    planetsLayout = new QHBoxLayout;
    planetsInLayout = new QVector<QGroupBox*>();

    mainVLayout->addLayout(warLayout);
    mainVLayout->addLayout(planetsLayout);

    window->setLayout(mainVLayout);
    myMainWindow->setCentralWidget(window);
}

QSet<int> DisplayInfoHandler::planetsCurrentlyDisplayed;
bool DisplayInfoHandler::isWarDisplayed  = false;

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

void DisplayInfoHandler::addPlanetToCurrentLayout(API_Types::planetStructT& planet)
{
    if(!getIsPlanetDisplayed(planet.myPlanetIndex))
    {
        setIsPlanetDisplayed(planet.myPlanetIndex);
        QGroupBox* planetGroupBox = new QGroupBox(planet.myPlanetName, window);

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

        QHBoxLayout* progressBarlayout = new QHBoxLayout;
        progressBarlayout->addWidget(progressBar1);
        progressBarlayout->addWidget(progressBar2);

        // Layout to organize everything inside QGroupBox
        QVBoxLayout* mainLayout = new QVBoxLayout;
        mainLayout->addWidget(textContainer);
        mainLayout->addLayout(progressBarlayout);

        planetGroupBox->setLayout(mainLayout);
        planetsLayout->setSizeConstraint(QLayout::SetMaximumSize);
        planetsLayout->addWidget(planetGroupBox);
        planetsInLayout->append(planetGroupBox);
    }
};

void DisplayInfoHandler::addWarToCurrentLayout(API_Types::warInfoStructT& war)
{
    if(!getIsPlanetDisplayed(war.myWarId))
    {
        setIsWarDisplayed();

        QGroupBox* warGroupBox = new QGroupBox("Current War", window);
        warGroupBox->setFixedSize(QSize(700, 60));

        // Create layout for labels
        QHBoxLayout* textLayout = new QHBoxLayout;
        QLabel* warIdLabel = new QLabel("War ID: " + QString::number(war.myWarId));

        QDateTime warStartTime = QDateTime::fromSecsSinceEpoch(war.myStartDate, Qt::UTC);
        QLabel* warStartLabel = new QLabel("War start: " + warStartTime.toString(Qt::ISODate));

        QDateTime warEndTime = QDateTime::fromSecsSinceEpoch(war.myEndDate, Qt::UTC);
        QLabel* warEndLabel = new QLabel("War End: " + warEndTime.toString(Qt::ISODate));

        QDateTime warTotalTime = QDateTime::fromSecsSinceEpoch(war.myEndDate - war.myStartDate, Qt::UTC);
        QLabel* totalTimeLabel = new QLabel("Total WarTime: " + warEndTime.toString(Qt::ISODate));

        textLayout->addStretch(1);
        textLayout->addWidget(warIdLabel);
        textLayout->addStretch(1);
        textLayout->addWidget(warStartLabel);
        textLayout->addStretch(1);
        textLayout->addWidget(warEndLabel);
        textLayout->addStretch(1);
        textLayout->addWidget(totalTimeLabel);

        warGroupBox->setLayout(textLayout);

        warLayout->setAlignment(Qt::AlignTop | Qt::AlignLeft);
        warLayout->setSizeConstraint(QLayout::SetMaximumSize);
        warLayout->addWidget(warGroupBox);
    }
};

bool DisplayInfoHandler::getIsWarDisplayed()
{
    return isWarDisplayed;
};

void DisplayInfoHandler::setIsWarDisplayed()
{
    isWarDisplayed = !isWarDisplayed;
}


void DisplayInfoHandler::clearAllPlanetsDisplayed()
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

void DisplayInfoHandler::clearWarLayout()
{
    qDebug() << "DisplayInfoHandler::clearWarLayout";
    if(isWarDisplayed)
    {
        QLayoutItem* warLayoutItem = warLayout->takeAt(0);
        delete warLayoutItem->widget();
        delete warLayoutItem;
        setIsWarDisplayed();
    }
};
