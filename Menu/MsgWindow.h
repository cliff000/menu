#pragma once
#include <vector>

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
	MsgWindow(int x, int y, int w, int h);
	~MsgWindow();
	virtual void Process();
	virtual void Draw();
	MsgWindow* setPos(int x, int y) { this->x = x; this->y = y; return this; }
	MsgWindow* setSize(int w, int h) { this->w = w; this->h = h; return this; }
	void add(WindowContent *c);
};