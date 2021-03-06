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
	vector<Vector2D> cal_result;

public:
	virtual void Process();
	virtual void Draw();
	void set(vector<Choice*>* cho);
};

class Cursor2D : public Cursor{
protected:
	virtual void Process();
	void Recalculation();
};

class ChoiceMgr : public WindowContent
{
protected:
	vector<Choice*> cho;
	Cursor *crsr;

public:
	ChoiceMgr(Cursor* crsr = nullptr);
	~ChoiceMgr();
	void Process();
	void Draw();
	void add(Choice* c);
};