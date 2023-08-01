#include "Stage.h"
#include "DxLib.h"
#include "InputControl.h"


/**********************************************************
*�}�N����`
***********************************************************/

#define HEIGHT					(12)		//�u���b�N�z�u�T�C�Y�i�����j
#define WIDTH					(12)		//�u���b�N�z�u�T�C�Y�i���j
#define BLOCKSIZE				(48)		//�u���b�N�T�C�Y
#define BLOCK_IMAGE_MAX			(10)		//�u���b�N�摜��



#define ITEM_MAX				(8)			//�A�C�e���ő吔


#define SELECT_CURSOR			(0)
#define NEXT_CURSOR				(1)
#define TMP_CURSOR				(2)

/**********************************************************
*�^��`
***********************************************************/

typedef struct

{
	int flg;
	int x, y;
	int width, height;
	int image;
	int backup;
}T_Object;


typedef struct

{
	int x;
	int y;
}T_CURSOR;


enum

{
	E_NONE,
	E_ONCE,
	E_SECOND
};


/**********************************************************
*�ϐ��錾
***********************************************************/

T_Object Block[HEIGHT][WIDTH];				//�I�u�W�F�N�g�f�[�^
T_CURSOR Select[3];								//�Z���N�g�J�[�\�����W
int Item[ITEM_MAX];
int ClickStatus;
int Stage_State;
int Stage_Mission;
int Stage_Score;
int ClearFlag;


int BlockImage[BLOCK_IMAGE_MAX];		//�u���b�N�摜
int StageImage;								//�w�i�p�摜


int ClickSE;
int FadeOutSE;
int MoveBlockSE;

/**********************************************************
*�v���g�^�C�v�錾
***********************************************************/

int combo_check(int x, int y);
void combo_check_h(int y, int x, int* cnt, int* col);
void comb_check_w(int y, int x, int* cnt, int* col);
void save_block(void);
void restore_block(void);



/**********************************************************
*�X�e�[�W����@�\�F�@����������
*�����F�@�Ȃ�
*�߂�l�F�@�G���[���
***********************************************************/

int StageInitialize(void)
{
	int ret = 0;
	int i;


	//�摜�Ǎ���
	LoadDivGraph("image/block.png", BLOCK_IMAGE_MAX, BLOCK_IMAGE_MAX, 1, BLOCKSIZE, BLOCKSIZE, BlockImage);
	StageImage = LoadGraph("images/stage.png");


	//�����Ǎ���
	ClickSE = LoadSoundMem("sounds/click_se.mp3");
	FadeOutSE = LoadSoundMem("sounds/fadeout_se.mp3");
	MoveBlockSE = LoadSoundMem("sounds/moveblock_se.mp3");


	//�u���b�N��������
	CreateBlock();


	ClickStatus = E_NONE;
	Stage_State = 0;
	Stage_Score = 0;
	ClearFlag = FALSE;


	for (i = 0; i < 3; i++)
	{
		Select[i].x = 0;
		Select[i].y = 0;
	}


	//�G���[�`�F�b�N
	

}
