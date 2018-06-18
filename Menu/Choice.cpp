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
Cursor::Cursor(vector<Choice*>* cho) {
	this->cho = cho;
}

void Cursor::Draw() {
	if ((*cho).size() == 0) return;

	int x = (*cho)[slct]->getX() + dx;
	int y = (*cho)[slct]->getY() + dy;

	DrawBox(x, y, x + 100, y + 50, 0x00ff00, false);
}

void Cursor::Process() {
	if ((*cho).size() == 0) return;

	//�I������
	(*cho)[slct]->Select(false);

	//���֐i�߂�
	if (Key[KEY_INPUT_DOWN] == 1 || Key[KEY_INPUT_RIGHT] == 1) {
		if (slct < (*cho).size() - 1)
			++slct;
		else
			slct = 0;
	}
	//�O�ɖ߂�
	if (Key[KEY_INPUT_UP] == 1 || Key[KEY_INPUT_LEFT] == 1) {
		if (slct > 0)
			--slct;
		else
			slct = (*cho).size() - 1;
	}

	//�I��
	(*cho)[slct]->Select();

	//����
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
	//�I�����̍X�V
	for (auto& i : cho) {
		i->Process();
	}

	//�J�[�\���̍X�V
	crsr->Process();
}

void ChoiceMgr::Draw() {
	//�I�����̕`��
	for (auto& i : cho)
		i->Draw();

	//�J�[�\���̕`��
	crsr->Draw();
}

void ChoiceMgr::add(Choice* c) {
	cho.push_back(c);
}