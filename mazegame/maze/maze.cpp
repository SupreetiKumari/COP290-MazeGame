#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <cstdio>

#define OUTFILE "MAZE"
#define WHITE fprintf(outfile, "%c%c%c", 255,255,255)
#define BLACK fprintf(outfile, "%c%c%c", 0,0,0)
#define RED   fprintf(outfile, "%c%c%c", 102,100,255)
#define GREEN fprintf(outfile, "%c%c%c", 0,204,102)
#define BROWN   fprintf(outfile, "%c%c%c", 0,76,153)
#define GRAY  fprintf(outfile, "%c%c%c", 128,128,128)
#define YELLOW  fprintf(outfile, "%c%c%c", 153,255,255)
#define BLUE   fprintf(outfile, "%c%c%c", 255,178,102)
#define BACK   fprintf(outfile, "%c%c%c", 229,255,204)


int numin=1;     //Number of cells in the maze.
const int xsize=100;
const int ysize=60;


void savebmp(int xspecial, int yspecial);

char MAZE[xsize][ysize]={{'#','#','#','#','#','#','@','@','#','#','#','#','#','%','%','%','%','%','%','%','%',
'&','%','%','%','%','%','%','%','&','%','%','%','%','%','%','%','%','%','%','%','%','%','&','%','%','%','%',
'%','%','%','%','%','%','&','&','&','&','#','#'},
{'#','#','#','#','#','#','@','@','#','#','#','#','#','%','%','%','%','%','%','%','%','&','%','%','%','%','%',
'%','%','&','%','%','%','%','%','%','%','%','%','%','%','%','%','&','%','%','%','%','%','%','%','%','%','%','&',
'&','&','&','#','#'},
{'#','#','#','#','#','#','#','#','#','#','#','#','#','%','%','%','%','%','%','%','%','&','%','%','%','%','%','%',
'%','&','%','%','%','%','%','%','%','%','%','%','%','%','%','&','%','%','%','%','%','%','%','%','%','%','#','#',
'#','#','#','#'},
{'*','*','*','*','*','*','#','#','#','#','#','#','#','%','%','%','%','%','%','%','%','&','%','%','%','%','%','%',
'%','&','%','%','%','%','%','%','%','%','%','%','%','%','%','&','%','%','%','%','%','%','%','%','%','%','#','#',
'#','#','#','#'},
{'*','*','*','*','*','*','#','#','#','#','#','#','#','%','%','%','%','%','%','%','%','&','%','%','%','%','%','%',
'%','&','%','%','%','%','%','%','%','%','%','%','%','%','%','&','%','%','%','%','%','%','%','%','%','%','#','#',
'#','#','#','#'},
{'*','*','*','*','*','*','#','#','*','*','#','#','#','%','%','%','%','%','%','%','%','&','%','%','%','%','%','%',
'%','&','%','%','%','%','%','%','%','%','%','%','%','%','%','&','%','%','%','%','%','%','%','%','%','%','#','#',
'#','#','#','#'},
{'*','*','*','*','*','*','#','#','*','*','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#',
'#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#',
'#','#','@','@'},
{'*','*','*','*','*','*','#','#','*','*','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#',
'#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#',
'#','#','@','@'},
{'*','*','*','*','*','*','#','#','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*',
'*','*','*','*','*','*','*','#','#','$','$','$','%','%','$','$','$','#','#','#','%','%','%','%','&','#','#','#',
'#','%','%','%'},
{'*','*','*','*','*','*','#','#','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*',
'*','*','*','*','*','*','*','#','#','$','$','$','%','%','$','$','$','#','#','#','%','%','%','%','&','#','#','#',
'#','%','%','%'},
{'*','*','*','*','*','*','#','#','*','$','$','$','$','$','$','$','$','*','*','*','*','*','*','*','*','*','*','*',
'*','*','*','*','*','*','*','#','#','$','$','$','%','%','$','$','$','#','#','#','%','%','%','%','&','#','#','#',
'#','%','%','%'},
{'*','*','*','*','*','*','#','#','*','$','$','$','$','$','$','$','$','*','*','*','*','*','*','*','*','*','*','*',
'*','*','*','*','*','*','*','#','#','$','$','$','%','%','$','$','$','#','#','#','%','%','%','%','&','&','*','*',
'*','*','#','#'},				
{'*','*','*','*','*','*','#','#','*','$','$','$','$','$','$','$','$','*','*','*','*','*','*','*','*','*','*','*',
'*','*','*','*','*','*','*','#','#','$','$','$','%','%','$','$','$','#','#','#','%','%','%','%','&','&','*','*',
'*','*','#','#'},					
{'*','*','*','*','*','*','#','#','*','$','$','$','$','$','$','$','$','*','*','*','*','*','*','*','*','*','*','*',
'*','*','*','*','*','*','*','#','#','$','$','$','%','%','$','$','$','#','#','#','%','%','%','%','&','&','*','*',
'*','*','#','#'},	
{'*','*','*','*','*','*','#','#','*','$','$','$','$','$','$','$','$','*','*','*','*','*','*','*','*','*','*','*',
'*','*','*','*','*','*','*','#','#','$','$','$','%','%','$','$','$','#','#','#','%','%','%','%','&','&','*','*',
'*','*','#','#'},				
{'*','*','*','*','*','*','#','#','*','$','$','$','$','$','#','#','#','#','#','#','#','#','#','#','#','#','#','#',
'#','#','#','#','*','*','*','#','#','$','$','$','$','$','$','$','$','#','#','#','%','%','%','%','&','&','#','#',
'#','#','#','#'},			
{'*','*','*','*','*','*','#','#','*','$','$','$','$','$','#','#','#','#','#','#','#','#','#','#','#','#','#','#',
'#','#','#','#','*','*','*','#','#','$','$','$','$','$','$','$','$','#','#','#','%','%','%','%','&','&','#','#',
'#','#','#','#'},	
{'*','*','*','*','*','*','#','#','*','*','*','*','*','*','#','#','#','#','#','#','#','#','#','#','#','#','#','#',
'#','#','#','#','*','*','*','#','#','$','$','$','$','$','$','$','$','#','#','#','%','%','%','%','&','&','*','*',
'*','*','*','*'},						
{'*','*','*','*','*','*','#','#','*','*','*','*','*','*','%','%','%','%','%','%','*','*','*','%','%','%','*','*',
'*','*','#','#','*','*','*','#','#','$','$','$','$','$','$','$','$','#','#','#','%','%','%','%','&','&','*','*',
'*','*','*','*'},					
{'*','*','*','*','*','*','#','#','*','*','*','*','*','*','%','%','%','%','%','%','*','*','*','%','%','%','*','*',
'*','*','#','#','*','*','*','#','#','$','$','$','$','$','$','$','$','#','#','#','%','%','%','%','&','&','*','*',
'*','*','*','*'},					
{'*','*','*','*','*','*','#','#','*','*','*','*','*','*','%','%','%','%','%','%','*','*','*','%','%','%','*','*',
'*','*','#','#','*','*','*','#','#','$','$','$','$','$','$','$','$','#','#','#','&','&','&','&','&','&','*','*',
'*','*','*','*'},
{'*','*','*','*','*','*','#','#','*','*','*','*','*','*','%','%','%','%','%','%','*','*','*','%','%','%','*','*',
'*','*','#','#','*','*','*','#','#','$','$','$','$','$','$','$','$','*','*','*','&','&','&','&','&','&','*','*',
'*','*','*','*'},
{'*','*','*','*','*','*','#','#','#','#','#','#','#','#','%','%','%','%','%','%','*','*','*','%','%','%','*','*',
'*','*','!','!','*','*','*','#','#','$','$','$','$','$','$','$','$','*','*','*','%','%','%','%','%','%','*','*',
'*','*','*','*'},				
{'*','*','*','*','*','*','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#',
'#','!','$','$','!','#','#','#','#','$','$','$','$','$','$','$','$','*','*','*','%','%','%','%','%','%','*','*',
'*','*','*','*'},
{'*','*','*','*','*','*','#','#','#','#','#','#','#','#','%','%','%','%','%','%','#','#','#','#','#','#','#','#',
'#','!','$','$','!','#','#','#','#','*','*','*','*','*','*','*','*','*','*','*','%','%','%','%','%','%','*','*',
'*','*','*','*'},
{'*','*','*','*','*','*','*','*','&','&','%','%','%','%','%','%','%','%','%','%','%','%','%','%','&','&','#','#',
'#','!','$','$','!','#','#','#','#','*','*','*','*','*','*','*','*','*','*','*','%','%','%','%','%','%','*','*',
'*','*','*','*'},
{'*','*','*','*','*','*','*','*','&','&','%','%','%','%','%','%','%','%','%','%','%','%','%','%','&','&','*','*',
'*','*','!','!','*','*','#','#','*','*','*','*','*','*','*','*','*','*','*','*','%','%','%','%','%','%','*','*',
'*','*','*','*'},
{'*','*','*','*','*','*','*','*','&','&','%','%','%','%','%','%','%','%','%','%','%','%','%','%','&','&','*','*',
'*','*','#','#','*','*','#','#','#','#','#','#','#','#','#','#','#','#','#','#','%','%','%','%','%','%','*','*',
'*','*','*','*'},	
{'*','*','*','*','*','*','*','*','&','&','%','%','%','%','%','%','%','%','%','%','%','%','%','%','&','&','*','*',
'*','*','#','#','*','*','#','#','#','#','#','#','#','#','#','#','#','#','#','#','%','%','%','%','%','%','*','*',
'*','*','*','*'},	
{'*','*','*','*','*','*','*','*','&','&','%','%','%','%','%','%','%','%','%','%','%','%','%','%','&','&','*','*',
'*','*','#','#','*','*','%','%','%','%','%','&','%','%','%','%','%','#','#','#','%','%','%','%','%','%','*','*',
'*','*','*','*'},
{'*','*','*','*','*','*','*','*','&','&','%','%','%','%','%','%','%','%','%','%','%','%','%','%','&','&','*','*',
'*','*','#','#','*','*','%','%','%','%','%','&','%','%','%','%','%','#','#','#','&','&','&','&','&','&','*','*',
'*','*','*','*'},
{'*','*','*','*','*','*','*','*','&','&','%','%','%','%','%','%','%','%','%','%','%','%','%','%','&','&','*','*',
'*','*','#','#','*','*','%','%','%','%','%','&','%','%','%','%','%','#','#','#','&','&','&','&','&','&','*','*',
'*','*','*','*'},	
{'*','*','*','*','*','*','*','*','&','&','%','%','%','%','%','%','%','%','%','%','%','%','%','%','&','&','*','*',
'*','*','#','#','*','*','%','%','%','%','%','&','%','%','%','%','%','#','#','#','&','&','&','&','&','&','*','*',
'*','*','*','*'},	
{'*','*','*','*','*','*','*','*','&','&','%','%','%','%','%','%','%','%','%','%','%','%','%','%','&','&','*','*',
'*','*','#','#','*','*','%','%','%','%','%','&','%','%','%','%','%','#','#','#','&','&','&','&','&','&','*','*',
'*','*','*','*'},	
{'*','*','*','*','*','*','*','*','&','&','%','%','%','%','%','%','%','%','%','%','%','%','%','%','&','&','*','*',
'*','*','#','#','*','*','%','%','%','%','%','&','%','%','%','%','%','#','#','#','&','&','&','&','&','&','*','*',
'*','*','*','*'},	
{'*','*','*','*','*','*','*','*','&','&','%','%','%','%','%','%','%','%','%','%','%','%','%','%','&','&','*','*',
'*','*','#','#','*','*','*','*','*','*','*','*','*','*','*','*','*','*','#','#','#','#','#','#','#','#','*','*',
'*','*','*','*'},	
{'*','*','*','*','*','*','*','*','&','&','%','%','%','%','%','%','%','%','%','%','%','%','%','%','&','&','*','*',
'*','*','#','#','%','%','%','%','%','%','&','%','%','%','%','*','*','*','#','#','#','#','#','#','#','#','*','*',
'*','*','*','*'},
{'*','*','*','*','*','*','*','*','&','&','%','%','%','%','%','%','%','%','%','%','%','%','%','%','&','&','*','*',
'*','*','#','#','%','%','%','%','%','%','&','%','%','%','%','*','*','*','#','#','#','#','#','#','#','#','*','*',
'*','*','*','*'},
{'*','*','*','*','*','*','*','*','&','&','&','&','&','&','&','&','&','&','&','&','&','&','&','&','&','&','*','*',
'*','*','#','#','%','%','%','%','%','%','&','%','%','%','%','#','#','#','#','#','#','#','#','#','#','#','*','*',
'*','*','*','*'},
{'*','*','*','*','*','*','*','*','&','&','&','&','&','&','&','&','&','&','&','&','&','&','&','&','&','&','*','*',
'*','*','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','*','*',
'*','*','*','*'},
{'*','*','*','*','*','*','*','*','&','&','&','&','&','&','&','&','&','&','&','&','&','&','&','&','&','&','*','*',
'*','*','#','#','*','*','*','*','*','*','*','*','*','*','*','*','*','*','#','#','%','%','%','%','#','#','*','*',
'*','*','*','*'},
{'*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*',
'*','*','#','#','%','%','%','%','%','%','*','*','*','*','*','*','*','*','#','#','%','%','%','%','#','#','*','*',
'*','*','*','*'},	
{'*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*',
'*','*','#','#','%','%','%','%','%','%','*','*','*','*','*','*','*','*','#','#','%','%','%','%','#','#','*','*',
'*','*','*','*'},	
{'*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*',
'*','*','#','#','%','%','%','%','%','%','*','*','*','*','*','*','*','*','#','#','%','%','%','%','#','#','#','#',
'#','#','*','*'},
{'*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*',
'*','*','#','#','%','%','%','%','%','%','*','*','*','*','*','*','*','*','#','#','#','#','#','#','#','#','#','#',
'#','#','*','*'},	
{'*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*',
'*','*','#','#','%','%','%','%','%','%','*','*','*','*','*','*','*','*','#','#','#','#','#','#','#','#','#','#',
'#','#','*','*'},	
{'*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*',
'*','*','#','#','%','%','%','%','%','%','*','*','*','*','*','*','*','*','#','#','%','%','%','%','%','%','%','%',
'#','#','*','*'},	
{'*','*','%','%','%','%','%','%','%','%','%','%','%','%','%','%','&','&','&','&','$','$','$','$','$','$','$','$',
'&','&','#','#','&','&','&','&','&','&','*','*','*','*','*','*','*','*','#','#','%','%','%','%','%','%','%','%',
'#','#','*','*'},
{'*','*','%','%','%','%','%','%','%','%','%','%','%','%','%','%','&','&','&','&','$','$','$','$','$','$','$','$',
'&','&','#','#','&','&','&','#','#','*','*','*','*','*','*','*','*','*','#','#','%','%','%','%','%','%','%','%',
'#','#','*','*'},
{'*','*','%','%','%','%','%','%','%','%','%','%','%','%','%','%','&','&','&','&','$','$','$','$','$','$','$','$',
'&','&','#','#','&','&','&','#','#','*','*','*','*','*','*','*','*','*','#','#','%','%','%','%','%','%','%','%',
'#','#','*','*'},
{'*','*','%','%','%','%','%','%','%','%','%','%','%','%','%','%','&','&','&','&','$','$','$','$','$','$','$','$',
'&','&','#','#','&','&','&','#','#','*','*','*','*','*','*','*','*','*','#','#','%','%','%','%','%','%','%','%',
'#','#','*','*'},
{'*','*','%','%','%','%','%','%','%','%','%','%','%','%','%','%','&','&','&','&','$','$','$','$','$','$','$','$',
'&','&','#','#','&','&','&','#','#','*','*','*','*','*','*','*','*','*','#','#','&','&','&','&','&','&','&','&',
'#','#','*','*'},
{'*','*','%','%','%','%','%','%','%','%','%','%','%','%','%','%','&','&','&','&','$','$','$','$','$','$','$','$',
'&','&','#','#','&','&','&','#','#','*','*','*','*','*','*','*','*','*','#','#','&','&','&','&','&','&','&','&',
'#','#','*','*'},
{'*','*','%','%','%','%','%','%','%','%','%','%','%','%','%','%','&','&','&','&','$','$','$','$','$','$','$','$',
'&','&','#','#','&','&','&','#','#','*','*','*','*','*','*','*','*','*','#','#','%','%','%','%','%','%','%','%',
'#','#','*','*'},
{'*','*','%','%','%','%','%','%','%','%','%','%','%','%','&','&','&','&','&','&','$','$','$','$','$','$','$','$',
'&','&','#','#','&','&','&','#','#','*','*','*','*','*','*','*','*','*','#','#','%','%','%','%','%','%','%','%',
'#','#','*','*'},
{'*','*','%','%','%','%','%','%','%','%','%','%','%','%','&','&','&','&','&','&','$','$','$','$','$','$','$','$',
'&','&','#','#','&','&','&','#','#','*','*','*','*','*','*','*','*','*','#','#','%','%','%','%','%','%','%','%',
'#','#','*','*'},
{'*','*','%','%','%','%','%','%','%','%','%','%','%','%','&','&','&','&','&','&','&','&','&','&','&','&','&','&',
'&','&','#','#','&','&','&','#','#','*','*','*','*','*','*','*','*','*','#','#','%','%','%','%','%','%','%','%',
'#','#','*','*'},
{'*','*','%','%','%','%','%','%','%','%','%','%','%','%','&','&','&','&','&','&','&','&','&','&','&','&','&','&',
'&','&','#','#','&','&','&','#','#','*','*','*','*','*','*','*','*','*','#','#','%','%','%','%','%','%','%','%',
'#','#','*','*'},
{'*','*','%','%','%','%','%','%','%','%','%','%','%','%','&','&','&','&','&','&','&','&','&','&','&','&','&','&',
'&','&','#','#','&','&','&','#','*','*','*','*','*','*','*','*','*','*','#','#','%','%','%','%','%','%','%','%',
'#','#','*','*'},
{'*','*','%','%','%','%','%','%','%','%','%','%','%','%','&','&','&','&','&','&','$','$','$','$','$','$','$','$',
'&','&','#','#','&','&','&','#','*','*','*','*','*','*','*','*','*','*','#','#','#','#','#','#','#','#','#','#',
'#','#','*','*'},
{'*','*','%','%','%','%','%','%','%','%','%','%','%','%','%','%','&','&','&','&','$','$','$','$','$','$','$','$',
'&','&','#','#','&','&','&','#','*','*','*','*','*','*','*','*','*','*','#','#','#','#','#','#','#','#','#','#',
'#','#','*','*'},
{'*','*','%','%','%','%','%','%','%','%','%','%','%','%','%','%','%','%','&','&','$','$','$','$','$','$','$','$',
'&','&','#','#','&','&','&','#','*','*','*','*','*','*','*','*','*','*','*','*','*','*','#','#','#','#','#','#',
'#','#','*','*'},
{'*','*','%','%','%','%','%','%','%','%','%','%','%','%','%','%','%','%','&','&','$','$','$','$','$','$','$','$',
'&','&','#','#','%','%','%','#','*','*','%','%','%','%','*','*','*','*','*','*','*','*','*','$','$','$','$','*',
'*','*','*','*'},
{'*','*','%','%','%','%','%','%','%','%','%','%','%','%','%','%','%','%','&','&','$','$','$','$','$','$','$','$',
'&','&','#','#','%','%','%','#','*','*','%','%','%','%','*','*','*','*','*','*','*','*','*','$','$','$','$','*',
'*','*','*','*'},
{'*','*','%','%','%','%','%','%','%','%','%','%','%','%','%','%','%','%','&','&','$','$','$','$','$','$','$','$',
'&','&','#','#','%','%','%','#','*','*','%','%','%','%','*','*','*','*','*','*','*','*','*','$','$','$','$','*',
'*','*','*','*'},
{'*','*','%','%','%','%','%','%','%','%','%','%','%','%','%','%','%','%','&','&','$','$','$','$','$','$','$','$',
'&','&','#','#','%','%','%','#','*','*','*','#','#','*','*','*','*','*','*','*','*','*','*','$','$','$','$','*',
'*','*','*','*'},
{'*','*','%','%','%','%','%','%','%','%','%','%','%','%','%','%','%','%','&','&','$','$','$','$','$','$','$','$',
'&','&','#','#','%','%','%','#','*','#','#','#','#','*','*','*','*','*','*','*','*','*','*','$','$','$','$','*',
'*','*','*','*'},
{'*','*','%','%','%','%','%','%','%','%','%','%','%','%','%','%','%','%','&','&','$','$','$','$','$','$','$','$',
'&','&','#','#','%','%','%','#','*','#','%','%','%','%','%','%','*','*','*','*','*','*','*','$','$','$','$','*',
'*','*','*','*'},
{'*','*','%','%','%','%','%','%','%','%','%','%','%','%','%','%','%','%','&','&','$','$','$','$','$','$','$','$',
'&','&','#','#','*','*','*','*','*','#','%','%','%','%','%','%','*','*','*','*','*','*','*','$','$','$','$','*',
'*','*','*','*'},
{'*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*',
'*','*','#','#','*','*','*','*','*','#','%','%','%','%','%','%','*','*','*','*','*','*','*','*','#','#','*','*',
'*','*','*','*'},
{'*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*',
'*','*','#','#','*','*','*','*','*','#','%','%','%','%','%','%','*','*','*','*','*','*','*','*','#','#','*','*',
'*','*','*','*'},
{'*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*',
'*','*','#','#','*','*','*','*','*','#','%','%','%','%','%','%','*','*','*','*','*','*','*','*','#','#','*','*',
'*','*','*','*'},
{'*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*',
'*','*','#','#','*','*','*','*','*','#','%','%','%','%','%','%','*','*','*','*','*','*','*','*','!','!','*','*',
'*','*','*','*'},
{'*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','%','%','%','%',
'%','%','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','!','$','$','!','#',
'#','#','@','@'},
{'*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','%','%','%','%',
'%','%','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','!','$','$','!','#',
'#','#','@','@'},
{'*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','%','%','%','%',
'%','%','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','!','$','$','!','#',
'&','&','&','#'},
{'*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','%','%','%','%',
'%','%','%','*','*','*','*','*','*','%','%','%','%','%','%','*','%','%','%','*','*','*','*','*','!','!','*','#',
'$','$','$','#'},
{'*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','%','%','%','%',
'%','%','%','*','*','*','*','*','*','%','%','%','%','%','%','*','%','%','%','*','*','*','*','*','#','#','*','#',
'$','$','$','#'},
{'*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','%','%','%','%',
'%','%','%','*','*','*','*','*','*','%','%','%','%','%','%','*','%','%','%','*','*','*','*','*','#','#','*','#',
'$','$','$','#'},
{'*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*',
'*','*','*','*','*','*','*','*','*','%','%','%','%','%','%','*','*','*','*','*','*','*','*','*','#','#','*','#',
'%','%','%','#'},
{'*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*',
'*','*','*','*','*','*','*','*','*','%','%','%','%','%','%','*','*','*','*','*','*','*','*','*','#','#','*','#',
'%','%','%','#'},
{'*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*',
'*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','#','#','*','#',
'%','%','%','#'},
{'*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*',
'*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','#','#','*','#',
'%','%','%','#'},
{'*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*',
'*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','#','#','*','#',
'%','%','%','#'},
{'*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*',
'#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','&','&','&','&','@','@','#','#',
'#','#','#','#'},
{'*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*',
'#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','&','&','&','&','@','@','#','#',
'#','#','#','#'},
{'*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*',
'#','#','&','&','&','&','&','&','#','#','&','&','&','&','&','&','&','&','*','*','*','*','*','*','*','*','#','%',
'%','%','%','#'},
{'*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*',
'#','#','&','&','&','&','&','&','#','#','&','&','&','&','&','&','&','&','*','*','*','*','*','*','*','*','#','%',
'%','%','%','#'},
{'*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*',
'#','#','&','&','&','&','&','&','#','#','&','&','&','&','&','&','&','&','*','*','*','*','*','*','*','*','#','%',
'%','%','%','#'},
{'*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*',
'#','#','&','&','&','&','&','&','#','#','&','&','&','&','&','&','&','&','*','*','*','*','*','*','*','*','#','%',
'%','%','%','#'},
{'*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*',
'#','#','&','&','&','&','&','&','#','#','&','&','&','&','&','&','&','&','*','*','*','*','*','*','*','*','#','%',
'%','%','%','#'},
{'*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*',
'#','#','&','&','&','&','&','&','#','#','&','&','&','&','&','&','&','%','%','%','%','*','*','*','*','*','#','#',
'&','&','&','#'},
{'*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*',
'#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','%','%','%','%','*','*','*','*','*','#','#',
'&','&','&','#'},
{'*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*',
'#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','%','%','%','%','*','*','*','*','*','#','#',
'&','&','&','#'},
{'*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*',
'*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','%','%','%','%','*','%','%','*','*','#','#',
'&','&','&','#'},
{'*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*',
'*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','%','%','%','%','*','%','%','*','*','#','#',
'&','&','&','#'},
{'*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*',
'*','*','*','*','*','*','*','*','*','*','*','*','*','@','@','@','*','#','#','#','#','*','#','#','#','#','#','#',
'&','&','&','#'},
{'#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#',
'#','#','#','#','#','#','#','#','#','#','#','#','#','@','@','@','#','#','#','#','#','#','#','#','#','#','#','#',
'#','#','#','#'},
{'#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#',
'#','#','#','#','#','#','#','#','#','#','#','#','#','@','@','@','#','#','#','#','#','#','#','#','#','#','#','#',
'#','#','#','#'},


};						

int main(){
	  
	savebmp(0,0);
	return 0;
}


void savebmp(int xspecial, int yspecial){
	//save a bitmap file! the xspecial, yspecial pixel is coloured red.
	FILE * outfile;
	int extrabytes, paddedsize;
	int x, y, n;
	int width=(xsize-1)*2-1;
	int height=(ysize-1)*2-1;

	extrabytes = (4 - ((width * 3) % 4))%4; 

	char filename[200];
	
	sprintf(filename, "%s_%dx%d_n%d.bmp", OUTFILE, xsize, ysize, numin);
	paddedsize = ((width * 3) + extrabytes) * height;

	unsigned int headers[13] = {paddedsize + 54, 0, 54, 40, width, height, 0, 0, paddedsize, 0, 0, 0, 0};

	outfile = fopen(filename, "wb");
	fprintf(outfile, "BM");

	for (n = 0; n <= 5; n++){
	   fprintf(outfile, "%c", headers[n] & 0x000000FF);
	   fprintf(outfile, "%c", (headers[n] & 0x0000FF00) >> 8);
	   fprintf(outfile, "%c", (headers[n] & 0x00FF0000) >> 16);
	   fprintf(outfile, "%c", (headers[n] & (unsigned int) 0xFF000000) >> 24);
	}

	fprintf(outfile, "%c", 1);fprintf(outfile, "%c", 0);
	fprintf(outfile, "%c", 24);fprintf(outfile, "%c", 0);

	for (n = 7; n <= 12; n++){
	   fprintf(outfile, "%c", headers[n] & 0x000000FF);
	   fprintf(outfile, "%c", (headers[n] & 0x0000FF00) >> 8);
	   fprintf(outfile, "%c", (headers[n] & 0x00FF0000) >> 16);
	   fprintf(outfile, "%c", (headers[n] & (unsigned int) 0xFF000000) >> 24);
	}

	//Actual writing of data begins here:
	for(y = 0; y <= height - 1; y++){
		for(x = 0; x <= width - 1; x++){
			if(x%2 == 1 && y%2 == 1){
				if(x/2+1 == xspecial && y/2+1 == yspecial) RED;
				else{
					if(MAZE[x/2+1][y/2+1].in) WHITE; else BLACK;
				}
			}else if(x%2 == 0 && y%2 == 0){
				BLACK;
			}else if(x%2 == 0 && y%2 == 1){
				if(MAZE[x/2+1][y/2+1].left) BLACK; else WHITE;
			}else if(x%2 == 1 && y%2 == 0){
				if(MAZE[x/2+1][y/2+1].up) BLACK; else WHITE;
			}
		}
		if (extrabytes){     // See above - BMP lines must be of lengths divisible by 4.
			for (n = 1; n <= extrabytes; n++){
				fprintf(outfile, "%c", 0);
			}
		}
	}
	printf("file printed: %s\n", filename); 
	fclose(outfile);
	return;
}

