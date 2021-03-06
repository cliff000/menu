#include "MsgWindow.h"
#include "DxLib.h"

#define safe_delete(x) delete x; x = nullptr;


MsgWindow::MsgWindow(int x, int y, int w, int h) {
	setPos(x, y);
	setSize(w, h);
}

MsgWindow::~MsgWindow() {
	for (auto& i : content)
		delete i;
}

void MsgWindow::Process() {
	for (auto &i : content)
		i->Process();
}

void MsgWindow::Draw() {
	int screen = MakeScreen(w, h, TRUE);
	SetDrawScreen(screen);
	for (auto &i : content)
		i->Draw();
	DrawBox(0, 0, w, h, 0xffffff, FALSE);

	SetDrawScreen(DX_SCREEN_BACK);
	DrawGraph(x, y, screen, FALSE);
}

void MsgWindow::add(WindowContent *c) { 
	content.push_back(c); 
}