//================================================
//3Dゲーム制作
//Author:鈴木聖大
//================================================
#ifndef DAMAGEBLOCK_H_
#define DAMAGEBLOCK_H_

#define CRT_SECURE_NO_WARNINGS

//=====================================================
// インクルードファイル
//=====================================================
#include "main.h"

//================================================
//マクロ定義
//================================================
#define MAX_DAMAGEBLOCK (68)		//ブロックの最大数
#define DAMAGEBLOCK_SIZE (18.0f)	//ブロックのサイズ

//================================================
//グローバル変数
//================================================


//================================================
//構造体定義
//================================================
typedef enum//敵の状態
{
	DAMAGEBLOCKSTATE_NOMAL = 0,	//通常
	DAMAGEBLOCKSTATE_DAMAGE,	//ダメージ
	DAMAGEBLOCKSTATE_MAX		//状態の最大数
}DAMAGEBLOCKSTATE;

typedef struct
{
	D3DXVECTOR3 vecU;			//!<上方向ベクトル
	D3DXMATRIX mtxProjection;	//!<プロジェクションマトリックス
	D3DXMATRIX mtxView;			//!<ビューマトリックス
	D3DXVECTOR3 pos;			//位置情報
	D3DXVECTOR3 posOld;			//位置情報
	D3DXVECTOR3 size;			// 大きさ
	DAMAGEBLOCKSTATE state;
	D3DXVECTOR3 rot;			//!<向き取得用
	D3DXVECTOR3 rotDest;		//目的の角度
	float fDistance;			//!<視点-注視点の距離
	int nType;					//種類
	bool isDown;
	bool bUse;					//使用しているかどうか
	int nLife;					//体力
	int nCounterState;			//状態のカウンタ
}Damageblock;

//=====================================================
// プロトタイプ宣言
//=====================================================
void InitDamageblock(void);
void UninitDamageblock(void);
void UpdateDamageblock(void);
void DrawDamageblock(void);
Damageblock*GetDamageblock(void);
void SetDamageblock(D3DXVECTOR3 pos, D3DXVECTOR3 size, int nType);
bool HitDamageblock(int nCntEnemy, int nDamage);
bool HitDamageblock2(D3DXVECTOR3* pPos, D3DXVECTOR3* pPosOld, D3DXVECTOR3 size);
bool IsGameClear();
bool CollisionDamageblock(D3DXVECTOR3* pPos, D3DXVECTOR3* pPosOld, D3DXVECTOR3 size);

#endif