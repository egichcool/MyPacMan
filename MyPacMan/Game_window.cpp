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

    for(int i=0;i<4;i++)
    {
        ghosts[i].setIsScared(false);
        ghosts[i].setGhost_X(ghost_first_x);
        ghosts[i].setGhost_Y(ghost_first_y);
        ghosts[i].setGhostColor(colors[i]);
        ghoststarts[i]=false;
        scene.addItem(&ghosts[i]);
    }

    all_ghosts_started = false;
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
    for(int i=0;i<4;i++)
    {
        ghosts[i].show();
    }

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

    for(int i=0;i<4;i++)
    {
        ghosts[i].hide();
        scene.removeItem(&ghosts[i]);
    }

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
            for(int i=0;i<4;i++)
            {
                ghosts[i].setskin(skin);
            }
            Map::s_setSkin(skin);
        }
        break;
    case Qt::Key_2:
        if(!playing && ready_to_restart == true)
        {
            skin=1;
            for(int i=0;i<4;i++)
            {
                ghosts[i].setskin(skin);
            }
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
    if(pac_man.collidesWithItem(&ghosts[0]) ||
            pac_man.collidesWithItem(&ghosts[1]) ||
            pac_man.collidesWithItem(&ghosts[2]) ||
            pac_man.collidesWithItem(&ghosts[3]))
    {
        bool check=false;
        for(int i=0;i<4;i++)
        {
            if(pac_man.collidesWithItem(&ghosts[i]) && ghosts[i].getIsScared())
            {
                sounds.eat_ghost_sound.play();
                score+=200;
                score_display->setPlainText("Score: " + QString::number(score));
                ghosts[i].setGhost_X(ghost_death_x);
                ghosts[i].setGhost_Y(ghost_death_y);
                ghosts[i].setIsScared(false);
                check=true;
            }
        }
        if (!check)
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

            for(int i=0;i<4;i++)
            {
                ghosts[i].setIsScared(true);
            }

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
            for(int i=0;i<4;i++)
            {
                ghosts[i].setScaredWhite(true);
            }
            ghost1.setScaredWhite(true);
            ghost2.setScaredWhite(true);
            ghost3.setScaredWhite(true);
            ghost4.setScaredWhite(true);
        }

        if(scarestate==1000)
        {
            scared=false;
            for(int i=0;i<4;i++)
            {
                ghosts[i].setIsScared(false);
                ghosts[i].setScaredWhite(false);
            }
            scarestate = 0;
            ghoststimer.setInterval(4);
        }
    }

    pac_man.advance();
    for(int i=0;i<4;i++)
    {
        ghosts[i].advance();
    }
    scene.update(scene.sceneRect());
}

void Game_window::ghostupdater()
{
    int ghosts_x[4];
    int ghosts_y[4];
    for(int i=0;i<4;i++)
    {
        ghosts_x[i]=ghosts[i].getGhost_X();
        ghosts_y[i]=ghosts[i].getGhost_Y();
    }
    if(all_ghosts_started)
    {
        for(int i=0;i<4;i++)
        {
            GhostMove(ghosts[i]);
        }
    }
    else
    {
        for(int i=0;i<4;i++)
        {
            if(!ghoststarts[i])
                MoveGhostInStartingRect(ghosts[i]);
            else
                GhostMove(ghosts[i]);
        }

        if(ghosts_x[0]==300 || ghosts_x[1]==300 || ghosts_x[2]==300 || ghosts_x[3]==300) //substitute of timer to be implemented for every ghost do differentiate start time
        {
            start_timer++;
        }

        for(int i=0;i<4;i++)
        {
            if(start_timer>=(i+1)*3)
            {
                QPoint p1;
                if(ghosts_x[i]>ghost_first_x)
                {
                    ghosts_x[i]-=1;
                }
                else if(ghosts_x[i]<ghost_first_x)
                {
                    ghosts_x[i]+=1;
                }

                if(!ghoststarts[i])
                {
                    ghosts_y[i]-=1;
                    ghosts[i].setGhost_X(ghosts_x[i]);
                    ghosts[i].setGhost_Y(ghosts_y[i]);
                    p1.setX(ghosts_x[i]);
                    p1.setY(ghosts_y[i]);
                    if(Map::s_getPacmanPaths().contains(p1))
                    {
                        ghoststarts[i]=true;
                    }
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
