#include "project.h"



// Créé le monde et set les différents pions dans leur position initiale
int main(int argc,char *argv[]){
 
  char* type_victoire="s";
  int RNG=2; //initialisation random
  int MAX_TURNS=2*WORLD_SIZE;
  int option;
  while ((option = getopt(argc, argv, "smt")) != -1) {
    switch (option) {
    case 's':
      RNG=atoi(argv[optind]);
      break;
    case 'm':
      MAX_TURNS=atoi(argv[optind]);
      break;
    case 't':
      type_victoire=argv[optind];
      break;
    }
  }
  /*Initializing all the structures*/
  struct world_t* world=world_init();
  //struct jail_t* jail=jail_init();
  show_world_square(world);
  position_initialisation(PAWNS_TOWERS_ELEPHANTS,world);

  enum color_t current_player = get_random_player();//choosing a starting player

  //imprison(world,0,jail); 
  //imprison(world,WIDTH-1,jail); 

  init_neighbors(RNG); // Use seed 0 at the beginning of a game
  printf("\n-Turn  %d/%d :\n",0,MAX_TURNS);
  show_world(world);

  
  int index_pawn;
  int move;
  int nbr_turns=0;
  int table_change_remote=0;
  int change_value=floor(sqrt(MAX_TURNS));
  while(victory_condition(world,type_victoire,MAX_TURNS,nbr_turns)!=0)//testing victory according to its type
  {
    if(table_change_remote>change_value){//condition of table switch reached
      printf("================================= SWITCHING TABLE ==================================\n");
      table_change_remote=0;//reset the remote
      srand((time(NULL)));
      unsigned int random_table_seed=get_neighbors_seed();//getting the the table type
      while(random_table_seed==get_neighbors_seed()){//while the table type is the same as the one before
        random_table_seed=rand()%3;//rolling random
      }
      init_neighbors(random_table_seed);//a seed that is different from the one before
    }
    printf("\n-Turn %d/%d :\n",nbr_turns+1,MAX_TURNS);
    printf("\tTurn of %d\n",current_player);
    index_pawn = choose_random_piece_belonging_to(world, current_player);
    move = choose_random_move_for_piece(world, index_pawn);
    move_piece(world, move,index_pawn);
    nbr_turns++;
    current_player = next_player(current_player);
    show_world(world);
    //sleep(1); //Uncomment this line to have more random plays.(keep in mind that they will be slower)
    table_change_remote+=1;
  }
  
  return 0;
}