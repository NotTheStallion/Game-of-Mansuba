#include "project.h"

//Return the possible directions for the tower.
struct neighbors_t cardinal_translation(struct world_t *world, unsigned int idx){
  struct neighbors_t mvt_tour;
  int j = 0;//This will be indecrectly used to store the number of neighbors.
  for(int i = -3;i < 4; i = i + 2){  //Going throgh all the cardinal directions.
    if(get_neighbor_in_table(idx,i,get_neighbors_seed())<UINT_MAX){ //neighbor is a valid index
      if(get_neighbor_in_table(idx,i,get_neighbors_seed()) != UINT_MAX && world_get_sort(world, get_neighbor_in_table(idx,i,get_neighbors_seed())) == 0){ //Check the existence of a neighbor.
        mvt_tour.n[j].i = get_neighbor_in_table(idx,i,get_neighbors_seed());
        mvt_tour.n[j].d = i;
        j++;
      }
    }
  }
  if(j == 0){ //No possible moves
    mvt_tour.n[j].i = idx; //Put the current index of the tower (no movement)
    mvt_tour.n[j].d = 0;
    j++;
  }
  mvt_tour.n[j].i = UINT_MAX;  //Finish the list with a UINT_MAX.
  mvt_tour.n[j].d = 0;
  return mvt_tour;
}

//Return the end index of the tower.
unsigned int move_tower(struct world_t *world, int index){
    struct neighbors_t tour = cardinal_translation(world,index);
    if(tour.n[0].i == UINT_MAX){//This case isn't possible since we already tested if the tower can't move and we return its index in the first slot of the list
      return index;
    }
    int nbre_mvt = 0;//This variable stores the number of possible movements for the tower
    for(int j = 0; tour.n[j].i != UINT_MAX; j++){ //Count the possible moves
      nbre_mvt = j+1;
    }
    srand(time(NULL));
    int rand_dir = rand()%nbre_mvt; //Choose random direction
    int compteur_case = 0;//This variable counts the number of empty slots before reaching a first obstacle.
    unsigned int pos = get_neighbor_in_table(index,tour.n[rand_dir].d,get_neighbors_seed());//get a nieghbor in the same direction
    while(pos != UINT_MAX && world_get_sort(world,pos) == NO_SORT){ //Count number of empty slots
      compteur_case++;
      pos = get_neighbor_in_table(pos,tour.n[rand_dir].d,get_neighbors_seed());//Get the neighbor of the current slot in the same direction
    }
    if(compteur_case == 0){//Case in which there are no empty slots in the chosen direction (=no move possible)
      return index;
    }
    int rand_mvt = rand()%(compteur_case)+1; //Choose random slot to move to.
    for(int k = 0; k < rand_mvt; k++){//Redo the loop until you reach the chosen slot.
      index = get_neighbor_in_table(index,tour.n[rand_dir].d,get_neighbors_seed());
    }
    return index;
}

int position_init_tour(struct world_t* world){
    for(int i = 0; i< WORLD_SIZE; i++){
      if(i%WIDTH==0){
        world_set(world,i,BLACK);
        world_set_sort(world,i,TOUR);
      }
      if(i%WIDTH==WIDTH-1){
        world_set(world,i,WHITE);
        world_set_sort(world,i,TOUR);
      }
    }
    return 0;
}