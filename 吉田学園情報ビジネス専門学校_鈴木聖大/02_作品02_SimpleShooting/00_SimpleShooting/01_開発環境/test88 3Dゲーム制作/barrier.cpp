//=====================================================
//
// 3Dゲーム ブロックの処理 [barrier.h]
// Author:小西優斗
//
//=====================================================

//=====================================================
// インクルードファイル
//=====================================================
#include "barrier.h"
#include "camera.h"
#include "player.h"
#include "collision.h"
#include "bullet.h"
#include "enemy.h"

//=====================================================
// マクロ定義
//=====================================================

//=====================================================
// グローバル変数
//=====================================================
BARRIER g_Barrier[MAX_BARRIER];

// 頂点バッファへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBarrier = NULL;

// テクスチャへのポインタ
LPDIRECT3DTEXTURE9 g_pTextureBarrier = NULL;

// メッシュ情報へのポインタ
LPD3DXMESH g_pMeshBarrier = NULL;

// マテリアル情報へのポインタ
LPD3DXBUFFER g_pBuffMatBarrier = NULL;

// マテリアル情報の数
DWORD g_nNumMatBarrier = 0;


//=====================================================
// 初期化処理
//=====================================================
void InitBarrier(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();		// デバイスへのポインタ


	int nCntBarrier;


	// 配列初期化
	for (nCntBarrier = 0; nCntBarrier < MAX_BARRIER; nCntBarrier++)
	{
		g_Barrier[nCntBarrier].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Barrier[nCntBarrier].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Barrier[nCntBarrier].size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Barrier[nCntBarrier].bUse = false;
		g_Barrier[nCntBarrier].bUse = false;
		g_Barrier[nCntBarrier].isDown = false;
		g_Barrier[nCntBarrier].nLife = 3;						//敵の体力

	}

	// Xファイルの読み込み
	D3DXLoadMeshFromX("Xファイル/barrier.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_pBuffMatBarrier, NULL, &g_nNumMatBarrier, &g_pMeshBarrier);
}

//=====================================================
// 終了処理
//=====================================================
void UninitBarrier(void)
{
	// メッシュの破棄
	if (g_pMeshBarrier != NULL)
	{
		g_pMeshBarrier->Release();
		g_pMeshBarrier = NULL;
	}
	// マテリアルの破棄
	if (g_pBuffMatBarrier != NULL)
	{
		g_pBuffMatBarrier->Release();
		g_pBuffMatBarrier = NULL;
	}
	// テクスチャの破棄
	if (g_pTextureBarrier != NULL)
	{
		g_pTextureBarrier->Release();
		g_pTextureBarrier = NULL;
	}
}

//=====================================================
// 更新処理
//=====================================================
void UpdateBarrier(void)
{
	for (int nCntBarrier = 0; nCntBarrier < MAX_BARRIER; nCntBarrier++)
	{
		if (g_Barrier[nCntBarrier].bUse == true)
		{
			////1F前の位置を記憶
			//g_Barrier[nCntBarrier].posOld = g_Barrier[nCntBarrier].pos;

			//for (nCntBarrier = 0; nCntBarrier < MAX_BARRIER; nCntBarrier++)
			//{
				if (g_Barrier[nCntBarrier].isDown == false)
				{
					////プレイヤーの弾に当たった時
					//if (CollisionBullet(&g_Barrier[nCntBarrier].pos, &g_Barrier[nCntBarrier].posOld, D3DXVECTOR3(BARRIER_SIZE_X, BARRIER_SIZE_Y, BARRIER_SIZE_Z + 10), BULLETTYPE_PLAYER) == true)
					//{
					if (IsZakoDown() == true)
					{
						HitBarrier(nCntBarrier, 10);//(誰に対して,何ダメージ与えるか)
					}
					//}
				}
			//}
		}
	}
}

//=====================================================
// 描画処理
//=====================================================
void DrawBarrier(void)
{
	int nCntBarrier;
	LPDIRECT3DDEVICE9 pDevice = GetDevice();		// デバイスへのポインタ
	D3DXMATRIX mtxRot, mtxTrans, mtxScale;
	D3DMATERIAL9 matDef;		// 現在のマテリアル保持用
	D3DXMATERIAL* pMat;			// マテリアルデータへのポインタ


	for (nCntBarrier = 0; nCntBarrier < MAX_BARRIER; nCntBarrier++)
	{
		if (g_Barrier[nCntBarrier].bUse == true)
		{
			// ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_Barrier[nCntBarrier].mtxWorld);

			// スケールを反映
			D3DXMatrixScaling(&mtxScale,
				g_Barrier[nCntBarrier].size.x / BARRIER_SIZE_X,
				g_Barrier[nCntBarrier].size.y / BARRIER_SIZE_Y,
				g_Barrier[nCntBarrier].size.z / BARRIER_SIZE_Z);
			D3DXMatrixMultiply(&g_Barrier[nCntBarrier].mtxWorld, &g_Barrier[nCntBarrier].mtxWorld, &mtxScale);
			// 向きを反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot,
				g_Barrier[nCntBarrier].rot.y,
				g_Barrier[nCntBarrier].rot.x,
				g_Barrier[nCntBarrier].rot.z);
			D3DXMatrixMultiply(&g_Barrier[nCntBarrier].mtxWorld, &g_Barrier[nCntBarrier].mtxWorld, &mtxRot);
			// 位置を反映
			D3DXMatrixTranslation(&mtxTrans,
				g_Barrier[nCntBarrier].pos.x,
				g_Barrier[nCntBarrier].pos.y,
				g_Barrier[nCntBarrier].pos.z);
			D3DXMatrixMultiply(&g_Barrier[nCntBarrier].mtxWorld, &g_Barrier[nCntBarrier].mtxWorld, &mtxTrans);


			// ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_Barrier[nCntBarrier].mtxWorld);
			// テクスチャの設定
			pDevice->SetTexture(0, NULL);
			// 現在のマテリアルを取得する
			pDevice->GetMaterial(&matDef);
			// マテリアルデータへのポインタを取得
			pMat = (D3DXMATERIAL*)g_pBuffMatBarrier->GetBufferPointer();
			for (int nCntMat = 0; nCntMat < (int)g_nNumMatBarrier; nCntMat++)
			{
				// テクスチャの設定
				pDevice->SetTexture(0, g_pTextureBarrier);
				// マテリアルの設定
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);
				pMat[nCntMat].MatD3D.Ambient = pMat[nCntMat].MatD3D.Diffuse;
				// モデルパーツ
				g_pMeshBarrier->DrawSubset(nCntMat);
			}
			// 保持していたマテリアルを戻す
			pDevice->SetMaterial(&matDef);
		}
	}
}

//=====================================================
// ブロックの設定
//=====================================================
void SetBarrier(D3DXVECTOR3 pos, D3DXVECTOR3 dir, D3DXVECTOR3 size)
{

	int nCntBarrier;				// ローカル変数

	for (nCntBarrier = 0; nCntBarrier < MAX_BARRIER; nCntBarrier++)
	{
		// ブロックが使われてないとき
		if (g_Barrier[nCntBarrier].bUse == false)
		{
			// 対象の配列の要素に、usedやposやsizeをセット

			// ブロックを使用している状態にする

			g_Barrier[nCntBarrier].pos = pos;
			g_Barrier[nCntBarrier].rot = dir;
			g_Barrier[nCntBarrier].size = size;
			g_Barrier[nCntBarrier].bUse = true;
			break;
		}
	}
}

//=====================================================
// ブロックに横からあたったときの設定
//=====================================================
bool CollisionBarrier(D3DXVECTOR3* pPos, D3DXVECTOR3* pPosOld, D3DXVECTOR3 size)
{
	int nCntBarrier;					// ローカル変数
	bool isHit = false;

	for (nCntBarrier = 0; nCntBarrier < MAX_BARRIER; nCntBarrier++)
	{
		// ブロックが使われたら
		if (g_Barrier[nCntBarrier].bUse == true)
		{
			//当たり判定を計算
			if (WallCollision(pPos, pPosOld, size, &g_Barrier[nCntBarrier].pos, g_Barrier[nCntBarrier].size) == true)
			{
				isHit = true;
			}
		}
	}
	return isHit;
}

BARRIER*GetBarrier(void)
{
	return &g_Barrier[0];		// 値を返す(渡す)
}

//=====================================================
// 当たり判定の設定
//=====================================================
bool HitBarrier(int nCntEnemy, int nDamage)
{
	bool bHit = false;

	g_Barrier[nCntEnemy].nLife -= nDamage;//敵の体力を減らす

	if (g_Barrier[nCntEnemy].nLife <= 0)
	{
		g_Barrier[nCntEnemy].bUse = false;
		g_Barrier[nCntEnemy].isDown = true;
	}
	return bHit;
}

//=====================================================
// 当たり判定の設定
//=====================================================
bool HitBarrier2(D3DXVECTOR3* pPos, D3DXVECTOR3* pPosOld, D3DXVECTOR3 size)
{
	int nCntBarrier;					// ローカル変数
	bool bHit = false;

	for (nCntBarrier = 0; nCntBarrier < MAX_BARRIER; nCntBarrier++)
	{
		// アイテムが使われたら
		if (g_Barrier[nCntBarrier].bUse == true)
		{
			if (RectangleCollision(pPos, pPosOld, size, &g_Barrier[nCntBarrier].pos, g_Barrier[nCntBarrier].size) == true)
			{
				bHit = true;
			}
		}
	}

	return bHit;
}