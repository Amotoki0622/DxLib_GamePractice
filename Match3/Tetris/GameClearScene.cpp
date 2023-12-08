#include "DxLib.h"
#include "GameClearScene.h"
#include "SceneManager.h"

/**********************************************************
*�}�N����`
***********************************************************/

/**********************************************************
*�^��`
***********************************************************/

/**********************************************************
*�ϐ���`
***********************************************************/

int GameClearImage;
int GameClearSE;
int GameClearFlag;

/**********************************************************
*�v���g�^�C�v�錾
***********************************************************/

/**********************************************************
*�Q�[���N���A��� �F ����������
*���@�� �F �Ȃ�
*�߂�l �F �Ȃ�
***********************************************************/
int GameClearScene_Initialize(void)
{
	int ret = 0;

	//��ʂ̓ǂݍ���
	GameClearImage = LoadGraph("images/Clear.bmp");

	//�����̓Ǎ���
	GameClearSE = LoadSoundMem("sounds/Clear.mp3");

	GameClearFlag = 0;

	//�G���[�`�F�b�N
	if (GameClearImage == -1)
	{
		ret = 1;
	}

	if (GameClearSE == -1)
	{
		ret = -1;
	}

	return ret;
}
/**********************************************************
*�Q�[���N���A��� �F �X�V����
*���@�� �F �Ȃ�
*�߂�l �F �Ȃ�
***********************************************************/
void GameClearScene_Update(void)
{
	//�Q�[���N���A���ʉ��Đ��`�F�b�N
	if (CheckSoundMem(GameClearSE) == 0)
	{
		if (GameClearFlag == TRUE)
		{
			Change_Scene(E_GAMEMAIN);
		}
		else
		{
			PlaySoundMem(GameClearSE, DX_PLAYTYPE_BACK);
			GameClearFlag = TRUE;
		}
	}
}

/**********************************************************
*�Q�[���N���A��� �F �`�揈��
*���@�� �F �Ȃ�
*�߂�l �F �Ȃ�
***********************************************************/
void GameClearScene_Draw(void)
{
	DrawGraph(0, 0, GameClearImage, FALSE);
}