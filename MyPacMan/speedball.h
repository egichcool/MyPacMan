#ifndef SPEEDBALL_H
#define SPEEDBALL_H

#include <QVector>
#include <QPoint>
#include <map.h>

class SpeedBall
{
private:
    int skin=1;
    QVector<QPoint> speedballpositions;
    QPoint speedballposition1;
    QPoint speedballposition2;
    QPoint speedballposition3;
    QPoint speedballposition4;
public:
    SpeedBall();
    void setSpeedballPositions();
    void CreateSpeedballPositions();
    QVector<QPoint> getSpeedBallPositions() {return speedballpositions;}
};

#endif // SPEEDBALL_H
