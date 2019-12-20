#include "sounds.h"

Sounds::Sounds()
{
    beginning_sound.setMedia(QUrl("qrc:/sounds/pacman_beginning.wav"));
    eat_sound1.setMedia(QUrl("qrc:/sounds/pacman_eat.wav"));
    eat_sound2.setMedia(QUrl("qrc:/sounds/pacman_eat.wav"));
    eat_ghost_sound.setMedia(QUrl("qrc:/sounds/pacman_eatghost.wav"));
    pacman_death_sound.setMedia(QUrl("qrc:/sounds/pacman_death.wav"));
    pacman_siren.setMedia(QUrl("qrc:/sounds/pacman_siren.wav"));
}
