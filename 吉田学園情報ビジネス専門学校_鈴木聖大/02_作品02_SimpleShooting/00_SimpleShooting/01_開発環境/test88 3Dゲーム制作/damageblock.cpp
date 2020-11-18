//================================================
//3Dゲーム制作
//Author:鈴木聖大
//================================================
#include "main.h"
#include "damageblock.h"
#include "camera.h"
#include "input.h"
#include "shadow.h"
#include "bullet.h"
#include "game.h"
#include "effect.h"
#include "collision.h"

//=====================================================
//マクロ定義
//=====================================================
#define VALUE_MOVE (10.0f)//ポリゴンの横移動の速さ

//================================================
//グローバル変数
//================================================
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffDamageblock = NULL;	//頂点バッファへのポインタ
LPD3DXMESH g_pMeshDamageblock = NULL;					//メッシュ情報へのポインタ
LPD3DXBUFFER g_pBuffMatDamageblock = NULL;				//マテリアル情報へのポインタ
DWORD g_nNumMatDamageblock = 0;							//マテリアル情報の数
D3DXMATRIX g_mtxWorldDamageblock;						//ワールドマトリックス
Damageblock g_aDamageblock[MAX_DAMAGEBLOCK];			//敵の情報
int g_IndexDamageblock = 0;
int g_nCntBillboardDamageblock = 0;

//================================================
//初期化処理
//================================================
void InitDamageblock(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//Xファイルの読み込み
	D3DXLoadMeshFromX("Xファイル/damageblock.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_pBuffMatDamageblock, NULL, &g_nNumMatDamageblock, &g_pMeshDamageblock);

	for (int nCntDamageblock = 0; nCntDamageblock < MAX_DAMAGEBLOCK; nCntDamageblock++)
	{
		g_aDamageblock[nCntDamageblock].bUse = false;
		g_aDamageblock[nCntDamageblock].isDown = false;
		g_aDamageblock[nCntDamageblock].nLife = 3;
		g_aDamageblock[nCntDamageblock].pos = D3DXVECTOR3(0, 0, 0);
		g_aDamageblock[nCntDamageblock].posOld = D3DXVECTOR3(0, 0, 0);
		g_aDamageblock[nCntDamageblock].rot = D3DXVECTOR3(0, 0, 0);
		g_aDamageblock[nCntDamageblock].rotDest = D3DXVECTOR3(0, 0, 0);
	}
}

//================================================
//終了処理
//================================================
void UninitDamageblock(void)
{
	//メッシュの破棄
	if (g_pMeshDamageblock != NULL)
	{
		g_pMeshDamageblock->Release();
		g_pMeshDamageblock = NULL;
	}

	//マテリアルの破棄
	if (g_pBuffMatDamageblock != NULL)
	{
		g_pBuffMatDamageblock->Release();
		g_pBuffMatDamageblock = NULL;
	}
}

//================================================
//更新処理
//================================================
void UpdateDamageblock(void)
{
	for (int nCntDamageblock = 0; nCntDamageblock < MAX_DAMAGEBLOCK; nCntDamageblock++)
	{
		if (g_aDamageblock[nCntDamageblock].bUse == true)
		{
			//1F前の位置を記憶
			g_aDamageblock[nCntDamageblock].posOld = g_aDamageblock[nCntDamageblock].pos;

			for (nCntDamageblock = 0; nCntDamageblock < MAX_DAMAGEBLOCK; nCntDamageblock++)
			{
				if (g_aDamageblock[nCntDamageblock].isDown == false)
				{
					//プレイヤーの弾に当たった時
					if (CollisionBullet(&g_aDamageblock[nCntDamageblock].pos, &g_aDamageblock[nCntDamageblock].posOld, D3DXVECTOR3(DAMAGEBLOCK_SIZE, DAMAGEBLOCK_SIZE, DAMAGEBLOCK_SIZE + 10), BULLETTYPE_PLAYER) == true)
					{
						HitDamageblock(nCntDamageblock, 1);//(誰に対して,何ダメージ与えるか)
					}
				}
			}
		}
	}
}

//================================================
//描画処理
//================================================
void DrawDamageblock(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();//デバイスのポインタ
	D3DXMATRIX mtxRot, mtxTrans;
	D3DMATERIAL9 matDef;//現在のマテリアル保存用
	D3DXMATERIAL*pMat;//マテリアルデータへのポインタ

	for (int nCntDamageblock = 0; nCntDamageblock < MAX_DAMAGEBLOCK; nCntDamageblock++)
	{
		if (g_aDamageblock[nCntDamageblock].bUse == true)
		{
			//ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_mtxWorldDamageblock);

			//向きを反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aDamageblock[nCntDamageblock].rot.y, g_aDamageblock[nCntDamageblock].rot.x, g_aDamageblock[nCntDamageblock].rot.z);
			D3DXMatrixMultiply(&g_mtxWorldDamageblock, &g_mtxWorldDamageblock, &mtxRot);

			//位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_aDamageblock[nCntDamageblock].pos.x, g_aDamageblock[nCntDamageblock].pos.y, g_aDamageblock[nCntDamageblock].pos.z);
			D3DXMatrixMultiply(&g_mtxWorldDamageblock, &g_mtxWorldDamageblock, &mtxTrans);

			//テクスチャの設定
			pDevice->SetTexture(0, NULL);

			//ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldDamageblock);

			//現在のマテリアルを取得する
			pDevice->GetMaterial(&matDef);

			//マテリアルデータへのポインタを取得
			pMat = (D3DXMATERIAL*)g_pBuffMatDamageblock->GetBufferPointer();
			for (int nCntMat = 0; nCntMat < (int)g_nNumMatDamageblock; nCntMat++)
			{
				//マテリアルの設定
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);
				pMat[nCntMat].MatD3D.Ambient = pMat[nCntMat].MatD3D.Diffuse;

				//モデルパーツの描画
				g_pMeshDamageblock->DrawSubset(nCntMat);
			}

			//保持していたマテリアルを戻す
			pDevice->SetMaterial(&matDef);
		}
	}
}

//=====================================================
//敵の取得
//=====================================================
Damageblock*GetDamageblock(void)
{
	int nCntDamageblock;

	for (nCntDamageblock = 0; nCntDamageblock < MAX_DAMAGEBLOCK; nCntDamageblock++)
	{
		return&g_aDamageblock[nCntDamageblock];
	}
	return&g_aDamageblock[nCntDamageblock];
}

//=====================================================
//設定処理
//=====================================================
void SetDamageblock(D3DXVECTOR3 pos, D3DXVECTOR3 size, int nType)
{
	for (int nCntDamageblock = 0; nCntDamageblock < MAX_DAMAGEBLOCK; nCntDamageblock++)
	{
		if (g_aDamageblock[nCntDamageblock].bUse == false)
		{
			g_aDamageblock[nCntDamageblock].pos = pos;
			g_aDamageblock[nCntDamageblock].size= size;
			g_aDamageblock[nCntDamageblock].nType = 0;
			g_aDamageblock[nCntDamageblock].bUse = true;

			break;
		}
	}
}

//=====================================================
// 当たり判定の設定
//=====================================================
bool HitDamageblock(int nCntEnemy, int nDamage)
{
	bool bHit = false;

	g_aDamageblock[nCntEnemy].nLife -= nDamage;//敵の体力を減らす

	if (g_aDamageblock[nCntEnemy].nLife <= 0)
	{
		g_aDamageblock[nCntEnemy].bUse = false;
		g_aDamageblock[nCntEnemy].isDown = true;
	}
	return bHit;
}

//=====================================================
// 当たり判定の設定
//=====================================================
bool HitDamageblock2(D3DXVECTOR3* pPos, D3DXVECTOR3* pPosOld, D3DXVECTOR3 size)
{
	int nCntBlock;					// ローカル変数
	bool bHit = false;

	for (nCntBlock = 0; nCntBlock < MAX_DAMAGEBLOCK; nCntBlock++)
	{
		// アイテムが使われたら
		if (g_aDamageblock[nCntBlock].bUse == true)
		{
			if (RectangleCollision(pPos, pPosOld, size, &g_aDamageblock[nCntBlock].pos, g_aDamageblock[nCntBlock].size) == true)
			{
				bHit = true;
			}
		}
	}

	return bHit;
}

//=====================================================
// ブロックに横からあたったときの設定
//=====================================================
bool CollisionDamageblock(D3DXVECTOR3* pPos, D3DXVECTOR3* pPosOld, D3DXVECTOR3 size)
{
	int nCntBlock;					// ローカル変数
	bool isHit = false;

	for (nCntBlock = 0; nCntBlock < MAX_DAMAGEBLOCK; nCntBlock++)
	{
		// ブロックが使われたら
		if (g_aDamageblock[nCntBlock].bUse == true)
		{
			//当たり判定を計算
			if (WallCollision(pPos, pPosOld, size, &g_aDamageblock[nCntBlock].pos, g_aDamageblock[nCntBlock].size) == true)
			{
				isHit = true;
			}
		}
	}
	return isHit;
}