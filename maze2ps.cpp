#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

const double kPageWidth = 595.0;  // A4 page width in points
const double kPageHeight = 842.0; // A4 page height in points
const double kMargin = 20.0;      // margin around the maze in points
const double kCellSize = 20.0;    // size of each maze cell in points
const double kLineWidth = 2.0;    // width of maze walls in points

void drawLine(ofstream &file, double x1, double y1, double x2, double y2, double width)
{
    file << x1 << " " << y1 << " moveto " << x2 << " " << y2 << " lineto "
         << width << " setlinewidth " << " stroke" << endl;
}

void drawMaze(const vector<string> &maze, ofstream &file)
{
    double x = kMargin + kLineWidth / 2.0;
    double y = kMargin + kLineWidth / 2.0;
    file << "newpath" << endl;
    drawLine(file, x, y, x, y + kCellSize * (maze.size() - 1), kLineWidth);    // left wall of maze
    drawLine(file, x, y, x + kCellSize * (maze[0].size() - 1), y, kLineWidth); // top wall of maze

    std::cout << maze.size() << std::endl;

    for (int i = 0; i < maze.size(); ++i)
    {
        for (int j = 0; j < maze[i].size(); ++j)
        {
            if (maze[i][j] == '+')
            {
                // draw corners of maze cell
                double cx = x + kCellSize * j;
                double cy = y + kCellSize * i;
                drawLine(file, cx - kLineWidth / 2.0, cy + kCellSize + kLineWidth / 2.0, cx + kLineWidth / 2.0,
                         cy + kCellSize + kLineWidth / 2.0, kLineWidth);
                drawLine(file, cx + kCellSize + kLineWidth / 2.0, cy + kCellSize + kLineWidth / 2.0,
                         cx + kCellSize + kLineWidth / 2.0, cy + kLineWidth / 2.0, kLineWidth);
                drawLine(file, cx + kCellSize + kLineWidth / 2.0, cy + kLineWidth / 2.0,
                         cx + kCellSize - kLineWidth / 2.0, cy + kLineWidth / 2.0, kLineWidth);
                drawLine(file, cx + kLineWidth / 2.0, cy + kLineWidth / 2.0, cx + kLineWidth / 2.0,
                         cy + kCellSize - kLineWidth / 2.0, kLineWidth);
            }
            else if (maze[i][j] == '-')
            {
                // draw horizontal wall
                double cx = x + kCellSize * j;
                double cy = y + kCellSize * i;
                drawLine(file, cx + kLineWidth / 2.0, cy + kCellSize + kLineWidth / 2.0,
                         cx + kCellSize - kLineWidth / 2.0, cy + kCellSize + kLineWidth / 2.0, kLineWidth);
            }
            else if (maze[i][j] == '|')
            {
                // draw vertical wall
                double cx = x + kCellSize * j;
                double cy = y + kCellSize * i;
                drawLine(file, cx + kCellSize + kLineWidth / 2.0, cy + kCellSize + kLineWidth / 2.0,
                         cx + kCellSize + kLineWidth / 2.0, cy + kLineWidth / 2.0, kLineWidth);
            }
        }
    }
}

int main()
{
    // read maze from stdin
    vector<string> maze;
    string line;
    while (getline(cin, line))
    {
        maze.push_back(line);
    }

    // create output file and write PostScript header
    ofstream file("maze.ps");
    file << "%!PS-Adobe-3.0" << endl;
    file << "%%BoundingBox: 0 0 " << kPageWidth << " " << kPageHeight << endl;
    file << "%%EndComments" << endl;

    // draw maze
    drawMaze(maze, file);

    // write PostScript trailer and close file
    file << "showpage" << endl;
    file.close();

    return 0;
}
