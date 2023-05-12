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
    int map_x = (int)position_x;
    int map_y = (int)position_y;

    float delta_distance_x = fabsf(1.0f / direction_x);
    float delta_distance_y = fabsf(1.0f / direction_y);

    float distance_x;
    float distance_y;
    int step_x;
    int step_y;

    int hit = 0;
    if(direction_x < 0) {
        step_x = -1;
        distance_x = (position_x - (float)map_x) * delta_distance_x;
    }
    else {
        step_x = 1;
        distance_x = ((float)map_x + 1.0f - position_x) * delta_distance_x;
    }
    if(direction_y < 0) {
        step_y = -1;
        distance_y = (position_y - (float)map_y) * delta_distance_y;
    }
    else {
        step_y = 1;
        distance_y = ((float)map_y + 1.0f - position_y) * delta_distance_y;
    }

    while(!hit) {
        if(distance_x < distance_y) {
            distance_x += delta_distance_x;
            map_x += step_x;
            *side = 0;
        }
        else {
            distance_y += delta_distance_y;
            map_y += step_y;
            *side = 1;
        }
        if(tiles[map_y][map_x] > 0) hit = 1;
    }

    if(*side == 0)
        *perspective_distance = (distance_x - delta_distance_x);
    else
        *perspective_distance = (distance_y - delta_distance_y);

    *tile = tiles[map_y][map_x];
}