//================================================
//DirectXシューティングゲーム
//Author:鈴木聖大
//================================================
#ifndef _TUTORIAL_H_			// 2重インクルード防止のマクロ定義
#define _TUTORIAL_H_

#define _CRT_SECURE_NO_WARNINGS

//================================================
//インクルードファイル
//================================================
#include "main.h"
//================================================
//プロトタイプ宣言
//================================================
void InitTutorial(void);
void UninitTutorial(void);
void UpdateTutorial(void);
void DrawTutorial(void);

#endif