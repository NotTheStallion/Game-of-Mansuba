#include "project.h"


void print_get_neighbors(unsigned int index){
    struct neighbors_t print;
    print = get_neighbors(index);
    printf("On regarde les voisins du pion à la position : %d", i);
    for(int j = 0; j < MAX_NEIGHBORS; j++){
        printf("Le voisin à la direction %c a l'indice %d",dir_to_string(print.n[j].d, print.n[j].i));
    }
}