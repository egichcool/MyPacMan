#ifndef PACMAN_H
#define PACMAN_H

#include <QGraphicsItem>

class Pacman : public QGraphicsItem
{
private:
    int pac_x;
    int pac_y;
    int direction;
    int nextdirection;
    int animestate;
    int animation_modify_factor;

    bool is_accelerated;

    QPixmap pacman_pixmap;

    QPixmap left1,left2,left3,left4;
    QPixmap up1,up2,up3,up4;
    QPixmap down1,down2,down3,down4;
    QPixmap right1,right2,right3,right4;

public:
    Pacman();

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void LoadPacmanImages();
    void advance();

    void setPac_X(int);
    void setPac_Y(int);
    void setDirection(int dir);
    void setNextDirection(int dir);

    int getPac_X() {return pac_x;}
    int getPac_Y() {return pac_y;}
    int getDirection() {return direction;}
    int getNextDirection() {return nextdirection;}
};

#endif // PACMAN_H
