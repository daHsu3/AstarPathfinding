/* Dan Su
 * March 19, 2017
 * Part of my A* project
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "Astar.h"


int g(point *a, point *b, int **g)
{
	//b isn't used but if distance formula is more complicated
	//or neighbors function is changed, we'll need it
	return g[a->y][a->x] + 1;
}

int h(point *b, point *dest)
{
	return abs(dest->x - b->x) + abs(dest->y - b->y);
}

void updateF(int x, int y, int **gs, int **hs, int **fs)
{
	fs[y][x] = gs[y][x] + hs[y][x];
}

void newParent(point *child, point *par, point ***parents)
{
	int x = child->x;
	int y = child->y;
	if(parents[y][x])
		free(parents[y][x]);
	parents[y][x] = pt(par->x,par->y);
}

path* shortestPath(board *b, point *start, point *dest, int filter)
{
	int **closed = blank2d(b->rows,b->columns);
	int **open = blank2d(b->rows,b->columns);
	//int numOpen = 1;
	plist *openList = NULL;
	int **gScore = blank2d(b->rows,b->columns);
	int **hScore = blank2d(b->rows,b->columns);
	int **fScore = blank2d(b->rows,b->columns);
	point ***parents = point2d(b->rows,b->columns);

	point *a = pt(start->x,start->y);
	openList = pCons(pt(a->x,a->y),openList);
	gScore[a->y][a->x] = 0;
	h(a,dest);
	updateF(a->x,a->y,gScore,hScore,fScore);

	while((a->x != dest->x) || (a->y != dest->y)){
		open[a->y][a->x] = 0;
		pRemove(a,openList);
		closed[a->y][a->x] = 1;
		path *n = neighbors(a);
		for (int i = 0; i < n->length; i++){
			int x = n->tiles[i]->x;
			int y = n->tiles[i]->y;
			if(valid(b,n->tiles[i]) && reachable(b->tiles[y][x],filter)){
				if(closed[y][x] == 0){
					if(open[y][x]){
						int newg = g(a,n->tiles[i],gScore);
						if(newg < gScore[y][x]){
							gScore[y][x] = newg;
							updateF(x,y,gScore,hScore,fScore);
							newParent(n->tiles[i],a,parents);
						}
					}else{
						open[y][x] = 1;
						openList = pCons(pt(x,y),openList);
						gScore[y][x] = g(a,n->tiles[i],gScore);
						hScore[y][x] = h(n->tiles[i],dest);
						updateF(x,y,gScore,hScore,fScore);
						newParent(n->tiles[i],a,parents);
					}

				}
			}
		}
		pathFree(n);
		if(!openList)
			return NULL;

		free(a);
		a = NULL;
		plist *tempList = openList;
		while(tempList){
			int tx = tempList->tile->x;
			int ty = tempList->tile->y;
			if(!a){
				a = pt(tx,ty);
			}else if(fScore[ty][tx] < fScore[a->y][a->x]){
				free(a);
				a = pt(tx,ty);
			}
			tempList = tempList->rest;
		}
	}
	//find length of our path, then generate it
	int length = 1;
	point *par = dest;
	while((par->x != start->x) || (par->y != start->y)){
		par = parents[par->y][par->x];
		length++;
	}
	point **tiles = (point**) malloc(length*sizeof(point*));
	par = dest;
	for(int i = length - 1; i >= 0; i--){
		tiles[i] = pt(par->x,par->y);
		par = parents[par->y][par->x];
	}
	path *p = (path*) malloc(sizeof(path));
	p->tiles = tiles;
	p->length = length;
	int2dFree(closed,b->rows);
	int2dFree(open,b->rows);
	int2dFree(gScore,b->rows);
	int2dFree(hScore,b->rows);
	int2dFree(fScore,b->rows);
	point2dFree(parents,b->rows,b->columns);
	free(a);
	pLFree(openList);
	return p;
}