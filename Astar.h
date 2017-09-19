#ifndef __ASTAR__
#define __ASTAR__

/* Dan Su
 * March 19, 2017
 * Part of my A* project
 */

 typedef struct {
	int** tiles;
	int columns;
	int rows;
} board;

typedef struct {
	int r;
	int g;
	int b;
} color;

typedef struct {
	int x;
	int y;
} point;

typedef struct {
	point** tiles;
	int length;
} path;

typedef struct plist plist;
struct plist {
	point* tile;
	plist* rest;
};

//Draw
int** pathToArray(path* p, int** blank);
board* boardToArray(const char* f);
void drawBoard(board* board, int** highlights, int width, int height);

//Utils
void int2dFree(int **b,int rows);
void pathFree(path *p);
void point2dFree(point ***p, int rows, int columns);
void boardFree(board* b);
point* pt(int x, int y);
int** blank2d(int rows, int columns);
point*** point2d(int rows, int columns);
path* neighbors(point *a);
int valid(board *b, point *p);
int reachable(int tile, int filter);
plist* newPlist(point *p);
plist* pCons(point *p, plist *pl);
plist* pRemove(point *p, plist *pl);
void pLFree(plist *pl);

//Pathfinder
path* shortestPath(board *b, point *start, point *dest, int filter);

#endif /* __ASTAR__ */