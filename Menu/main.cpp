#include "Dxlib.h"
#include "MsgWin.h"
#include <string>

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	ChangeWindowMode(TRUE); // �E�B���h�E���[�h�ɐݒ�
	//SetWindowSizeExtendRate(2);//��ʂ��g��
	SetWindowSizeChangeEnableFlag(TRUE, TRUE);//��ʂ̑傫�������R�ɕς�����悤�ɂ���
	DxLib_Init(); // DX���C�u��������������
	SetDrawScreen(DX_SCREEN_BACK); //�`���𗠉�ʂɐݒ�

	
	Choice* c[5] = { new Choice(), new Choice(), new Choice(), new Choice(), new Choice(), };
	for (int i = 0; i < 5; i++) {
		std::string str = "choice" + std::to_string(i + 1);
		c[i]->setPos(200, 100 + 50 * i)->setString(str.c_str());
	}
	ChoiceMgr* mgr = new ChoiceMgr();
	mgr->setChoices(c, 5);

	// while(����ʂ�\��ʂɔ��f, ���b�Z�[�W����, ��ʃN���A, �L�[�X�V)
	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0 && gpUpdateKey() == 0) {
		mgr->Process();
		mgr->Draw();
	}

	DxLib_End(); // DX���C�u�����I������
	return 0;
}