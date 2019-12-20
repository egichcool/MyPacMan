#ifndef MAP_H
#define MAP_H

#include <QVector>
#include <QPixmap>

class Map
{
private:
    QPixmap map_background_picture;
    QVector<QPoint> pacman_paths;
    int skin=0;

public:
    Map();
    void CreatePathPoints(int x_begin, int y_begin, int x_end, int y_end);
    void setskin(int skin);
    void LoadMapImage();
    bool IsPointAvailable(QPoint);
    QRectF boundingRect() const;

    QPixmap getMap_Background_Picture() {return map_background_picture;}
    QVector<QPoint> getPacmanPaths() {return pacman_paths;}

    ~Map();
};

#endif // MAP_H
