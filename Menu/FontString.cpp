#include "FontString.h"
#include "DxLib.h"

int FontString::font = 0;
int FontString::color = 0xffffff;

FontString::FontString(const char* str) {
	this->str = str;
}

void FontString::Load(const char *FileName, int EdgeSize, int _color) {
	Load(LoadFontDataToHandle(FileName, EdgeSize), _color);
}

void FontString::Load(int _font, int _color) {
	font = _font;
	color = _color;
}

void FontString::Draw(int x, int y) {
	if (font != 0)
		DrawStringToHandle(x, y, str.c_str(), color, font);
	else
		DrawString(x, y, str.c_str(), color);
}