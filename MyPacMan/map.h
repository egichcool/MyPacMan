#ifndef MAP_H
#define MAP_H

#include <QVector>
#include <QPixmap>

class Map
{
private:
    QPixmap map_background_picture;
    QVector<QPoint> pacman_paths;
    static QVector<QPoint> s_pacman_paths;
    static int s_skin;
    const int map_width=614;
    const int map_hight=740;


public:
    Map();
    void CreatePathPoints(int x_begin, int y_begin, int x_end, int y_end);
    void DeletePathPoints();
    void LoadMap();
    void LoadMapImage();
    bool IsPointAvailable(QPoint);
    QRectF boundingRect() const;

    QPixmap getMap_Background_Picture() {return map_background_picture;}
    QVector<QPoint> getPacmanPaths() {return  pacman_paths;}
    static QVector<QPoint> s_getPacmanPaths() {return  s_pacman_paths;}
    static void s_setSkin(int skin) {Map::s_skin=skin;}
    static int s_getSkin() {return s_skin;}


    ~Map();
};

#endif // MAP_H
