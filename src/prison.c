#include "project.h"


struct jail_t jail;
struct jail_t* jail_init(){
  for(int i = 0; i < 2*HEIGHT; i++){
    jail.n[i].c = NO_COLOR;
    jail.n[i].s = NO_SORT;
    jail.index[i] = UINT_MAX;
  }
  return &jail;
}

void escape_attempt(struct jail_t* jail,struct world_t * world){
    unsigned int index;
    for(int i = 0; i < 2*HEIGHT; i++){
        if(jail->index[i]==UINT_MAX){
            continue;
        }
        if(world_get(world,jail->index[i])==NO_COLOR && world_get_sort(world,jail->index[i])==NO_SORT ){
            srand(time(NULL));
            if(rand()%2==0){
                index=jail->index[i];
                world_set(world,index,jail->n[i].c);
                world_set_sort(world,index,jail->n[i].s);
            }
        }
    }
}


void imprison(struct world_t* world,unsigned int index,struct jail_t* jail){
    enum color_t color=world_get(world,index);
    enum sort_t sort=world_get_sort(world,index);
    world_set(world,index,NO_COLOR);
    world_set_sort(world,index,NO_SORT);
    for(int i = 0; i < 2*HEIGHT; i++){
        if(jail->index[i]==UINT_MAX){
            jail->index[i]=index;
            jail->n[i].c=color;
            jail->n[i].s=sort;
            break;
        }
    }
}