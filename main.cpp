#include <iostream>
#include <cstdlib>      // rand()
#include <ctime>        // srand(time)
#include <iomanip>      // setw()

#define MAZE_ROW 10
#define MAZE_COLUMN 10

void initMaze(unsigned int Maze[MAZE_ROW][MAZE_COLUMN])
{
    for (int i = 0; i < MAZE_ROW; i++)
    {
        for (int j = 0; j < MAZE_COLUMN; j++)
        {
            Maze[i][j] = 0;
        }
    }
}

void printMaze(unsigned int Maze[MAZE_ROW][MAZE_COLUMN])
{
    for (int i = 0; i < MAZE_ROW; i++)
    {
        for (int j = 0; j < MAZE_COLUMN; j++)
        {
            std::cout << std::setw(3) << Maze[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

void GetNeighbours(unsigned int Maze[MAZE_ROW][MAZE_COLUMN], unsigned int neighbours[4], unsigned int mapxIndex, unsigned int mapyIndex)
{
    if ((mapxIndex > 0) && (Maze[mapxIndex - 1][mapyIndex] == 0)) {
        neighbours[0] = 1;
    }
    else {
        neighbours[0] = 0;
    }

    if ((mapyIndex > 0) && (Maze[mapxIndex][mapyIndex - 1] == 0)) {
        neighbours[1] = 1;
    }
    else {
        neighbours[1] = 0;
    }

    if ((mapxIndex < MAZE_ROW - 1) && (Maze[mapxIndex + 1][mapyIndex] == 0)) {
        neighbours[2] = 1;
    }
    else {
        neighbours[2] = 0;
    }

    if ((mapyIndex < MAZE_COLUMN - 1) && (Maze[mapxIndex][mapyIndex + 1] == 0)) {
        neighbours[3] = 1;
    }
    else {
        neighbours[3] = 0;
    }
}

bool NeighbourAvailable(unsigned int neighbours[])
{
    for (int i = 0; i < 4; i++)
    {
        if (neighbours[i] == 1)
            return true;
    }

    return false;
}

void randomizeMaze(unsigned int Maze[MAZE_ROW][MAZE_COLUMN])
{
    unsigned int counter = MAZE_ROW * MAZE_COLUMN;

    unsigned int currentVal = 1;
    unsigned int mapXIndex = 0;
    unsigned int mapYIndex = 0;
    int randomVal;

    unsigned int neighbours[4] = { 0,0,0,0 };

    Maze[mapXIndex][mapYIndex] = currentVal;
    counter--;

    while (counter > 0)
    {
        GetNeighbours(Maze, neighbours, mapXIndex, mapYIndex);
        if (!NeighbourAvailable(neighbours))
        {
            if (mapXIndex != 0 && Maze[mapXIndex - 1][mapYIndex] == currentVal - 1)
            {
                mapXIndex--;
                currentVal--;
            }
            else if (mapXIndex < MAZE_ROW && Maze[mapXIndex + 1][mapYIndex] == currentVal - 1)
            {
                mapXIndex++;
                currentVal--;
            }
            else if (mapYIndex != 0 && Maze[mapXIndex][mapYIndex - 1] == currentVal - 1)
            {
                mapYIndex--;
                currentVal--;
            }
            else
            {
                mapYIndex++;
                currentVal--;
            }
        }
        else
        {
            do {
                randomVal = rand() % 4;
            } while (neighbours[randomVal] == 0);

            switch (randomVal)
            {
            case 0:
                mapXIndex--;
                break;
            case 1:
                mapYIndex--;
                break;
            case 2:
                mapXIndex++;
                break;
            case 3:
                mapYIndex++;
                break;
            default:
                break;
            }
            currentVal++;
            Maze[mapXIndex][mapYIndex] = currentVal;
            counter--;
        }
    }
}


int main()
{
    std::srand(std::time(0));
    unsigned int Maze[MAZE_ROW][MAZE_COLUMN];
    initMaze(Maze);
    randomizeMaze(Maze);
    printMaze(Maze);

    std::cout << std::endl << std::endl << "Draw a line between numbers that have a value difference is greater than one. " << std::endl << std::endl;
    return 0;
}