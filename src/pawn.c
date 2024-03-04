#include "project.h"

//Ce fichier concerne les fonctions associés aux pions.

//Regarde les déplacements simples réalisables
struct neighbors_t simple_movement(struct world_t* world, unsigned int idx)
{
  unsigned int k = 0;
  unsigned int j =0;
  struct neighbors_t neighbors = get_neighbors(idx);
  struct neighbors_t deplacement_smpl;
  while((neighbors.n[k].i != UINT_MAX) && (k<MAX_NEIGHBORS))
  {
    if(world_get_sort(world,neighbors.n[k].i) == NO_SORT )
    {
      deplacement_smpl.n[j].i = neighbors.n[k].i;
      deplacement_smpl.n[j].d = neighbors.n[k].d;
      j++;
    }
    k++;
  }
  deplacement_smpl.n[j].i=UINT_MAX;
  deplacement_smpl.n[j].d=0;
  j++;
  while(j<MAX_NEIGHBORS+1)
  {
    deplacement_smpl.n[j].i=0;
    deplacement_smpl.n[j].d=0;
    j++;
  }
  return deplacement_smpl;
}

//CHecks the possible simple jumps and returns the indexes of the slots the piece can jump.
struct neighbors_t simple_jump(struct world_t* world, unsigned int idx)
{
  unsigned int k = 0;
  unsigned int j = 0;
  struct neighbors_t neighbors = get_neighbors(idx);
  struct neighbors_t saut_simp; //Structure à retouner pour voir les directions et index des sauts.
  unsigned int position =0; 
  while(neighbors.n[k].i < UINT_MAX && k<MAX_NEIGHBORS)
  {

    if(world_get_sort(world,neighbors.n[k].i) != NO_SORT)
    {
      position = get_neighbor_in_table(neighbors.n[k].i,neighbors.n[k].d,get_neighbors_seed());
      if(position<UINT_MAX)
      {
        if(world_get_sort(world,position) == NO_SORT)
        {
          saut_simp.n[j].i = neighbors.n[k].i;
          saut_simp.n[j].d = neighbors.n[k].d;
          j++;
        }
      }
    }
    k++;
  }
  saut_simp.n[j].i=UINT_MAX;
  saut_simp.n[j].d=0;
  j++;
  while(j<MAX_NEIGHBORS+1)
  {
    saut_simp.n[j].i=0;
    saut_simp.n[j].d=0;
    j++;
  }
  return saut_simp;
}

unsigned int multiple_jumps(struct world_t* world, unsigned int idx){
  unsigned int passed_index[WORLD_SIZE];
  for(int i=0;i<WORLD_SIZE;i++){
    passed_index[i]=UINT_MAX;
  }
  struct neighbors_t saut_simpl=simple_jump(world,idx);
  unsigned int jump_counter=0;
  enum color_t color=world_get(world,idx);
  enum sort_t sort=world_get_sort(world,idx);

  if(saut_simpl.n[0].i==UINT_MAX){//Case of even the simple jump isn't possible
    return UINT_MAX;
  }
  passed_index[jump_counter]=idx;
  idx=saut_simpl.n[0].i;
  idx=get_neighbor_in_table(idx,saut_simpl.n[0].d,get_neighbors_seed());//Get the index of the slot after the jump

  if(idx==UINT_MAX){
    return UINT_MAX;
  }

  world_set(world,idx,color);//Put the piece in the slot after the simple jump
  world_set_sort(world,idx,sort);
  jump_counter++;
  passed_index[jump_counter]=idx;
  while(idx!=UINT_MAX){//A loop that keeps choosing the first jump of the current piece adds it to the world and changes the current piece
    world_set(world,idx,color);//Adding the piece to the world
    world_set_sort(world,idx,sort);

    saut_simpl=simple_jump(world,idx);//Getting the list of possible pieces to jump
    idx=saut_simpl.n[0].i;//choosing the first one
    if(idx==UINT_MAX){
      break;
    }
    idx=get_neighbor_in_table(idx,saut_simpl.n[0].d,get_neighbors_seed());//change the current piece to the piece after the jump
    jump_counter++;
    passed_index[jump_counter]=idx;
  }

  for(int i=1;i<WORLD_SIZE;i++){//Deleting all the pieces expect the first one (the end_index will be given to move() that will delete the piece from the first position and add it to the last.)
    if(passed_index[i]!=UINT_MAX){
      world_set(world,passed_index[i],NO_COLOR);
      world_set_sort(world,passed_index[i],NO_SORT);
    }
  }
  return idx;
}

unsigned int move_pawn(struct world_t *world, unsigned int index){
    if(world_get_sort(world, index) != PAWN ){
      return index;
    }
    struct neighbors_t simple_movement_list=simple_movement(world,index);
    struct neighbors_t simple_jump_list=simple_jump(world,index);
    unsigned int simple_movement_counter=0;
    unsigned int simple_jump_counter=0;
    unsigned int movement_number=number_of_movements(world,index);
    srand(time(NULL));
    if (movement_number==0)
    {
      return index;
    }
    int random_movement_number=(rand()%movement_number);
    int sum_movement_remote=0;
    while(simple_movement_list.n[simple_movement_counter].i!=UINT_MAX && simple_movement_counter < MAX_NEIGHBORS)//Looping through the simple moves
    {
      if(sum_movement_remote==random_movement_number)
      {
        printf("Simple mouvement : ");
        return simple_movement_list.n[simple_movement_counter].i;
      }
      simple_movement_counter++;
      sum_movement_remote++;
    }
    while (simple_jump_list.n[simple_jump_counter].i!=UINT_MAX && simple_jump_counter < MAX_NEIGHBORS)//Looping through the simple jumps
    {
      if(sum_movement_remote==random_movement_number)
      {
        printf("Simple jump : ");
        return get_neighbor_in_table(simple_jump_list.n[simple_jump_counter].i,simple_jump_list.n[simple_jump_counter].d,get_neighbors_seed());
      }
      simple_jump_counter++;
      sum_movement_remote++;
    }
    if(sum_movement_remote == random_movement_number)//Choosing the multiplejump
    {
      printf("Multiple jumps : ");
      return multiple_jumps(world,index);
    }
    return index;
}

int position_init(struct world_t* world){
  for(int i = 0; i< WORLD_SIZE; i++){
    if(i%WIDTH==0){
      world_set(world,i,BLACK);
      world_set_sort(world,i,PAWN);
    }
    if(i%WIDTH==WIDTH-1){
      world_set(world,i,WHITE);
      world_set_sort(world,i,PAWN);
    }
  }
  return 0;
}