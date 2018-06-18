#include "Choice.h"
#include "DxLib.h"
#include "keyboard.h"

void Choice::Process() {

}

void Choice::Draw() {
	str.Draw(x, y);
}

Choice* Choice::setString(const char* string) {
	str = string;
	return this;
}

//------------------------------------------------
Cursor::Cursor(vector<Choice*>* cho) {
	this->cho = cho;
}

void Cursor::Draw() {
	if ((*cho).size() == 0) return;

	int x = (*cho)[slct]->getX() + dx;
	int y = (*cho)[slct]->getY() + dy;

	DrawFormatString(x - 25, y, 0xffffff, "☆");
}

void Cursor::Process() {
	if ((*cho).size() == 0) return;

	//選択解除
	(*cho)[slct]->Select(false);

	//次へ進める
	if (Key[KEY_INPUT_DOWN] == 1 || Key[KEY_INPUT_RIGHT] == 1) {
		if (slct < (*cho).size() - 1)
			++slct;
		else
			slct = 0;
	}
	//前に戻す
	if (Key[KEY_INPUT_UP] == 1 || Key[KEY_INPUT_LEFT] == 1) {
		if (slct > 0)
			--slct;
		else
			slct = (*cho).size() - 1;
	}

	//選択
	(*cho)[slct]->Select();

	//決定
	if (Key[KEY_INPUT_Z] == 1)
		(*cho)[slct]->Click();
}

//------------------------------------------------

ChoiceMgr::~ChoiceMgr() {
	for (auto& i : cho)
		delete i;
	delete crsr;
}

void ChoiceMgr::Process() {
	for (auto& i : cho)
		i->Process();
	crsr->Process();
}

void ChoiceMgr::Draw() {
	for (auto& i : cho)
		i->Draw();
	crsr->Draw();
}

void ChoiceMgr::add(Choice* c) {
	cho.push_back(c);
}