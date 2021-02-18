#ifndef MESSAGEBOX_H
#define MESSAGEBOX_H

#include <string>

#include "window.h"

class MessageBox : public Window
{
public:
	MessageBox(std::string message);
	MessageBox(std::string message, std::string title);

private:
};

#endif // MESSAGEBOX_H
