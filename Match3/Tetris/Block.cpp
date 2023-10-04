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
	E_BLOCK_IMAGE,MAX,

};

/**********************************************************
*定数定義
***********************************************************/

