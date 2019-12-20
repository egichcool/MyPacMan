#include "speedball.h"
#include <QPoint>
#include <QVector>

SpeedBall::SpeedBall()
{
    QPoint speedballposition1 = QPoint(55,35);
    QPoint speedballposition2 = QPoint(559,35);
    QPoint speedballposition3 = QPoint(55,645);
    QPoint speedballposition4 = QPoint(559,645);

    speedballpositions.push_back(speedballposition1);
    speedballpositions.push_back(speedballposition2);
    speedballpositions.push_back(speedballposition3);
    speedballpositions.push_back(speedballposition4);
}

