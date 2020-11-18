//=============================================================================
//
// PLASTIC TROOPERSの処理 [bullet.h] (敵と自機の弾)
// Author : 後藤慎之助
//
//=============================================================================
#ifndef _BULLET_H_
#define _BULLET_H_
#define _CRT_SECURE_NO_WARNINGS

//=============================================================================
// インクルードファイル
//=============================================================================
#include"main.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define	MAX_BULLET (256)	//弾の最大数
#define BULLET_SIZE (4.0f)

//=============================================================================
//構造体定義
//=============================================================================
typedef enum
{
	BULLETTYPE_PLAYER = 0,	//プレイヤーの弾
	BULLETTYPE_ENEMY1,		//敵の弾(消せる)
	BULLETTYPE_ENEMY2,		//敵の弾(消せない)
	BULLETTYPE_003,		//
	BULLETTYPE_004,		//
	BULLETTYPE_005,		//
	BULLETTYPE_MAX
}BULLETTYPE;//アイテムの種類

typedef struct
{
	D3DXVECTOR3 pos;	//現在の位置
	D3DXVECTOR3 posOld; //1F前の位置
	D3DXVECTOR3 move;	//移動量
	D3DXVECTOR3 size;   //大きさ
	D3DXVECTOR3 dir;	//方向
	D3DXMATRIX mtxWorld;//行列計算用
	BULLETTYPE type;	//種類
	int nLife;			//寿命
	bool bUse;			//使用しているかどうか
}BULLET;

//=============================================================================
// プロトタイプ宣言
//=============================================================================
void InitBullet(void);
void UninitBullet(void);
void UpdateBullet(void);
void DrawBullet(void);
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 move, D3DXVECTOR3 moveDir, int nLife, BULLETTYPE type);
BULLET*GetBullet(void);
bool CollisionBullet(D3DXVECTOR3* pPos, D3DXVECTOR3* pPosOld, D3DXVECTOR3 size, BULLETTYPE type);

#endif