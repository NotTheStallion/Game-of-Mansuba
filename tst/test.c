#include "project.h"


//In this file we make random lines to test all the functions we make.


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

  //MAX_TURNS = getopt(argc,argv,"-m:");
  struct world_t* world=world_init();
  struct jail_t* prison=jail_init();
  show_world_hexagon(world);
  position_initialisation(PAWNS,world);
  enum color_t current_player = get_random_player();
  printf("current_player = %d\n",current_player);

  victory_condition(world,type_victoire,MAX_TURNS,0);
  ///////////////////////////////////////////////////////////test
  //int neigh=get_neighbor(10,-2);
  //printf("%d\n",neigh);
  //world_set(world,6,2);
  //world_set(world,13,2);
  //world_set(world,14,2);
  //world_set(world,19,2);
  //victory_condition(world,"c",20);
  

  /*
  int i = 0;
  while(i < WORLD_SIZE){
    struct neighbors_t dpl = simple_movement(world,i);
    printf("%d :\n", i);
    int j = 0;
    while(dpl.n[j].i != UINT_MAX){
      printf("%d\n", dpl.n[j].i);
      j++;
    }
    i = i + 10;
  }
  */
  /*
  world_set(world,6,1);
  world_set_sort(world,6,1);
  world_set(world,13,2);
  world_set_sort(world,13,2);
  struct neighbors_t neigh=get_neighbors(7);
  for(int j=0;j<MAX_NEIGHBORS+1;j++)
  {
    printf("voisin %u de direction %u\n",neigh.n[j].i,neigh.n[j].d);
    //printf("voisin %u\n",get_neighbor(7,j-4));
  }
  */
 
  //printf("%d",MAX_NEIGHBORS);
  /*
  printf("voisin de 0 %d\n",get_neighbor(0,3));
  //printf("%d\n",next_player(1));
  */
  /*
  world_set(world,6,1);
  world_set_sort(world,6,1);
  printf("avant exemple nbr mvt\n");
  printf("nombre mvt = %d\n",number_of_movements(world,0));
  printf("avant choose random\n");
  printf("%d\n",choose_random_piece_belonging_to(world,1,));
  */
  ///////////////////////////////////////////////////////////test_fin

  init_neighbors(RNG); // Use seed 0 at the beginning of a game
  imprison(world,WIDTH-1,prison);
  world_set(world,1,WHITE);
  world_set_sort(world,1,PAWN);
  world_set(world,3,WHITE);
  world_set_sort(world,3,PAWN);
  world_set(world,5,WHITE);
  world_set_sort(world,5,PAWN);
  printf("\n-Turn #%d/%d# :\n",0,MAX_TURNS);
  show_world(world);

  
  int index_pion;
  int move;
  int nbr_turns=0;
  int condition_changement_tableau=0;
  int valeur_changement=floor(sqrt(MAX_TURNS));
  while(victory_condition(world,type_victoire,MAX_TURNS,nbr_turns)!=0)
  {

    if(condition_changement_tableau>valeur_changement){
      printf("========================================== CHANGEMENT DE TABLE =========================================\n");
      condition_changement_tableau=0;
      srand((time(NULL)));
      unsigned int random_table_seed=get_neighbors_seed();
      while(random_table_seed==get_neighbors_seed()){
        random_table_seed=rand()%3;
      }
      init_neighbors(random_table_seed);
    }
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
  
  return 0;
}


