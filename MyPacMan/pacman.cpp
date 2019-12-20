#include "map.h"
#include "pacman.h"
#include <QGraphicsPixmapItem>
#include <QPainter>

Pacman::Pacman()
{
    animestate = 0;
    animation_modify_factor = 6;
    LoadPacmanImages();
}

QRectF Pacman::boundingRect() const
{
    return QRect(pac_x-15, pac_y-15, 20, 20);
}

void Pacman::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    switch(direction)
    {
        case 1:
            if(animestate<2*animation_modify_factor)
            {
                painter->drawPixmap(pac_x-15,pac_y-15,30,30,left1);
            }
            else if(animestate<4*animation_modify_factor)
            {
                painter->drawPixmap(pac_x-15,pac_y-15,30,30,left2);
            }
            else if(animestate<6*animation_modify_factor)
            {
                painter->drawPixmap(pac_x-15,pac_y-15,30,30,left3);
            }
            else if(animestate<8*animation_modify_factor)
            {
                painter->drawPixmap(pac_x-15,pac_y-15,30,30,left4);
            }
            break;
        case 4:
            if(animestate<2*animation_modify_factor)
            {
                painter->drawPixmap(pac_x-15,pac_y-15,30,30,right1);
            }
            else if(animestate<4*animation_modify_factor)
            {
                painter->drawPixmap(pac_x-15,pac_y-15,30,30,right2);
            }
            else if(animestate<6*animation_modify_factor)
            {
                painter->drawPixmap(pac_x-15,pac_y-15,30,30,right3);
            }
            else if(animestate<8*animation_modify_factor)
            {
                painter->drawPixmap(pac_x-15,pac_y-15,30,30,right4);
            }
            break;
        case 3:
            if(animestate<2*animation_modify_factor)
            {
                painter->drawPixmap(pac_x-15,pac_y-15,30,30,down1);
            }
            else if(animestate<4*animation_modify_factor)
            {
                painter->drawPixmap(pac_x-15,pac_y-15,30,30,down2);
            }
            else if(animestate<6*animation_modify_factor)
            {
                painter->drawPixmap(pac_x-15,pac_y-15,30,30,down3);
            }
            else if(animestate<8*animation_modify_factor)
            {
                painter->drawPixmap(pac_x-15,pac_y-15,30,30,down4);
            }
            break;
        case 2:
            if(animestate<2*animation_modify_factor)
            {
                painter->drawPixmap(pac_x-15,pac_y-15,30,30,up1);
            }
            else if(animestate<4*animation_modify_factor)
            {
                painter->drawPixmap(pac_x-15,pac_y-15,30,30,up2);
            }
            else if(animestate<6*animation_modify_factor)
            {
                painter->drawPixmap(pac_x-15,pac_y-15,30,30,up3);
            }
            else if(animestate<8*animation_modify_factor)
            {
                painter->drawPixmap(pac_x-15,pac_y-15,30,30,up4);
            }
            break;
    }
}

void Pacman::advance()
{
    if(animestate>8*animation_modify_factor-2)
    {
        animestate=0;
    }
    else
    {
        animestate++;
    }
}

void Pacman::LoadPacmanImages()
{
    right1.load(":/pacman/images/pacman_images/pacclose.png");
    right2.load(":/pacman/images/pacman_images/pacopen1.png");
    right3.load(":/pacman/images/pacman_images/pacopen2.png");
    right4.load(":/pacman/images/pacman_images/pacopen3.png");

    up1.load(":/pacman/images/pacman_images/paccloseu.png");
    up2.load(":/pacman/images/pacman_images/pacopen1u.png");
    up3.load(":/pacman/images/pacman_images/pacopen2u.png");
    up4.load(":/pacman/images/pacman_images/pacopen3u.png");

    down1.load(":/pacman/images/pacman_images/pacclosed.png");
    down2.load(":/pacman/images/pacman_images/pacopen1d.png");
    down3.load(":/pacman/images/pacman_images/pacopen2d.png");
    down4.load(":/pacman/images/pacman_images/pacopen3d.png");

    left1.load(":/pacman/images/pacman_images/pacclosel.png");
    left2.load(":/pacman/images/pacman_images/pacopen1l.png");
    left3.load(":/pacman/images/pacman_images/pacopen2l.png");
    left4.load(":/pacman/images/pacman_images/pacopen3l.png");
}

void Pacman::setPac_X(int x)
{
    pac_x=x;
}

void Pacman::setPac_Y(int y)
{
    pac_y=y;
}

void Pacman::setDirection(int dir)
{
    direction=dir;
}

void Pacman::setNextDirection(int dir)
{
    nextdirection=dir;
}
