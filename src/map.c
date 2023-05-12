#include "map.h"

#include <math.h>

static tile_t tiles[10][10] = {
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 2, 0, 3, 2, 0, 3, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 3, 0, 0, 0, 0, 2, 0, 1},
        {1, 0, 2, 0, 0, 0, 0, 3, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 3, 0, 2, 3, 0, 2, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
};

void map_create(float *position_x, float *position_y) {
    *position_x = 5;
    *position_y = 5;
}

void map_destroy() {

}

void map_cast_ray(float position_x, float position_y, float direction_x, float direction_y, float *perspective_distance,
                  tile_t *tile, int *side) {
    int mapX = (int)position_x;
    int mapY = (int)position_y;

    float sideDistX;
    float sideDistY;

    float deltaDistX = (direction_x == 0) ? 1e30f : fabsf(1.0f / direction_x);
    float deltaDistY = (direction_y == 0) ? 1e30f : fabsf(1.0f / direction_y);

    int stepX;
    int stepY;

    int hit = 0;
    if(direction_x < 0) {
        stepX = -1;
        sideDistX = (position_x - (float)mapX) * deltaDistX;
    }
    else {
        stepX = 1;
        sideDistX = ((float)mapX + 1.0f - position_x) * deltaDistX;
    }
    if(direction_y < 0) {
        stepY = -1;
        sideDistY = (position_y - (float)mapY) * deltaDistY;
    }
    else {
        stepY = 1;
        sideDistY = ((float)mapY + 1.0f - position_y) * deltaDistY;
    }

    while(!hit) {
        if(sideDistX < sideDistY) {
            sideDistX += deltaDistX;
            mapX += stepX;
            *side = 0;
        }
        else {
            sideDistY += deltaDistY;
            mapY += stepY;
            *side = 1;
        }
        if(tiles[mapX][mapY] > 0) hit = 1;
    }

    if(*side == 0)
        *perspective_distance = (sideDistX - deltaDistX);
    else
        *perspective_distance = (sideDistY - deltaDistY);

    *tile = tiles[mapX][mapY];
}