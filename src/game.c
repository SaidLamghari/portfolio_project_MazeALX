#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include "game.h"
#include "rain.h"

/* Global variables declaration */
Player player;                          /* Player object */
int map[10][10];                        /* Game map */
Raindrop raindrops[100];                /* Array of raindrops */
LightSource light_sources[MAX_LIGHTS];  /* Array of light sources */
int num_light_sources = 0;              /* Number of light sources */
int raining = 0;                        /* Flag for rain status */

/**
 * init_game - Initialize the game
 */
void init_game(void)
{
    player.x = 1.5;
    player.y = 1.5;
    player.dirX = -1;
    player.dirY = 0;
    player.planeX = 0;
    player.planeY = 0.66;

    /* Initialize light sources */
    light_sources[0] = (LightSource){5.0, 5.0, 1.0, {255, 255, 255, 255}};
    light_sources[1] = (LightSource){10.0, 10.0, 0.8, {255, 0, 0, 255}};
    num_light_sources = 2;

    init_rain();
}

/**
 * load_map - Load a map from a file
 * @filename: The name of
 * the file to load the map from
 */
void load_map(const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (!file)
    {
        fprintf(stderr, "Error: Could not load map file %s\n", filename);
        exit(1);
    }

    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            fscanf(file, "%d", &map[i][j]);
        }
    }

    fclose(file);
}

/**
 * handle_events - Handle events
 * @event: The event to handle
 * @running: Pointer to the variable
 * controlling the game loop
 */
void handle_events(SDL_Event *event, int *running)
{
    while (SDL_PollEvent(event))
    {
        if (event->type == SDL_QUIT)
        {
            *running = 0;
        }
        const Uint8 *key_states = SDL_GetKeyboardState(NULL);
        if (key_states[SDL_SCANCODE_W])
        {
            player.x += player.dirX * 0.1;
            player.y += player.dirY * 0.1;
        }
        if (key_states[SDL_SCANCODE_S])
        {
            player.x -= player.dirX * 0.1;
            player.y -= player.dirY * 0.1;
        }
        if (key_states[SDL_SCANCODE_A])
        {
            rotate(-0.1);
        }
        if (key_states[SDL_SCANCODE_D])
        {
            rotate(0.1);
        }
        if (key_states[SDL_SCANCODE_R])
        {
            raining = !raining; /* Toggle rain */
        }
    }
}


/**
 * update_game - Update the game
 */
void update_game(void)
{
    if (raining)
        update_rain();
}



/**
 * render_game - Render the game
 * @renderer: The SDL renderer
 */

void render_game(SDL_Renderer *renderer)
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    cast_rays(renderer);
    render_ground_ceiling(renderer);
    render_enemies(renderer);
    render_weapon(renderer);
    render_lights(renderer);
    if (raining)
        render_rain(renderer);

    SDL_RenderPresent(renderer);
}

/**
 * cleanup_game - Clean up the game
 */
void cleanup_game(void)
{
    /* Free resources if necessary */
}

/**
 * main - Main function
 * @argc: Argument count
 * @argv: Argument vector
 * Return: 0 on success, 1 on failure
 */
int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <map_file>\n", argv[0]);
        return 1;
    }

    load_map(argv[1]);

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        fprintf(stderr, "Error: Could not initialize SDL - %s\n", SDL_GetError());
        return 1;
    }

    SDL_Window *window = SDL_CreateWindow("Maze Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (!window)
    {
        fprintf(stderr, "Error: Could not create window - %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer)
    {
        fprintf(stderr, "Error: Could not create renderer - %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    init_game();

    int running = 1;
    SDL_Event event;

    while (running)
    {
        handle_events(&event, &running);
        update_game();
        render_game(renderer);
    }

    cleanup_game();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
