#ifndef FOODBALL_H
#define FOODBALL_H

#include <QVector>
#include <QPoint>
#include <map.h>

class FoodBall
{
private:
    int foodballcount;
    QVector<QPoint> foodballpositions;
    QVector<QPoint> pacmanmapforreference;
    Map referencemap;
    int x=10;
    int y=10;
    int skin=1;
    int* vertical_lines_x= new int;
    int* horizontal_lines_y= new int;
public:
    FoodBall();
    void SetFoodBallPositions();
    QVector<QPoint> getFoodBallPositions() {return foodballpositions;}
    void CreateFoodballPositionsVector();
};

#endif // FOODBALL_H
