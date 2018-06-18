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