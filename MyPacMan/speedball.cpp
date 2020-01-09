#include "speedball.h"

SpeedBall::SpeedBall()
{
    setSpeedballPositions();
}

void SpeedBall::setSpeedballPositions()
{
    speedballpositions.clear();
    this->skin=Map::s_getSkin();
    CreateSpeedballPositions();
}

void SpeedBall::CreateSpeedballPositions()
{
    switch (skin)
    {
    case 0:
    case 1:
        speedballposition1 = QPoint(55,35);
        speedballposition2 = QPoint(559,35);
        speedballposition3 = QPoint(55,645);
        speedballposition4 = QPoint(559,645);
        break;
    case 2:
        speedballposition1 = QPoint(55,35);
        speedballposition2 = QPoint(559,35);
        speedballposition3 = QPoint(55,645);
        speedballposition4 = QPoint(559,645);
        break;
    case 3:
        speedballposition1 = QPoint(55,35);
        speedballposition2 = QPoint(559,35);
        speedballposition3 = QPoint(55,645);
        speedballposition4 = QPoint(559,645);
        break;
    }
    speedballpositions.push_back(speedballposition1);
    speedballpositions.push_back(speedballposition2);
    speedballpositions.push_back(speedballposition3);
    speedballpositions.push_back(speedballposition4);
}

