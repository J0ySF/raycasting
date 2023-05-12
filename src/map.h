#ifndef RAYCASTING_MAP_H
#define RAYCASTING_MAP_H

typedef enum tile_t {
    TILE_FLOOR,
    TILE_WALL_1,
    TILE_WALL_2,
    TILE_WALL_3,
} tile_t;

void map_create(float *position_x, float *position_y);

void map_destroy();

void map_cast_ray(float position_x, float position_y, float direction_x, float direction_y, float *perspective_distance,
                  tile_t *tile, int *side);

#endif //RAYCASTING_MAP_H
