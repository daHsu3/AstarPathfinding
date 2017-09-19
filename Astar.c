/* Dan Su
 * March 19, 2017
 * Part of my A* project
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "Astar.h"


int main(int argc, char *argv[])
{
	board *b = boardToArray(argv[1]);
	point *a = pt(0,0);
	point *d = pt(b->columns - 1,b->rows - 1);
	path *p = shortestPath(b,a,d,0);
	drawBoard(b,pathToArray(p,blank2d(b->rows,b->columns)),30,30);
	boardFree(b);
	return 0;
}