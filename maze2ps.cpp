#include <iostream>
#include <string>
#include <vector>

using namespace std;

// 1インチあたりのポイント数
const int POINTS_PER_INCH = 72;

// 余白を指定する
const double MARGIN = 0.5 * POINTS_PER_INCH;

// 迷路の各セルを描画する際のサイズを指定する
const double CELL_SIZE = 30.0;

// PostScriptファイルを生成する関数
void generatePostScript(vector<string> maze) {
  // 迷路の幅と高さを決定する
  int width = 0;
  int height = maze.size();
  for (const string &row : maze) {
    if (row.size() > width) {
      width = row.size();
    }
  }

  // ページサイズを決定する
  double pageWidth = (double)width * CELL_SIZE + 2.0 * MARGIN;
  double pageHeight = (double)height * CELL_SIZE + 2.0 * MARGIN;

  // PostScriptファイルを生成する
  cout << "%!PS-Adobe-3.0" << endl;
  cout << "%%BoundingBox: 0 0 " << pageWidth << " " << pageHeight << endl;

  // ページを開始する
  cout << "%%Page: 1 1" << endl;
  cout << "0 0 translate" << endl;

  // 迷路を描画する
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < maze[i].size(); j++) {
      char c = maze[i][j];
      switch (c) {
      case '+':
        cout << "newpath" << endl;
        cout << j * CELL_SIZE + MARGIN << " "
             << (height - i - 1) * CELL_SIZE + MARGIN << " moveto" << endl;
        cout << "0 " << CELL_SIZE << " rlineto" << endl;
        cout << CELL_SIZE << " 0 rlineto" << endl;
        cout << "0 -" << CELL_SIZE << " rlineto" << endl;
        cout << "-" << CELL_SIZE << " 0 rlineto" << endl;
        cout << "closepath" << endl;
        cout << "stroke" << endl;
        break;
      case '-':
        cout << "newpath" << endl;
        cout << j * CELL_SIZE + MARGIN << " "
             << (height - i - 1) * CELL_SIZE + MARGIN + CELL_SIZE / 2
             << " moveto" << endl;
        cout << CELL_SIZE << " 0 rlineto" << endl;
        cout << "stroke" << endl;
        break;
      case '|':
        cout << "newpath" << endl;
        cout << j * CELL_SIZE + MARGIN + CELL_SIZE / 2 << " "
             << (height - i - 1) * CELL_SIZE + MARGIN << " moveto" << endl;
        cout << "0 " << CELL_SIZE << " rlineto" << endl;
        cout << "stroke" << endl;
        break;
      case ' ':
        // 通れるセルは何も描画しない
        break;
      }
    }
  }
  // ページを終了する
  cout << "showpage" << endl;
}

int main() {
  // 迷路のデータを読み込む
  vector<string> maze;
  string line;
  while (getline(cin, line)) {
    maze.push_back(line);
  }

  // PostScriptファイルを生成する
  generatePostScript(maze);

  return 0;
}
