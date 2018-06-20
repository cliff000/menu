#include "Choice.h"
#include "DxLib.h"
#include "keyboard.h"
#include "math.h"
#include <algorithm>

void Choice::Process() {

}

void Choice::Draw() {
	DrawString(x, y, str.c_str(), 0xffffff);
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



Cursor2D::Cursor2D(vector<Choice*>* cho) {
	this->cho = cho;
}

void Cursor2D::Process() {
	if ((*cho).size() == 0) return;

	if (Key[KEY_INPUT_DOWN] == 1) {
		Recalculation();
		for (auto& i : cal_result) {
			if (i.angle() > 0.2 && i.angle() < 2.94) {
				slct = i.getIdentity();
				break;
			}
		}
	}
	if (Key[KEY_INPUT_UP] == 1) {
		Recalculation();
		for (auto& i : cal_result) {
			if (i.angle() < -0.2 && i.angle() > -2.94) {
				slct = i.getIdentity();
				break;
			}
		}
	}
	if (Key[KEY_INPUT_LEFT] == 1) {
		Recalculation();
		for (auto& i : cal_result) {
			if (i.angle() > 1.77 || i.angle() < -1.77) {
				slct = i.getIdentity();
				break;
			}
		}
	}
	if (Key[KEY_INPUT_RIGHT] == 1) {
		Recalculation();
		for (auto& i : cal_result) {
			if (i.angle() < 1.37 && i.angle() > -1.37) {
				slct = i.getIdentity();
				break;
			}
		}
	}
}

//角度の再計算
void Cursor2D::Recalculation() {
	cal_result.clear();

	for (int i = 0; i < (*cho).size(); i++) {
		if (i == slct) continue;
		
		int x = (*cho)[i]->getX() - (*cho)[slct]->getX();
		int y = (*cho)[i]->getY() - (*cho)[slct]->getY();
		cal_result.push_back(Vector2D(x, y, i));
	}

	std::sort(cal_result.begin(), cal_result.end());
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