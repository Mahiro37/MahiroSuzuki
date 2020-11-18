//================================================
//3Dゲーム制作
//Author:鈴木聖大
//================================================
#ifndef CAMERA_H_
#define CAMERA_H_

#define CRT_SECURE_NO_WARNINGS

//================================================
//インクルードファイル
//================================================
#include "main.h"

//================================================
// マクロ定義
//================================================
#define CAMERA_MOVE (5)
#define CAMERA_COEFFICIENT (0.2)

//================================================
//構造体定義
//================================================
typedef struct
{
	D3DXVECTOR3 posV;//!<カメラの座標
	D3DXVECTOR3 posR;//!<注視点(中心点)
	D3DXVECTOR3 vecU;//!<上方向ベクトル
	D3DXVECTOR3 posVDest;//!<カメラの座標(目的地)
	D3DXVECTOR3 posRDest;//!<注視点(目的地)
	D3DXMATRIX mtxProjection;//!<プロジェクションマトリックス
	D3DXMATRIX mtxView;//!<ビューマトリックス
	D3DXVECTOR3 rot;//!<向き取得用
	float fDistance;//!<視点-注視点の距離
}Camera;

//================================================
//プロトタイプ宣言
//================================================
void InitCamera(void);
void UninitCamera(void);
void UpdateCamera(void);
void SetCamera(void);
Camera*GetCamera(void);

#endif