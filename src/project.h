#include "world.h"
#include "neighbors.h"
#include <unistd.h>
#include <time.h>
#include "limits.h"
#include <stdio.h>
//#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <getopt.h>


//In this file we have the remaining signatures of the functions used in theis project. Moreover, short sentences that describe what the functions are meant to do.

//A structure that represents a pawn.
struct pawn{
  enum color_t c;
  enum sort_t s;
};

//A structure that defines the playing table (world)
struct world_t{
  struct pawn point[WORLD_SIZE];
};

//A structure that is made to receive the ELEPHANT neighbors.
struct elephant_set_t{
  struct vector_t n[12+1];
};
//An enumeration that has all the possible world initialisations that the coder might desire or need.
enum init{
  PAWNS = 0,
  PAWNS_TOWERS_ELEPHANTS = 1,
  MAX_INIT =2
};


//A function that returns a random player.
enum color_t get_random_player();

//A function that switches the playing hand from a player to another.
enum color_t next_player(enum color_t current_player);

//A function that chooses a random piece from the pieces that are on the playing table and belong a the current player and returns its index in the table (world).
int choose_random_piece_belonging_to(struct world_t* world, enum color_t current_player);

//A function that chooses a random move for a chosen piece and returns the end_index.
unsigned int choose_random_move_for_piece(struct world_t *world,int index);

//A function that makes the move by deleting the piece on the start_index and puting it at the end_index.
void move_piece(struct world_t* world,unsigned int end_index,unsigned int start_index);

//A function that decides if a player won or not according to the victory type given, MAX_TURNS and the current turn number.
unsigned int victory_condition(struct world_t * world,char *type_victoire,int MAX_TURNS,int TURN);

//A function that defines a simple movement for a PAWN and returns a structure that has all the possible simple moves.
struct neighbors_t simple_movement(struct world_t* world, unsigned int idx);

//A function that defines a simple jump for a PAWN and returns a list of possible jumps.
struct neighbors_t simple_jump(struct world_t* world, unsigned int idx);

//This function was meant to return a list of possible multiple jumps end index, but due a time factor we only managed to make it take one multiple jump.
unsigned int multiple_jumps(struct world_t* world, unsigned int idx);

//A function that counts the number of all the possible moves (simple movement, simple jump, multiple jump).
unsigned int number_of_movements(struct world_t* world, unsigned int idx);

//A function that initialises the world by puting PAWNS on all lines and on the first and last columns
int position_init(struct world_t* world);

//unsigned int victory_condition(struct world_t * world,char *type_victoire,int MAX_TURNS,int TURN);

//A function that returns a list of neighbors to the elephant.
struct elephant_set_t get_neighbors_elephant(unsigned int idx);

//A function that returns a list of possible simple moves for the elephant.
struct elephant_set_t simple_movement_elephant(struct world_t* world, unsigned int idx);

//A function that counts the number of simple moves for the ELEPHANT.
unsigned int number_semidiag(struct world_t*world,unsigned int index);

//A function that returns a list of all the possible cardinal translations to the TOWER.
struct neighbors_t cardinal_translation(struct world_t *world, unsigned int idx);

//A function that shows the world on a square shape.
void show_world_square(struct world_t* world);

//A function that shows the world on a hexagonal shape.
void show_world_hexagon(struct world_t* world);

//A function that shows the world on a triangular shape.
void show_world_triangle(struct world_t* world);

//A function that shows the world according to the time of world we are playing on.
void show_world(struct world_t* world);

//A function that defines the neighbor of a slot on a certain direction in the hexagonal world.
unsigned int get_neighbor_hexagon(unsigned int idx, enum dir_t d);

//A function that returns a list of possible neighbors to a slot on an hexagonal world.
struct neighbors_t get_neighbors_hex(unsigned int idx);

//A function that defines the neighbor of a slot on a certain direction in the triangular world.
unsigned int get_neighbor_triangle(unsigned int idx, enum dir_t d);

//A function that chooses a move for the PAWN and returns the end index.
unsigned int move_pawn(struct world_t *world, unsigned int index);

//A function that chooses a move for the TOWER and returns the end index.
unsigned int move_tower(struct world_t *world, int index);

//A function that chooses a move for the ELEPHANT and returns the end index.
unsigned int move_elephant(struct world_t *world, int index);

//A function that defines the neighbor of a slot according to the type of the world.
unsigned int get_neighbor_in_table(unsigned int idx ,enum dir_t d,unsigned int type_plateau);

//A function that initialises the world according to the coder desire.
void position_initialisation(enum init type_init,struct world_t* world);

//A function that store pieces when they are emprisoned.
struct jail_t{
  struct pawn n[2*HEIGHT];
  unsigned int index[2*HEIGHT];
};

//A function that creates a jail ready to receive emprisoned peices.
struct jail_t* jail_init();

//A function that emprisons pieces by deleting them from the world and putting them in the jail.
void imprison(struct world_t* world,unsigned int index,struct jail_t* jail);

//A function that defines the excape attempt and puts the pieces back in the world if they succed to escape.
void escape_attempt(struct jail_t* jail, struct world_t* world);
