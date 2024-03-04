#include "project.h"

//This file has all the functions related to the elephant piece.

//Gets all the neighbors of an elephant.
struct elephant_set_t get_neighbors_elephant(unsigned int idx)
{
  struct elephant_set_t neighbors; 
  enum dir_t d;
  enum dir_t r;
  unsigned int k=0;
  unsigned int ind;
  unsigned int ind1;
  for(d = -3; d<=4; d+=2)    //Going through all the cardinal directions.
  {
    if(idx!=UINT_MAX){
      ind=get_neighbor_in_table(idx,d,get_neighbors_seed()); 
      for(r = -3; r<=4; r+=2)  //Going through all the cardinal directions of the neighbor.
      {
        if(ind!=UINT_MAX){
          ind1=get_neighbor_in_table(ind,r,get_neighbors_seed());
          if(ind1!=UINT_MAX && idx!=ind1) //No turning back.(going back to the initial position)
          {
            neighbors.n[k].i=ind1;
            neighbors.n[k].d=r;
            k++;
          }
        }
      }
    }
  }
  neighbors.n[k].i=UINT_MAX; //Close with an UINT_MAX.         
  k++;
  while(k<13) //Filling the rest with zeros.
  {
    neighbors.n[k].i=0;
    k++;
  }
  return neighbors;
}


struct elephant_set_t simple_movement_elephant(struct world_t* world, unsigned int idx)
{
  unsigned int k = 0;
  unsigned int j =0;
  struct elephant_set_t neighbors = get_neighbors_elephant(idx);
  struct elephant_set_t simple_movement_list;
  while(neighbors.n[k].i < UINT_MAX && k<13) //going though the neighbors of the elephant.
  {
    if(world_get_sort(world,neighbors.n[k].i)== NO_SORT)//if the slot is empty.
    {
      simple_movement_list.n[j].i = neighbors.n[k].i;//adding the slot to the list.
      simple_movement_list.n[j].d = neighbors.n[k].d;
      j++;
    }
    k++;
  }
  simple_movement_list.n[j].i=UINT_MAX;//Closing with an UINT_MAX.
  simple_movement_list.n[j].d=NO_DIR;
  j++;
  while(j<13)//Completing with zeros. 
  {
    simple_movement_list.n[j].i=0;
    simple_movement_list.n[j].d=NO_DIR;
    j++;
  }
  return simple_movement_list;
}


unsigned int number_semidiag(struct world_t*world,unsigned int index)
{
  struct elephant_set_t simple_movement = simple_movement_elephant(world,index);
  unsigned int counter = 0;
  unsigned int j = 0;
  while (simple_movement.n[j].i < UINT_MAX && j<13)
  {
    counter+=1;
    j++;
  }
  return counter;
}


unsigned int move_elephant(struct world_t *world, int index){
    struct elephant_set_t simple_movement_list=simple_movement_elephant(world,index);
    unsigned int simple_movement_counter=0;
    unsigned int nombre_mvt=number_semidiag(world,index);

    srand(time(NULL));
    if (nombre_mvt==0)
    {
      return index;
    }
    int rand_mvt=rand()%nombre_mvt;
    int somme=0;
    while(simple_movement_list.n[simple_movement_counter].i!=UINT_MAX && simple_movement_counter < 13)
    {
      if(somme==rand_mvt)
      {
        printf("Simple movement");
        return simple_movement_list.n[simple_movement_counter].i;
      }
      simple_movement_counter++;
      somme++;
    }
    return UINT_MAX;
}