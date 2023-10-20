#include "RankingScene.h"
#include "DxLib.h"
#include "InputControl.h"
#include "SceneManager.h"

/**********************************************************
*マクロ定義
***********************************************************/
#define RANKING_FILE		("dat/rankingdata.csv")
#define RANKING_MAX					(10)
#define RANKING_NAME_LEN	(11)

/**********************************************************
*型定義
***********************************************************/
typedef struct
{
	int rank;									//ランク
	char name[RANKING_NAME_LEN];		//名前
	int score;									//スコア
}T_RANKING;

typedef struct
{
	int x;
	int y;
}T_CURSOR;

/**********************************************************
*グローバル変数定義
***********************************************************/
T_RANKING Ranking_Data[RANKING_MAX];							//ランキングデータ
T_RANKING New_Score;													//新しいスコアボード
int DispMode;																//表示モード

T_CURSOR Cursor;														//カーソル用変数
int name_num;

/**********************************************************
*プロトタイプ宣言
***********************************************************/
void file_read(void);									//ファイル読込み
void file_write(void);										//ファイルの書き込み
void ranking_sort(void);								//ランキングソート処理
void ranking_inupt_name(void);							//名前入力処理
void ranking_input_name_draw(void);						//名前入力描画処理

/**********************************************************
*ランキング画面 ： 初期化処理
*引数 ： なし
*戻り値 ： エラー情報(-1 ： 異常有, -1以外 ： 正常終了)
***********************************************************/
int RankingScene_Initialize(void)
{
	int ret = 0;

	file_read();
	switch (DispMode)
	{
	case RANKING_INPUT_MODE:
		Cursor.x = 0;
		Cursor.y = 0;
		name_num = 0;
		break;

	case RANKING_DISP_MODE:
	default:
		break;
	}

	return ret;

}

/**********************************************************
*ランキング画面 ： 更新処理
*引数 ： なし
*戻り値 ： なし
***********************************************************/
void RankingScene_Update(void)
{
	switch (DispMode)
	{
	case RANKING_INPUT_MODE:
		ranking_inupt_name();
		break;

	case RANKING_DISP_MODE:
	default:
		if (GetButtonDown(XINPUT_BUTTON_B))
		{
			Change_Scene(E_TITLE);
		}
		break;
	}
}

/**********************************************************
*ランキング画面 ： 描画処理
*引数 ： なし
*戻り値 ： なし
***********************************************************/
void RankingScene_Draw(void)
{
	int i;

	switch (DispMode)
	{
	case RANKING_INPUT_MODE:
		ranking_input_name_draw();
		break;

	case RANKING_DISP_MODE:
	default:
		for (i = 0; i < RANKING_MAX; i++)
		{
			DrawFormatString(20, 10 + (i * 25), GetColor(255, 255, 255), "%2d, %10s, %10d", Ranking_Data[i].rank, Ranking_Data[i].name, Ranking_Data[i].score);
		}
		break;
	}
}
/**********************************************************
*ランキング画面 ： 画面描画処理
*引数 ： なし
*戻り値 ： なし
***********************************************************/
void Set_RankingMode(int mode)
{
	DispMode = mode;
}

/**********************************************************
*ランキング画面 ： スコア取得処理
*引数 ： なし
*戻り値 ： なし
***********************************************************/
void Set_RankingScore(int score)
{
	New_Score.score = score;
}

/**********************************************************
*ランキング画面 ： ファイル読込み処理
*引数 ： なし
*戻り値 ： なし
***********************************************************/
void file_read(void)
{
	FILE* fp = NULL;
	int i;

	OutputDebugString("ファイルを読み込みます");
	fopen_s(&fp, RANKING_FILE, "r");

	if(fp == NULL)
	{
		OutputDebugString("ファイルが読み込めません");
		OutputDebugString("ファイルを生成します");
		file_write();
	}
	else
	{
		for (i = 0; i < RANKING_MAX; i++)
		{
			fscanf_s(fp, "%2d, %[^,], %10d/n", &Ranking_Data[i].rank, Ranking_Data[i].name, RANKING_NAME_LEN, &Ranking_Data[i].score);
		}
		fclose(fp);
	}
}

/**********************************************************
*ランキング画面 ： ファイル書き込み処理
*引数 ： なし
*戻り値 ： なし
***********************************************************/
void file_write(void)
{
	FILE* fp = NULL;
	int i;

	OutputDebugString("ファイルを書き込みます");
	fopen_s(&fp, RANKING_FILE, "w");

	if (fp == NULL)
	{
		OutputDebugString("ファイルが書き込めません");
	}
	else
	{
		for (i = 0; i < RANKING_MAX; i++)
		{
			fprintf(fp, "%2d,%[^,],%10d/n", Ranking_Data[i].rank, Ranking_Data[i].name, Ranking_Data[i].score);
		}

		fclose(fp);

	}
}

/**********************************************************
*ランキング画面 ： ランキングソート処理
*引数 ： なし
*戻り値 ： なし
***********************************************************/
void ranking_sort(void)
