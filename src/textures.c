#include "game.h"

SDL_Texture *wallTexture;    /* Texture for walls */
SDL_Texture *groundTexture;  /* Texture for ground */
SDL_Texture *weaponTexture;  /* Texture for weapon */

/**
 * load_textures - Load game textures
 * @renderer: The SDL renderer
 * 
 * Loads the textures
 * required for the game.
 * Returns 0 on success, -1 on failure.
 */
int load_textures(SDL_Renderer *renderer)
{
    wallTexture = SDL_CreateTextureFromSurface(renderer, SDL_LoadBMP("assets/textures/wall.bmp"));
    if (!wallTexture)
    {
        fprintf(stderr, "Error: Unable to load wall texture - %s\n", SDL_GetError());
        return -1;
    }
    groundTexture = SDL_CreateTextureFromSurface(renderer, SDL_LoadBMP("assets/textures/ground.bmp"));
    if (!groundTexture)
    {
        fprintf(stderr, "Error: Unable to load ground texture - %s\n", SDL_GetError());
        return -1;
    }
    weaponTexture = SDL_CreateTextureFromSurface(renderer, SDL_LoadBMP("assets/textures/weapon.bmp"));
    if (!weaponTexture)
    {
        fprintf(stderr, "Error: Unable to load weapon texture - %s\n", SDL_GetError());
        return -1;
    }
    return 0;
}

/**
 * render_weapon - Render the
 * player's weapon
 * @renderer: The SDL renderer
 * 
 * Renders the player's
 * weapon on the screen.
 */
void render_weapon(SDL_Renderer *renderer)
{
    SDL_Rect dstRect = {SCREEN_WIDTH / 2 - 50, SCREEN_HEIGHT - 100, 100, 100};
    SDL_RenderCopy(renderer, weaponTexture, NULL, &dstRect);
}
