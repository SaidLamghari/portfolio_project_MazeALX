#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define MAX_ENEMIES 10
#define MAX_LIGHTS 10

typedef struct {
    float x, y;
    float dirX, dirY;
    float planeX, planeY;
} Player;

typedef struct {
    float x, y;
    float speed;
    SDL_Color color;
} Raindrop;

typedef struct {
    float x, y;
    float intensity;
    SDL_Color color;
} LightSource;

extern Player player;
extern int map[10][10];
extern Raindrop raindrops[100];
extern LightSource light_sources[MAX_LIGHTS];
extern int num_light_sources;
extern int raining;

void init_game(void);
void load_map(const char *filename);
void handle_events(SDL_Event *event, int *running);
void update_game(void);
void render_game(SDL_Renderer *renderer);
void cleanup_game(void);
void cast_rays(SDL_Renderer *renderer);
void render_ground_ceiling(SDL_Renderer *renderer);
void render_enemies(SDL_Renderer *renderer);
void draw_map(SDL_Renderer *renderer);
void render_weapon(SDL_Renderer *renderer);
void render_rain(SDL_Renderer *renderer);
void update_rain(void);
void rotate(float angle);
int load_textures(SDL_Renderer *renderer);
void render_lights(SDL_Renderer *renderer);
void apply_fog(SDL_Color *color, float distance);

#endif
