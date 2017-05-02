/*
 * File:   maze.cpp
 * Author: ronald_baasland
 *
 * Created on February 12, 2011
 * Modified on February 19, 2011
 *
 * This program take input from a file with 225 characters of 0's, 1's an S, and
 * an F. The 0's represent areas not in the maze. The 1's represents parts of the
 * maze path. S is the start of the maze, and F is the finish. This program will
 * work for any 2-dimensional array of 15x15. The program recursiveley goes
 * through to test if each spot heads to the finish. If it does the spot remains
 * an X and goes to the next possible path. If a path is not found, then the spot
 * is returned to a 1.
 */

#include <iostream> //Used for input and output to the console
#include <fstream> //Used for input and output to a file
using namespace std;

void setMaze(char[][15]); // This function reads input from a file, and sets the 2d array from the input
void printMaze(char[][15]); //This function prints the 2D array of the Maze
bool findPath(int, int, char [][15]); //Recursivly finds a path to the finish of the maze
void findStart(char [][15], int []); //Finds where the start of the maze is


int main()
{
    char maze[15][15]; // 2D-Array for maze
    int startPosition[2]; //Array to hold the position of the Start
    bool test; //Bool variable to return the function of findPath()
    setMaze(maze); //call to set the maze from the file input
    findStart(maze, startPosition); //cll to find the start of the maze
    cout << "Here is the original Maze" << endl;
    printMaze(maze); //Prints the maze before searched
    test = findPath(startPosition[0],startPosition[1],maze); //bool value to hold the value of the function call to findPath
    cout << endl << "Here is the Path to the Maze" << endl;
    printMaze(maze); //Prints the maze after a path is found

    return 0;
}

/*
 * Function: setMaze()
 *
 * This function take the 2D array, and sets the array based upon the input from
 * the file.
 */

void setMaze(char temp[][15])
{
    ifstream infile;
    infile.open("Maze.txt");
    char maze1;

    if(infile) // If the file has data
    {
        for (int i = 0; i < 15; i++)
        {
            for (int j = 0; j < 15; j++)
            {
                infile >> maze1;
                temp[i][j] = maze1;
            }
        }
    }
    infile.close(); //Closes the file
}

/* Function: printMaze()
 *
 * This function takes the 2D array of the maze, and then outputs the array based
 * upon the input from the file, and after a path has been found.
 *
 */

void printMaze(char temp[][15])
{
    cout << "---------------------------------" << endl;
    for(int i = 0; i < 15; i++)
    {
        cout << "| ";
        for(int j = 0; j < 15; j++)
         {
            cout << temp[i][j] << " ";
         }
        cout << "|";
        cout << endl;
    }
    cout << "---------------------------------" << endl;
}

/*
 * Function: findPath
 *
 * This function takes the position of the start, and the 2D array containing the
 * maze. It returns true or false based on if a path to the finish is found from
 * that position. It recursively finds a path to the finish, marking an X along
 * the way.
 */

bool findPath(int x, int y, char temp[][15])
{

    enum mazeDirection {North, East, South, West, Failed}; //Enum to change direction
    mazeDirection direction; //instance of the enum
    bool found; //Bool value to see if a path is found or not

    if (temp[x][y] == 'F') //If the position if the finish
    {
        return true;
    }
    else if (temp[x][y] == 'X' || temp[x][y] == '0') //If the position already has a path, or is a 0
    {
        return false;
    }
    else
    {

        direction = North; //Direction is set to the first direction of North
        if (temp[x][y] == '1') //If the position is part of the maze
        {
            temp[x][y] = 'X'; //Set the position to an X
            found = false; // Set found equal to false
        }

        /*
         * This while loop checks to see if the position hasnt been checked to see
         * if there is a path to the finish, and if it hasnt checked all the 4
         * directions.
         */

        while(found == false && direction != Failed)
        {
            if (direction == North)
            {
                found = findPath(x, y-1, temp); //Checks the spot above the position
            }
            else if (direction == East)
            {
                found = findPath(x+1, y, temp); //Checks the spot to the right of the position
            }
            else if (direction == South)
            {
                found = findPath(x, y+1, temp); //Checks the spot below the position
            }
            else if (direction == West)
            {
                found = findPath(x-1, y, temp); //Checks the sport to the left of the position
            }

            direction = (mazeDirection)(direction + 1); //Change the direction to the next direction

        }
          if (found == false && temp[x][y] == 'X') // only when you did not find a path  and the previous value is 1, you backtrack .
          {
             temp[x][y] = '1'; //Sets the position back to the original value if a path is not found to the finish
          }

        return found; // you return whatever value for found you got from while loop.

    }// end of the last if statement
}

/* Function: findStart()
 *
 * This function takes the maze 2d array, and an empty array and searches the 2D
 * array to find where the start position is, and then sets the empty array to the
 * position of the start of the maze.
 *
 */

void findStart(char temp[][15], int pos[])
{
    for (int i = 0; i < 15; i++)
    {
        for (int j = 0; j < 15; j++)
        {
            if (temp[i][j] == 'S')
            {
                pos[0] = i; //sets the column of the start
                pos[1] = j; //sets the row of the start
            }
        }
    }
}