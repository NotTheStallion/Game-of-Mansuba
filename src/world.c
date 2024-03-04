#include "project.h"


//In this file : we initialise the world and make function to get and set information in the world.

struct world_t world;

//Initialises the world with empty slots.
struct world_t* world_init(){
  for(int i = 0; i < WORLD_SIZE; i++){
    world.point[i].c = NO_COLOR;
    world.point[i].s = NO_SORT;
  }
  return &world;
}

//Sets the color of the piece in the world.
enum color_t world_get(const struct world_t* b, unsigned int idx){
  return b -> point[idx].c;
}

//Sets the type of piece in the world.
void world_set(struct world_t* b, unsigned int idx, enum color_t c){
  b->point[idx].c = c;
}

//Gets the color of the piece in the world.
enum sort_t world_get_sort(const struct world_t* b, unsigned int idx){
  return b->point[idx].s;
}

//Gets the type of piece in the world.
void world_set_sort(struct world_t* b, unsigned int idx, enum sort_t c){
  b -> point[idx].s = c;
}


