#pragma once
#include <vector>
#include <map>
#include "MsgWindow.h"
#include "Vector2D.h"


class Choice
{
protected:
	int x, y;
	std::string str;
	int lngth;

public:
	Choice() {};
	virtual void Process();
	virtual void Draw();
	virtual void Click() {};
	Choice* setString(const char* string);
	Choice* setPos(int x, int y) { this->x = x;  this->y = y;  return this; }
	int getX() { return x; }
	int getY() { return y; }
	virtual void Select() {}
};

class Cursor
{
protected:
	int dx = 0, dy = 0;
	vector<Choice*>* cho;
	int slct = 0;

public:
	Cursor() {}
	Cursor(vector<Choice*>* cho);
	virtual void Process();
	virtual void Draw();
};

class Cursor2D : public Cursor
{
	vector<Vector2D> cal_result;
public:
	Cursor2D(vector<Choice*>* cho);
	void Process();
	void Recalculation();
};


class ChoiceMgr : public WindowContent
{
protected:
	vector<Choice*> cho;
	Cursor *crsr;

public:
	ChoiceMgr() { crsr = new Cursor2D(&cho); }
	~ChoiceMgr();
	void Process();
	void Draw();
	void add(Choice* c);
};