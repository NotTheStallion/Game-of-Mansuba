#include "project.h"

//In this file. All the laws of the game are defined.


struct piece_t{
  int blanc[WORLD_SIZE];
  int noir[WORLD_SIZE];
};

struct depart_t{
  struct piece_t piece;
};

//Call the correct get_neighbor function according the table type.
unsigned int get_neighbor_in_table(unsigned int idx ,enum dir_t d,unsigned int type_plateau){
    if(type_plateau==0){ //Square.
        return get_neighbor(idx,d);
    }
    if(type_plateau==1){ //Hexagonal.
        return get_neighbor_hexagon(idx,d);
    }
    if(type_plateau==2){ //Triangular.
        return get_neighbor_triangle(idx,d);
    }
    return UINT_MAX;
}

//Choose a random player to start the game.
enum color_t get_random_player()
{
  srand(time(NULL));
  return rand()%2+1;
}

//Switche the playing hand to the other player.
enum color_t next_player(enum color_t current_player)
{
  if(current_player==BLACK)
  {
    current_player++;
    return current_player;
  }
  if(current_player==WHITE)
  {
    current_player--;
    return current_player;
  }
  return current_player;
}

//Choose a random piece belonging to a player.
int choose_random_piece_belonging_to(struct world_t* world, enum color_t current_player){
  int compteur = 0;
  for(int i = 0; i<WORLD_SIZE; i++){ //Count the number of pieces in the world.
    if(world_get(world,i)==current_player && world_get_sort(world,i)!=NO_SORT){
      //printf("found %d ",i);
      compteur++;
    }
  }
  /*
  if(compteur <4){
    exit(100);
  }
  */
  srand(time(NULL));
  int pos = (rand()%compteur)+1;//Gets the number of a random piece.
  int num = 0;//Will be increacing until it reaches the number of the piece.
  int i = 0; //The index of the piece.
  while(num <= compteur && i< WORLD_SIZE){ //Travel the world.
    if(world_get(world,i)==current_player && world_get_sort(world,i)!=NO_SORT){ //Increasing num.
      num++;
    }
    if(num==pos) //We reached the piece the rand() gave us.(We are 100% sure this case will be true at some point)
    {
      return i; //Retun it's index.
    }
    i++; 
  }
  //The case i=WORLD_SIZE is already solved in the loop.
  i--; //This case will never be reached but in case i=WORLD_SIZE we substract one and return it.
  return i;
}

//This function calls the functions that chooses a random move for a piece according to its type.
unsigned int choose_random_move_for_piece(struct world_t *world,int index)
{
  
  if(world_get_sort(world,index)==PAWN)
  {
    return move_pawn(world,index);
  }
  if(world_get_sort(world,index)==TOUR)
  {
    return move_tower(world,index);
  }
  if(world_get_sort(world,index)==ELEPHANT)
  {
    return move_elephant(world,index);
  }
  return UINT_MAX;
}

//Move a piece from a starting position to an end position.
void move_piece(struct world_t* world,unsigned int end_index,unsigned int start_index) 
{
  printf("%d -> %d\n\n\n\n\n\n\n",start_index,end_index);
   if(end_index == UINT_MAX){ 
   }
   else{
   enum color_t color=world_get(world,start_index);
   enum sort_t sort=world_get_sort(world,start_index);
   world_set(world,start_index,0);
   world_set_sort(world,start_index,0);
   world_set(world,end_index,color);
   world_set_sort(world,end_index,sort);
  }
}

//Define victory conditions according the type of victory.
unsigned int victory_condition(struct world_t * world,char *victory_type,int MAX_TURNS,int TURN){
  if(MAX_TURNS <= TURN){
    printf("MAX_TURNS reached.\n");
    return 0;
  }
  if(victory_type[0] == 's'){
    for(int i = 0; i<WORLD_SIZE;i++){
      if(world_get(world,i)== WHITE && i%WIDTH==0){
	      printf("Simple Victory (WHITE)\n");
	      return 0;
      }
      if(world_get(world,i)==BLACK && i%WIDTH==WIDTH-1){
      	printf("Simple Victory (BLACK)\n");
	      return 0;
      }
    }
  }
  int white_counter = 0; //Count the number of white pieces are in the
  int black_counter = 0;
  if(victory_type[0] == 'c'){
    for(int i = 0; i<WORLD_SIZE;i++){
      if(world_get(world,i)==WHITE && i%WIDTH==0){ //Counting the number of white pieces.
	      white_counter++;
      }
      if(world_get(world,i)==BLACK && i%WIDTH==WIDTH-1){ //Counting the number of black pieces.
	      black_counter++;
      }
    }
    if (white_counter == HEIGHT){ //Max number of pieces reached.
      printf("Complex victory (WHITE)\n");
      return 0;
    }
    if(black_counter == HEIGHT){ //Max number of pieces reached.
      printf("Complex victory (BLACK)\n");
      return 0;
    }
  }
  return UINT_MAX;
}



void position_initialisation(enum init type_init,struct world_t* world){
  if(type_init==PAWNS){ //Two columns of pawns.
    position_init(world);
  }else if(type_init==PAWNS_TOWERS_ELEPHANTS){ //Mix of pawns elephants and tours.
    position_init(world);
    world_set(world,0,BLACK);
    world_set_sort(world,0,TOUR);
    world_set(world,WIDTH-1,WHITE);
    world_set_sort(world,WIDTH-1,TOUR);

    world_set(world,WORLD_SIZE-WIDTH,BLACK);
    world_set_sort(world,WORLD_SIZE-WIDTH,ELEPHANT);
    world_set(world,WORLD_SIZE-1,WHITE);
    world_set_sort(world,WORLD_SIZE-1,ELEPHANT);
  }else {
    printf("INVALID INITIALISATION\n");
  }
}





