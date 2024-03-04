#include <stdio.h>
#include "geometry.h"


const char* place_to_string(enum color_t c, enum sort_t s){
  if(c == NO_COLOR && s == NO_SORT){
    return "NO_COLOR and NO_SORT";
  }
  if(c == BLACK && s == NO_SORT){
    return "BLACK and NO_SORT";
  }
  if(c == WHITE && s == NO_SORT){
    return "WHITE and NO_SORT";
  }
  if(c == NO_COLOR && s == PAWN){
    return "NO_COLOR and PAWN";
  }
  if(c == BLACK && s == PAWN){
    return "BLACK PAWN";
  }
  if(c == WHITE && s == PAWN){
    return "WHITE PAWN";
  }
  else{
    return "BAD ARGUMENT";
  }
}
 

const char* dir_to_string(enum dir_t d)
{
  char* str;
  printf("%d",d);
  if (d == NO_DIR)
  {
    str = "NO_DIR";
  }
  if (d == EAST)
  {
    str = "EAST";
  }
  if (d == NEAST)
  {
    str = "NEAST";
  }
  if (d == NORTH)
  {
    str = "NORTH";
  }
  if (d == NWEST)
  {
    str = "NWEST";
  }
    if (d == WEST)
  {
    str = "WEST";
  }
    if (d == SWEST)
  {
    str = "SWEST";
  }
  if (d == SOUTH)
  {
    str = "SOUTH";
  }
    if (d == SEAST)
  {
    str = "SEAST";
  }
    if (d>4 || d<-4)
  {
    str = "INVALID DIRECTION";
  }
  return str;
}

