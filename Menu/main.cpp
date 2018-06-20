#include "Dxlib.h"
#include "MsgWindow.h"
#include "Choice.h"
#include <string>
#include "keyboard.h"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	ChangeWindowMode(TRUE); // ウィンドウモードに設定
	//SetWindowSizeExtendRate(2);//画面を拡大
	SetWindowSizeChangeEnableFlag(TRUE, TRUE);//画面の大きさを自由に変えられるようにする
	DxLib_Init(); //DXライブラリ初期化処理
	SetDrawScreen(DX_SCREEN_BACK); //描画先を裏画面に設定
	
	ChangeFont("ＭＳ 明朝");

	ChoiceMgr* mgr = new ChoiceMgr();
	for (int i = 0; i < 5; i++) {
		Choice* c = new Choice();
		std::string str = "choice" + std::to_string(i + 1);
		//c->setPos(50, 50 + 50 * i)->setString(str.c_str());
		c->setPos(GetRand(300), GetRand(300))->setString(str.c_str());
		mgr->add(c);
	}
	MsgWindow* mw = new MsgWindow(150, 50, 300, 300);
	mw->add(mgr);

	// while(裏画面を表画面に反映, メッセージ処理, 画面クリア, キー更新)
	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0 && gpUpdateKey() == 0) {
		mw->Process();
		mw->Draw();
	}

	DxLib_End(); // DXライブラリ終了処理
	return 0;
}