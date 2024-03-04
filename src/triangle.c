#include "project.h"

//This file has all the laws related the triangular table.(getting neighbor)

//Gets the neighbor of a piece in a direction.
unsigned int get_neighbor_triangle(unsigned int idx, enum dir_t d){
    if(idx/WIDTH == 0){
        if(d == NORTH || d == NEAST || d == NWEST){ //No north allowed for slots on the north.
            return UINT_MAX;
        }
    }
    if(idx/WIDTH == WIDTH - 2){
        if(d == SOUTH || d == SWEST || d == SEAST){ //No south for slots in the south.
            return UINT_MAX;
        }
    }
    if(idx%WIDTH == 0){
        if(d == SWEST || d == NWEST || d == WEST){ //No west for slots in the west.
            return UINT_MAX;
        }
    }
    if(idx%WIDTH == WIDTH - 1){
        if(d == SEAST || d == NEAST || d == EAST){ //No east for slots in the east.
            return UINT_MAX;
        }
    }
    /*
    if(((idx%WIDTH)%2) == 0){ //Case high.
        if(d == NWEST || d == NEAST){ //Structure with 6 neighbors, we don't take the North West and North East.
            return UINT_MAX;
        }
    }
    if(((idx%WIDTH)%2) == 1){ //Case low.
        if(d == SWEST || d == SEAST){ //Structure with 6 neighbors, we don't take the South West and South East.
            return UINT_MAX;
        }
    }
    */
    if(idx%2==0){ //The triangle is pointing to the north => vertical neighbor to the south.
        if(d==EAST){
            idx++;
            return idx;
        }
        if(d==WEST){
            idx--;
            return idx;
        }
        if(d==SOUTH){
            idx+=WIDTH;
            return idx;
        }else{
            return UINT_MAX;
        }
    }
    if(idx%2!=0){ //The triangle is pointing to the south => vertical neighbor to the north.
        if(d==EAST){
            idx++;
            return idx;
        }
        if(d==WEST){
            idx--;
            return idx;
        }
        if(d==NORTH){
            idx-=WIDTH;
            return idx;
        }else{
            return UINT_MAX;
        }
    }
    return UINT_MAX;
}

