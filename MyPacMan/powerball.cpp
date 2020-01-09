#include "powerball.h"

PowerBall::PowerBall()
{
    setPowerballPositions();
}

void PowerBall::setPowerballPositions()
{
    powerballpositions.clear();
    this->skin=Map::s_getSkin();
    CreatePowerballPositions();
}

void PowerBall::CreatePowerballPositions()
{
    switch (skin)
    {
    case 0:
    case 1:
        powerballposition1 = QPoint(35,121);
        powerballposition2 = QPoint(579,121);
        powerballposition3 = QPoint(35,514);
        powerballposition4 = QPoint(579,514);
        break;
    case 2:
        powerballposition1 = QPoint(35,99);
        powerballposition2 = QPoint(579,99);
        powerballposition3 = QPoint(80,514);
        powerballposition4 = QPoint(514,514);
        break;
    case 3:
        powerballposition1 = QPoint(35,102);
        powerballposition2 = QPoint(580,102);
        powerballposition3 = QPoint(35,514);
        powerballposition4 = QPoint(580,514);
        break;
    }
    powerballpositions.push_back(powerballposition1);
    powerballpositions.push_back(powerballposition2);
    powerballpositions.push_back(powerballposition3);
    powerballpositions.push_back(powerballposition4);
}

