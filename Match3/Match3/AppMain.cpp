/**********************************************************
* �v���O���~���O���K
* �}�b�`�R�Q�[���̐���
***********************************************************/

#include "DxLib.h"
#include "freamcontrol.h"
#include "InputControl.h"
#include "SceneManager.h"

/**********************************************************
* �}�N����`
***********************************************************/
#define SCREEN_HIEGHT			(480)		//�X�N���[���T�C�Y�i�����j
#define SCREEN_WIDTH			(640)		//�X�N���[�T�C�Y�i���j
#define SCREEN_COLORBIT			(32)		//�X�N���[���J���[�r�b�g
#define FONT_SIZE				(20)		//�����T�C�Y

/**********************************************************
* �ϐ��^
***********************************************************/

/**********************************************************
*�O���[�o���ϐ��錾
***********************************************************/

/**********************************************************
*�v���g�^�C�v�ϐ��錾
***********************************************************/

/**********************************************************
�v���O�����̊J�n
***********************************************************/

int WINAPI WinMain(_In_ HINSTANCE hinstance, _In_opt_ HINSTANCE hPrevInstance, _In_
	LPSTR lpCmdLine, _In_ int nShowCmd)
{
	//�E�B���h�E�^�C�g���ݒ�
	SetMainWindowText("Match 3 Puzzle");

	//�E�B���h�E���[�h�ŋN��

	ChangeWindowMode(TRUE);

	//��ʃT�C�Y�̍ő�T�C�Y,�J���[�r�b�g����ݒ�
	SetGraphMode(SCREEN_HIEGHT, SCREEN_WIDTH, SCREEN_COLORBIT);


	//Dx���C�u�����̏���������
	//�G���[������������I������
	if (DxLib_Init() == D_ERROR)
	{
		return D_ERROR;
	}

	//�e�@�\�̏���������
	FreamControl_Initialize();				//�t���[�����[�g����@�\
	Input_Initialize();						//���͐���@�\

	//�V�[���}�l�[�W���[����������
	// �G���[������������A�I������
	if (ScreenManager_Initialize(E_TITLE) == D_ERROR)
	{
		return D_ERROR;
	}

	//�`����ʂ𗠂ɂ���
	SetDrawScreen(DX_SCREEN_BACK) :

		//�����T�C�Y��ݒ�
		SetFontsize(FONT_SIZE);

	//�Q�[�����[�v
	while (ProcessMassage() != D_ERROR && Input_Escape() == FALSE)
	{
		//���͐���@�\�X�V����
		Input_Update();

		//�V�[���}�l�[�W���[�X�V����
		SceneManager_Update();

		//��ʃN���A
		ClearDrawScreen();

		//�V�[���}�l�[�W���[�`�揈��
		ScreenManager_Draw();

		//�t���[�����[�g���䏈��
		FreamControl_Update();
		//��ʂ̓��e��\��ʂɔ��f
		ScreenFlip();
	}

	//Dx���C�u�����g�p�̏I������

	DxLib_End();
	return 0;
}