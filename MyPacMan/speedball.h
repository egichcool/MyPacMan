#ifndef SPEEDBALL_H
#define SPEEDBALL_H

#include <QVector>
#include <QPoint>

class SpeedBall
{
private:
    QVector<QPoint> speedballpositions;
public:
    SpeedBall();
    QVector<QPoint> getSpeedBallPositions() {return speedballpositions;}
};

#endif // SPEEDBALL_H
