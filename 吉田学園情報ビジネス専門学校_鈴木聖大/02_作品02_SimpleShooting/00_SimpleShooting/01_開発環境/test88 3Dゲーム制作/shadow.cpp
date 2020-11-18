//================================================
//3Dゲーム制作
//Author:鈴木聖大
//================================================
#include "main.h"
#include "shadow.h"
#include "input.h"
#include "camera.h"

//================================================
//グローバル変数
//================================================
//頂点バッファへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffShadow = NULL;

//影の位置
D3DXVECTOR3 g_posShadow;

//影の向き
D3DXVECTOR3 g_rotShadow;

//影のワールドマトリックス
D3DXMATRIX g_mtxWorldShadow;

//影のテクスチャ
LPDIRECT3DTEXTURE9 g_pTextureShadow = NULL;

//影
Shadow g_shadow[MAX_SHADOW];

//================================================
//初期化処理
//================================================
void InitShadow(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	int nCntShadow;

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "テクスチャ/shadow.png", &g_pTextureShadow);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffShadow,
		NULL);

	VERTEX_3D*pVtx = NULL;

	//影の情報の初期化
	for (nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++)
	{
		g_shadow[nCntShadow].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_shadow[nCntShadow].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}

	//頂点バッファをロック
	g_pVtxBuffShadow->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(-(SHADOW_SIZE_X / 2), 0.1f, +(SHADOW_SIZE_Y / 2));
	pVtx[1].pos = D3DXVECTOR3(+(SHADOW_SIZE_X / 2), 0.1f, +(SHADOW_SIZE_Y / 2));
	pVtx[2].pos = D3DXVECTOR3(-(SHADOW_SIZE_X / 2), 0.1f, -(SHADOW_SIZE_Y / 2)-5);
	pVtx[3].pos = D3DXVECTOR3(+(SHADOW_SIZE_X / 2), 0.1f, -(SHADOW_SIZE_Y / 2)-5);

	//各頂点の法線の設定(※ベクトルの大きさは1にする必要がある)
	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	// 頂点カラーの設定
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファのアンロック
	g_pVtxBuffShadow->Unlock();
}

//================================================
//終了処理
//================================================
void UninitShadow(void)
{
	//テクスチャの開放
	if (g_pTextureShadow != NULL)
	{
		g_pTextureShadow->Release();
		g_pTextureShadow = NULL;
	}

	//頂点バッファの開放
	if (g_pVtxBuffShadow != NULL)
	{
		g_pVtxBuffShadow->Release();
		g_pVtxBuffShadow = NULL;
	}
}

int SetShadow(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	int nCntShadow = 0;

	for (; nCntShadow < MAX_SHADOW; nCntShadow++)
	{
		if (!g_shadow[nCntShadow].use)
		{
			g_shadow[nCntShadow].pos = pos;
			g_shadow[nCntShadow].rot = rot;
			g_shadow[nCntShadow].use = true;
			break;
		}
	}
	return nCntShadow;//影生成に使用した配列のインデックスを返す
}

//================================================
//更新処理
//================================================
void SetPositionShadow(int nldxShadow, D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	g_shadow[nldxShadow].pos = pos;
	g_shadow[nldxShadow].rot = rot;
}

//================================================
//描画処理
//================================================
void DrawShadow(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();//デバイスポインタ
	D3DXMATRIX mtxRot, mtxTrans;//行列計算用のマトリクス

	//減算合成に設定(影は黒いから減算して黒に近づける)
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	pDevice->SetTexture(0, g_pTextureShadow);

	for (int i = 0; i < MAX_SHADOW; i++)
	{
		if (g_shadow[i].use)
		{
			//ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldShadow);

			//ワールドマトリクスの初期化
			D3DXMatrixIdentity(&g_mtxWorldShadow);

			//向きを反転
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_shadow[i].rot.y, g_shadow[i].rot.x, g_shadow[i].rot.z);
			D3DXMatrixMultiply(&g_mtxWorldShadow, &g_mtxWorldShadow, &mtxRot);

			//位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_shadow[i].pos.x, g_shadow[i].pos.y, g_shadow[i].pos.z);
			D3DXMatrixMultiply(&g_mtxWorldShadow, &g_mtxWorldShadow, &mtxTrans);

			//頂点バッファをデバイスのデータストリームに設定
			pDevice->SetStreamSource(0, g_pVtxBuffShadow, 0, sizeof(VERTEX_3D));

			//頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_3D);

			//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
		}
	}

	//レンダーステート設定を元に戻す
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	pDevice->SetTexture(0, NULL);
}