#include <cstdio>

#include "gamestate.h"
#include "window.h"

Window::Window(int rows, int cols, int y, int x) :
	rows(rows),
	cols(cols),
	y(0),
	x(0),
	window(newwin(rows, cols, y, x)) {
}

Window::~Window() {
	delwin(this->window);
}

void Window::initialize() {
	// Start curses mode
	initscr();
	// Disable line buffering
	cbreak();
	// Enable reading of function keys
	keypad(stdscr, TRUE);
	// Dont echo while reading input
	noecho();
	// Disable cursor visibility
	curs_set(0);

	// If terminal supports colors
	if(!has_colors()) {
		printw("Your terminal does not support color\n");
	}
	else {
		start_color();
		use_default_colors();

		init_pair(PAIR_WHITE_BLACK, COLOR_WHITE, COLOR_BLACK);
		init_pair(PAIR_WHITE_BRIGHT_BLACK, COLOR_WHITE_BRIGHT, COLOR_BLACK);
		init_pair(PAIR_RED_BLACK, COLOR_RED, COLOR_BLACK);
		init_pair(PAIR_BLUE_BLACK, COLOR_BLUE, COLOR_BLACK);
		init_pair(PAIR_GRAY_BLACK_BRIGHT, COLOR_GRAY, COLOR_BLACK_BRIGHT);
	}

	// Add bright colors, intensity range: 0-1000
	if(!can_change_color()) {
		printw("Your terminal does not support changing colors\n");
	}
	else {
		init_color(COLOR_BLACK,             0,    0,    0);
		init_color(COLOR_WHITE,           680,  680,  680);
		init_color(COLOR_GRAY,            380,  380,  380);

		init_color(COLOR_BLACK_BRIGHT,    110,  110,  110); //   0,   0,   0
		init_color(COLOR_RED_BRIGHT,      900,    0,    0); // 680,   0,   0
		init_color(COLOR_GREEN_BRIGHT,      0,  900,    0); //   0, 680,   0
		init_color(COLOR_YELLOW_BRIGHT,   900,  900,    0); // 680, 680,   0
		init_color(COLOR_BLUE_BRIGHT,       0,    0,  900); //   0,   0, 680
		init_color(COLOR_MAGENTA_BRIGHT,  900,    0,  900); // 680,   0, 680
		init_color(COLOR_CYAN_BRIGHT,       0,  900,  900); //   0, 680, 680
		init_color(COLOR_WHITE_BRIGHT,    900,  900,  900); // 680, 680, 680
	}
}

void Window::update() {
	Window::getMaXYZ(stdscr, this->maxRows, this->maxCols);
}

void Window::render() {
	box(this->window, 0, 0);
	wrefresh(this->window);
}

void Window::destroy() {
	// Restore line buffering
	nocbreak();
	// Restore cursor
	curs_set(1);
	// End curses mode
	endwin();
}

void Window::clear() {
	this->setYX(0, 0);

	// Set background color
	// wbkgdset(this->window, COLOR_PAIR(3));

	// Copy blanks to every position in the window, clearing the screen
	werase(this->window);
}

void Window::resize() {
	wresize(this->window, this->rows, this->cols);
	mvwin(this->window, this->y, this->x);
}

void Window::print(std::string str, char newLine) {
	this->print(str, this->y, this->x);
	this->x += str.length();
	if (newLine == 1) {
		this->x = 0;
		this->y++;
	}
}

void Window::print(std::string str, int y, int x) {
	this->y = y;
	this->x = x;
	mvwprintw(this->window, y + 1, x + 1, str.c_str());
}

void Window::print(std::string str, int y, int x, int attribute) {
	wattron(this->window, attribute);
	this->print(str, y, x);
	wattroff(this->window, attribute);
}

void Window::printCenter(std::string str) {
	int halfBoard = this->cols / 2;
	int halfStr = str.length() / 2;
	this->print(str, this->y, halfBoard - halfStr - 1);
}

void Window::printCenter(std::string str, int attribute) {
	wattron(this->window, attribute);
	this->printCenter(str);
	wattroff(this->window, attribute);
}

void Window::printSide(std::string left, std::string right) {
	this->print(left, this->y, 1);
	this->print(right, this->y, this->cols - right.length() - 3);
}

void Window::getYX(int &y, int &x) {
	getyx(this->window, y, x);
}

void Window::setYX(int y, int x) {
	this->y = y;
	this->x = x;
	wmove(this->window, y, x);
}

void Window::getMaXYZ(int &rows, int &cols) {
	getmaxyx(this->window, rows, cols);
}

void Window::getMaXYZ(WINDOW *window, int &rows, int &cols) {
	getmaxyx(window, rows, cols);
}

std::string Window::getStr() {
	curs_set(1);
	echo();
	char *tmp = new char();
	wgetstr(this->window, tmp);
	noecho();
	curs_set(0);
	return std::string(tmp);
}

int Window::getMaxRows() {
	return this->maxRows;
}

int Window::getMaxCols() {
	return this->maxCols;
}

int Window::getRows() {
	return this->rows;
}

void Window::setRows(int rows) {
	this->rows = rows;
}

int Window::getCols() {
	return this->cols;
}

void Window::setCols(int cols) {
	this->cols = cols;
}

int Window::getY() {
	return this->y;
}

void Window::setY(int y) {
	this->y = y;
}

int Window::getX() {
	return this->x;
}

void Window::setX(int x) {
	this->x = x;
}

void Window::setWindow(int rows, int cols, int y, int x) {
	this->setRows(rows);
	this->setCols(cols);
	this->setY(y);
	this->setX(x);
	if (this->window == nullptr) {
		this->window = newwin(rows, cols, y, x);
	}
}

//----------------------------------------------------------------------------//

Window::Window() :
	rows(0),
	cols(0),
	y(0),
	x(0),
	window(nullptr) {
}
