#include "Choice.h"
#include "DxLib.h"
#include "keyboard.h"

void Choice::Process() {

}

void Choice::Draw() {
	if (select == true)
		str.Draw(x - 20, y);
	else
		str.Draw(x, y);
}

Choice* Choice::setString(const char* string) {
	str = string;
	return this;
}

//------------------------------------------------
Cursor::Cursor(ChoiceItr i) {
	itr = i;
	(*itr)->Select();
}

ChoiceItr Cursor::Move(int n) {
	(*itr)->Select(false);
	itr += n;
	(*itr)->Select();
	return itr;
}

void Cursor::Draw() {
	int x = (*itr)->getPosX() + dx;
	int y = (*itr)->getPosY() + dy;

	DrawBox(x, y, x + 100, y + 50, 0x00ff00, false);
}

void Cursor::Process() {
	if (Key[KEY_INPUT_Z] == 1)
		(*itr)->Click();
}

//------------------------------------------------

ChoiceMgr::~ChoiceMgr() {
}

void ChoiceMgr::MoveCursor() {
	//次へ進める
	if (Key[KEY_INPUT_UP] == 1 || Key[KEY_INPUT_LEFT] == 1) {
		if (*crsr != cho.begin())
			--crsr;
		else
			*crsr = cho.end() - 1;
	}
	//前に戻す
	if (Key[KEY_INPUT_DOWN] == 1 || Key[KEY_INPUT_RIGHT] == 1) {
		if (*crsr != cho.end() - 1)
			++crsr;
		else
			*crsr = cho.begin();
	}
}

void ChoiceMgr::Process() {
	if (cho.size() != 0) {
		MoveCursor();

		//選択肢の更新
		for (auto &i : cho) {
			i->Process();
		}

		//カーソルの更新
		crsr->Process();
	}
}

void ChoiceMgr::Draw() {
	if (cho.size() != 0) {
		//選択肢の描画
		for (auto &i : cho)
			i->Draw();

		//カーソルの描画
		crsr->Draw();
	}
}

void ChoiceMgr::add(Choice* c) {
	cho.push_back(c);
	auto itr = cho.begin();
	//if (crsr == nullptr && cho.empty() == false)
	//crsr = new Cursor(cho.begin());
}