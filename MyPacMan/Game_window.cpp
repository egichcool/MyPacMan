#include "Game_window.h"
#include "ui_Game_window.h"
#include "map.h"
#include "powerball.h"
#include "speedball.h"
#include <QGraphicsScene>

Game_window::Game_window(QWidget *parent) : QDialog(parent),ui(new Ui::Game_window)
{
    ui->setupUi(this);
    scene.setParent(this);
    ui->gameplay_area->setScene(&scene);
    ui->gameplay_area->setRenderHint(QPainter::Antialiasing);
    scene.setSceneRect(0,0,614,740);
    ui->gameplay_area->setSceneRect(scene.sceneRect());

    GenerateAndPopulateMap();
    GenerateAndPlacePacman();
    GenerateAndPlaceGhosts();

    ShowScore();

    collision_detection_delay = 0; //delay collision detection after game restart

    scene.addItem(&text_start_end);

    playing = false;
    ready_to_restart = false;

    this->setFocus(Qt::ActiveWindowFocusReason);
}

void Game_window::GenerateAndPopulateMap()
{
    powerball_positions = power_ball.getPowerBallPositions();
    speedball_positions = speed_ball.getSpeedBallPositions();
    foodball_positions = food_ball.getFoodBallPositions();
    pac_map.LoadMapImage();

    map_item = scene.addPixmap(pac_map.getMap_Background_Picture());

    for(int i=0;i<powerball_positions.size();i++)
    {
        powerball_graphical_items_table.push_back(scene.addEllipse(powerball_positions.at(i).x()-5,powerball_positions.at(i).y()-8,15,15,QPen(Qt::NoPen),QBrush(Qt::yellow)));
    }

    for(int i=0;i<speedball_positions.size();i++)
    {
        speedball_graphical_items_table.push_back(scene.addEllipse(speedball_positions.at(i).x()-5,speedball_positions.at(i).y()-8,15,15,QPen(Qt::NoPen),QBrush(Qt::green)));
    }

    foodball_items_count=foodball_positions.size();

    for(int i=0;i<foodball_positions.size();i++)
    {
        foodball_graphical_items_table.push_back(scene.addEllipse(foodball_positions.at(i).x(),foodball_positions.at(i).y(),7,7,QPen(Qt::NoPen),QBrush(Qt::white)));
    }
}

void Game_window::GenerateAndPlacePacman()
{
    start=false;

    pac_man.setDirection(1); //pacman moves left after game start

    pac_man.setPac_X(320);
    pac_man.setPac_Y(514);

   scene.addItem(&pac_man);
}

void Game_window::GenerateAndPlaceGhosts()
{
    start_timer = 0;

    scared = false;

    scarestate = 0;

    speedup = false;

    speedstate = 0;

    ghost1.setIsScared(false);
    ghost2.setIsScared(false);
    ghost3.setIsScared(false);
    ghost4.setIsScared(false);

    ghost1.setGhost_X(307);
    ghost1.setGhost_Y(318);
    ghost2.setGhost_X(307);
    ghost2.setGhost_Y(318);
    ghost3.setGhost_X(307);
    ghost3.setGhost_Y(318);
    ghost4.setGhost_X(307);
    ghost4.setGhost_Y(318);

    ghost1.setGhostColor("orange");
    ghost2.setGhostColor("red");
    ghost3.setGhostColor("blue");
    ghost4.setGhostColor("pink");

    ghostmoving1=false;
    ghostmoving2=false;
    ghostmoving3=false;
    ghostmoving4=false;

    ghoststart1=false;
    ghoststart2=false;
    ghoststart3=false;
    ghoststart4=false;

    all_ghosts_started = false;

    scene.addItem(&ghost1);
    scene.addItem(&ghost2);
    scene.addItem(&ghost3);
    scene.addItem(&ghost4);
}

void Game_window::ShowScore()
{
    score=0;
    score_display = scene.addText("Score:");
    score_display->setDefaultTextColor(Qt::white);
    score_display->setFont(QFont("Arial", 40));
    score_display->setPos(0,671);
}

void Game_window::StartGame()
{
    sounds.beginning_sound.play();

    text_start_end.hide();

    connect(&timer, SIGNAL(timeout()), this,SLOT(updater()));
    connect(&ghoststimer, SIGNAL(timeout()), this,SLOT(ghostupdater()));

    timer.start(4);
    ghoststimer.start(4);
    this->setFocus(); //gives the keyboard input focus to this widget
}

void Game_window::RestartGame()
{
    ClearVariablesAndContainers();

    pac_man.show();
    ghost1.show();
    ghost2.show();
    ghost3.show();
    ghost4.show();

    GenerateAndPopulateMap();
    GenerateAndPlacePacman();
    GenerateAndPlaceGhosts();

    ShowScore();

    sounds.beginning_sound.play();

    text_start_end.hide();

    timer.start(4);
    ghoststimer.start(4);
    this->setFocus(); //gives the keyboard input focus to this widget
}

void Game_window::ClearVariablesAndContainers()
{
    powerball_graphical_items_table.clear();
    foodball_graphical_items_table.clear();
    speedball_graphical_items_table.clear();
    powerball_graphical_items_table.squeeze();
    foodball_graphical_items_table.squeeze();
    speedball_graphical_items_table.squeeze();
}

void Game_window::HideSceneItems()
{
    map_item->hide();
    score_display->hide();

    pac_man.hide();
    scene.removeItem(&pac_man);

    ghost1.hide();
    ghost2.hide();
    ghost3.hide();
    ghost4.hide();
    scene.removeItem(&ghost1);
    scene.removeItem(&ghost2);
    scene.removeItem(&ghost3);
    scene.removeItem(&ghost4);

    for(int i=0; i<foodball_graphical_items_table.size();i++)
    {
        foodball_graphical_items_table.at(i)->hide();
    }

    for(int i=0; i<powerball_graphical_items_table.size();i++)
    {
        powerball_graphical_items_table.at(i)->hide();
    }
    for(int i=0; i<speedball_graphical_items_table.size();i++)
    {
        speedball_graphical_items_table.at(i)->hide();
    }
}

void Game_window::EndGame(int win)
{
    if(win==1)
    {
        HideSceneItems();

        text_start_end.show();

        text_start_end.setScore(score);
        text_start_end.setGameWon(true);
        text_start_end.show();

        score=0;

        scene.update();
        playing = false;
        ready_to_restart = true;
    }

    else
    {
        sounds.pacman_death_sound.play();

        HideSceneItems();

        text_start_end.show();
        text_start_end.setScore(score);
        text_start_end.setGameLost(true);
        text_start_end.show();

        score=0;

        scene.update();
        playing = false;
        ready_to_restart = true;
    }
}

void Game_window::PacmanMove()
{
    QPoint p;

    int pac_x = pac_man.getPac_X();
    int pac_y = pac_man.getPac_Y();
    int direction = pac_man.getDirection();
    int nextdirection = pac_man.getNextDirection();
    int boost=1;

    if(nextdirection!=direction)
    {
        switch(nextdirection)
        {
        case 1: //left
            p.setX(pac_x-1);
            p.setY(pac_y);

            if(pac_map.IsPointAvailable(p))
            {
                direction=nextdirection;
                nextdirection=0;
            }
            break;

        case 2: //up
            p.setX(pac_x);
            p.setY(pac_y-1);
            if(pac_map.IsPointAvailable(p))
            {
                direction=nextdirection;
                nextdirection=0;
            }
            break;

        case 3: //down
            p.setX(pac_x);
            p.setY(pac_y+1);
            if(pac_map.IsPointAvailable(p))
            {
                direction=nextdirection;
                nextdirection=0;
            }
            break;

        case 4: //right
            p.setX(pac_x+1);
            p.setY(pac_y);
            if(pac_map.IsPointAvailable(p))
            {
                direction=nextdirection;
                nextdirection=0;
            }
            break;
        }
    }

    if (speedup==true){boost=2;}
    else {boost=1;}

    switch(direction)
    {
    case 1: //left
        while(boost>0)
        {
            p.setX(pac_x-1);
            p.setY(pac_y);
            pac_man.setDirection(direction);

            if(pac_map.IsPointAvailable(p))
            {
                pac_x = pac_x - 1;
            }
            boost--;
        }
        break;

    case 2: //up
        while(boost>0)
        {
            p.setX(pac_x);
            p.setY(pac_y-1);
            pac_man.setDirection(direction);

            if(pac_map.IsPointAvailable(p))
            {
                pac_y= pac_y - 1;
            }
            boost--;
        }
        break;

    case 3: //down
        while(boost>0)
        {
            p.setX(pac_x);
            p.setY(pac_y+1);
            pac_man.setDirection(direction);

            if(pac_map.IsPointAvailable(p))
            {
                pac_y= pac_y + 1;
            }
            boost--;
        }
        break;

    case 4: //right
        while(boost>0)
        {
            p.setX(pac_x+1);
            p.setY(pac_y);
            pac_man.setDirection(direction);

            if(pac_map.IsPointAvailable(p))
            {
                pac_x = pac_x + 1;
            }
            boost--;
        }
        break;
    }

    if(pac_x==0 && pac_y==318) //teleportation when reached left boundary of middle horizontal line
    {
        pac_x=613;
    }

    if(pac_x==614 && pac_y==318) //teleportation when reached right boundary of middle horizontal line
    {
        pac_x=1;
    }

    pac_man.setPac_X(pac_x);
    pac_man.setPac_Y(pac_y);
}

void Game_window::GhostMove1()
{
    QPoint p;

    int pac_x = pac_man.getPac_X();
    int pac_y = pac_man.getPac_Y();
    int ghost1_x = ghost1.getGhost_X();
    int ghost1_y = ghost1.getGhost_Y();
    int ghost1_dir = ghost1.getGhostDirection();
    int nextghost1_dir = ghost1.getNextGhostDirection();

    if(!ghostmoving1)
    {
        ghost1_dir=(qrand()%4)+1;
    }
    else
    {
        if((ghost1_dir==4 &&ghost1_y<pac_y) || (ghost1_dir==1 && ghost1_y>pac_y))
        {
            if(ghost1_dir==1 && ghost1_y>pac_y)
            {
                nextghost1_dir=2;
            }
            else if(ghost1_dir==4 &&ghost1_y<pac_y)
            {
                nextghost1_dir=3;
            }
        }
        else if((ghost1_dir==3 && ghost1_x<pac_x) || (ghost1_dir==2 && ghost1_x>pac_x))
        {
            if(ghost1_dir==2 && ghost1_x>pac_x)
            {
                nextghost1_dir=1;
            }
            else if(ghost1_dir==3 && ghost1_x<pac_x)
            {
                nextghost1_dir=4;
            }
        }
    }

    if(nextghost1_dir!=ghost1_dir)
    {
        switch(nextghost1_dir)
        {
        case 1:
            p.setX(ghost1_x-1);
            p.setY(ghost1_y);

            if(pac_map.IsPointAvailable(p))
            {
                ghost1_dir=nextghost1_dir;
                nextghost1_dir=0;
            }

            break;

        case 4:
            p.setX(ghost1_x+1);
            p.setY(ghost1_y);
            if(pac_map.IsPointAvailable(p))
            {
                ghost1_dir=nextghost1_dir;
                nextghost1_dir=0;
            }

            break;
        case 3:
            p.setX(ghost1_x);
            p.setY(ghost1_y+1);
            if(pac_map.IsPointAvailable(p))
            {
                ghost1_dir=nextghost1_dir;
                nextghost1_dir=0;
            }

            break;
        case 2:
            p.setX(ghost1_x);
            p.setY(ghost1_y-1);
            if(pac_map.IsPointAvailable(p))
            {
                ghost1_dir=nextghost1_dir;
                nextghost1_dir=0;
            }

            break;
        }
    }

    switch(ghost1_dir)
    {
    case 1:
        p.setX(ghost1_x-1);
        p.setY(ghost1_y);
        ghost1.setGhostDirection(ghost1_dir);

        if(pac_map.IsPointAvailable(p))
        {
            ghost1_x-=1;
            ghostmoving1=true;
        }
        else
        {
            ghostmoving1=false;
        }

        break;

    case 4:
        ghost1.setGhostDirection(ghost1_dir);
        p.setX(ghost1_x+1);
        p.setY(ghost1_y);
        if(pac_map.IsPointAvailable(p))
        {
            ghost1_x+=1;
            ghostmoving1=true;
        }
        else
        {
            ghostmoving1=false;
        }

        break;

    case 3:
        ghost1.setGhostDirection(ghost1_dir);
        p.setX(ghost1_x);
        p.setY(ghost1_y+1);
        if(pac_map.IsPointAvailable(p))
        {
            ghost1_y+=1;
            ghostmoving1=true;
        }
        else
        {
            ghostmoving1=false;
        }

        break;
    case 2:
        ghost1.setGhostDirection(ghost1_dir);
        p.setX(ghost1_x);
        p.setY(ghost1_y-1);
        if(pac_map.IsPointAvailable(p))
        {
            ghost1_y-=1;
            ghostmoving1=true;
        }
        else
        {
            ghostmoving1=false;
        }

        break;
    }

    if(ghost1_x<=0)
    {
        ghost1_x=613;
        ghost1_y=318;
    }
    else if(ghost1_x>=614)
    {
        ghost1_x=1;
        ghost1_y=318;
    }

    ghost1.setGhost_X(ghost1_x);
    ghost1.setGhost_Y(ghost1_y);
    ghost1.setNextGhostDirection(nextghost1_dir);
}
void Game_window::GhostMove2()
{
    QPoint p;

    int pac_x = pac_man.getPac_X();
    int pac_y = pac_man.getPac_Y();
    int ghost2_x = ghost2.getGhost_X();
    int ghost2_y = ghost2.getGhost_Y();
    int ghost2_dir = ghost2.getGhostDirection();
    int nextghost2_dir = ghost2.getNextGhostDirection();

    if(!ghostmoving2)
    {
        ghost2_dir=(qrand()%4)+1;
    }
    else
    {
        if((ghost2_dir==4 &&ghost2_y<pac_y) || (ghost2_dir==1 && ghost2_y>pac_y))
        {
            if(ghost2_dir==1 && ghost2_y>pac_y)
            {
                nextghost2_dir=2;
            }
            else if(ghost2_dir==4 &&ghost2_y<pac_y)
            {
                nextghost2_dir=3;
            }
        }
        else if((ghost2_dir==3 && ghost2_x<pac_x) || (ghost2_dir==2 && ghost2_x>pac_x))
        {
            if(ghost2_dir==2 && ghost2_x>pac_x)
            {
                nextghost2_dir=1;
            }
            else if(ghost2_dir==3 && ghost2_x<pac_x)
            {
                nextghost2_dir=4;
            }
        }
    }

    if(nextghost2_dir!=ghost2_dir)
    {
        switch(nextghost2_dir)
        {
        case 1:
            p.setX(ghost2_x-1);
            p.setY(ghost2_y);

            if(pac_map.IsPointAvailable(p))
            {
                ghost2_dir=nextghost2_dir;
                nextghost2_dir=0;
            }

            break;

        case 4:
            p.setX(ghost2_x+1);
            p.setY(ghost2_y);
            if(pac_map.IsPointAvailable(p))
            {
                ghost2_dir=nextghost2_dir;
                nextghost2_dir=0;
            }

            break;
        case 3:
            p.setX(ghost2_x);
            p.setY(ghost2_y+1);
            if(pac_map.IsPointAvailable(p))
            {
                ghost2_dir=nextghost2_dir;
                nextghost2_dir=0;
            }

            break;
        case 2:
            p.setX(ghost2_x);
            p.setY(ghost2_y-1);
            if(pac_map.IsPointAvailable(p))
            {
                ghost2_dir=nextghost2_dir;
                nextghost2_dir=0;
            }
            break;
        }
    }

    switch(ghost2_dir)
    {
    case 1:
        p.setX(ghost2_x-1);
        p.setY(ghost2_y);
        ghost2.setGhostDirection(ghost2_dir);

        if(pac_map.IsPointAvailable(p))
        {
            ghost2_x-=1;
            ghostmoving2=true;
        }
        else
        {
            ghostmoving2=false;
        }

        break;

    case 4:
        ghost2.setGhostDirection(ghost2_dir);
        p.setX(ghost2_x+1);
        p.setY(ghost2_y);
        if(pac_map.IsPointAvailable(p))
        {
            ghost2_x+=1;
            ghostmoving2=true;
        }
        else
        {
            ghostmoving2=false;
        }

        break;
    case 3:
        ghost2.setGhostDirection(ghost2_dir);
        p.setX(ghost2_x);
        p.setY(ghost2_y+1);
        if(pac_map.IsPointAvailable(p))
        {
            ghost2_y+=1;
            ghostmoving2=true;
        }
        else
        {
            ghostmoving2=false;
        }

        break;
    case 2:
        ghost2.setGhostDirection(ghost2_dir);
        p.setX(ghost2_x);
        p.setY(ghost2_y-1);
        if(pac_map.IsPointAvailable(p))
        {
            ghost2_y-=1;
            ghostmoving2=true;
        }
        else
        {
            ghostmoving2=false;
        }

        break;
    }

    if(ghost2_x<=0)
    {
        ghost2_x=613;
        ghost2_y=318;
    }
    else if(ghost2_x>=614)
    {
        ghost2_x=1;
        ghost2_y=318;
    }

    ghost2.setGhost_X(ghost2_x);
    ghost2.setGhost_Y(ghost2_y);
    ghost2.setNextGhostDirection(nextghost2_dir);
}
void Game_window::GhostMove3()
{
    QPoint p;

    int pac_x = pac_man.getPac_X();
    int pac_y = pac_man.getPac_Y();
    int ghost3_x = ghost3.getGhost_X();
    int ghost3_y = ghost3.getGhost_Y();
    int ghost3_dir = ghost3.getGhostDirection();
    int nextghost3_dir = ghost3.getNextGhostDirection();

    if(!ghostmoving3)
    {
        ghost3_dir=(qrand()%4)+1;
    }
    else
    {
        if((ghost3_dir==4 &&ghost3_y<pac_y) || (ghost3_dir==1 && ghost3_y>pac_y))
        {
            if(ghost3_dir==1 && ghost3_y>pac_y)
            {
                nextghost3_dir=2;
            }
            else if(ghost3_dir==4 &&ghost3_y<pac_y)
            {
                nextghost3_dir=3;
            }

        }
        else if((ghost3_dir==3 && ghost3_x<pac_x) || (ghost3_dir==2 && ghost3_x>pac_x))
        {
            if(ghost3_dir==2 && ghost3_x>pac_x)
            {
                nextghost3_dir=1;
            }
            else if(ghost3_dir==3 && ghost3_x<pac_x)
            {
                nextghost3_dir=4;
            }
        }
    }

    if(nextghost3_dir!=ghost3_dir)
    {
        switch(nextghost3_dir)
        {
        case 1:
            p.setX(ghost3_x-1);
            p.setY(ghost3_y);

            if(pac_map.IsPointAvailable(p))
            {
                ghost3_dir=nextghost3_dir;
                nextghost3_dir=0;

            }

            break;

        case 4:
            p.setX(ghost3_x+1);
            p.setY(ghost3_y);
            if(pac_map.IsPointAvailable(p))
            {
                ghost3_dir=nextghost3_dir;
                nextghost3_dir=0;
            }

            break;
        case 3:
            p.setX(ghost3_x);
            p.setY(ghost3_y+1);
            if(pac_map.IsPointAvailable(p))
            {
                ghost3_dir=nextghost3_dir;
                nextghost3_dir=0;
            }

            break;
        case 2:
            p.setX(ghost3_x);
            p.setY(ghost3_y-1);
            if(pac_map.IsPointAvailable(p))
            {
                ghost3_dir=nextghost3_dir;
                nextghost3_dir=0;
            }
            break;
        }

    }
    switch(ghost3_dir)
    {
    case 1:
        p.setX(ghost3_x-1);
        p.setY(ghost3_y);
        ghost3.setGhostDirection(ghost3_dir);

        if(pac_map.IsPointAvailable(p))
        {
            ghost3_x-=1;
            ghostmoving3=true;

        }
        else
        {
            ghostmoving3=false;
        }

        break;

    case 4:
        ghost3.setGhostDirection(ghost3_dir);
        p.setX(ghost3_x+1);
        p.setY(ghost3_y);
        if(pac_map.IsPointAvailable(p))
        {
            ghost3_x+=1;
            ghostmoving3=true;
        }
        else
        {
            ghostmoving3=false;
        }

        break;
    case 3:
        ghost3.setGhostDirection(ghost3_dir);
        p.setX(ghost3_x);
        p.setY(ghost3_y+1);
        if(pac_map.IsPointAvailable(p))
        {
            ghost3_y+=1;
            ghostmoving3=true;
        }
        else
        {
            ghostmoving3=false;
        }

        break;
    case 2:
        ghost3.setGhostDirection(ghost3_dir);
        p.setX(ghost3_x);
        p.setY(ghost3_y-1);
        if(pac_map.IsPointAvailable(p))
        {
            ghost3_y-=1;
            ghostmoving3=true;
        }
        else
        {
            ghostmoving3=false;
        }
        break;
    }


    if(ghost3_x<=0)
    {
        ghost3_x=613;
        ghost3_y=318;
    }
    else if(ghost3_x>=614)
    {
        ghost3_x=1;
        ghost3_y=318;
    }

    ghost3.setGhost_X(ghost3_x);
    ghost3.setGhost_Y(ghost3_y);
    ghost3.setNextGhostDirection(nextghost3_dir);
}
void Game_window::GhostMove4()
{
    QPoint p;

    int pac_x = pac_man.getPac_X();
    int pac_y = pac_man.getPac_Y();
    int ghost4_x = ghost4.getGhost_X();
    int ghost4_y = ghost4.getGhost_Y();
    int ghost4_dir = ghost4.getGhostDirection();
    int nextghost4_dir = ghost4.getNextGhostDirection();

    if(!ghostmoving4)
    {
        ghost4_dir=(qrand()%4)+1;
    }
    else
    {
        if((ghost4_dir==4 &&ghost4_y<pac_y) || (ghost4_dir==1 && ghost4_y>pac_y))
        {
            if(ghost4_dir==1 && ghost4_y>pac_y)
            {
                nextghost4_dir=2;
            }
            else if(ghost4_dir==4 &&ghost4_y<pac_y)
            {
                nextghost4_dir=3;
            }
        }
        else if((ghost4_dir==3 && ghost4_x<pac_x) || (ghost4_dir==2 && ghost4_x>pac_x))
        {
            if(ghost4_dir==2 && ghost4_x>pac_x)
            {
                nextghost4_dir=1;
            }
            else if(ghost4_dir==3 && ghost4_x<pac_x)
            {
                nextghost4_dir=4;
            }
        }
    }

    if(nextghost4_dir!=ghost4_dir)
    {
        switch(nextghost4_dir)
        {
        case 1:
            p.setX(ghost4_x-1);
            p.setY(ghost4_y);

            if(pac_map.IsPointAvailable(p))
            {
                ghost4_dir=nextghost4_dir;
                nextghost4_dir=0;
            }

            break;

        case 4:
            p.setX(ghost4_x+1);
            p.setY(ghost4_y);
            if(pac_map.IsPointAvailable(p))
            {
                ghost4_dir=nextghost4_dir;
                nextghost4_dir=0;
            }

            break;
        case 3:
            p.setX(ghost4_x);
            p.setY(ghost4_y+1);
            if(pac_map.IsPointAvailable(p))
            {
                ghost4_dir=nextghost4_dir;
                nextghost4_dir=0;
            }

            break;
        case 2:
            p.setX(ghost4_x);
            p.setY(ghost4_y-1);
            if(pac_map.IsPointAvailable(p))
            {
                ghost4_dir=nextghost4_dir;
                nextghost4_dir=0;
            }

            break;
        }

    }
    switch(ghost4_dir)
    {
    case 1:
        p.setX(ghost4_x-1);
        p.setY(ghost4_y);
        ghost4.setGhostDirection(ghost4_dir);

        if(pac_map.IsPointAvailable(p))
        {
            ghost4_x-=1;
            ghostmoving4=true;
        }
        else
        {
            ghostmoving4=false;
        }

        break;

    case 4:
        ghost4.setGhostDirection(ghost4_dir);
        p.setX(ghost4_x+1);
        p.setY(ghost4_y);
        if(pac_map.IsPointAvailable(p))
        {
            ghost4_x+=1;
            ghostmoving4=true;
        }
        else
        {
            ghostmoving4=false;
        }

        break;
    case 3:
        ghost4.setGhostDirection(ghost4_dir);
        p.setX(ghost4_x);
        p.setY(ghost4_y+1);
        if(pac_map.IsPointAvailable(p))
        {
            ghost4_y+=1;
            ghostmoving4=true;
        }
        else
        {
            ghostmoving4=false;
        }

        break;
    case 2:
        ghost4.setGhostDirection(ghost4_dir);
        p.setX(ghost4_x);
        p.setY(ghost4_y-1);
        if(pac_map.IsPointAvailable(p))
        {
            ghost4_y-=1;
            ghostmoving4=true;
        }
        else
        {
            ghostmoving4=false;
        }
        break;
    }

    if(ghost4_x<=0)
    {
        ghost4_x=613;
        ghost4_y=318;
    }
    else if(ghost4_x>=614)
    {
        ghost4_x=1;
        ghost4_y=318;
    }
    ghost4.setGhost_X(ghost4_x);
    ghost4.setGhost_Y(ghost4_y);
    ghost4.setNextGhostDirection(nextghost4_dir);
}

void Game_window::MoveGhostInStartingRect1()
{
    int ghost1_x = ghost1.getGhost_X();
    int ghost1_y = ghost1.getGhost_Y();
    int ghost1_dir = ghost1.getGhostDirection();

    if(ghost1_x==307-50 || ghost1_x==307+50)
    {
        if(ghost1_dir==4)
        {
            ghost1_dir=1; //go left
        }
        else
        {
            ghost1_dir=4; //go right
        }
    }

    if(ghost1_dir==4)
    {
        ghost1_x+=1;
    }
    else
    {
        ghost1_x-=1;
    }

    ghost1.setGhost_X(ghost1_x);
    ghost1.setGhost_Y(ghost1_y);
    ghost1.setGhostDirection(ghost1_dir);
}
void Game_window::MoveGhostInStartingRect2()
{
    int ghost2_x = ghost2.getGhost_X();
    int ghost2_y = ghost2.getGhost_Y();
    int ghost2_dir = ghost2.getGhostDirection();

    if(ghost2_x==307-50 || ghost2_x==307+50)
    {
        if(ghost2_dir==4)
        {
            ghost2_dir=1;
        }
        else
        {
            ghost2_dir=4;
        }
    }
    if(ghost2_dir==4)
    {
        ghost2_x+=1;
    }
    else
    {
        ghost2_x-=1;
    }

    ghost2.setGhost_X(ghost2_x);
    ghost2.setGhost_Y(ghost2_y);
    ghost2.setGhostDirection(ghost2_dir);
}
void Game_window::MoveGhostInStartingRect3()
{
    int ghost3_x = ghost3.getGhost_X();
    int ghost3_y = ghost3.getGhost_Y();
    int ghost3_dir = ghost3.getGhostDirection();

    if(ghost3_x==307-50 || ghost3_x==307+50)
    {
        if(ghost3_dir==4)
        {
            ghost3_dir=1;
        }
        else
        {
            ghost3_dir=4;
        }
    }
    if(ghost3_dir==4)
    {
        ghost3_x+=1;
    }
    else
    {
        ghost3_x-=1;
    }

    ghost3.setGhost_X(ghost3_x);
    ghost3.setGhost_Y(ghost3_y);
    ghost3.setGhostDirection(ghost3_dir);
}
void Game_window::MoveGhostInStartingRect4()
{
    int ghost4_x = ghost4.getGhost_X();
    int ghost4_y = ghost4.getGhost_Y();
    int ghost4_dir = ghost4.getGhostDirection();

    if(ghost4_x==307-50 || ghost4_x==307+50)
    {
        if(ghost4_dir==4)
        {
            ghost4_dir=1;
        }
        else
        {
            ghost4_dir=4;
        }
    }
    if(ghost4_dir==4)
    {
        ghost4_x+=1;
    }
    else
    {
        ghost4_x-=1;
    }

    ghost4.setGhost_X(ghost4_x);
    ghost4.setGhost_Y(ghost4_y);
    ghost4.setGhostDirection(ghost4_dir);
}

void Game_window::keyPressEvent(QKeyEvent *event) //supports pacman movement using WSAD and directional keys
{
    int nextdirection=pac_man.getNextDirection();

    switch(event->key())
    {
    case Qt::Key_Left:
        nextdirection=1;
        break;
    case Qt::Key_A:
        nextdirection=1;
        break;

    case Qt::Key_Right:
        nextdirection=4;
        break;
    case Qt::Key_D:
        nextdirection=4;
        break;

    case Qt::Key_Down:
        nextdirection=3;
        break;
    case Qt::Key_S:
        nextdirection=3;
        break;

    case Qt::Key_Up:
        nextdirection=2;
        break;
    case Qt::Key_W:
        nextdirection=2;
        break;

    case Qt::Key_1:
        if(!playing && ready_to_restart == true)
        {
            ghost1.setskin(0);
            ghost2.setskin(0);
            ghost3.setskin(0);
            ghost4.setskin(0);
            pac_map.setskin(0);
        }
    break;
    case Qt::Key_2:
        if(!playing && ready_to_restart == true)
        {
            ghost1.setskin(1);
            ghost2.setskin(1);
            ghost3.setskin(1);
            ghost4.setskin(1);
            pac_map.setskin(1);
        }

    break;
    case Qt::Key_Space:
        if(!playing && ready_to_restart == false)
        {
            playing = true;
            StartGame();
        }
        if(!playing && ready_to_restart == true)
        {
            ready_to_restart = false;
            playing = true;
            RestartGame();
        }

    default:
        break;
    }
    pac_man.setNextDirection(nextdirection);
}

void Game_window::CheckCollision()
{
    if(pac_man.collidesWithItem(&ghost1) ||
            pac_man.collidesWithItem(&ghost2) ||
            pac_man.collidesWithItem(&ghost3) ||
            pac_man.collidesWithItem(&ghost4))
    {
        if(pac_man.collidesWithItem(&ghost1) && ghost1.getIsScared())
        {
            sounds.eat_ghost_sound.play();
            score+=200;
            score_display->setPlainText("Score: " + QString::number(score));
            ghost1.setGhost_X(307);
            ghost1.setGhost_Y(252);
            ghost1.setIsScared(false);
        }
        else if(pac_man.collidesWithItem(&ghost2) && ghost2.getIsScared())
        {
            sounds.eat_ghost_sound.play();
            score+=200;
            score_display->setPlainText("Score: " + QString::number(score));
            ghost2.setGhost_X(307);
            ghost2.setGhost_Y(252);
            ghost2.setIsScared(false);
        }
        else if(pac_man.collidesWithItem(&ghost3) && ghost3.getIsScared())
        {
            sounds.eat_ghost_sound.play();
            score+=200;
            score_display->setPlainText("Score: " + QString::number(score));
            ghost3.setGhost_X(307);
            ghost3.setGhost_Y(252);
            ghost3.setIsScared(false);
        }
        else if(pac_man.collidesWithItem(&ghost4) && ghost4.getIsScared())
        {
            sounds.eat_ghost_sound.play();
            score+=200;
            score_display->setPlainText("Score: " + QString::number(score));
            ghost4.setGhost_X(307);
            ghost4.setGhost_Y(252);
            ghost4.setIsScared(false);
        }
        else
        {
            timer.stop();
            ghoststimer.stop();
            EndGame(0);
        }
    }
}

void Game_window::updater()
{
    int pac_x = pac_man.getPac_X();
    int pac_y = pac_man.getPac_Y();

    if(collision_detection_delay >= 500)
        CheckCollision();
    else
        collision_detection_delay++;

    PacmanMove();  //changes position of pacman

    for(int i=0;i<foodball_positions.size();i++)
    {
        if((pac_x==foodball_positions.at(i).x() && pac_y==foodball_positions.at(i).y())
            || (pac_x-1==foodball_positions.at(i).x() && pac_y==foodball_positions.at(i).y())
                || (pac_x+1==foodball_positions.at(i).x() && pac_y==foodball_positions.at(i).y())
                    || (pac_x==foodball_positions.at(i).x() && pac_y-1==foodball_positions.at(i).y())
                        || (pac_x==foodball_positions.at(i).x() && pac_y+1==foodball_positions.at(i).y()))
        {
            foodball_positions.remove(i);
            foodball_graphical_items_table.at(i)->hide();
            foodball_graphical_items_table.remove(i);

            if(sounds.eat_sound1.state()==QMediaPlayer::StoppedState)
            {
                sounds.eat_sound1.play();
            }

            if(sounds.eat_sound1.state()==QMediaPlayer::PlayingState)
            {
                sounds.eat_sound2.play();
            }

            score++;
            score_display->setPlainText("Score: " + QString::number(score));

            foodball_items_count--;
        }
    }

    for(int i=0;i<speedball_positions.size();i++)
    {
        if((pac_x==speedball_positions.at(i).x() && pac_y==speedball_positions.at(i).y())
            || (pac_x-1==speedball_positions.at(i).x() && pac_y==speedball_positions.at(i).y())
                || (pac_x+1==speedball_positions.at(i).x() && pac_y==speedball_positions.at(i).y())
                    || (pac_x==speedball_positions.at(i).x() && pac_y-1==speedball_positions.at(i).y())
                        || (pac_x==speedball_positions.at(i).x() && pac_y+1==speedball_positions.at(i).y()))
        {
           speedball_positions.remove(i);
           speedball_graphical_items_table.at(i)->hide();
           speedball_graphical_items_table.remove(i);

           score += 100;
           score_display->setPlainText("Score: " + QString::number(score));

           speedstate = 0;

           speedup=true;

           score_display->setPlainText("Score: " + QString::number(score));
       }
   }
    if(speedup)
    {
        speedstate+=1;

        if(speedstate==1)
        {
            pacmantimer.setInterval(50);
        }

        if(speedstate==1000)
        {
            speedup=false;

            speedstate = 0;
            pacmantimer.setInterval(4);
        }
    }
    for(int i=0;i<powerball_positions.size();i++)
    {
        if((pac_x==powerball_positions.at(i).x() && pac_y==powerball_positions.at(i).y())
            || (pac_x-1==powerball_positions.at(i).x() && pac_y==powerball_positions.at(i).y())
                || (pac_x+1==powerball_positions.at(i).x() && pac_y==powerball_positions.at(i).y())
                    || (pac_x==powerball_positions.at(i).x() && pac_y-1==powerball_positions.at(i).y())
                        || (pac_x==powerball_positions.at(i).x() && pac_y+1==powerball_positions.at(i).y()))
        {
            powerball_positions.remove(i);
            powerball_graphical_items_table.at(i)->hide();
            powerball_graphical_items_table.remove(i);

            score += 100;
            score_display->setPlainText("Score: " + QString::number(score));

            scarestate = 0;

            ghost1.setIsScared(true);
            ghost2.setIsScared(true);
            ghost3.setIsScared(true);
            ghost4.setIsScared(true);

            scared=true;

            score_display->setPlainText("Score: " + QString::number(score));
        }
    }

    if(foodball_items_count==0)
    {
        timer.stop();
        ghoststimer.stop();
        EndGame(1);
    }

    if(scared)
    {
        scarestate+=1;

        if(scarestate==1)
        {
            ghoststimer.setInterval(50);
        }

        if(scarestate==750)
        {
            ghost1.setScaredWhite(true);
            ghost2.setScaredWhite(true);
            ghost3.setScaredWhite(true);
            ghost4.setScaredWhite(true);
        }

        if(scarestate==1000)
        {
            scared=false;
            ghost1.setIsScared(false);
            ghost2.setIsScared(false);
            ghost3.setIsScared(false);
            ghost4.setIsScared(false);

            ghost1.setScaredWhite(false);
            ghost2.setScaredWhite(false);
            ghost3.setScaredWhite(false);
            ghost4.setScaredWhite(false);

            scarestate = 0;
            ghoststimer.setInterval(4);
        }
    }

    pac_man.advance();
    ghost1.advance();
    ghost2.advance();
    ghost3.advance();
    ghost4.advance();

    scene.update(scene.sceneRect());
}

void Game_window::ghostupdater()
{
    int ghost1_x = ghost1.getGhost_X();
    int ghost1_y = ghost1.getGhost_Y();
    int ghost2_x = ghost2.getGhost_X();
    int ghost2_y = ghost2.getGhost_Y();
    int ghost3_x = ghost3.getGhost_X();
    int ghost3_y = ghost3.getGhost_Y();
    int ghost4_x = ghost4.getGhost_X();
    int ghost4_y = ghost4.getGhost_Y();

    if(all_ghosts_started)
    {
        GhostMove1();
        GhostMove2();
        GhostMove3();
        GhostMove4();
    }
    else
    {
        if(!ghoststart1)
            MoveGhostInStartingRect1();
        else
            GhostMove1();

        if(!ghoststart2)
            MoveGhostInStartingRect2();
        else
            GhostMove2();

        if(!ghoststart3)
            MoveGhostInStartingRect3();
        else
            GhostMove3();

        if(!ghoststart4)
            MoveGhostInStartingRect4();
        else
            GhostMove4();

        if(ghost1_x==300 || ghost2_x==300 || ghost3_x==300 || ghost4_x==300) //substitute of timer to be implemented for every ghost do differentiate start time
        {
            start_timer++;
        }

        if(start_timer>=3) // ghost 1 starts
        {
            QPoint p1;
            if(ghost1_x>307)
            {
                ghost1_x-=1;
            }
            else if(ghost1_x<307)
            {
                ghost1_x+=1;
            }

            if(!ghoststart1)
            {
                ghost1_y-=1;
                ghost1.setGhost_X(ghost1_x);
                ghost1.setGhost_Y(ghost1_y);
                p1.setX(ghost1_x);
                p1.setY(ghost1_y);
                if(pac_map.getPacmanPaths().contains(p1))
                {
                    ghoststart1=true;
                }
            }
        }

        if(start_timer>=6) // ghost 2 starts
        {
            QPoint p2;
            if(ghost2_x>307)
            {
                ghost2_x-=1;
            }
            else if(ghost2_x<307)
            {
                ghost2_x+=1;
            }

            if(!ghoststart2)
            {
                ghost2_y-=1;
                ghost2.setGhost_X(ghost2_x);
                ghost2.setGhost_Y(ghost2_y);
                p2.setX(ghost2_x);
                p2.setY(ghost2_y);
                if(pac_map.getPacmanPaths().contains(p2))
                {
                    ghoststart2=true;
                }
            }
        }

        if(start_timer>=9) // ghost 3 starts
        {
            QPoint p3;
            if(ghost3_x>307)
            {
                ghost3_x-=1;
            }
            else if(ghost3_x<307)
            {
                ghost3_x+=1;
            }

            if(!ghoststart3)
            {
                ghost3_y-=1;
                ghost3.setGhost_X(ghost3_x);
                ghost3.setGhost_Y(ghost3_y);
                p3.setX(ghost3_x);
                p3.setY(ghost3_y);
                if(pac_map.getPacmanPaths().contains(p3))
                {
                    ghoststart3=true;
                }
            }
        }

        if(start_timer>=12) // ghost 4 starts
        {
            QPoint p4;
            if(ghost4_x>307)
            {
                ghost4_x-=1;
            }
            else if(ghost4_x<307)
            {
                ghost4_x+=1;
            }

            if(!ghoststart4)
            {
                ghost4_y-=1;
                ghost4.setGhost_X(ghost4_x);
                ghost4.setGhost_Y(ghost4_y);
                p4.setX(ghost4_x);
                p4.setY(ghost4_y);
                if(pac_map.getPacmanPaths().contains(p4))
                {
                    ghoststart4=true;
                }
            }
        }

        if(ghoststart1&&ghoststart2&&ghoststart3&&ghoststart4)
            all_ghosts_started=true;
    }
}

Game_window::~Game_window()
{
    delete ui;
}
