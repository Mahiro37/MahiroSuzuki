//================================================
//DirectXシューティングゲーム
//Author:鈴木聖大
//================================================
#ifndef _GAME_H_			// 2重インクルード防止のマクロ定義
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
	GAMESTATE_NONE = 0,
	GAMESTATE_NORMAL,
	GAMESTATE_END,
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