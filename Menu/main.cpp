#include "Dxlib.h"
#include <string>
#include "keyboard.h"
#include "StageSelect.h"



int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	ChangeWindowMode(TRUE); // �E�B���h�E���[�h�ɐݒ�
	//SetWindowSizeExtendRate(2);//��ʂ��g��
	SetWindowSizeChangeEnableFlag(TRUE, TRUE);//��ʂ̑傫�������R�ɕς�����悤�ɂ���
	DxLib_Init(); //DX���C�u��������������
	SetDrawScreen(DX_SCREEN_BACK); //�`���𗠉�ʂɐݒ�
	

	StageSelect* ss = new StageSelect();

	// while(����ʂ�\��ʂɔ��f, ���b�Z�[�W����, ��ʃN���A, �L�[�X�V)
	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0 && gpUpdateKey() == 0) {
		ss->Process();
		ss->Draw();
	}
	delete ss;

	DxLib_End(); // DX���C�u�����I������
	return 0;
}