//=====================================================
//
// 3Dゲーム ブロックの処理 [block.h]
// Author:小西優斗
//
//=====================================================
#ifndef _BARRIER_H_
#define _BARRIER_H_

#define _CRT_SECURE_NO_WARNINGS

//=====================================================
// インクルードファイル
//=====================================================
#include "main.h"

//=====================================================
// マクロ定義
//=====================================================
#define MAX_BARRIER (1)
#define BARRIER_SIZE_X (28)		// X座標の大きさ
#define BARRIER_SIZE_Y (28)		// Y座標の大きさ
#define BARRIER_SIZE_Z (28)		// Z座標の大きさ

//=====================================================
// 構造体定義
//=====================================================
typedef struct
{
	D3DXVECTOR3 pos;				// 現在の位置
	D3DXVECTOR3 rot;				// 現在の角度
	D3DXVECTOR3 size;				// 大きさ
	D3DXMATRIX mtxWorld;			// 行列計算用
	LPD3DXMESH pMeshBarrierz;		// メッシュ情報へのポインタ
	LPD3DXBUFFER pBuffMatBarrier;	// マテリアル情報へのポインタ
	DWORD nNumMatBarrier;			// マテリアル情報の数
	bool bUse;						// 使われているか
	bool isDown;
	int nLife;						//体力

}BARRIER;

//=====================================================
// プロトタイプ宣言
//=====================================================
void InitBarrier(void);
void UninitBarrier(void);
void UpdateBarrier(void);
void DrawBarrier(void);
void SetBarrier(D3DXVECTOR3 pos, D3DXVECTOR3 dir, D3DXVECTOR3 size);
bool CollisionBarrier(D3DXVECTOR3* pPos, D3DXVECTOR3* pPosOld, D3DXVECTOR3 size);
bool HitBarrier(int nCntEnemy, int nDamage);
bool HitBarrier2(D3DXVECTOR3* pPos, D3DXVECTOR3* pPosOld, D3DXVECTOR3 size);
BARRIER*GetBarrier(void);

#endif