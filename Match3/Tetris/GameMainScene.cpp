#include "GameMainScene.h"
#include "DxLib.h"
#include "Block.h"
#include "SceneManager.h"


/**********************************************************
*�}�N����`
***********************************************************/


/**********************************************************
*�^��`
***********************************************************/


/**********************************************************
*�O���[�o���ϐ��錾
***********************************************************/
int BlockGround_image;					//�w�i�摜�C���[�W
int BlockGround_sound;					//BGM
int GameOver_sound;								//�Q�[���I�[�o�[SE
int Score;												//�X�R�A

/**********************************************************
*�v���g�^�C�v�錾
***********************************************************/


/**********************************************************
*�Q�[�����C����� �F ����������
*���� �F �Ȃ�
*�߂�l �F �G���[���
***********************************************************/
int GameMainScene_Initialize(void)
{
	int ret = 0;

	ret = GameMainScene_Initialize();
	BlockGround_image = LoadGraph("images/stage.png");
	BlockGround_sound = LoadSoundMem("sounds/BGM017.ogg");
	GameOver_sound = LoadSoundMem("sounds/GameOver.mp3");

	//�G���[�`�F�b�N
	if (BlockGround_image == -1)
	{
		ret = -1;
	}
	if (BlockGround_sound == -1)
	{
		ret = -1;
	}

	return ret;

}

/**********************************************************
*�Q�[�����C����� �F �X�V����
*���� �F �Ȃ�
*�߂�l �F �Ȃ�
***********************************************************/
void GameMainScene_Update(void)
{
	//BGM�̍Đ�
	PlaySoundMem(BlockGround_sound, DX_PLAYTYPE_LOOP, FALSE);

	//�u���b�N�@�\�̍X�V
	Block_Update();

	Score = Get_Line() * 50;

	//�����ł��Ȃ��Ȃ�����
	if (Get_GenerateFlg() != TRUE)
	{
		PlaySoundMem(GameOver_sound, DX_PLAYTYPE_BACK, FALSE);
		Change_Scene(E_RANKING);
		StopSoundMem(BlockGround_sound);
	}
}

/**********************************************************
*�Q�[�����C����� �F �`�揈��
*���� �F �Ȃ�
*�߂�l �F �Ȃ�
***********************************************************/
void GameMainScene_Draw(void)
{
	//�w�i�̕`��
	DrawGraph(0, 0, BlockGround_image, TRUE);

	//�u���b�N�̕`��
	Block_Draw();
	SetFontSize(100);

	//�X�R�A��`��
	DrawFormatString(800, 100, GetColor(255, 255, 255), "%d", Score);
	SetFontSize(20);
}

/**********************************************************
*�Q�[�����C����� �F �X�R�A�擾����
*���� �F �Ȃ�
*�߂�l �F �Ȃ�
***********************************************************/
int Get_Score(void)
{
	return Score;
}