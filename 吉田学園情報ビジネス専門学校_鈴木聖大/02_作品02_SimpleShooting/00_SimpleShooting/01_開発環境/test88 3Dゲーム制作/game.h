//================================================
//DirectXシューティングゲーム
//Author:鈴木聖大
//================================================
#ifndef _GAME_H_
#define _GAME_H_

#define _CRT_SECURE_NO_WARNINGS

//================================================
//インクルードファイル
//================================================
#include "main.h"

//=====================================================
//構造体定義
//=====================================================
typedef enum
{
	GAMESTATE_NONE = 0,		//ゲームが動いていない状態
	GAMESTATE_NORMAL,		//ゲームが動いている状態
	GAMESTATE_FINISH,		//ゲームをクリアorゲームオーバーした状態
	GAMESTATE_END,			//ゲームを終了した状態
	GAMESTATE_MAX
}GAMESTATE;

//=====================================================
// プロトタイプ宣言
//=====================================================
void InitGame(void);
void UninitGame(void);
void UpdateGame(void);
void DrawGame(void);
void SetGameState(GAMESTATE state);
GAMESTATE GetGameState(void);

#endif