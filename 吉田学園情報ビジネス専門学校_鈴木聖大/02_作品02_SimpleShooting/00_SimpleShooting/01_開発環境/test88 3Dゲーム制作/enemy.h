//================================================
//3Dゲーム制作
//Author:鈴木聖大
//================================================
#ifndef ENEMY_H_
#define ENEMY_H_

#define CRT_SECURE_NO_WARNINGS

//=====================================================
// インクルードファイル
//=====================================================
#include "main.h"

//================================================
//マクロ定義
//================================================
#define MAX_ENEMY (9)		//敵の最大数
#define ENEMY_SIZE (15.0f)  //敵のサイズ

//================================================
//グローバル変数
//================================================


//================================================
//構造体定義
//================================================
typedef enum//敵の状態
{
	ENEMYSTATE_NOMAL = 0,	//通常
	ENEMYSTATE_DAMAGE,		//ダメージ
	ENEMYSTATE_MAX			//状態の最大数
}ENEMYSTATE;

typedef struct
{
	D3DXVECTOR3 vecU;			//!<上方向ベクトル
	D3DXMATRIX mtxProjection;	//!<プロジェクションマトリックス
	D3DXMATRIX mtxView;			//!<ビューマトリックス
	D3DXVECTOR3 pos;			//位置情報
	D3DXVECTOR3 posOld;			//位置情報
	D3DXVECTOR3 rot;			//!<向き取得用
	D3DXVECTOR3 size;			// 大きさ
	ENEMYSTATE state;
	float fDistance;			//!<視点-注視点の距離
	int nType;					//種類
	int nLife;					//体力
	int nCounterState;			//状態のカウンタ
	bool isDown;
	bool bUse;					//使用しているかどうか
	int nCntBillboardEnemy;		//弾を出すカウント
}Enemy;

//=====================================================
// プロトタイプ宣言
//=====================================================
void InitEnemy(void);
void UninitEnemy(void);
void UpdateEnemy(void);
void DrawEnemy(void);
Enemy*GetEnemy(void);
void SetEnemy(D3DXVECTOR3 pos, int nType, int number);
void HitEnemy(int nCntEnemy, int nDamage);
bool IsGameClear();
bool IsZakoDown();
bool IsBossDown();
bool CollisionEnemy(D3DXVECTOR3* pPos, D3DXVECTOR3* pPosOld, D3DXVECTOR3 size);

#endif