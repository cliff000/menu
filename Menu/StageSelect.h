#pragma once
#include "Choice.h"

class StageChoice : public Choice {
	const int w = 120;
	const int h = w * 3 / 4;
	const int h2 = 35;
public:
	void Draw();
	int getW() { return w; }
	int getH() { return h + h2; }
};
class StageCursor : public Cursor2D {
public:
	void Draw();
};

class StageSelect {
	MsgWindow* mw;
public:
	StageSelect();
	void Process();
	void Draw();
};