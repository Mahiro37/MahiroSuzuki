//================================================
//3Dゲーム制作
//Author:鈴木聖大
//================================================
#ifndef SHADOW_H_
#define SHADOW_H_

#define CRT_SECURE_NO_WARNINGS

//================================================
//インクルードファイル
//================================================
#include "main.h"

//================================================
//マクロ定義
//================================================
#define MAX_SHADOW (1)			//影の最大数
#define SHADOW_SIZE_X (10.5)	//影の横幅
#define SHADOW_SIZE_Y (17)		//影の縦幅

//================================================
//構造体定義
//================================================
typedef struct
{
	D3DXVECTOR3 pos;//位置情報
	D3DXVECTOR3 rot;//回転情報
	D3DXMATRIX mtxWorld;//行列計算用
	bool use;//使用判定
}Shadow;

//================================================
//プロトタイプ宣言
//================================================
void InitShadow(void);
void UninitShadow(void);
int SetShadow(D3DXVECTOR3 pos, D3DXVECTOR3 rot);
void SetPositionShadow(int nldxShadow, D3DXVECTOR3 pos, D3DXVECTOR3 rot);
void DrawShadow(void);

#endif