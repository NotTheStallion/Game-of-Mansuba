#include "project.h"


void test_show_world_and_position_init(struct world_t* world){
  show_world(world);
  printf("\n");

  position_initialisation(PAWNS_TOWERS_ELEPHANTS,world);
  show_world(world);
  printf("\n");

  position_initialisation(PAWNS,world);
  show_world(world);
  printf("\n");
}

void test_victoire(struct world_t* world,int MAX_TURNS){
    char* type_victoire="s";
    int nbr_turns=MAX_TURNS-1;
    world_set(world,0,WHITE);
    world_set_sort(world,0,PAWN);
    show_world(world);
    victory_condition(world,type_victoire,MAX_TURNS,nbr_turns);

    world_set(world,0,NO_COLOR);
    world_set_sort(world,0,NO_SORT);
    world_set(world,WIDTH-1,BLACK);
    world_set_sort(world,WIDTH-1,PAWN);
    show_world(world);
    victory_condition(world,type_victoire,MAX_TURNS,nbr_turns);

    nbr_turns=MAX_TURNS;
    world_set(world,WIDTH-1,NO_COLOR);
    world_set_sort(world,WIDTH-1,NO_SORT);
    world_set(world,0,WHITE);
    world_set_sort(world,0,PAWN);
    show_world(world);
    victory_condition(world,type_victoire,MAX_TURNS,nbr_turns);

    world_set(world,0,NO_COLOR);
    world_set_sort(world,0,NO_SORT);
    world_set(world,WIDTH-1,BLACK);
    world_set_sort(world,WIDTH-1,PAWN);
    show_world(world);
    victory_condition(world,type_victoire,MAX_TURNS,nbr_turns);
}


// Créé le monde et set les différents pions dans leur position initiale
int main(int argc,char *argv[]){
 
  char* type_victoire="s";
  int RNG=2; //initialisation random
  int MAX_TURNS=2*WORLD_SIZE;

  int option;

  /* parse short options */

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
  
  (void) type_victoire;
  (void) RNG;
  (void) MAX_TURNS;


  struct world_t* world=world_init();
  test_show_world_and_position_init(world); 
  
  test_victoire(world,50);
  
  /*
  enum color_t current_player = get_random_player();
  init_neighbors(RNG); // Use seed 0 at the beginning of a game
  printf("\n-Turn #%d/%d# :\n",0,MAX_TURNS);
  show_world(world);

  
  int index_pion;
  int move;
  int nbr_turns=0;
  while(victory_condition(world,type_victoire,MAX_TURNS,nbr_turns)!=0)
  {
    printf("\n-Turn #%d/%d# :\n",nbr_turns+1,MAX_TURNS);
    printf("\tTour du %d\n",current_player);
    index_pion = choose_random_piece_belonging_to(world, current_player);
    printf("\tLa piece en mvt est %d\n",index_pion);
    printf("\tSes voisins sont :");
    struct neighbors_t neighbors = get_neighbors(index_pion);
    struct neighbors_t saut = simple_jump(world,index_pion);
    for(int k = 0; k < MAX_NEIGHBORS+1;k++){
      printf("%d ", neighbors.n[k].i);
    }
    printf("\n\tSauts possibles :");
    for(int k = 0; k < MAX_NEIGHBORS+1;k++){
      printf("%d ", saut.n[k].i);
    }
    printf("\n");
    move = choose_random_move_for_piece(world, index_pion);
    printf("\tDéplacement vers %d\n",move);
    move_piece(world, move,index_pion);
    nbr_turns++;
    current_player = next_player(current_player);
    show_world(world);
    sleep(0.2);
    condition_changement_tableau+=1;
  }
  */
  return 0;
}