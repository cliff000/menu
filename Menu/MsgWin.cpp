#include "MsgWin.h"
#include "DxLib.h"

#define safe_delete(x) delete x; x = nullptr;


int FontString::font = 0;
int FontString::color = 0xffffff;

FontString::FontString(const char* str) {
	this->str = str;
}

void FontString::Load(const char *FileName, int EdgeSize, int _color) {
	Load(LoadFontDataToHandle(FileName, EdgeSize), _color);
}

void FontString::Load(int _font, int _color) {
	font = _font;
	color = _color;
}

void FontString::Draw(int x, int y) {
	if (font != 0)
		DrawStringToHandle(x, y, str.c_str(), color, font);
	else
		DrawString(x, y, str.c_str(), color);
}

//------------------------------------------------------

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
	if (Key[KEY_INPUT_UP] == 1 || Key[KEY_INPUT_RIGHT] == 1) {
		if (crsr != cho.begin())
			--crsr;
		else
			crsr = cho.end() - 1;
	}
	//前に戻す
	if (Key[KEY_INPUT_DOWN] == 1 || Key[KEY_INPUT_LEFT] == 1) {
		if (crsr != cho.end() - 1)
			++crsr;
		else
			crsr = cho.begin();
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
		crsr.Process();
	}
}

void ChoiceMgr::Draw() {
	if (cho.size() != 0) {
		//選択肢の描画
		for (auto &i : cho)
			i->Draw();

		//カーソルの描画
		crsr.Draw();
	}
}

void ChoiceMgr::setChoices(Choice** c, int length) {
	//選択肢をセット
	for(int i = 0; i < length; i++)
		cho.push_back(c[i]);

	crsr = Cursor(cho.begin());
}