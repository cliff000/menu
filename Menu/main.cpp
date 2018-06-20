#include "Dxlib.h"
#include "MsgWindow.h"
#include "Choice.h"
#include <string>
#include "keyboard.h"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	ChangeWindowMode(TRUE); // �E�B���h�E���[�h�ɐݒ�
	//SetWindowSizeExtendRate(2);//��ʂ��g��
	SetWindowSizeChangeEnableFlag(TRUE, TRUE);//��ʂ̑傫�������R�ɕς�����悤�ɂ���
	DxLib_Init(); //DX���C�u��������������
	SetDrawScreen(DX_SCREEN_BACK); //�`���𗠉�ʂɐݒ�
	
	ChangeFont("�l�r ����");

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

	// while(����ʂ�\��ʂɔ��f, ���b�Z�[�W����, ��ʃN���A, �L�[�X�V)
	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0 && gpUpdateKey() == 0) {
		mw->Process();
		mw->Draw();
	}

	DxLib_End(); // DX���C�u�����I������
	return 0;
}