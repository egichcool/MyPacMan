#include "map.h"

Map::Map()
{
    LoadMapImage();
    LoadMap();
}

QVector<QPoint> Map::s_pacman_paths;
int Map::s_skin=1;

void Map::LoadMap()
{
    pacman_paths.clear();
    switch(Map::s_skin)
    {
    case 0:
    case 1:
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

        break;
    case 2:
        //HORIZONTAL LINES
        //LINE 1
        CreatePathPoints(0, 35 ,145, 35);
        CreatePathPoints(208, 35, 406, 35);
        CreatePathPoints(470, 35, 614, 35);

        //LINE 2
        CreatePathPoints(35, 99, 276, 99);
        CreatePathPoints(338,99,580, 99);

        //LINE 3/3.5
        CreatePathPoints(100, 165, 208, 165);
        CreatePathPoints(406, 165, 514, 165);
        CreatePathPoints(276, 190, 338, 190);

        //LINE 4/4.5
        CreatePathPoints(35, 233, 145, 233);
        CreatePathPoints(470, 233, 580, 233);
        CreatePathPoints(208, 252, 406, 252);

        //LINE 5/5.5
        CreatePathPoints(35, 296, 145, 296);
        CreatePathPoints(470, 296, 580, 296);
        CreatePathPoints(145, 340, 208, 340);
        CreatePathPoints(406, 340, 470, 340);

        //LINE 6/6.5
        CreatePathPoints(35, 362, 80, 362);
        CreatePathPoints(534, 362, 580, 362);
        CreatePathPoints(208, 385, 406, 385);

        //LINE 7
        CreatePathPoints(80, 448, 254, 448);
        CreatePathPoints(360, 448, 534, 448);

        //LINE 8
        CreatePathPoints(0, 514, 145, 514);
        CreatePathPoints(208, 514, 406, 514);
        CreatePathPoints(470, 514, 614, 514);

        //LINE 9
        CreatePathPoints(35, 582, 80, 582);
        CreatePathPoints(145, 582, 276, 582);
        CreatePathPoints(338, 582, 470, 582);
        CreatePathPoints(534, 582, 580, 582);

        //LINE 10
        CreatePathPoints(35, 645, 580, 645);

        //VERTICAL LINES
        //LINE 1
        CreatePathPoints(35, 99, 35, 233);
        CreatePathPoints(35, 296, 35, 362);
        CreatePathPoints(35, 582, 35, 645);

        //LINE 2/2.5
        CreatePathPoints(80, 362, 80, 582);
        CreatePathPoints(100, 165, 100, 233);

        //LINE 3
        CreatePathPoints(145, 35, 145, 99);
        CreatePathPoints(145, 233, 145, 448);
        CreatePathPoints(145, 514, 145, 645);

        //LINE 4/4.5
        CreatePathPoints(208, 35, 208, 385);
        CreatePathPoints(208, 514, 208, 582);
        CreatePathPoints(254, 385, 254, 514);

        //LINE 5
        CreatePathPoints(276, 99, 276, 190);
        CreatePathPoints(276, 582, 276, 645);

        //LINE 6/6.5
        CreatePathPoints(338, 99, 338, 190);
        CreatePathPoints(338, 582, 338, 645);
        CreatePathPoints(360, 385, 360, 514);

        //LINE 7
        CreatePathPoints(406, 35, 406, 385);
        CreatePathPoints(406, 514, 406, 582);

        //LINE 8
        CreatePathPoints(470, 35, 470, 99);
        CreatePathPoints(470, 233, 470, 448);
        CreatePathPoints(470, 514, 470, 645);

        //LINE 9/9.5
        CreatePathPoints(514, 165, 514, 233);
        CreatePathPoints(534, 362, 534, 582);

        //LINE 10
        CreatePathPoints(580, 99, 580, 233);
        CreatePathPoints(580, 296, 580, 362);
        CreatePathPoints(580, 582, 580, 645);

        break;
    case 3:
        //HORIZONTAL LINES
        //LINE 1
        CreatePathPoints(35, 35, 142, 35);
        CreatePathPoints(208, 35, 404, 35);
        CreatePathPoints(470, 35, 580, 35);

        //LINE 2
        CreatePathPoints(35, 102, 580, 102);

        //LINE 3
        CreatePathPoints(0, 188, 76, 188);
        CreatePathPoints(142, 188, 273, 188);
        CreatePathPoints(339, 188, 470, 188);
        CreatePathPoints(536, 188, 614, 188);

        //LINE 4
        CreatePathPoints(76, 252, 536, 252);

        //LINE 5
        CreatePathPoints(142, 318, 208, 318);
        CreatePathPoints(404, 318, 470, 318);

        //LINE 6
        CreatePathPoints(0, 384, 142, 384);
        CreatePathPoints(208, 384, 404, 384);
        CreatePathPoints(470, 384, 614, 384);

        //LINE 7
        CreatePathPoints(76, 450, 273, 450);
        CreatePathPoints(339, 450, 536, 450);

        //LINE 8
        CreatePathPoints(35, 514, 580, 514);

        //LINE 9
        CreatePathPoints(208, 582, 273, 582);
        CreatePathPoints(339, 582, 404, 582);

        //LINE 10
        CreatePathPoints(35, 645, 580, 645);

        //VERTICAL LINES
        //LINE 1
        CreatePathPoints(35, 35, 35, 102);
        CreatePathPoints(35, 514, 35, 645);

        //LINE 2
        CreatePathPoints(76, 102, 76, 514);

        //LINE 3
        CreatePathPoints(142, 35, 142, 188);
        CreatePathPoints(142, 318, 142, 384);
        CreatePathPoints(142, 514, 142, 645);

        //LINE 4
        CreatePathPoints(208, 35, 208, 102);
        CreatePathPoints(208, 188, 208, 384);
        CreatePathPoints(208, 450, 208, 514);
        CreatePathPoints(208, 582, 208, 645);

        //LINE 5
        CreatePathPoints(273, 102, 273, 188);
        CreatePathPoints(273, 384, 273, 450);
        CreatePathPoints(273, 514, 273, 582);

        //LINE 6
        CreatePathPoints(339, 102, 339, 188);
        CreatePathPoints(339, 384, 339, 450);
        CreatePathPoints(339, 514, 339, 582);

        //LINE 7
        CreatePathPoints(404, 35, 404, 102);
        CreatePathPoints(404, 188, 404, 384);
        CreatePathPoints(404, 450, 404, 514);
        CreatePathPoints(404, 582, 404, 645);

        //LINE 8
        CreatePathPoints(470, 35, 470, 188);
        CreatePathPoints(470, 318, 470, 384);
        CreatePathPoints(470, 514, 470, 645);

        //LINE 9
        CreatePathPoints(536, 102, 536, 514);

        //LINE 10
        CreatePathPoints(580, 35, 580, 102);
        CreatePathPoints(580, 514, 580, 645);

        break;
    }
    Map::s_pacman_paths=this->pacman_paths;
}

void Map::LoadMapImage()
{
    switch(Map::s_skin)
    {
    case 0:  map_background_picture.load(":/images/pac_map.png");
        break;
    case 1:  map_background_picture.load(":/images/pac_map2.png");
        break;
    case 2: map_background_picture.load(":/images/pac_map3.png");
        break;
    case 3: map_background_picture.load(":/images/pac_map4.png");
    }
}

QRectF Map::boundingRect() const //sets map bounding rect which will be updated and redrawn every timer cycle
{
    return QRect(0,0,map_width,map_hight);
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
