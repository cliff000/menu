#include "Dxlib.h"
#include <string>
#include "keyboard.h"
#include "StageSelect.h"



int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	ChangeWindowMode(TRUE); // ウィンドウモードに設定
	//SetWindowSizeExtendRate(2);//画面を拡大
	SetWindowSizeChangeEnableFlag(TRUE, TRUE);//画面の大きさを自由に変えられるようにする
	DxLib_Init(); //DXライブラリ初期化処理
	SetDrawScreen(DX_SCREEN_BACK); //描画先を裏画面に設定
	

	StageSelect* ss = new StageSelect();

	// while(裏画面を表画面に反映, メッセージ処理, 画面クリア, キー更新)
	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0 && gpUpdateKey() == 0) {
		ss->Process();
		ss->Draw();
	}
	delete ss;

	DxLib_End(); // DXライブラリ終了処理
	return 0;
}