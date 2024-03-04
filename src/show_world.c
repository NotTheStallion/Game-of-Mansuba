#include "project.h"

//Shows the world, but with square relations.
void show_world_square(struct world_t* world)
{
    for(int i = 0; i <WORLD_SIZE ; i++){
      if(world_get(world,i)==BLACK) //If the piece is black.
      {
        if(world_get_sort(world,i)==PAWN)
        {
          printf("%s"," ⛀ ");
        }
        if(world_get_sort(world,i)==TOUR)
        {
          printf("%s"," ♖ ");
        }
        if(world_get_sort(world,i)==ELEPHANT)
        {
          printf("%s"," ♘ ");
        }
      }
      if(world_get(world,i)==WHITE) //If the piece is white.
      { 
        if(world_get_sort(world,i)==PAWN)
        {
          printf("%s"," ⛂ ");
        }
        if(world_get_sort(world,i)==TOUR)
        {
          printf("%s"," ♜ ");
        }
        if(world_get_sort(world,i)==ELEPHANT)
        {
          printf("%s"," ♞ ");
        }
          
      }
      if(world_get(world,i)==NO_COLOR) //Empty slot.
      {
        printf(" . ");
      }
      if(i%WIDTH == WIDTH-1) //End of the line.
      {
        printf("\n");
      }    
    }
}

//Shows the world, but with hexagonal relations.
//The folowing example is only one line of the square table.
//spaces ⛀ spaces ⛀
//  ⛀ spaces ⛀ spaces 
void show_world_hexagon(struct world_t* world)
{
  int idx=0;
    for(int i = 0; i <HEIGHT ; i++)
    {
      for(int j = 1; j <WIDTH ; j+=2) //Printing the high positions
      {
        idx=i*WIDTH+j;
        if(world_get(world,idx)==BLACK)
        {
          if(world_get_sort(world,idx)==PAWN)
          {
            printf("%s","    ⛀ ");
          }
          if(world_get_sort(world,idx)==TOUR)
          {
            printf("%s","    ♖ ");
          }
          if(world_get_sort(world,idx)==ELEPHANT)
          {
            printf("%s","    ♘ ");
          }
        }
        if(world_get(world,idx)==WHITE)
        { 
          if(world_get_sort(world,idx)==PAWN)
          {
            printf("%s","    ⛂ ");
          }
          if(world_get_sort(world,idx)==TOUR)
          {
            printf("%s","    ♜ ");
          }
          if(world_get_sort(world,idx)==ELEPHANT)
          {
            printf("%s","    ♞ ");
          }
            
        }
        if(world_get(world,idx)==NO_COLOR)//High empty
        {
          printf("    . ");
        }
      }
      printf("\n");
      for(int k = 0; k <WIDTH ; k+=2) //Printing the low positions.
      {
        
        idx=i*WIDTH+k;
        if(world_get(world,idx)==BLACK)
        {
          if(world_get_sort(world,idx)==PAWN)
          {
            printf("%s"," ⛀    ");
          }
          if(world_get_sort(world,idx)==TOUR)
          {
            printf("%s"," ♖    ");
          }
          if(world_get_sort(world,idx)==ELEPHANT)
          {
            printf("%s"," ♘    ");
          }
        }
        if(world_get(world,idx)==WHITE)
        { 
          if(world_get_sort(world,idx)==PAWN)
          {
            printf("%s"," ⛂    ");
          }
          if(world_get_sort(world,idx)==TOUR)
          {
            printf("%s"," ♜    ");
          }
          if(world_get_sort(world,idx)==ELEPHANT)
          {
            printf("%s"," ♞    ");
          } 
        }
        if(world_get(world,idx)==NO_COLOR)//Low empty.
        {
          printf(" .    ");
        }
      }
      printf("\n");
    }
}


//Shows the world, but with triangle relations.
void show_world_triangle(struct world_t* world)
{
    for(int i = 0; i <WORLD_SIZE ; i++){
        if(i%2!=0){
            if(world_get(world,i)==BLACK)
            {
            if(world_get_sort(world,i)==PAWN)
            {
            printf("%s","⛀/");
            }
            if(world_get_sort(world,i)==TOUR)
            {
            printf("%s","♖/");
            }
            if(world_get_sort(world,i)==ELEPHANT)
            {
            printf("%s","♘/");
            }
            }
            if(world_get(world,i)==WHITE)
            { 
            if(world_get_sort(world,i)==PAWN)
            {
            printf("%s","⛂/");
            }
            if(world_get_sort(world,i)==TOUR)
            {
            printf("%s","♜/");
            }
            if(world_get_sort(world,i)==ELEPHANT)
            {
            printf("%s","♞/");
            }
            
            }
            if(world_get(world,i)==NO_COLOR)
            {
                printf("./");
            }
            if(i%WIDTH == WIDTH-1)
            {
            printf("\n");
            }    
        }
        if (i%2==0){
            if(world_get(world,i)==BLACK)
            {
            if(world_get_sort(world,i)==PAWN)
            {
            printf("%s","⛀\\");
            }
            if(world_get_sort(world,i)==TOUR)
            {
            printf("%s","♖\\");
            }
            if(world_get_sort(world,i)==ELEPHANT)
            {
            printf("%s","♘\\");
            }
            }
            if(world_get(world,i)==WHITE)
            { 
            if(world_get_sort(world,i)==PAWN)
            {
            printf("%s","⛂\\");
            }
            if(world_get_sort(world,i)==TOUR)
            {
            printf("%s","♜\\");
            }
            if(world_get_sort(world,i)==ELEPHANT)
            {
            printf("%s","♞\\");
            }
            
            }
            if(world_get(world,i)==NO_COLOR)
            {
                printf(".\\");
            }
            if(i%WIDTH == WIDTH-1)
            {
            printf("\n");
            }                
        }
      
        
    }
}

//Calls functions that show the world but according to the current relations.
void show_world(struct world_t* world){
  if(get_neighbors_seed()==0){
    show_world_square(world);
  }
  if(get_neighbors_seed()==1){
    show_world_hexagon(world);
  }
  if(get_neighbors_seed()==2){
    show_world_triangle(world);
  }
}

