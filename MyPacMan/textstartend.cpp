#include "textstartend.h"

TextStartEnd::TextStartEnd()
{
    game_won=false;
    game_lost=false;

    w=600;
    h=200;
    x=614/2-w/2;
    y=714/2-h/2;

    score=0;
    playing=false;
}

QRectF TextStartEnd::boundingRect() const
{
    return QRect(x, y, w, h);
}

void TextStartEnd::setScore(int _score)
{
    this -> score = _score;
}

void TextStartEnd::setGameWon(bool _game_won)
{
    this -> game_won = _game_won;
}

void TextStartEnd::setGameLost(bool _game_lost)
{
    this -> game_lost = _game_lost;
}

void TextStartEnd::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPen pen_red(Qt::red);
    QPen pen_yellow(Qt::yellow);
    QPen pen_blue(Qt::blue);
    painter->setPen(pen_red);
    QFont font = painter->font();
    font.setPointSize (30);
    painter->setFont(font);

    if(!playing)
    {
        if(game_won)
        {
            painter->setPen(pen_yellow);
            painter->drawText(boundingRect(),Qt::AlignTop | Qt::AlignHCenter,"CONGRATULATIONS");
            painter->drawText(boundingRect(),Qt::AlignCenter, "FINAL SCORE : "+QString::number(score));
            painter->setPen(pen_blue);
            painter->drawText(boundingRect(),Qt::AlignBottom | Qt::AlignHCenter,"PRESS SPACE TO RESTART");
        }
        else if(game_lost)
        {
            painter->setPen(pen_red);
            painter->drawText(boundingRect(),Qt::AlignTop | Qt::AlignHCenter,"YOU LOST, GAME OVER");
            painter->setPen(pen_yellow);
            painter->drawText(boundingRect(),Qt::AlignCenter, "FINAL SCORE : "+QString::number(score));
            painter->setPen(pen_blue);
            painter->drawText(boundingRect(),Qt::AlignBottom | Qt::AlignHCenter,"PRESS SPACE TO RESTART");
        }
        else
        {
            painter->drawText(boundingRect(),Qt::AlignCenter, "PRESS SPACE TO START");
        }
    }
}
