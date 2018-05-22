#pragma once
#include <vector>
#include <map>
#include "keyboard.h"

using namespace std;

class MsgWin
{
public:
	virtual void Process() = 0;
	virtual void Draw() = 0;
};

class ChoiceWin : public MsgWin
{
public:
	void Process();
	void Draw();
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
	FontString str ;
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
	Cursor() {};
	Cursor(ChoiceItr i) { itr = i;  (*itr)->Select(); }//�ŏ��ɂ�������s
	virtual void Process();
	virtual void Draw();

	Choice* operator *() { return *itr; }
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


class ChoiceMgr
{
	ChoiceVec cho;
	Cursor crsr;
protected:
	void MoveCursor();
public:
	ChoiceMgr() {};
	~ChoiceMgr();
	void Process();
	void Draw();
	void setChoices(Choice** c, int length);
};