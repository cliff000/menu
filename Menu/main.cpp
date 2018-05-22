#include "Dxlib.h"
#include "MsgWin.h"
#include <string>

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	ChangeWindowMode(TRUE); // ウィンドウモードに設定
	//SetWindowSizeExtendRate(2);//画面を拡大
	SetWindowSizeChangeEnableFlag(TRUE, TRUE);//画面の大きさを自由に変えられるようにする
	DxLib_Init(); // DXライブラリ初期化処理
	SetDrawScreen(DX_SCREEN_BACK); //描画先を裏画面に設定

	
	Choice* c[5] = { new Choice(), new Choice(), new Choice(), new Choice(), new Choice(), };
	for (int i = 0; i < 5; i++) {
		std::string str = "choice" + std::to_string(i + 1);
		c[i]->setPos(200, 100 + 50 * i)->setString(str.c_str());
	}
	ChoiceMgr* mgr = new ChoiceMgr();
	mgr->setChoices(c, 5);

	// while(裏画面を表画面に反映, メッセージ処理, 画面クリア, キー更新)
	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0 && gpUpdateKey() == 0) {
		mgr->Process();
		mgr->Draw();
	}

	DxLib_End(); // DXライブラリ終了処理
	return 0;
}