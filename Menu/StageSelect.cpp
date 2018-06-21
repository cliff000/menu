#include "StageSelect.h"
#include "DxLib.h"
#include <string>

void StageChoice::Draw() {
	DrawBox(x, y, x + w, y + h, 0xffffff, FALSE); //プレビュー
	DrawBox(x, y + h, x + w, y + h + h2, 0xffffff, FALSE); //ステージ名枠
	DrawString(x + 35, y + h + 10, str.c_str(), 0xffffff); //ステージ名
}
void StageCursor::Draw() {
	StageChoice* c = (StageChoice*)(*cho)[slct];
	int x = c->getX();
	int y = c->getY();
	int w = c->getW();
	int h = c->getH();
	DrawBox(x - 10, y - 10, x + w + 10, y + h + 10, 0xffffff, FALSE);
}

//--------------------------------------------------------------------------

StageSelect::StageSelect() {
	ChoiceMgr* mgr = new ChoiceMgr(new StageCursor());
	int stage_num = 1;
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 4; j++) {
			Choice* c = new StageChoice();
			std::string str = "stage" + std::to_string(stage_num++);
			c->setPos(30 + 150 * j, 70 + 200 * i)->setString(str.c_str());
			mgr->add(c);
		}
	}
	mw = new MsgWindow(0, 0, 640, 480);
	mw->add(mgr);
}

void StageSelect::Process() {
	mw->Process();
}
void StageSelect::Draw() {
	mw->Draw();
}