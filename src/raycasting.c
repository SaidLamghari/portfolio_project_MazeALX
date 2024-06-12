#include "game.h"
#include <math.h>

/**
 * cast_rays - Cast rays to render the walls
 * @renderer: The SDL renderer
 * 
 * This function casts rays to render the
 * walls using the raycasting technique.
 * It calculates the intersection points
 * of the rays with the walls and draws
 * vertical lines on the screen to represent the walls.
 */
void cast_rays(SDL_Renderer *renderer)
{
    for (int x = 0; x < SCREEN_WIDTH; x++)
    {
        float cameraX = 2 * x / (float)SCREEN_WIDTH - 1;
        float rayDirX = player.dirX + player.planeX * cameraX;
        float rayDirY = player.dirY + player.planeY * cameraX;

        int mapX = (int)player.x;
        int mapY = (int)player.y;

        float sideDistX;
        float sideDistY;

        float deltaDistX = fabs(1 / rayDirX);
        float deltaDistY = fabs(1 / rayDirY);
        float perpWallDist;

        int stepX;
        int stepY;

        int hit = 0;
        int side;

        if (rayDirX < 0)
        {
            stepX = -1;
            sideDistX = (player.x - mapX) * deltaDistX;
        }
        else
        {
            stepX = 1;
            sideDistX = (mapX + 1.0 - player.x) * deltaDistX;
        }
        if (rayDirY < 0)
        {
            stepY = -1;
            sideDistY = (player.y - mapY) * deltaDistY;
        }
        else
        {
            stepY = 1;
            sideDistY = (mapY + 1.0 - player.y) * deltaDistY;
        }

        while (hit == 0)
        {
            if (sideDistX < sideDistY)
            {
                sideDistX += deltaDistX;
                mapX += stepX;
                side = 0;
            }
            else
            {
                sideDistY += deltaDistY;
                mapY += stepY;
                side = 1;
            }
            if (map[mapX][mapY] > 0)
                hit = 1;
        }

        if (side == 0)
            perpWallDist = (mapX - player.x + (1 - stepX) / 2) / rayDirX;
        else
            perpWallDist = (mapY - player.y + (1 - stepY) / 2) / rayDirY;

        int lineHeight = (int)(SCREEN_HEIGHT / perpWallDist);

        int drawStart = -lineHeight / 2 + SCREEN_HEIGHT / 2;
        if (drawStart < 0)
            drawStart = 0;
        int drawEnd = lineHeight / 2 + SCREEN_HEIGHT / 2;
        if (drawEnd >= SCREEN_HEIGHT)
            drawEnd = SCREEN_HEIGHT - 1;

        SDL_Color color;
        switch (map[mapX][mapY])
        {
        case 1:
            color = (side == 1) ? (SDL_Color){255, 0, 0, 255} : (SDL_Color){200, 0, 0, 255};
            break;
        case 2:
            color = (side == 1) ? (SDL_Color){0, 255, 0, 255} : (SDL_Color){0, 200, 0, 255};
            break;
        case 3:
            color = (side == 1) ? (SDL_Color){0, 0, 255, 255} : (SDL_Color){0, 0, 200, 255};
            break;
        case 4:
            color = (side == 1) ? (SDL_Color){255, 255, 0, 255} : (SDL_Color){200, 200, 0, 255};
            break;
        default:
            color = (side == 1) ? (SDL_Color){255, 255, 255, 255} : (SDL_Color){200, 200, 200, 255};
            break;
        }

        apply_fog(&color, perpWallDist);

        SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
        SDL_RenderDrawLine(renderer, x, drawStart, x, drawEnd);
    }
}

/**
 * apply_fog - Apply fog effect
 * to the color based on distance
 * @color: The color to apply fog to
 * @distance: The distance of the object from the player
 * 
 * This function applies fog effect to
 * the color based on the distance
 * of the object from the player.
 */
void apply_fog(SDL_Color *color, float distance)
{
    float fogDensity = 0.05;
    float fogFactor = exp(-fogDensity * distance);
    color->r = (Uint8)(color->r * fogFactor);
    color->g = (Uint8)(color->g * fogFactor);
    color->b = (Uint8)(color->b * fogFactor);
}

