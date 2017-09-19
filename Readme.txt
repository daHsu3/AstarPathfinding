Welcome to my A* Pathfinding! Here's a list of the files and descriptions. If you use or distribute them, please give credit where it's due.
~ Dan Su
https://fierocode.wordpress.com/

Progam dependencies
Astar.h -- specifies what other files do
Astar.c
Draw.c
Pathfinder.c
Utils.c

Compiler and program:
Makefile
astar

Sample Txts:
a.txt
b.txt

==================
To run the program
==================
You need the astar program and a sample txt. Open a command prompt tool (terminal on mac), enter the directory with the files, and type
./astar a.txt >a.ppm
(for example, to run astar on a.txt). A file called a.ppm should now appear, with an image in it! I actually already ran astar on both sample txts, but you can draw your own!

=======================
To draw your own boards
=======================
Currently, my algorithm supports two kinds of tiles. 0 means walkable tile and any other number (I prefer 1) means unwalkable. Create a .txt file and type in your tiles with spaces between them, new lines for a new row of tiles. That's it!
The algorithm will try to find a path from the top left corner to the bottom right. You can modify Astar.c to change where it draws the path from.

====================
To build the program
====================
(You don't need to do this unless you modify the dependencies):
Enter the directory with the files using a command prompt tool (terminal on mac), and type
make astar
This should rebuild the astar program!

To learn more about this algorithm and how I made it visit
https://fierocode.wordpress.com/2017/04/01/a-pathfinding-intro/
Thanks for trying out my software!