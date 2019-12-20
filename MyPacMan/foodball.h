#ifndef FOODBALL_H
#define FOODBALL_H

#include <QVector>
#include <QPoint>

class FoodBall
{
private:
    int foodballcount;
    QVector<QPoint> foodballpositions;
    QVector<QPoint> pacmanmapforreference;
public:
    FoodBall();
    QVector<QPoint> getFoodBallPositions() {return foodballpositions;}
    void CreateFoodballPositionsVector();
};

#endif // FOODBALL_H
