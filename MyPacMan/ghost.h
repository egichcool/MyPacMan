#ifndef GHOST_H
#define GHOST_H
#include <QGraphicsItem>
#include <QPainter>
#include <QString>

class Ghost : public QGraphicsItem
{
private:
    QPixmap ghost_pixmap;
    QPixmap ghost_scared_blue;
    QPixmap ghost_scared_white;
    
    QPixmap left1,left2;
    QPixmap up1,up2;
    QPixmap down1,down2;
    QPixmap right1,right2;
    QPixmap scaredblue, scaredblue1;
    QPixmap scaredwhite, scaredwhite1;
    
    bool is_scared;
    bool scared_white;
    bool hidden;
    
    int animestate;
    int animation_modify_factor;
    
    int ghost_x,ghost_y;
    int ghostdirection;
    int nextghostdirection;
    
    int skin=0;
    
    QString image[2][36]= {
        {":/ghosts/images/ghost_images/ghostright1.png",
         ":/ghosts/images/ghost_images/ghostright2.png",
         ":/ghosts/images/ghost_images/ghostup1.png",
         ":/ghosts/images/ghost_images/ghostup2.png",
         ":/ghosts/images/ghost_images/ghostdown1.png",
         ":/ghosts/images/ghost_images/ghostdown2.png",
         ":/ghosts/images/ghost_images/ghostleft1.png",
         ":/ghosts/images/ghost_images/ghostleft2.png",
         ":/ghosts/images/ghost_images/ghostscaredblue1.png",
         ":/ghosts/images/ghost_images/ghostscaredblue2.png",
         ":/ghosts/images/ghost_images/ghostscaredwhite1.png",
         ":/ghosts/images/ghost_images/ghostscaredwhite2.png",
         ":/ghosts/images/ghost_images/ghostrightblue1.png",
         ":/ghosts/images/ghost_images/ghostrightblue2.png",
         ":/ghosts/images/ghost_images/ghostupblue1.png",
         ":/ghosts/images/ghost_images/ghostupblue2.png",
         ":/ghosts/images/ghost_images/ghostdownblue1.png",
         ":/ghosts/images/ghost_images/ghostdownblue2.png",
         ":/ghosts/images/ghost_images/ghostleftblue1.png",
         ":/ghosts/images/ghost_images/ghostleftblue2.png",
         ":/ghosts/images/ghost_images/ghostrightorange1.png",
         ":/ghosts/images/ghost_images/ghostrightorange2.png",
         ":/ghosts/images/ghost_images/ghostuporange1.png",
         ":/ghosts/images/ghost_images/ghostuporange2.png",
         ":/ghosts/images/ghost_images/ghostdownorange1.png",
         ":/ghosts/images/ghost_images/ghostdownorange2.png",
         ":/ghosts/images/ghost_images/ghostleftorange1.png",
         ":/ghosts/images/ghost_images/ghostleftorange2.png",
         ":/ghosts/images/ghost_images/ghostrightred1.png",
         ":/ghosts/images/ghost_images/ghostrightred2.png",
         ":/ghosts/images/ghost_images/ghostupred1.png",
         ":/ghosts/images/ghost_images/ghostupred2.png",
         ":/ghosts/images/ghost_images/ghostdownred1.png",
         ":/ghosts/images/ghost_images/ghostdownred2.png",
         ":/ghosts/images/ghost_images/ghostleftred1.png",
         ":/ghosts/images/ghost_images/ghostleftred2.png"},
        
        {":/ghosts_neon/images/ghost2_images/ghostright1.png",
         ":/ghosts_neon/images/ghost2_images/ghostright2.png",
         ":/ghosts_neon/images/ghost2_images/ghostup1.png",
         ":/ghosts_neon/images/ghost2_images/ghostup2.png",
         ":/ghosts_neon/images/ghost2_images/ghostdown1.png",
         ":/ghosts_neon/images/ghost2_images/ghostdown2.png",
         ":/ghosts_neon/images/ghost2_images/ghostleft1.png",
         ":/ghosts_neon/images/ghost2_images/ghostleft2.png",
         ":/ghosts_neon/images/ghost2_images/ghostscaredblue1.png",
         ":/ghosts_neon/images/ghost2_images/ghostscaredblue2.png",
         ":/ghosts_neon/images/ghost2_images/ghostscaredwhite1.png",
         ":/ghosts_neon/images/ghost2_images/ghostscaredwhite2.png",
         ":/ghosts_neon/images/ghost2_images/ghostrightblue1.png",
         ":/ghosts_neon/images/ghost2_images/ghostrightblue2.png",
         ":/ghosts_neon/images/ghost2_images/ghostupblue1.png",
         ":/ghosts_neon/images/ghost2_images/ghostupblue2.png",
         ":/ghosts_neon/images/ghost2_images/ghostdownblue1.png",
         ":/ghosts_neon/images/ghost2_images/ghostdownblue2.png",
         ":/ghosts_neon/images/ghost2_images/ghostleftblue1.png",
         ":/ghosts_neon/images/ghost2_images/ghostleftblue2.png",
         ":/ghosts_neon/images/ghost2_images/ghostrightorange1.png",
         ":/ghosts_neon/images/ghost2_images/ghostrightorange2.png",
         ":/ghosts_neon/images/ghost2_images/ghostuporange1.png",
         ":/ghosts_neon/images/ghost2_images/ghostuporange2.png",
         ":/ghosts_neon/images/ghost2_images/ghostdownorange1.png",
         ":/ghosts_neon/images/ghost2_images/ghostdownorange2.png",
         ":/ghosts_neon/images/ghost2_images/ghostleftorange1.png",
         ":/ghosts_neon/images/ghost2_images/ghostleftorange2.png",
         ":/ghosts_neon/images/ghost2_images/ghostrightred1.png",
         ":/ghosts_neon/images/ghost2_images/ghostrightred2.png",
         ":/ghosts_neon/images/ghost2_images/ghostupred1.png",
         ":/ghosts_neon/images/ghost2_images/ghostupred2.png",
         ":/ghosts_neon/images/ghost2_images/ghostdownred1.png",
         ":/ghosts_neon/images/ghost2_images/ghostdownred2.png",
         ":/ghosts_neon/images/ghost2_images/ghostleftred1.png",
         ":/ghosts_neon/images/ghost2_images/ghostleftred2.png"}
    };
    
public:
    Ghost();
    QRectF boundingRect() const;
    void setskin(int skin);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void advance();
    
    void setGhost_X(int);
    void setGhost_Y(int);
    void setIsScared(bool option) {is_scared=option;}
    void setScaredWhite(bool option) {scared_white=option;}
    void setGhostDirection(int dir) {ghostdirection=dir;}
    void setNextGhostDirection(int dir) {nextghostdirection=dir;}
    void setGhostColor(QString col);
    
    int getGhost_X() {return ghost_x;}
    int getGhost_Y() {return ghost_y;}
    int getGhostDirection() {return ghostdirection;}
    int getNextGhostDirection() {return nextghostdirection;}
    bool getIsScared() {return is_scared;}
    bool getScaredWhite() {return scared_white;}
};

#endif // GHOST_H
