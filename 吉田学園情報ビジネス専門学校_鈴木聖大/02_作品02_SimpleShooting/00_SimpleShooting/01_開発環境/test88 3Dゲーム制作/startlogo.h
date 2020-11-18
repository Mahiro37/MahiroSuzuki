//================================================
//DirectXシューティングゲーム
//Author:鈴木聖大
//================================================
#ifndef _STARTLOGO_H_
#define _STARTLOGO_H_

#define _CRT_SECURE_NO_WARNINGS

//================================================
//インクルードファイル
//================================================
#include "main.h"

//================================================
// マクロ定義
//================================================
#define MAX_STARTLOGO (1)
#define STARTLOGO_SIZE_X (1280)		// X座標の大きさ
#define STARTLOGO_SIZE_Y (720)		// Y座標の大きさ

//================================================
//構造体定義
//================================================
typedef struct
{
	D3DXVECTOR3 pos;	//現在の位置
	D3DXVECTOR3 posOld; //1F前の位置
	D3DXVECTOR3 move;	//移動量
	D3DXVECTOR3 size;   //大きさ
	D3DXMATRIX mtxWorld;//行列計算用
						//BULLETTYPE type;	//種類
	bool bUse;			//使用しているかどうか
}STARTLOGO;

//================================================
//プロトタイプ宣言
//================================================
void InitStartlogo(void);
void UninitStartlogo(void);
void UpdateStartlogo(void);
void DrawStartlogo(void);
void SetStartlogo(D3DXVECTOR3 pos, D3DXVECTOR3 size);

#endif