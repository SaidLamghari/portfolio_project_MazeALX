#include "game.h"

SDL_Texture *wallTexture;
SDL_Texture *groundTexture;
SDL_Texture *weaponTexture;

int load_textures(SDL_Renderer *renderer) {
    wallTexture = SDL_CreateTextureFromSurface(renderer, SDL_LoadBMP("assets/textures/wall.bmp"));
    if (!wallTexture) {
        fprintf(stderr, "Erreur : Impossible de charger la texture du mur - %s\n", SDL_GetError());
        return -1;
    }
    groundTexture = SDL_CreateTextureFromSurface(renderer, SDL_LoadBMP("assets/textures/ground.bmp"));
    if (!groundTexture) {
        fprintf(stderr, "Erreur : Impossible de charger la texture du sol - %s\n", SDL_GetError());
        return -1;
    }
    weaponTexture = SDL_CreateTextureFromSurface(renderer, SDL_LoadBMP("assets/textures/weapon.bmp"));
    if (!weaponTexture) {
        fprintf(stderr, "Erreur : Impossible de charger la texture de l'arme - %s\n", SDL_GetError());
        return -1;
    }
    return 0;
}

void render_weapon(SDL_Renderer *renderer) {
    SDL_Rect dstRect = {SCREEN_WIDTH / 2 - 50, SCREEN_HEIGHT - 100, 100, 100};
    SDL_RenderCopy(renderer, weaponTexture, NULL, &dstRect);
}
