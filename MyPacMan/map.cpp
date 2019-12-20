#include "map.h"

Map::Map()
{
    LoadMapImage();

    //HORIZONTAL LINES
    //LINE 1
    CreatePathPoints(35, 35, 274, 35);
    CreatePathPoints(340, 35, 579, 35);

    //LINE 2
    CreatePathPoints(35, 121, 579, 121);

    //LINE 3
    CreatePathPoints(35, 187, 144, 187);
    CreatePathPoints(209, 187, 274, 187);
    CreatePathPoints(340, 187, 406, 187);
    CreatePathPoints(470, 187, 579, 187);

    //LINE 4
    CreatePathPoints(209, 252, 406, 252);

    //LINE 5 - MIDDLE LINE
    CreatePathPoints(0, 318, 209, 318);
    CreatePathPoints(406, 318, 614, 318);

    //LINE 6
    CreatePathPoints(209, 384,406, 384);

    //LINE 7
    CreatePathPoints(35, 449, 274, 449);
    CreatePathPoints(340, 449, 579, 449);

    //LINE 8
    CreatePathPoints(35, 514, 79, 514);
    CreatePathPoints(144, 514, 470, 514);
    CreatePathPoints(536, 514, 579, 514);

    //LINE 9
    CreatePathPoints(35, 580, 144, 580);
    CreatePathPoints(209, 580, 274, 580);
    CreatePathPoints(340, 580, 406, 580);
    CreatePathPoints(470, 580, 579, 580);

    //LINE 10
    CreatePathPoints(35, 645, 579, 645);

    //VERTICAL LINES
    //LINE 1
    CreatePathPoints(35, 35, 35, 187);
    CreatePathPoints(35, 449, 35, 514);
    CreatePathPoints(35, 580, 35, 645);

    //LINE 2
    CreatePathPoints(79, 514, 79, 580);

    //LINE 3
    CreatePathPoints(144, 35, 144, 580);

    //LINE 4
    CreatePathPoints(209, 121, 209, 187);
    CreatePathPoints(209, 252, 209, 449);
    CreatePathPoints(209, 514, 209, 580);

    //LINE 5
    CreatePathPoints(274, 35, 274, 121);
    CreatePathPoints(274, 187, 274, 252);
    CreatePathPoints(274, 449, 274, 514);
    CreatePathPoints(274, 580, 274, 645);

    //LINE 6
    CreatePathPoints(340, 35, 340, 121);
    CreatePathPoints(340, 187, 340, 252);
    CreatePathPoints(340, 449, 340, 514);
    CreatePathPoints(340, 580, 340, 645);

    //LINE 7
    CreatePathPoints(406, 121, 406, 187);
    CreatePathPoints(406, 252, 406, 449);
    CreatePathPoints(406, 514, 406, 580);

    //LINE 8
    CreatePathPoints(470, 35, 470, 580);

    //LINE 9
    CreatePathPoints(536, 514, 536, 580);

    //LINE 10
    CreatePathPoints(579, 35, 579, 187);
    CreatePathPoints(579, 449, 579, 514);
    CreatePathPoints(579, 580, 579, 645);
}

void Map::setskin(int skin)
{
    this->skin=skin;
}

void Map::LoadMapImage()
{
    switch(skin)
    {
    case 0:  map_background_picture.load(":/images/pac_map.png");
    break;
    case 1:  map_background_picture.load(":/images/pac_map2.png");
    }
}

QRectF Map::boundingRect() const //sets map bounding rect which will be updated and redrawn every timer cycle
{
    return QRect(0,0,614,740);
}

void Map::CreatePathPoints(int x_begin, int y_begin, int x_end, int y_end) //only left-right and up-down lines
{
    QPoint p;

    if (x_begin == x_end) //vertical line condition
    {
        if (y_begin < y_end) //vertical line from y_begin to y_end
        {
            for (int y=y_begin; y<=y_end; y++)
            {
                p.setX(x_begin);
                p.setY(y);
                if (! pacman_paths.contains(p))
                {
                    pacman_paths.push_front(p);
                }
            }
        }

        else if(y_begin==y_end) //single point
        {
                p.setX(x_begin);
                p.setY(y_begin);
                if (! pacman_paths.contains(p))
                {
                    pacman_paths.push_front(p);
                }
        }
    }

    if (y_begin == y_end) //horizontal line condition
    {
        if (x_begin < x_end) //horizontal line from x_begin to x_end
        {
            for (int x=x_begin; x<=x_end; x++)
            {
                p.setX(x);
                p.setY(y_begin);
                if (! pacman_paths.contains(p))
                {
                    pacman_paths.push_front(p);
                }
            }
        }
        else //single point
        {
                p.setX(x_begin);
                p.setY(y_begin);
                if (! pacman_paths.contains(p))
                {
                    pacman_paths.push_front(p);
                }
        }
    }
}

bool Map::IsPointAvailable(QPoint point) //checks if given point is accessible for Pacman (is present in pacman_paths vector)
{
    for(int i=0;i<pacman_paths.size();i++)
    {
        if(pacman_paths.at(i)==point)
        {
             return true;
        }
    }
    return false;
}

Map::~Map()
{
}
