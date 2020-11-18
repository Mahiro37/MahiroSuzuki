#pragma once
//================================================
//DirectXシューティングゲーム
//Author:鈴木聖大
//================================================
#ifndef _BLOCK_H_			// 2重インクルード防止のマクロ定義
#define _BLOCK_H_

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
	
}BLOCKSTATE;

typedef struct
{
	BLOCKSTATE state;
	D3DXVECTOR3 pos;	//現在の位置
	D3DXVECTOR3 move;	//移動量
	float fWidth;		//幅
	float fHeight;		//高さ
	int nType;			//タイプ
	bool bUse;			//利用可能かどうか
}BLOCK;
//=====================================================
// プロトタイプ宣言
//=====================================================
void InitBlock(void);
void UninitBlock(void);
void UpdateBlock(void);
bool CollisionBlock(D3DXVECTOR3*pPos,	//位置
	D3DXVECTOR3*pPosOld,				//幅
	D3DXVECTOR3*pMove,					//高さ
	D3DXVECTOR3 size);					//サイズ
void DrawBlock(void);
void SetBlock(D3DXVECTOR3 pos,D3DXVECTOR3 move,int nType);
BLOCK * GetBlock(int nCntBlock);
BLOCKSTATE * GetBlockState(int nCntBlock);

#endif