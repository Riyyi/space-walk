#ifndef INPUTOUTPUT_H
#define INPUTOUTPUT_H

#define KEY_ESC 27
#define KEY_SPACE 32

#include <string>

class IO
{
public:
	static void initialize();
	static void update();

	static std::string trim(std::string str);
	static std::string untrim(std::string str, unsigned int length);

	static int getKeyCode();
	static std::string getKeyName();
	static std::string getStrInput();
	static bool getQuit();
	static void setQuit();

private:
	static int keyCode;
	static bool quit;
};

#endif // INPUTOUTPUT_H
