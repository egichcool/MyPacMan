#ifndef POWERBALL_H
#define POWERBALL_H

#include <QVector>
#include <QPoint>
#include <map.h>

class PowerBall
{
private:
    int skin=1;
    QVector<QPoint> powerballpositions;
    QPoint powerballposition1;
    QPoint powerballposition2;
    QPoint powerballposition3;
    QPoint powerballposition4;
public:
    PowerBall();
    void setPowerballPositions();
    void CreatePowerballPositions();
    QVector<QPoint> getPowerBallPositions() {return powerballpositions;}
};

#endif // POWERBALL_H
