#include "game.h"

void rotate(float angle) {
    float oldDirX = player.dirX;
    player.dirX = player.dirX * cos(angle) - player.dirY * sin(angle);
    player.dirY = oldDirX * sin(angle) + player.dirY * cos(angle);
    float oldPlaneX = player.planeX;
    player.planeX = player.planeX * cos(angle) - player.planeY * sin(angle);
    player.planeY = oldPlaneX * sin(angle) + player.planeY * cos(angle);
}
