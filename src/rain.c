#include "rain.h"
#include "game.h"
#include <stdlib.h>

void init_rain(void) {
    for (int i = 0; i < 100; i++) {
        raindrops[i].x = rand() % SCREEN_WIDTH;
        raindrops[i].y = rand() % SCREEN_HEIGHT;
        raindrops[i].speed = (rand() % 5) + 2;
        raindrops[i].color = (SDL_Color){0, 0, 255, 255};
    }
}

void update_rain(void) {
    for (int i = 0; i < 100; i++) {
        raindrops[i].y += raindrops[i].speed;
        if (raindrops[i].y > SCREEN_HEIGHT) {
            raindrops[i].y = 0;
            raindrops[i].x = rand() % SCREEN_WIDTH;
        }
    }
}

void render_rain(SDL_Renderer *renderer) {
    for (int i = 0; i < 100; i++) {
        SDL_SetRenderDrawColor(renderer, raindrops[i].color.r, raindrops[i].color.g, raindrops[i].color.b, raindrops[i].color.a);
        SDL_RenderDrawPoint(renderer, raindrops[i].x, raindrops[i].y);
    }
}
