//=============================================================================
//
// 当たり判定 [collision.cpp]
// Author:KUDO AYANO
//
//=============================================================================
#include "collision.h"

//=============================================================================
// [LandCollision] 箱に対する着地の当たり判定
//
// 引数
//  [in] pPos1     : ぶつかる側の位置
//  [in] pPos1Old : ぶつかる側の1F前の位置
//  [in] size1    : ぶつかる側の大きさ
//  [in] pPos2    : ぶつかられる側の位置
//  [in] size2    : ぶつかられる側の大きさ
//
// 戻り値 : ぶつかる側がぶつかる側の上に乗っているかどうか
//=============================================================================
bool WallCollision(D3DXVECTOR3 * pPos1, D3DXVECTOR3 * pPos1Old, D3DXVECTOR3 size1,
	D3DXVECTOR3 * pPos2, D3DXVECTOR3 size2)
{
	bool bLand = false;

	D3DXVECTOR3 box1Max = D3DXVECTOR3(size1.x / 2, size1.y, size1.z / 2) + *pPos1;          //ぶつかる側の最大値
	D3DXVECTOR3 box1Min = D3DXVECTOR3(-size1.x / 2, 0.0f, -size1.z / 2) + *pPos1;           //ぶつかる側の最小値
	D3DXVECTOR3 box2Max = D3DXVECTOR3(size2.x / 2, size2.y / 2, size2.z / 2) + *pPos2;      //ぶつかられる側の最大値
	D3DXVECTOR3 box2Min = D3DXVECTOR3(-size2.x / 2, -size2.y / 2, -size2.z / 2) + *pPos2;   //ぶつかられる側の最小値

	if (box1Max.y > box2Min.y&&
		box1Min.y < box2Max.y&&
		box1Max.x > box2Min.x&&
		box1Min.x < box2Max.x&&
		box1Max.z > box2Min.z&&
		box1Min.z < box2Max.z)
	{
		if (box1Max.y > box2Min.y&&
			pPos1Old->y + size1.y / 2 < box2Min.y)
		{//y軸の下
			pPos1->y = box2Min.y - size1.y;
		}
		if (box1Min.y < box2Max.y&&
			pPos1Old->y >= box2Max.y)
		{//y軸の上
			pPos1->y = box2Max.y;
			bLand = true;
		}
		if (box1Max.x > box2Min.x&&
			pPos1Old->x + size1.x / 2 <= box2Min.x)
		{//X軸の左
			pPos1->x = box2Min.x - size1.x / 2;
		}
		if (box1Min.x < box2Max.x&&
			pPos1Old->x - size1.x / 2 >= box2Max.x)
		{//x軸の右
			pPos1->x = box2Max.x + size1.x / 2;
		}
		if (box1Max.z > box2Min.z&&
			pPos1Old->z + size1.z / 2 <= box2Min.z)
		{//z軸の手前
			pPos1->z = box2Min.z - size1.z / 2;
		}
		if (box1Min.z < box2Max.z&&
			pPos1Old->z - size1.z / 2 >= box2Max.z)
		{//z軸の奥
			pPos1->z = box2Max.z + size1.z / 2;
		}
	}
	return bLand;
}

//=============================================================================
// [RectangleCollision] 矩形の当たり判定
//
// 引数
//  [in] pPos1     : ぶつかる側の位置
//  [in] pPos1Old : ぶつかる側の1F前の位置
//  [in] size1    : ぶつかる側の大きさ
//  [in] pPos2    : ぶつかられる側の位置
//  [in] size2    : ぶつかられる側の大きさ
//
// 戻り値 : ぶつかっているかどうか
//=============================================================================
bool RectangleCollision(D3DXVECTOR3 * pPos1, D3DXVECTOR3 * pPos1Old, D3DXVECTOR3 size1,
	D3DXVECTOR3 * pPos2, D3DXVECTOR3 size2)
{
	bool bHit = false;

	D3DXVECTOR3 box1Max = D3DXVECTOR3(size1.x / 2, size1.y, size1.z / 2) + *pPos1;          //ぶつかる側の最大値
	D3DXVECTOR3 box1Min = D3DXVECTOR3(-size1.x / 2, 0.0f, -size1.z / 2) + *pPos1;           //ぶつかる側の最小値
	D3DXVECTOR3 box2Max = D3DXVECTOR3(size2.x / 2, size2.y / 2, size2.z / 2) + *pPos2;      //ぶつかられる側の最大値
	D3DXVECTOR3 box2Min = D3DXVECTOR3(-size2.x / 2, -size2.y / 2, -size2.z / 2) + *pPos2;   //ぶつかられる側の最小値

	if (box1Max.y > box2Min.y&&
		box1Min.y < box2Max.y&&
		box1Max.x > box2Min.x&&
		box1Min.x < box2Max.x&&
		box1Max.z > box2Min.z&&
		box1Min.z < box2Max.z)
	{
		bHit = true;
	}
	return bHit;
}

//=============================================================================
// [SphereCollision] 球の当たり判定
//
// 引数
//  [in] pos1     : ぶつかる側の位置
//  [in] size1    : ぶつかる側の直径
//  [in] pos2     : ぶつかられる側の位置
//  [in] size2    : ぶつかられる側の直径
//
// 戻り値 : ぶつかる側が円の中に入っているかどうか
//=============================================================================
bool SphereCollision(D3DXVECTOR3 pos1, float size1, D3DXVECTOR3 pos2, float size2)
{
	float distance = powf(pos1.x - pos2.x, 2.0f) + powf(pos1.y - pos2.y, 2.0f) + powf(pos1.z - pos2.z, 2.0f);      //位置
	float radius = powf(size1 + size2, 2.0f); //半径
	return (distance <= radius);
}