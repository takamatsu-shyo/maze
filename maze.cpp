#include <chrono>
#include <iostream>
#include <random>
#include <stack>
#include <vector>

using namespace std;

// Define a struct to represent a cell in the maze
struct Cell
{
    bool visited;
    bool top_wall;
    bool bottom_wall;
    bool left_wall;
    bool right_wall;

    Cell()
    {
        visited = false;
        top_wall = true;
        bottom_wall = true;
        left_wall = true;
        right_wall = true;
    }
};

// Define a struct to represent the maze
struct Maze
{
    int width;
    int height;
    vector<Cell> cells;

    Maze(int w, int h)
    {
        width = w;
        height = h;
        cells = vector<Cell>(w * h);
    }

    Cell &getCell(int x, int y)
    {
        return cells[y * width + x];
    }
};

// Define a function to get a random direction
pair<int, int> randomDirection()
{
    static random_device rd;
    static mt19937 gen(rd());
    
    static uniform_int_distribution<int> dir(0, 3);

    switch (dir(gen))
    {
    case 0:
        return {-1, 0}; // Left
    case 1:
        return {1, 0}; // Right
    case 2:
        return {0, -1}; // Up
    case 3:
        return {0, 1}; // Down
    }
}

// Define the recursive backtracker algorithm
void recursiveBacktracker(Maze &maze, int x, int y)
{
    stack<pair<int, int>> cellStack;
    maze.getCell(x, y).visited = true;
    cellStack.push({x, y});

    while (!cellStack.empty())
    {
        auto [x, y] = cellStack.top();
        maze.getCell(x, y).visited = true;
        vector<pair<int, int>> neighbors;

        // Check neighboring cells that haven't been visited
        if (x > 0 && !maze.getCell(x - 1, y).visited)
            neighbors.push_back({x - 1, y}); // Left
        if (x < maze.width - 1 && !maze.getCell(x + 1, y).visited)
            neighbors.push_back({x + 1, y}); // Right
        if (y > 0 && !maze.getCell(x, y - 1).visited)
            neighbors.push_back({x, y - 1}); // Up
        if (y < maze.height - 1 && !maze.getCell(x, y + 1).visited)
            neighbors.push_back({x, y + 1}); // Down

        if (!neighbors.empty())
        {
            // Choose a random neighbor to visit
            auto [nx, ny] = neighbors[rand() % neighbors.size()];
            auto &currentCell = maze.getCell(x, y);
            auto &nextCell = maze.getCell(nx, ny);

            // Remove the wall between the cells
            if (nx < x)
            { // Left
                currentCell.left_wall = false;
                nextCell.right_wall = false;
            }
            else if (nx > x)
            { // Right
                currentCell.right_wall = false;
                nextCell.left_wall = false;
            }
            else if (ny < y)
            { // Up
                currentCell.top_wall = false;
                nextCell.bottom_wall = false;
            }
            else if (ny > y)
            { // Down
                currentCell.bottom_wall = false;
                nextCell.top_wall = false;
            }

            cellStack.push({nx, ny});
        }
        else
        {
            // Back
            cellStack.pop();
        }
    }
}

// Define a function to print the maze
void printMaze(Maze &maze)
{
    for (int y = 0; y < maze.height; y++)
    {
        // Print the top wall of each cell in the first row
        for (int x = 0; x < maze.width; x++)
        {
            cout << "+";
            if (maze.getCell(x, y).top_wall)
                cout << "-";
            else
                cout << " ";
        }
        cout << "+" << endl;

        // Print the left and right walls (and the cell contents) of each cell in
        // the row
        for (int x = 0; x < maze.width; x++)
        {
            if (maze.getCell(x, y).left_wall)
                cout << "|";
            else
                cout << " ";
            cout << " ";
            if (x == maze.width - 1)
            {
                if (maze.getCell(x, y).right_wall)
                    cout << "|";
                else
                    cout << " ";
            }
        }
        cout << endl;

        // Print the bottom wall of each cell in the row below
        if (y == maze.height - 1)
        {
            for (int x = 0; x < maze.width; x++)
            {
                cout << "+";
                if (maze.getCell(x, y).bottom_wall)
                    cout << "-";
                else
                    cout << " ";
            }
            cout << "+" << endl;
        }
    }
}

int main()
{
    std::srand(std::time(nullptr));

    // Set up the maze
    int width = 20;
    int height = 10;
    Maze maze(width, height);

    // Run the algorithm to generate the maze
    auto start = chrono::steady_clock::now();
    recursiveBacktracker(maze, 0, 0);
    auto end = chrono::steady_clock::now();

    // Print the maze and the generation time
    printMaze(maze);
    cout << "Maze generated in " << chrono::duration_cast<chrono::milliseconds>(end - start).count() << " milliseconds."
         << endl;

    return 0;
}
