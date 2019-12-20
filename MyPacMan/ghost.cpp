#include "ghost.h"

Ghost::Ghost()
{
    animestate = 0;
    animation_modify_factor = 6;

    ghostdirection=1;
    is_scared=false;
    scared_white=false;

}

QRectF Ghost::boundingRect() const
{
    return QRect(ghost_x-15,ghost_y-15,20,20);
}

void Ghost::setskin(int skin)
{
    this->skin=skin;
}

void Ghost::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if(!is_scared)
    {
        switch(ghostdirection)
        {
            case 1:
                if(animestate==0)
                {
                    painter->drawPixmap(ghost_x-15,ghost_y-15,30,30,left1);
                }
                else
                {
                    painter->drawPixmap(ghost_x-15,ghost_y-15,30,30,left2);
                }
                break;
            case 4:
                if(animestate==0)
                {
                    painter->drawPixmap(ghost_x-15,ghost_y-15,30,30,right1);
                }
                else
                {
                    painter->drawPixmap(ghost_x-15,ghost_y-15,30,30,right2);
                }
                break;
            case 3:
                if(animestate==0)
                {
                    painter->drawPixmap(ghost_x-15,ghost_y-15,30,30,down1);
                }
                else
                {
                    painter->drawPixmap(ghost_x-15,ghost_y-15,30,30,down2);
                }
                break;
            case 2:
                if(animestate==0)
                {
                    painter->drawPixmap(ghost_x-15,ghost_y-15,30,30,up1);
                }
                else
                {
                    painter->drawPixmap(ghost_x-15,ghost_y-15,30,30,up2);
                }
                break;
        }
    }
    else
    {
        if(scared_white)
        {
            if(animestate==0)
            {
                painter->drawPixmap(ghost_x-15,ghost_y-15,30,30,scaredwhite);
            }
            else
            {
                painter->drawPixmap(ghost_x-15,ghost_y-15,30,30,scaredwhite1);
            }
        }
        else
        {
            if(animestate==0)
            {
                painter->drawPixmap(ghost_x-15,ghost_y-15,30,30,scaredblue);
            }
            else
            {
                painter->drawPixmap(ghost_x-15,ghost_y-15,30,30,scaredblue1);
            }
        }
    }
}


void Ghost::advance()
{
    if(animestate>2)
    {
        animestate=0;
    }
    else
    {
        animestate++;
    }
}

void Ghost::setGhost_X(int x)
{
    ghost_x=x;
}

void Ghost::setGhost_Y(int y)
{
    ghost_y=y;
}

void Ghost::setGhostColor(QString col)
{    
    scaredblue.load(image[skin][8]);
    scaredblue1.load(image[skin][9]);
    scaredwhite.load(image[skin][10]);
    scaredwhite1.load(image[skin][11]);
    if(col=="pink")
    {
        right1.load(image[skin][0]);
        right2.load(image[skin][1]);
        up1.load(image[skin][2]);
        up2.load(image[skin][3]);
        down1.load(image[skin][4]);
        down2.load(image[skin][5]);
        left1.load(image[skin][6]);
        left2.load(image[skin][7]);
    }
    if(col=="blue")
    {
        right1.load(image[skin][12]);
        right2.load(image[skin][13]);
        up1.load(image[skin][14]);
        up2.load(image[skin][15]);
        down1.load(image[skin][16]);
        down2.load(image[skin][17]);
        left1.load(image[skin][18]);
        left2.load(image[skin][19]);
    }
    else if(col=="orange")
    {
        right1.load(image[skin][20]);
        right2.load(image[skin][21]);
        up1.load(image[skin][22]);
        up2.load(image[skin][23]);
        down1.load(image[skin][24]);
        down2.load(image[skin][25]);
        left1.load(image[skin][26]);
        left2.load(image[skin][27]);
    }
    else if(col=="red")
    {
        right1.load(image[skin][28]);
        right2.load(image[skin][29]);
        up1.load(image[skin][30]);
        up2.load(image[skin][31]);
        down1.load(image[skin][32]);
        down2.load(image[skin][33]);
        left1.load(image[skin][34]);
        left2.load(image[skin][35]);
    }
}
