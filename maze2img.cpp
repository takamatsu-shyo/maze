#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>

#define MAX_ROW 1000
#define MAX_COL 1000

// 画像のサイズ
#define IMAGE_WIDTH 430 
#define IMAGE_HEIGHT 230 

// セルのサイズ
#define CELL_WIDTH 10
#define CELL_HEIGHT 10

// ページマージン
#define PAGE_MARGIN_LEFT 10
#define PAGE_MARGIN_RIGHT 10
#define PAGE_MARGIN_TOP 10
#define PAGE_MARGIN_BOTTOM 10

// メイン関数
int main() {
  // 迷路を読み込む
  char maze[MAX_ROW][MAX_COL];
  int _row = 0;
  int _col = 0;
  int row = 0;
  int col = 0;
  char c;
  while ((c = getchar()) != EOF) {
    if (c == '\n') {
      _row++;
      row = _row;
      _col = 0;
    } else {
      maze[_row][_col] = c;
      _col++;
     col = _col;
    }
  }
   
  // 画像を生成する
  cv::Mat image(IMAGE_HEIGHT, IMAGE_WIDTH, CV_8UC3, cv::Scalar(128, 128, 128));
  cv::Point pt1, pt2;
  for (int i = 0; i < row; i++) {
    for (int j = 0; j < col; j++) {
      if (maze[i][j] == '+') {
        // クロス
        ;
        //pt1.x = PAGE_MARGIN_LEFT + j * CELL_WIDTH + CELL_WIDTH / 2;
        //pt1.y = PAGE_MARGIN_TOP + i * CELL_HEIGHT;
        //pt2.x = PAGE_MARGIN_LEFT + j * CELL_WIDTH + CELL_WIDTH / 2;
        //pt2.y = PAGE_MARGIN_TOP + (i + 1) * CELL_HEIGHT;
        //cv::line(image, pt1, pt2, cv::Scalar(0, 0, 0), 1, cv::LINE_AA);
        //pt1.x = PAGE_MARGIN_LEFT + j * CELL_WIDTH;
        //pt1.y = PAGE_MARGIN_TOP + i * CELL_HEIGHT + CELL_HEIGHT / 2;
        //pt2.x = PAGE_MARGIN_LEFT + (j + 1) * CELL_WIDTH;
        //pt2.y = PAGE_MARGIN_TOP + i * CELL_HEIGHT + CELL_HEIGHT / 2;
        //cv::line(image, pt1, pt2, cv::Scalar(0, 0, 0), 1, cv::LINE_AA);
      } else if (maze[i][j] == '-') {
        // 横線
        ;
        //pt1.x = PAGE_MARGIN_LEFT + j * CELL_WIDTH;
        //pt1.y = PAGE_MARGIN_TOP + i * CELL_HEIGHT + CELL_HEIGHT / 2;
        //pt2.x = PAGE_MARGIN_LEFT + (j + 1) * CELL_WIDTH;
        //pt2.y = PAGE_MARGIN_TOP + i * CELL_HEIGHT + CELL_HEIGHT / 2;
        //cv::line(image, pt1, pt2, cv::Scalar(0, 0, 0), 1, cv::LINE_AA);
      } else if (maze[i][j] == '|') {
        // 縦線
        ;
        //pt1.x = PAGE_MARGIN_LEFT + j * CELL_WIDTH + CELL_WIDTH / 2;
        //pt1.y = PAGE_MARGIN_TOP + i * CELL_HEIGHT;
        //pt2.x = PAGE_MARGIN_LEFT + j * CELL_WIDTH + CELL_WIDTH / 2;
        //pt2.y = PAGE_MARGIN_TOP + (i + 1) * CELL_HEIGHT;
        //cv::line(image, pt1, pt2, cv::Scalar(0, 0, 0), 1, cv::LINE_AA);
      } else {
        // 通路
        cv::rectangle(image,
                      cv::Point(PAGE_MARGIN_LEFT + j * CELL_WIDTH,
                                PAGE_MARGIN_TOP + i * CELL_HEIGHT),
                      cv::Point(PAGE_MARGIN_LEFT + (j + 1) * CELL_WIDTH,
                                PAGE_MARGIN_TOP + (i + 1) * CELL_HEIGHT),
                      cv::Scalar(255, 255, 255), cv::FILLED);
      }
    }
  }

  // 画像を表示する
  cv::imshow("maze", image);
  cv::imwrite("maze.png", image);
  cv::waitKey();

  return 0;
}
