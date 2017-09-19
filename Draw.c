/* Dan Su
 * March 19, 2017
 * Part of my A* project
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "Astar.h"


int** pathToArray(path* p, int** blank)
{
	for (int i = 0; i < p->length; i++){
		int c;
		if(i == 0)
			c = 10;
		else if(i == p->length -1)
			c = 11;
		else
			c = 1;
		blank[p->tiles[i]->y][p->tiles[i]->x] = c;
	}
	return blank;
}

board* boardToArray(const char* f)
{
	FILE* file = fopen(f,"r");
  	//count number of integers by counting line breaks + spaces + 1
  	//count current line length with currentLength
  	//length is stored into lineLength
  	//count longest line with longest
  	//lineNum tracks the lines
	int longest = 0;
	int currentLength = 0;
	int lineLength[512];
  	int count = 0;
  	int lineNum = 0;
  	char c;
  	while (1) {
  		c = fgetc(file);
    	if(c == ' '){
    		currentLength++;
    		count++;
    	}else if(c == '\n'){
    		count++;
    		currentLength++;
    		longest = fmax(longest,currentLength);
    		lineLength[lineNum++] = currentLength;
    		currentLength = 0;
    	}else if(c == EOF){
    		count++;
    		currentLength++;
    		longest = fmax(longest,currentLength);
    		lineLength[lineNum++] = currentLength;
    		break;
    	}
    }
    rewind(file);
    // lines holds data of integers
    // line is current line of integers
    // pos is position in line
    // currentLine tracks position in lines and lineLength
    // lbuffer is number of leading -1's we put
    // to compensate for some lines being shorter
	int **lines = (int**)malloc(lineNum * sizeof(int*));
	int *line;
	int pos = 0;
    int currentLine = 0;
    int num;
    int lbuffer;
    while(currentLine < lineNum){
    	if(pos == 0){
    		line = (int*) malloc(longest*sizeof(int));
    		lbuffer = (longest - lineLength[currentLine]) / 2;
    		int i;
    		for (i = 0; i < longest; i++){
    			line[i] = -1;
    		}
    	}
    	fscanf(file,"%d",&num);
    	line[lbuffer + pos] = num;
    	if(++pos == lineLength[currentLine]){
    		pos = 0;
    		lines[currentLine++] = line;
    	}
    }
    currentLine = 0;
    pos = 0;
    //test
    /*while(currentLine < lineNum){
    	if(pos == 0){
    		lbuffer = (longest - lineLength[currentLine]) / 2;
    	}
    	fprintf(stderr,"%d ", lines[currentLine][pos]);
    	if(++pos == longest){
    		fprintf(stderr, "\n");
    		pos = 0;
    		currentLine++;
    	}
    }*/
    
  	fclose (file);
  	/*int i;
  	for(i = 0; i < lineNum; i++){
  		free(lines[i]);
  	}
  	free(lines);*/
	board *b = (board*) malloc(sizeof(board));
	b->tiles = lines;
	b->rows = lineNum;
	b->columns = longest;
  	return b;
}

void drawBoard(board* board, int** highlights, int width, int height)
{
	//add support for optional and default w, h values later
	int w = width;
	int h = height;

	//b values track arrays on the board
	//t values track individual pixels per tile
	int bRow = 0;
	int bCol = 0;
	int tRow = 0;
	int tCol = 0;

	printf("P3\n");
  	printf("%d %d\n",h * board->columns,h * board->rows);
  	printf("255\n");
	for (bRow = 0; bRow < board->rows; bRow++){
		for (tRow = 0; tRow < h; tRow++){
			for (bCol = 0; bCol < board->columns; bCol++){
				color *c = (color*) malloc(sizeof(color));
				switch(board->tiles[bRow][bCol]){
					case 0:{
						c->r = 80;
						c->g = 80;
						c->b = 80;
					}break;
					default:{
						c->r = 255;
						c->g = 255;
						c->b = 255;
					}
				}
				color *mix = (color*) malloc(sizeof(color));
				switch(highlights[bRow][bCol]){
					case 10:{
						mix->r = 400;
						mix->g = 50;
						mix->b = 50;
					}break;
					case 11:{
						mix->r = 50;
						mix->g = 50;
						mix->b = 400;
					}break;		
					case 1:{
						mix->r = 50;
						mix->g = 400;
						mix->b = 50;
					}break;				
					default:{
						mix->r = 255;
						mix->g = 255;
						mix->b = 255;
					}
				}

				c->r = fmin(255,(c->r * mix->r) / 255);
				c->g = fmin(255,(c->g * mix->g) / 255);
				c->b = fmin(255,(c->b * mix->b) / 255);
				for (tCol = 0; tCol < w; tCol++){
						fprintf(stdout,"%d %d %d\n", c->r,c->g,c->b);
				}
				free(c);
			}
		}
	}
}
