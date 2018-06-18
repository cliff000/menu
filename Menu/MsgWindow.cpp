#include "MsgWin.h"
#include "DxLib.h"

#define safe_delete(x) delete x; x = nullptr;


MsgWindow::MsgWindow(WindowContent *c) {
	content.push_back(c);
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