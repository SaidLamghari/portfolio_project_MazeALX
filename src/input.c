#include "game.h"


/**
 * rotate - Rotate the player's direction and camera plane
 * @angle: The angle by which to rotate, in radians
 */

void rotate(float angle)
{
    /* Store old direction and plane values */
    float oldDirX = player.dirX;
    /* Update player direction */
    player.dirX = player.dirX * cos(angle) - player.dirY * sin(angle);
    player.dirY = oldDirX * sin(angle) + player.dirY * cos(angle);
    /* Store old plane values */
    float oldPlaneX = player.planeX;
    /* Update player camera plane */
    player.planeX = player.planeX * cos(angle) - player.planeY * sin(angle);
    player.planeY = oldPlaneX * sin(angle) + player.planeY * cos(angle);
}
