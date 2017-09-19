/* Dan Su
 * March 19, 2017
 * Part of my A* project
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "Astar.h"

void int2dFree(int **b,int rows)
{
	for (int i = 0; i < rows; i++){
		free(b[i]);
	}
	free(b);
}
void point2dFree(point ***p, int rows, int columns)
{
	for (int i = 0; i < rows; i++){
		for (int j = 0; j < columns; j++){
			if(p[i][j])
				free(p[i][j]);
		}
		free(p[i]);
	}
	free(p);
}

void boardFree(board *b)
{
	int2dFree(b->tiles,b->rows);
	free(b);
}

void pathFree(path *p)
{
	for(int i = 0; i < p->length; i++){
		free(p->tiles[i]);
	}
	free(p);
}

point* pt(int x, int y)
{
	point *p = (point*) malloc(sizeof(point));
	p->x = x;
	p->y = y;
	return p;
}

int** blank2d(int rows, int columns)
{
	int **b = (int**)malloc(rows * sizeof(int*));
	for (int i = 0; i < rows; i++){
		int *r = (int*)calloc(columns,sizeof(int));
		b[i] = r;
	}
	return b;
}

point*** point2d(int rows, int columns)
{
	point ***b = (point***)malloc(rows * sizeof(point**));
	for (int i = 0; i < rows; i++){
		point **r = (point**)malloc(columns * sizeof(point*));
		b[i] = r;
	}
	return b;
}

path* neighbors(point *a)
{
	int x = a->x;
	int y = a->y;
	point **tiles = (point**) malloc(4 * sizeof(point*));
	tiles[0] = pt(x,y-1);
	tiles[1] = pt(x,y+1);
	tiles[2] = pt(x-1,y);
	tiles[3] = pt(x+1,y);
	path *p = (path*) malloc(sizeof(path));
	p->tiles = tiles;
	p->length = 4;
	return p;
}

int valid(board *b, point *p)
{
	if((p->x >= 0) &&
		(p->y >= 0) &&
		(p->x < b->columns) &&
		(p->y < b->rows))
		return 1;
	else
		return 0;
}

int reachable(int tile, int filter)
{
	if((tile == 0) || (tile == filter))
		return 1;
	else
		return 0;
}

plist* newPlist(point *p)
{
	plist *pl = (plist*) malloc(sizeof(plist));
	pl->tile = p;
	pl->rest = NULL;
	return pl;
}

plist* pCons(point *p, plist *pl)
{
	plist *newPl = newPlist(p);
	newPl->rest = pl;
	return newPl;
}

plist* pRemove(point *p, plist *pl)
{
	if(!pl){
		fprintf(stderr, "pRemove: couln't find (%d, %d)\n",p->x,p->y);
		return NULL;
	}
	if(pl->tile->x == p->x && pl->tile->y == p->y)
		return pl->rest;
	plist *ans = pl;
	while(pl){
		plist *temp = pl->rest;
		if(temp){
			if(temp->tile->x == p->x && temp->tile->y == p->y){
				pl->rest = temp->rest;
				free(temp->tile);
				free(temp);
				return ans;
			}
		}else{
			break;
		}
		pl = temp;
	}
		fprintf(stderr, "pRemove: couln't find (%d, %d)\n",p->x,p->y);
	return ans;
}
void pLFree(plist *pl)
{
	while(pl){
		plist *temp = pl;
		free(temp->tile);
		free(temp);
		pl = pl->rest;
	}
}