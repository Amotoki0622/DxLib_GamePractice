#include "DxLib.h"
#include "GameClearScene.h"
#include "SceneManager.h"

/**********************************************************
*マクロ定義
***********************************************************/

/**********************************************************
*型定義
***********************************************************/

/**********************************************************
*変数定義
***********************************************************/

int GameClearImage;
int GameClearSE;
int GameClearFlag;

/**********************************************************
*プロトタイプ宣言
***********************************************************/

/**********************************************************
*ゲームクリア画面 ： 初期化処理
*引　数 ： なし
*戻り値 ： なし
***********************************************************/
int GameClearScene_Initialize(void)
{
	int ret = 0;

	//画面の読み込み
	GameClearImage = LoadGraph("images/Clear.bmp");

	//音源の読込み
	GameClearSE = LoadSoundMem("sounds/Clear.mp3");

	GameClearFlag = 0;

	//エラーチェック
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
*ゲームクリア画面 ： 更新処理
*引　数 ： なし
*戻り値 ： なし
***********************************************************/
void GameClearScene_Update(void)
{
	//ゲームクリア効果音再生チェック
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
*ゲームクリア画面 ： 描画処理
*引　数 ： なし
*戻り値 ： なし
***********************************************************/
void GameClearScene_Draw(void)
{
	DrawGraph(0, 0, GameClearImage, FALSE);
}