#include <iostream>
#include <vector>
#include <stack>
#include <cstdlib>
#include <ctime>

using namespace std;

const int WALL_TOP    = 0b1000;
const int WALL_BOTTOM = 0b0100;
const int WALL_LEFT   = 0b0010;
const int WALL_RIGHT  = 0b0001;

class Maze {
public:
    Maze(int width, int height)
        : m_width(width), m_height(height), m_cells(width * height, 0b1111)
    {
        srand(time(NULL));
        generate();
    }

    int width() const { return m_width; }
    int height() const { return m_height; }
    int at(int x, int y) const { return m_cells[y * m_width + x]; }

private:
    void generate() {
        stack<int> stack;
        stack.push(rand() % (m_width * m_height));
        while (!stack.empty()) {
            int current = stack.top();
            stack.pop();
            if (m_cells[current] == 0) continue;
            int x = current % m_width;
            int y = current / m_width;
            vector<int> neighbors;
            if (y > 0)       neighbors.push_back(current - m_width);
            if (y < m_height - 1) neighbors.push_back(current + m_width);
            if (x > 0)       neighbors.push_back(current - 1);
            if (x < m_width - 1)   neighbors.push_back(current + 1);
            random_shuffle(neighbors.begin(), neighbors.end());
            for (int neighbor : neighbors) {
                if (m_cells[neighbor] == 0) continue;
                if (neighbor == current - m_width) {
                    m_cells[current] &= ~WALL_TOP;
                    m_cells[neighbor] &= ~WALL_BOTTOM;
                } else if (neighbor == current + m_width) {
                    m_cells[current] &= ~WALL_BOTTOM;
                    m_cells[neighbor] &= ~WALL_TOP;
                } else if (neighbor == current - 1) {
                    m_cells[current] &= ~WALL_LEFT;
                    m_cells[neighbor] &= ~WALL_RIGHT;
                } else if (neighbor == current + 1) {
                    m_cells[current] &= ~WALL_RIGHT;
                    m_cells[neighbor] &= ~WALL_LEFT;
                }
                stack.push(current);
                stack.push(neighbor);
                break;
            }
        }
    }

    int m_width;
    int m_height;
    vector<int> m_cells;
};

int main() {
    Maze maze(20, 10);
    for (int y = 0; y < maze.height(); y++) {
        for (int x = 0; x < maze.width(); x++) {
            int cell = maze.at(x, y);
            cout << ((cell & WALL_TOP)    ? " ___ " : "     ");
        }
        cout << endl;
        for (int x = 0; x < maze.width(); x++) {
            int cell = maze.at(x, y);
            cout << ((cell & WALL_LEFT)   ? "|" : " ");
            cout << "   ";
            if (x == maze.width() - 1) cout << "|";
        }
        cout << endl;
        for (int x = 0; x < maze.width(); x++) {
            int cell = maze.at(x, y);
            cout << ((cell & WALL_BOTTOM) ? " ___ " : "     ");
        }
        cout << endl;
    }
    return 0;
}

