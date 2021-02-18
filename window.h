#ifndef WINDOW_H
#define WINDOW_H

#define COLOR_UNSET 0
#define COLOR_BLACK_BRIGHT 8
#define COLOR_RED_BRIGHT 9
#define COLOR_GREEN_BRIGHT 10
#define COLOR_YELLOW_BRIGHT 11
#define COLOR_BLUE_BRIGHT 12
#define COLOR_MAGENTA_BRIGHT 13
#define COLOR_CYAN_BRIGHT 14
#define COLOR_WHITE_BRIGHT 15
#define COLOR_GRAY 16

#define PAIR_WHITE_BLACK 1
#define PAIR_WHITE_BRIGHT_BLACK 2
#define PAIR_RED_BLACK 3
#define PAIR_BLUE_BLACK 4
#define PAIR_GRAY_BLACK_BRIGHT 5

#include <ncurses.h>
#include <string>

class Window
{
public:
	Window(int rows, int cols, int y, int x);
	~Window();

	static void initialize();
	void update();
	void render();
	static void destroy();
	void clear();
	void resize();

	void print(std::string str, char newLine = 1);
	void print(std::string str, int y, int x);
	void print(std::string str, int y, int x, int attribute);
	void printCenter(std::string str);
	void printCenter(std::string str, int attribute);
	void printSide(std::string left, std::string right);

	void getYX(int &y, int &x);
	void setYX(int y, int x);
	void getMaXYZ(int &rows, int &cols);
	static void getMaXYZ(WINDOW *window, int &rows, int &cols);
	std::string getStr();

	int getMaxRows();
	int getMaxCols();
	int getRows();
	void setRows(int rows);
	int getCols();
	void setCols(int cols);
	int getY();
	void setY(int y);
	int getX();
	void setX(int x);
	void setWindow(int rows, int cols, int y, int x);

protected:
	Window();

private:
	int maxRows;
	int maxCols;
	int rows;
	int cols;
	int y;
	int x;
	WINDOW *window;
};

#endif // WINDOW_H
