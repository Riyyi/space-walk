#ifndef SELECTIONBOX_H
#define SELECTIONBOX_H

#include <string>

#include "window.h"

class SelectionBox : public Window
{
public:
	SelectionBox(int height, int width);

	void update();
	void resize();

	unsigned char select(std::string str, std::string *selection);
	void printSelection(std::string str, std::string *selection);

private:
	bool isNumber(const std::string &s);

	int height;
	int width;
};

#endif // SELECTIONBOX_H
