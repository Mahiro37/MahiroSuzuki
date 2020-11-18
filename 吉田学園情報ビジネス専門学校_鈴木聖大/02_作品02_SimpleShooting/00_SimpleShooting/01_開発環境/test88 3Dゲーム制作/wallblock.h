//=====================================================
//
// 3Dゲーム ブロックの処理 [block.h]
// Author:小西優斗
//
//=====================================================
#ifndef _BLOCK_H_
#define _BLOCK_H_

#define _CRT_SECURE_NO_WARNINGS

//=====================================================
// インクルードファイル
//=====================================================
#include "main.h"

//=====================================================
// マクロ定義
//=====================================================
#define MAX_BLOCK (4)
#define BLOCK_SIZE_X (80)		// X座標の大きさ
#define BLOCK_SIZE_Y (80)		// Y座標の大きさ
#define BLOCK_SIZE_Z (80)		// Z座標の大きさ

//=====================================================
// 構造体定義
//=====================================================
typedef struct
{
	D3DXVECTOR3 pos;				// 現在の位置
	D3DXVECTOR3 rot;				// 現在の角度
	D3DXVECTOR3 size;				// 大きさ
	D3DXMATRIX mtxWorld;			// 行列計算用
	LPD3DXMESH pMeshBlockz;			// メッシュ情報へのポインタ
	LPD3DXBUFFER pBuffMatBlock;		// マテリアル情報へのポインタ
	DWORD nNumMatBlock;				// マテリアル情報の数
	bool bUse;						// 使われているか
}BLOCK;

//=====================================================
// プロトタイプ宣言
//=====================================================
void InitBlock(void);
void UninitBlock(void);
void UpdateBlock(void);
void DrawBlock(void);
void SetBlock(D3DXVECTOR3 pos, D3DXVECTOR3 dir, D3DXVECTOR3 size);
bool CollisionBlock(D3DXVECTOR3* pPos, D3DXVECTOR3* pPosOld, D3DXVECTOR3 size);
bool HitBlock(D3DXVECTOR3* pPos, D3DXVECTOR3* pPosOld, D3DXVECTOR3 size);
BLOCK*GetBlock(void);

#endif