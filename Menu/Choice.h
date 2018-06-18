#pragma once
#include <vector>
#include "FontString.h"
#include "MsgWindow.h"


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
	int getX() { return x; }
	int getY() { return y; }
	void Select(bool flag = true) { select = flag; }
};

class Cursor
{
	int dx = 0, dy = 0;
	vector<Choice*>* cho;
	int slct = 0;

public:
	Cursor(vector<Choice*>* cho);
	virtual void Process();
	virtual void Draw();
};


class ChoiceMgr : public WindowContent
{
protected:
	vector<Choice*> cho;
	Cursor *crsr;
public:
	ChoiceMgr() { crsr = new Cursor(&cho); }
	~ChoiceMgr();
	void Process();
	void Draw();
	void add(Choice* c);
};