#ifndef __WORLD_H__
#define __WORLD_H__

#include "geometry.h"

/** Abstract struct representing the possible places in the world
    These places are indexed from 0 to WORLD_SIZE-1 */
struct world_t;

/** Initializes a world (NO_COLOR, NO_SORT everywhere)
    Always returns the same pointer */
struct world_t* world_init();

/** Return the color at a place */
enum color_t world_get(const struct world_t* b, unsigned int idx);

/** Sets the color at a place */
void world_set(struct world_t* b, unsigned int idx, enum color_t c);

/** Return the sort at a place */
enum sort_t world_get_sort(const struct world_t* b, unsigned int idx);

/** Sets the sort at a place */
void world_set_sort(struct world_t* b, unsigned int idx, enum sort_t c);

#endif // __WORLD_H__