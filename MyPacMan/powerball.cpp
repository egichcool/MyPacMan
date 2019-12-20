#include "powerball.h"
#include <QPoint>
#include <QVector>

PowerBall::PowerBall()
{
    QPoint powerballposition1 = QPoint(35,75);
    QPoint powerballposition2 = QPoint(579,75);
    QPoint powerballposition3 = QPoint(35,514);
    QPoint powerballposition4 = QPoint(579,514);

    powerballpositions.push_back(powerballposition1);
    powerballpositions.push_back(powerballposition2);
    powerballpositions.push_back(powerballposition3);
    powerballpositions.push_back(powerballposition4);
}

