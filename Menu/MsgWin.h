#pragma once
#include <vector>
#include "keyboard.h"

using namespace std;

class WindowContent
{
public:
	virtual ~WindowContent() {}
	virtual void Process() = 0;
	virtual void Draw() = 0;
};


class MsgWindow
{
	int x = 0, y = 0;
	int w, h;
	int screen;
	vector<WindowContent*> content;

public:
	MsgWindow() {}
	MsgWindow(WindowContent *c);
	virtual void Process();
	virtual void Draw();
	MsgWindow* setPos(int x, int y) { this->x = x; this->y = y; return this; }
	MsgWindow* setSize(int w, int h) { this->w = w; this->h = h; return this; }
	void add(WindowContent *c) { content.push_back(c); }
};


class FontString {
	static int font;
	static int color;
	string str;

public:
	static void Load(const char *FileName, int EdgeSize = 0, int color = 0xffffff);
	static void Load(int font, int color = 0xffffff);
	FontString() {};
	FontString(const char* str);
	void Draw(int x, int y);

	void operator =(const char* str) { this->str = str; }
};


class Choice
{
	int x, y;
	FontString str;
	int lngth;
	bool select = false;

public:
	Choice() {};
	virtual void Process();
	virtual void Draw();
	virtual void Click() {};
	Choice* setString(const char* string);
	Choice* setPos(int x, int y) { this->x = x;  this->y = y;  return this; }
	int getPosX() { return x; }
	int getPosY() { return y; }
	void Select(bool flag = true) { select = flag; }
};

typedef std::vector<Choice*> ChoiceVec;
typedef std::vector<Choice*>::iterator ChoiceItr;

class Cursor
{
	int dx = 0, dy = 0;
	ChoiceItr itr;
	ChoiceItr Move(int n);

public:
	Cursor(ChoiceItr i);
	virtual void Process();
	virtual void Draw();

	Choice* operator *() { return *itr; }
	Choice* operator ->() { return *itr; }
	void operator =(ChoiceItr i) {
		(*itr)->Select(false);
		itr = i;
		(*itr)->Select();
	}
	ChoiceItr operator ++() { return Move(1); }
	ChoiceItr operator --() { return Move(-1); }
	ChoiceItr operator +=(int n) { return Move(n); }
	ChoiceItr operator -=(int n) { return Move(-n); }
	bool operator !=(ChoiceItr i) { return (itr != i) ? true : false; }
	bool operator ==(ChoiceItr i) { return (itr == i) ? true : false; }
};


class ChoiceMgr : public WindowContent
{
protected:
	ChoiceVec cho;
	Cursor *crsr = nullptr;
	virtual void MoveCursor();
public:
	ChoiceMgr() {}
	~ChoiceMgr();
	void Process();
	void Draw();
	void add(Choice* c);
};

class ChoiceMgr2D : public ChoiceMgr
{
protected:
	vector<ChoiceVec> cho2d;
	void MoveCursor();
};