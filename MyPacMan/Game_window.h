#ifndef DIALOG_H
#define DIALOG_H

#include "map.h"
#include "pacman.h"
#include "powerball.h"
#include "speedball.h"
#include "foodball.h"
#include "ghost.h"
#include "textstartend.h"
#include "sounds.h"
#include <QDialog>
#include <QtCore>
#include <QtGui>
#include <QMediaPlayer>
#include <QGraphicsScene>

namespace Ui
{
class Game_window;
}

class Game_window : public QDialog
{
    Q_OBJECT

private:
    Ui::Game_window *ui;

    QGraphicsScene scene;

    TextStartEnd text_start_end;

    QTimer timer;
    QTimer ghoststimer;
    QTimer pacmantimer;

    Map pac_map;
    PowerBall power_ball;
    SpeedBall speed_ball;
    FoodBall food_ball;

    Pacman pac_man;
    Ghost ghost1;
    Ghost ghost2;
    Ghost ghost3;
    Ghost ghost4;

    Sounds sounds;

    int score;
    int foodball_items_count;
    int collision_detection_delay;
    int scarestate;
    int speedstate;
    int start_timer;

    bool ghostmoving1,ghostmoving2,ghostmoving3,ghostmoving4;
    bool ghoststart1,ghoststart2,ghoststart3,ghoststart4;
    bool start, playing, scared, speedup, all_ghosts_started, ready_to_restart;

    QVector<QPoint> powerball_positions;
    QVector<QPoint> speedball_positions;
    QVector<QPoint> foodball_positions;

    QGraphicsPixmapItem *map_item;

    QVector<QGraphicsEllipseItem*> foodball_graphical_items_table;
    QVector<QGraphicsEllipseItem*> powerball_graphical_items_table;
    QVector<QGraphicsEllipseItem*> speedball_graphical_items_table;

    QGraphicsTextItem *score_display;
    QGraphicsTextItem *lives_display;

    QMediaPlayer *beginning_sound;
    QMediaPlayer *eat_sound1;
    QMediaPlayer *eat_sound2;
    QMediaPlayer *eat_ghost_sound;
    QMediaPlayer *pacman_death_sound;

public:
    explicit Game_window(QWidget *parent = 0);
    void GenerateMap();
    void PopulateMap();

    void GenerateAndPopulateMap();
    void GenerateAndPlacePacman();
    void GenerateAndPlaceGhosts();
    void ResetMap();
    void ResetPacman();
    void ResetGhosts();
    void ShowScore();

    void GhostPlayerMove();
    void GhostMove1();
    void GhostMove2();
    void GhostMove3();
    void GhostMove4();
    void MoveGhostInStartingRect1();
    void MoveGhostInStartingRect2();
    void MoveGhostInStartingRect3();
    void MoveGhostInStartingRect4();
    void StartGame();
    void RestartGame();
    void HideSceneItems();
    void ClearVariablesAndContainers();
    void PacmanMove();
    void RespawnGhost();
    void CheckCollision();
    void EndGame(int win);

    ~Game_window();

public slots:
    void updater();
    void ghostupdater();

protected:
    void keyPressEvent(QKeyEvent *event);
};

#endif // DIALOG_H
