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
#include <QString>

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
    Ghost ghosts[4];

    Sounds sounds;

    enum direction {left=1, up, down, right};

    QString colors[4]={"orange","red","blue","pink"};

    int map=0;
    int score;
    int skin=1;
    int foodball_items_count;
    int collision_detection_delay;
    int scarestate;
    int speedstate;
    int start_timer;
    const int pacmap_speed=3; // To raise the speed set value less
    const int ghost_speed=3;  // To lower the speed set value more
    const int map_width=614;
    const int map_hight=740;
    const int pac_first_x=320;
    const int pac_first_y=514;
    const int ghost_first_x=307;
    const int ghost_first_y=318;
    const int ghost_death_x=307;
    const int ghost_death_y=252;
    const int wallpass_left_x=0;
    const int wallpass_right_x=614;
    const int cage_center=307;
    const int cage_wigth=50;

    bool ghoststarts[4];
    bool ghostmoving[4];
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
    explicit Game_window(QWidget *parent = nullptr);
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
    void GhostMove(Ghost&);
    void MoveGhostInStartingRect(Ghost&);
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
