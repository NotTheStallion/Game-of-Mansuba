#include "project.h"

unsigned int t_plateau;
//Gets a valid table type from any seed.
void init_neighbors(unsigned int seed){
  t_plateau=seed%MAX_RELATIONS;
}


//Gets the table type at all times.
unsigned int get_neighbors_seed(){
  return t_plateau;
}


//Gets the neighbor of a piece in the world following a direction.
unsigned int get_neighbor(unsigned int idx, enum dir_t d)
{
    if (idx>(HEIGHT*WIDTH))
    {
        printf("INVALID INDEX");
        return UINT_MAX;
    }

    //idx = q*n + r
    unsigned int n=WIDTH;
    unsigned int q=idx/n;
    unsigned int r=idx%n;
    //The coordinates of each piece are (q,r) q for lines and r for columns.
    
    if(idx%WIDTH == 0){ //No west for slots in the west.
       if (d==NWEST || d== SWEST || d== WEST)
	 {
	   return UINT_MAX;
	 }
    }
    if(idx%WIDTH == WIDTH - 1){ //No east for slots in the east.
      if(d == NEAST || d== SEAST || d == EAST){
	    return UINT_MAX;
      }
    }
    if(idx/WIDTH == 0){ //No north allowed for slots on the north.
      if(d==NEAST || d== NORTH || d==NWEST){
        return UINT_MAX;
      }
    }
    if(idx/WIDTH == WIDTH-2){ //No south for slots in the south.
      if(d==SWEST || d==SOUTH || d==SEAST)
      {
        return UINT_MAX;
      }
    }
    
    if (d==NWEST)
	 {
	   q--;
	   r--;
	 }
    if (d==SWEST)
	 {
	   r--;
	   q++;
	 }
    if (d==WEST)
	 {
	   r--;
	 }
    if (d==EAST)
    {
        r++;
    }
    if (d==NEAST)
    {
        r++;
        q--;
    }
    if (d==NORTH)
    {
        q--;
    }
    if (d==SOUTH)
    {
        q++;
    }
    if (d==SEAST)
    { 
        q++;
        r++;
    }
    if (d>4 || d<-4 || d==NO_DIR )
    {
      //printf("INVALID DIRECTION %d",d);
      return UINT_MAX;
    }
    unsigned int index=q*n+r;
    if (index > WORLD_SIZE - 1){
      return UINT_MAX;
    }
    return index;
}

//Gets all the neighbors of a piece.
struct neighbors_t get_neighbors(unsigned int idx)
{
  struct neighbors_t neighbors; 
  enum dir_t d;
  unsigned int k=0;
  for(d = -4; d<=4; d++){ //Adding all the possible neighbors.
    unsigned int ind=get_neighbor_in_table(idx,d,get_neighbors_seed());
    if(ind<UINT_MAX)
    {
      neighbors.n[k].i=ind;
      neighbors.n[k].d=d;
      k++;
    }
  }
  neighbors.n[k].i=UINT_MAX; //Marking the end of neighbors with UINT_MAX.
  k++;
  while(k<MAX_NEIGHBORS+1){ //Filling the rest with zeros.
    neighbors.n[k].i=0;
    k++;
  }
  return neighbors;
}

//Counts all the possible moves for a piece in the world.
unsigned int number_of_movements(struct world_t* world, unsigned int idx)
{
  struct neighbors_t mouvement1 = simple_movement(world,idx); //Storing the simple movements.
  struct neighbors_t mouvement2 = simple_jump(world,idx);        //Storing the simple jumps.
  unsigned int compteur = 0;
  unsigned int j = 0;
  //Counting number of mouvements.
  while (mouvement1.n[j].i < UINT_MAX && j<MAX_NEIGHBORS+1)//Adding all the simple mouvements.
  {
    compteur+=1;
    j++;
  }
  j = 0;
  while(mouvement2.n[j].i < UINT_MAX && j<MAX_NEIGHBORS+1)//Adding all the simple jumps.
  {
    compteur+=1;
    j++;
  }
  if(multiple_jumps(world, idx) != UINT_MAX){ //Adding the multiple jump if it's possible.
    compteur++;
  }
  return compteur;
}
