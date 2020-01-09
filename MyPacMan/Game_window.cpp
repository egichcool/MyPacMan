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
    scene.setSceneRect(0,0,map_width,map_hight);
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
    pac_map.LoadMapImage();
    pac_map.LoadMap();
    food_ball.SetFoodBallPositions();
    power_ball.setPowerballPositions();
    powerball_positions = power_ball.getPowerBallPositions();
    speedball_positions = speed_ball.getSpeedBallPositions();
    foodball_positions = food_ball.getFoodBallPositions();

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

    pac_man.setDirection(left); //pacman moves left after game start

    pac_man.setPac_X(pac_first_x);
    pac_man.setPac_Y(pac_first_y);

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

    ghost1.setGhost_X(ghost_first_x);
    ghost1.setGhost_Y(ghost_first_y);
    ghost2.setGhost_X(ghost_first_x);
    ghost2.setGhost_Y(ghost_first_y);
    ghost3.setGhost_X(ghost_first_x);
    ghost3.setGhost_Y(ghost_first_y);
    ghost4.setGhost_X(ghost_first_x);
    ghost4.setGhost_Y(ghost_first_y);

    ghost1.setGhostColor("orange");
    ghost2.setGhostColor("red");
    ghost3.setGhostColor("blue");
    ghost4.setGhostColor("pink");

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

    timer.start(pacmap_speed);
    ghoststimer.start(ghost_speed);
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

    timer.start(pacmap_speed);
    ghoststimer.start(ghost_speed);
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
        case left:
            p.setX(pac_x-1);
            p.setY(pac_y);

            if(pac_map.IsPointAvailable(p))
            {
                direction=nextdirection;
                nextdirection=0;
            }
            break;

        case up:
            p.setX(pac_x);
            p.setY(pac_y-1);
            if(pac_map.IsPointAvailable(p))
            {
                direction=nextdirection;
                nextdirection=0;
            }
            break;

        case down:
            p.setX(pac_x);
            p.setY(pac_y+1);
            if(pac_map.IsPointAvailable(p))
            {
                direction=nextdirection;
                nextdirection=0;
            }
            break;

        case right:
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
    case left:
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

    case up:
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

    case down:
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

    case right:
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

    if(pac_x==wallpass_left_x)
    {
        pac_x=wallpass_right_x-1;
    }

    if(pac_x==wallpass_right_x)
    {
        pac_x=wallpass_left_x;
    }

    pac_man.setPac_X(pac_x);
    pac_man.setPac_Y(pac_y);
}

void Game_window::GhostMove(Ghost & ghost)
{
    QPoint p;

    int pac_x = pac_man.getPac_X();
    int pac_y = pac_man.getPac_Y();
    int ghost_x = ghost.getGhost_X();
    int ghost_y = ghost.getGhost_Y();
    int ghost_dir = ghost.getGhostDirection();
    int nextghost_dir = ghost.getNextGhostDirection();

    if(!ghost.ghostmoving)
    {
        ghost_dir=(qrand()%4)+1;
    }
    else
    {
        if((ghost_dir==right &&ghost_y<pac_y) || (ghost_dir==left && ghost_y>pac_y))
        {
            if(ghost_dir==left && ghost_y>pac_y)
            {
                nextghost_dir=up;
            }
            else if(ghost_dir==right &&ghost_y<pac_y)
            {
                nextghost_dir=down;
            }
        }
        else if((ghost_dir==down && ghost_x<pac_x) || (ghost_dir==up && ghost_x>pac_x))
        {
            if(ghost_dir==up && ghost_x>pac_x)
            {
                nextghost_dir=left;
            }
            else if(ghost_dir==down && ghost_x<pac_x)
            {
                nextghost_dir=right;
            }
        }
    }

    if(nextghost_dir!=ghost_dir)
    {
        switch(nextghost_dir)
        {
        case left:
            p.setX(ghost_x-1);
            p.setY(ghost_y);

            if(pac_map.IsPointAvailable(p))
            {
                ghost_dir=nextghost_dir;
                nextghost_dir=0;
            }

            break;

        case right:
            p.setX(ghost_x+1);
            p.setY(ghost_y);
            if(pac_map.IsPointAvailable(p))
            {
                ghost_dir=nextghost_dir;
                nextghost_dir=0;
            }

            break;
        case down:
            p.setX(ghost_x);
            p.setY(ghost_y+1);
            if(pac_map.IsPointAvailable(p))
            {
                ghost_dir=nextghost_dir;
                nextghost_dir=0;
            }

            break;
        case up:
            p.setX(ghost_x);
            p.setY(ghost_y-1);
            if(pac_map.IsPointAvailable(p))
            {
                ghost_dir=nextghost_dir;
                nextghost_dir=0;
            }

            break;
        }

    }
    switch(ghost_dir)
    {
    case left:
        p.setX(ghost_x-1);
        p.setY(ghost_y);
        ghost.setGhostDirection(ghost_dir);

        if(pac_map.IsPointAvailable(p))
        {
            ghost_x-=1;
            ghost.ghostmoving=true;
        }
        else
        {
            ghost.ghostmoving=false;
        }

        break;

    case right:
        ghost.setGhostDirection(ghost_dir);
        p.setX(ghost_x+1);
        p.setY(ghost_y);
        if(pac_map.IsPointAvailable(p))
        {
            ghost_x+=1;
            ghost.ghostmoving=true;
        }
        else
        {
            ghost.ghostmoving=false;
        }

        break;
    case down:
        ghost.setGhostDirection(ghost_dir);
        p.setX(ghost_x);
        p.setY(ghost_y+1);
        if(pac_map.IsPointAvailable(p))
        {
            ghost_y+=1;
            ghost.ghostmoving=true;
        }
        else
        {
            ghost.ghostmoving=false;
        }

        break;
    case up:
        ghost.setGhostDirection(ghost_dir);
        p.setX(ghost_x);
        p.setY(ghost_y-1);
        if(pac_map.IsPointAvailable(p))
        {
            ghost_y-=1;
            ghost.ghostmoving=true;
        }
        else
        {
            ghost.ghostmoving=false;
        }
        break;
    }

    if(ghost_x<=wallpass_left_x)
    {
        ghost_x=wallpass_right_x-1;
    }
    else if(ghost_x>=wallpass_right_x)
    {
        ghost_x=wallpass_left_x+1;
    }

    ghost.setGhost_X(ghost_x);
    ghost.setGhost_Y(ghost_y);
    ghost.setNextGhostDirection(nextghost_dir);
}
void Game_window::MoveGhostInStartingRect(Ghost & ghost)
{
    int ghost_x = ghost.getGhost_X();
    int ghost_y = ghost.getGhost_Y();
    int ghost_dir = ghost.getGhostDirection();

    if(ghost_x==cage_center-cage_wigth || ghost_x==cage_center+cage_wigth)
    {
        if(ghost_dir==right)
        {
            ghost_dir=left;
        }
        else
        {
            ghost_dir=right;
        }
    }

    if(ghost_dir==right)
    {
        ghost_x+=1;
    }
    else
    {
        ghost_x-=1;
    }

    ghost.setGhost_X(ghost_x);
    ghost.setGhost_Y(ghost_y);
    ghost.setGhostDirection(ghost_dir);
}

void Game_window::keyPressEvent(QKeyEvent *event) //supports pacman movement using WSAD and directional keys
{
    int nextdirection=pac_man.getNextDirection();

    switch(event->key())
    {
    case Qt::Key_Left:
        nextdirection=left;
        break;
    case Qt::Key_A:
        nextdirection=left;
        break;

    case Qt::Key_Right:
        nextdirection=right;
        break;
    case Qt::Key_D:
        nextdirection=right;
        break;

    case Qt::Key_Down:
        nextdirection=down;
        break;
    case Qt::Key_S:
        nextdirection=down;
        break;

    case Qt::Key_Up:
        nextdirection=up;
        break;
    case Qt::Key_W:
        nextdirection=up;
        break;

    case Qt::Key_1:
        if(!playing && ready_to_restart == true)
        {
            skin=0;
            ghost1.setskin(skin);
            ghost2.setskin(skin);
            ghost3.setskin(skin);
            ghost4.setskin(skin);
            Map::s_setSkin(skin);
        }
        break;
    case Qt::Key_2:
        if(!playing && ready_to_restart == true)
        {
            skin=1;
            ghost1.setskin(skin);
            ghost2.setskin(skin);
            ghost3.setskin(skin);
            ghost4.setskin(skin);
            Map::s_setSkin(skin);
        }
        break;
    case Qt::Key_3:
        if(!playing && ready_to_restart == true)
        {
            skin=2;
            Map::s_setSkin(skin);
        }
        break;
    case Qt::Key_4:
        if(!playing && ready_to_restart == true)
        {
            skin=3;
            Map::s_setSkin(skin);
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

        break; default:
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
            ghost1.setGhost_X(ghost_death_x);
            ghost1.setGhost_Y(ghost_death_y);
            ghost1.setIsScared(false);
        }
        else if(pac_man.collidesWithItem(&ghost2) && ghost2.getIsScared())
        {
            sounds.eat_ghost_sound.play();
            score+=200;
            score_display->setPlainText("Score: " + QString::number(score));
            ghost2.setGhost_X(ghost_death_x);
            ghost2.setGhost_Y(ghost_death_y);
            ghost2.setIsScared(false);
        }
        else if(pac_man.collidesWithItem(&ghost3) && ghost3.getIsScared())
        {
            sounds.eat_ghost_sound.play();
            score+=200;
            score_display->setPlainText("Score: " + QString::number(score));
            ghost3.setGhost_X(ghost_death_x);
            ghost3.setGhost_Y(ghost_death_y);
            ghost3.setIsScared(false);
        }
        else if(pac_man.collidesWithItem(&ghost4) && ghost4.getIsScared())
        {
            sounds.eat_ghost_sound.play();
            score+=200;
            score_display->setPlainText("Score: " + QString::number(score));
            ghost4.setGhost_X(ghost_death_x);
            ghost4.setGhost_Y(ghost_death_y);
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

            score += 99;
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
        GhostMove(ghost1);
        GhostMove(ghost2);
        GhostMove(ghost3);
        GhostMove(ghost4);
    }
    else
    {
        if(!ghoststart1)
            MoveGhostInStartingRect(ghost1);
        else
            GhostMove(ghost1);

        if(!ghoststart2)
            MoveGhostInStartingRect(ghost2);
        else
            GhostMove(ghost2);

        if(!ghoststart3)
            MoveGhostInStartingRect(ghost3);
        else
            GhostMove(ghost3);

        if(!ghoststart4)
            MoveGhostInStartingRect(ghost4);
        else
            GhostMove(ghost4);

        if(ghost1_x==300 || ghost2_x==300 || ghost3_x==300 || ghost4_x==300) //substitute of timer to be implemented for every ghost do differentiate start time
        {
            start_timer++;
        }

        if(start_timer>=3) // ghost 1 starts
        {
            QPoint p1;
            if(ghost1_x>ghost_first_x)
            {
                ghost1_x-=1;
            }
            else if(ghost1_x<ghost_first_x)
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
                if(Map::s_getPacmanPaths().contains(p1))
                {
                    ghoststart1=true;
                }
            }
        }

        if(start_timer>=6) // ghost 2 starts
        {
            QPoint p2;
            if(ghost2_x>ghost_first_x)
            {
                ghost2_x-=1;
            }
            else if(ghost2_x<ghost_first_x)
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
                if(Map::s_getPacmanPaths().contains(p2))
                {
                    ghoststart2=true;
                }
            }
        }

        if(start_timer>=9) // ghost 3 starts
        {
            QPoint p3;
            if(ghost3_x>ghost_first_x)
            {
                ghost3_x-=1;
            }
            else if(ghost3_x<ghost_first_x)
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
                if(Map::s_getPacmanPaths().contains(p3))
                {
                    ghoststart3=true;
                }
            }
        }

        if(start_timer>=12) // ghost 4 starts
        {
            QPoint p4;
            if(ghost4_x>ghost_first_x)
            {
                ghost4_x-=1;
            }
            else if(ghost4_x<ghost_first_x)
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
                if(Map::s_getPacmanPaths().contains(p4))
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
