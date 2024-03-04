#include "project.h"


unsigned int get_neighbor_hexagon(unsigned int idx, enum dir_t d){
    if(idx/WIDTH == 0){
        if(d == NORTH || d == NEAST || d == NWEST){ // Pas de Nord pour les case en haut du plateau
            return UINT_MAX;
        }
    }
    if(idx/WIDTH == WIDTH - 2){
        if(d == SOUTH || d == SWEST || d == SEAST){ // Pas de Sud pour les case en bas du plateau
            return UINT_MAX;
        }
    }
    if(idx%WIDTH == 0){
        if(d == SWEST || d == NWEST || d == WEST){ // Pas d'Ouest pour les case à gauche du plateau
            return UINT_MAX;
        }
    }
    if(idx%WIDTH == WIDTH - 1){
        if(d == SEAST || d == NEAST || d == EAST){ // Pas d'Est pour les case à droite du plateau
            return UINT_MAX;
        }
    }
    if(((idx%WIDTH)%2) == 0){ //CASE EN BAS
        if(d == NWEST || d == NEAST){ // Structure à 6 voisins, on ne prends pas Nord Est et Nord Ouest
            return UINT_MAX;
        }
    }
    if(((idx%WIDTH)%2) == 1){ //CASE EN HAUT
        if(d == SWEST || d == SEAST){ // Structure à 6 voisins, on ne prends pas Sud Est et Sud Ouest
            return UINT_MAX;
        }
    }
    if(d == EAST){
        return idx + 1;
    }
    if(d==WEST){
        return idx - 1;
    }
    if(d==NORTH){
        return idx - WIDTH;
    }
    if(d == SOUTH){
        return idx + WIDTH;
    }
    if( d == SEAST){
      return idx + WIDTH + 1;
    }
    if(d == SWEST){
      return idx + WIDTH - 1;
    }
    if( d == NWEST){
      return idx - WIDTH - 1;
    }
    if( d == NEAST){
      return idx - WIDTH + 1;
    }
  return UINT_MAX;
}

struct neighbors_t get_neighbors_hex(unsigned int idx){
  struct neighbors_t neighbors; 
  enum dir_t d;
  unsigned int k=0;
  for(d = -4; d<=4; d++) //Ajout de tout les voisins possible.
  {
    unsigned int ind=get_neighbor_hexagon(idx,d);
    if(ind<UINT_MAX)
    {
      neighbors.n[k].i=ind;
      neighbors.n[k].d=d;
      k++;
    }
  }
  neighbors.n[k].i=UINT_MAX; //marquer la fin des voisins par UINT_MAX.
  k++;
  while(k<MAX_NEIGHBORS+1) //Completion par des zeros.
  {
    neighbors.n[k].i=0;
    k++;
  }
  return neighbors;
}