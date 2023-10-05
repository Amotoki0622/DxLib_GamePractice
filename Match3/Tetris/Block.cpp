#include "Block.h"
#include "DxLib.h"
#include "InputControl.h"


/**********************************************************
*マクロ定義
***********************************************************/

#define FIELD_HEIGHT		(21)				//フィールドのマスの高さ
#define FIELD_WIDTH					(12)			//フィールドのマスの高さ
#define BLOCK_TROUT_SIZE	(4)						//ブロックのマスサイズ
#define BLOCK_SIZE					(36)			//1ブロック当たりのサイズ
#define BLOCK_TYPE_MAX				(7)						//落ちてくるブロックの種類
#define BLOCK_NEXT_POS_X	(700)				//次のブロックの座標(X座標)
#define BLOCK_NEXT_POS_Y	(500)				//次のブロックの座標(Y座標)
#define BLOCK_STOCK_POS_X	(500)				//ストックされたブロックの座標(X座標)
#define BLOCK_STOCK_POS_Y	(350)				//ストックされたブロックの座標(Y座標)
#define DROP_BLOCK_INIT_X	(4)							//落ちてくるブロックの初期X座標
#define DROP_BLOCK_INIT_Y	(-1)				//落ちてくるブロックの初期Y座標
#define DROP_SPEED					(60)				//落下時間
#define TURN_CROCKWICE				(0)						//時計回りに回転させる
#define TURN_ANTICROCKWICE	(1)							//時計回りに回転させる

/**********************************************************
*型定義
***********************************************************/

enum BLOCK_STATE
{
	E_BLOCK_EMPTY,							//空ブロック
	E_BLOCK_LIGHT_BLUE,						//水色
	E_BLOCK_YELLOW_GREEN,				//黄緑
	E_BLOCK_YELLOW,							//黄色
	E_BLOCK_ORANGE,							//オレンジ
	E_BLOCK_BLUE,							//青
	E_BLOCK_PINK,							//ピンク
	E_BLOCK_RED,							//赤
	E_BLOCK_GLAY,							//灰色
	E_BLOCK_WALL,							//壁
	E_BLOCK_IMAGE_MAX,

};

/**********************************************************
*定数定義
***********************************************************/
const int C_BLOCK_TABLE[BLOCK_TYPE_MAX][BLOCK_TROUT_SIZE][BLOCK_TROUT_SIZE] = {
	{
		{0, 0, 0, 0},
		{0, 1, 1, 0},
		{0, 1, 1, 0},
		{0, 0, 0, 0}
},

	{
		{0, 0, 0, 0},
		{0, 0, 0, 0},
		{2, 2, 2, 2},
		{0, 0, 0, 0}
},

	{
		{0, 0, 0, 0},
		{3, 0, 0, 0},
		{3, 3, 3, 0},
		{0, 0, 0, 0}
},

	{
		{0, 0, 0, 0},
		{0, 0, 0, 0},
		{0, 0, 0, 4},
		{0, 4, 4, 4}
},

	{
		{0, 0, 0, 0},
		{0, 5, 5, 0},
		{0, 0, 5, 5},
		{0, 0, 0, 0}
},

	{
		{0, 0, 0, 0},
		{0, 6, 6, 0},
		{6, 6, 0, 0},
		{0, 0, 0, 0}
},

	{
		{0, 0, 0, 0},
		{0, 7, 0, 0},
		{7, 7, 7, 0},
		{0, 0, 0, 0}
}
};

/**********************************************************
*変数宣言
***********************************************************/
int BlockImage[E_BLOCK_IMAGE_MAX];									//ブロック画像
BLOCK_STATE Field[FIELD_HEIGHT][FIELD_WIDTH];				//フィールド配列
BLOCK_STATE Next[BLOCK_TROUT_SIZE][BLOCK_TROUT_SIZE];		//待機状態のブロック
BLOCK_STATE Stock[BLOCK_TROUT_SIZE][BLOCK_TROUT_SIZE];		//ストックのブロック
int DropBlock_x;														//落ちるブロックのx座標
int DropBlock_y;														//落ちるブロックのy座標

int WaitTime;			//待機時間
int Stock_Flg;			//ストックフラグ
int DeleteLine;			//生成フラグ
int SoundEffect[3];		//SE


/**********************************************************
*プロトタイプ宣言
***********************************************************/

void create_field(void);
void create_block(void);
void move_block(void);
void change_block(void);
void turn_block(void);
int check_overlap(void);
void lock_block(int x, int y);
void check_line(void);


/**********************************************************
*ブロック機能
*引数：　なし
*戻り値：　エラー情報(-1： 異常, それ以外： 正常)
***********************************************************/
int Block_Initialize(void)
{
	int ret = 0;		//戻り値
	int i = 0;


	//ブロック画像の読み込み
	ret = LoadDivGraph("images/block.png", E_BLOCK_IMAGE_MAX, 10, 1, BLOCK_SIZE, BLOCK_SIZE, BlockImage);

	//SEの読み込み
	SoundEffect[0] = LoadSoundMem("sound/SE3.mp3");
	SoundEffect[1] = LoadSoundMem("sound/SE4.mp3");
	SoundEffect[2] = LoadSoundMem("sound/SE5.wav");

	//音量の調整
	ChangeVolumeSoundMem(150, SoundEffect[0]);
	ChangeVolumeSoundMem(150, SoundEffect[1]);
	ChangeVolumeSoundMem(130, SoundEffect[2]);

	//フィールドの生成
	create_block();
	create_block();

	//待機時間の初期化
	WaitTime = 0;

	//ストックフラグの初期化
	Stock_Flg = FALSE;

	//消したラインの数の初期化
	DeleteLine = 0;

	//エラーチェック
	for (i = 0; i < 3; i++)
	{
		if (SoundEffect[i] == -1)
		{
			ret = -1;
			break;
		}
	}
	return ret;
}