#pragma once
#include <string>

class FontString {
	static int font;
	static int color;
	std::string str;

public:
	static void Load(const char *FileName, int EdgeSize = 0, int color = 0xffffff);
	static void Load(int font, int color = 0xffffff);
	FontString() {};
	FontString(const char* str);
	void Draw(int x, int y);

	void operator =(const char* str) { this->str = str; }
};