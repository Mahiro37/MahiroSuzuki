//================================================
//DirectXシューティングゲーム
//Author:鈴木聖大
//================================================
#ifndef _BORDERLOGO_H_
#define _BORDERLOGO_H_

#define _CRT_SECURE_NO_WARNINGS

//================================================
//インクルードファイル
//================================================
#include "main.h"

//================================================
// マクロ定義
//================================================
#define MAX_BORDERLOGO (1)
#define BORDERLOGO_SIZE_X (1920)		// X座標の大きさ
#define BORDERLOGO_SIZE_Y (1080)		// Y座標の大きさ

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
}BORDERLOGO;

//================================================
//プロトタイプ宣言
//================================================
void InitBorderlogo(void);
void UninitBorderlogo(void);
void UpdateBorderlogo(void);
void DrawBorderlogo(void);
void SetBorderlogo(D3DXVECTOR3 pos, D3DXVECTOR3 size);

#endif