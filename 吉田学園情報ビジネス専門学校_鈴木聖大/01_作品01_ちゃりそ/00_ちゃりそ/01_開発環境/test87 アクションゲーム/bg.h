#pragma once
//================================================
//DirectXシューティングゲーム
//Author:鈴木聖大
//================================================
#ifndef _BG_H_			// 2重インクルード防止のマクロ定義
#define _BG_H_

#define _CRT_SECURE_NO_WARNINGS

//================================================
//インクルードファイル
//================================================
#include "main.h"
//================================================
//プロトタイプ宣言
//================================================
void InitBg(void);
void UninitBg(void);
void UpdateBg(void);
void DrawBg(void);

#endif