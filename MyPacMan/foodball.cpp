#include "foodball.h"

FoodBall::FoodBall()
{
    SetFoodBallPositions();

}

void FoodBall::SetFoodBallPositions()
{    
    pacmanmapforreference.clear();
    pacmanmapforreference = Map::s_getPacmanPaths();

    this->skin=Map::s_getSkin();

    foodballcount=0;
    CreateFoodballPositionsVector();

}

void FoodBall::CreateFoodballPositionsVector()
{
    foodballpositions.clear();

    switch(skin)
    {
    case 0:
    case 1:
        vertical_lines_x= new int[x] {35,79,144,209,274,340,406,470,536,579};
        horizontal_lines_y= new int[y] {35,121,187,252,318,384,449,514,580,645};
        break;
    case 2:
        vertical_lines_x= new int[x] {35,80,145,208,276,338,406,470,514,580};
        horizontal_lines_y= new int[y] {35,99,165,233,296,362,448,514,582,645};
        break;
    case 3:
        vertical_lines_x= new int[x] {35,76,142,208,273,339,404,470,536,580};
        horizontal_lines_y= new int[y] {35,102,188,252,318,384,450,514,582,645};
        break;


    }

    for(int i=0;i<x;i++)
    {
        for(int j=0;j<y;j++)
        {
            if(pacmanmapforreference.contains(QPoint(vertical_lines_x[i],horizontal_lines_y[j])))
            {
                foodballpositions.push_back(QPoint(vertical_lines_x[i],horizontal_lines_y[j]));
            }
        }
    }

    // Create a new vector without the duplicates
    QVector<QPoint> unique_foodballpositions;

    for (QVector<QPoint>::iterator iter = foodballpositions.begin(); iter != foodballpositions.end();iter++)
    {
        if(std::find(unique_foodballpositions.begin(),unique_foodballpositions.end(), *iter)==unique_foodballpositions.end())
        {
            unique_foodballpositions.push_back(*iter);
            foodballcount++;
        }
    }
    foodballpositions.swap(unique_foodballpositions);
    delete vertical_lines_x;
    delete horizontal_lines_y;
}
