//=====================================================
//
// 3Dゲーム ブロックの処理 [block.h]
// Author:小西優斗
//
//=====================================================

//=====================================================
// インクルードファイル
//=====================================================
#include "wallblock.h"
#include "camera.h"
#include "player.h"
#include "collision.h"

//=====================================================
// マクロ定義
//=====================================================

//=====================================================
// グローバル変数
//=====================================================
BLOCK g_Block[MAX_BLOCK];

// 頂点バッファへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBlock = NULL;

// テクスチャへのポインタ
LPDIRECT3DTEXTURE9 g_pTextureBlock = NULL;

// メッシュ情報へのポインタ
LPD3DXMESH g_pMeshBlock = NULL;

// マテリアル情報へのポインタ
LPD3DXBUFFER g_pBuffMatBlock = NULL;

// マテリアル情報の数
DWORD g_nNumMatBlock = 0;


//=====================================================
// 初期化処理
//=====================================================
void InitBlock(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();		// デバイスへのポインタ


	int nCntBlock;


	// 配列初期化
	for (nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		g_Block[nCntBlock].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Block[nCntBlock].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Block[nCntBlock].size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Block[nCntBlock].bUse = false;
	}

	// Xファイルの読み込み
	D3DXLoadMeshFromX("Xファイル/Block.x",D3DXMESH_SYSTEMMEM,pDevice,NULL,&g_pBuffMatBlock,NULL,&g_nNumMatBlock,&g_pMeshBlock);
}

//=====================================================
// 終了処理
//=====================================================
void UninitBlock(void)
{
	// メッシュの破棄
	if (g_pMeshBlock != NULL)
	{
		g_pMeshBlock->Release();
		g_pMeshBlock = NULL;
	}
	// マテリアルの破棄
	if (g_pBuffMatBlock != NULL)
	{
		g_pBuffMatBlock->Release();
		g_pBuffMatBlock = NULL;
	}
	// テクスチャの破棄
	if (g_pTextureBlock != NULL)
	{
		g_pTextureBlock->Release();
		g_pTextureBlock = NULL;
	}
}

//=====================================================
// 更新処理
//=====================================================
void UpdateBlock(void)
{
	//// カメラ情報を取得する
	//CAMERA *pCamera = GetCamera();

}

//=====================================================
// 描画処理
//=====================================================
void DrawBlock(void)
{
	int nCntBlock;
	LPDIRECT3DDEVICE9 pDevice = GetDevice();		// デバイスへのポインタ
	D3DXMATRIX mtxRot, mtxTrans, mtxScale;
	D3DMATERIAL9 matDef;		// 現在のマテリアル保持用
	D3DXMATERIAL* pMat;			// マテリアルデータへのポインタ


	for (nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		if (g_Block[nCntBlock].bUse == true)
		{
			// ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_Block[nCntBlock].mtxWorld);

			// スケールを反映
			D3DXMatrixScaling(&mtxScale,
				g_Block[nCntBlock].size.x / BLOCK_SIZE_X,
				g_Block[nCntBlock].size.y / BLOCK_SIZE_Y,
				g_Block[nCntBlock].size.z / BLOCK_SIZE_Z);
			D3DXMatrixMultiply(&g_Block[nCntBlock].mtxWorld, &g_Block[nCntBlock].mtxWorld, &mtxScale);
			// 向きを反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot,
				g_Block[nCntBlock].rot.y,
				g_Block[nCntBlock].rot.x,
				g_Block[nCntBlock].rot.z);
			D3DXMatrixMultiply(&g_Block[nCntBlock].mtxWorld, &g_Block[nCntBlock].mtxWorld, &mtxRot);
			// 位置を反映
			D3DXMatrixTranslation(&mtxTrans,
				g_Block[nCntBlock].pos.x,
				g_Block[nCntBlock].pos.y,
				g_Block[nCntBlock].pos.z);
			D3DXMatrixMultiply(&g_Block[nCntBlock].mtxWorld, &g_Block[nCntBlock].mtxWorld, &mtxTrans);


			// ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_Block[nCntBlock].mtxWorld);
			// テクスチャの設定
			pDevice->SetTexture(0, NULL);
			// 現在のマテリアルを取得する
			pDevice->GetMaterial(&matDef);
			// マテリアルデータへのポインタを取得
			pMat = (D3DXMATERIAL*)g_pBuffMatBlock->GetBufferPointer();
			for (int nCntMat = 0; nCntMat < (int)g_nNumMatBlock; nCntMat++)
			{
				// テクスチャの設定
				pDevice->SetTexture(0, g_pTextureBlock);
				// マテリアルの設定
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);
				pMat[nCntMat].MatD3D.Ambient = pMat[nCntMat].MatD3D.Diffuse;
				// モデルパーツ
				g_pMeshBlock->DrawSubset(nCntMat);
			}
			// 保持していたマテリアルを戻す
			pDevice->SetMaterial(&matDef);
		}
	}
}

//=====================================================
// ブロックの設定
//=====================================================
void SetBlock(D3DXVECTOR3 pos, D3DXVECTOR3 dir, D3DXVECTOR3 size)
{

	int nCntBlock;				// ローカル変数

	for (nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		// ブロックが使われてないとき
		if (g_Block[nCntBlock].bUse == false)
		{
			// 対象の配列の要素に、usedやposやsizeをセット

			// ブロックを使用している状態にする

			g_Block[nCntBlock].pos = pos;
			g_Block[nCntBlock].rot = dir;
			g_Block[nCntBlock].size = size;
			g_Block[nCntBlock].bUse = true;
			break;
		}
	}
}

//=====================================================
// ブロックに横からあたったときの設定
//=====================================================
bool CollisionBlock(D3DXVECTOR3* pPos, D3DXVECTOR3* pPosOld, D3DXVECTOR3 size)
{
	int nCntBlock;					// ローカル変数
	bool isHit = false;

	for (nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		// ブロックが使われたら
		if (g_Block[nCntBlock].bUse == true)
		{
			//当たり判定を計算
			if (WallCollision(pPos, pPosOld, size, &g_Block[nCntBlock].pos, g_Block[nCntBlock].size) == true)
			{
				isHit = true;
			}
		}
	}
	return isHit;
}

BLOCK*GetBlock(void)
{
	return &g_Block[0];		// 値を返す(渡す)
}

//=====================================================
// 当たり判定の設定
//=====================================================
bool HitBlock(D3DXVECTOR3* pPos, D3DXVECTOR3* pPosOld, D3DXVECTOR3 size)
{
	int nCntBlock;					// ローカル変数
	bool bHit = false;

	for (nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		// アイテムが使われたら
		if (g_Block[nCntBlock].bUse == true)
		{
			if (RectangleCollision(pPos, pPosOld, size, &g_Block[nCntBlock].pos, g_Block[nCntBlock].size) == true)
			{
				bHit = true;
			}
		}
	}

	return bHit;
}