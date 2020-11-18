//================================================
//3Dゲーム制作
//Author:鈴木聖大
//================================================
#include "main.h"
#include "blur.h"

//================================================
//グローバル変数
//================================================
//頂点バッファへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBlur = NULL;

//ポリゴンのテクスチャ
LPDIRECT3DTEXTURE9 g_pTextureBlur = NULL;

//ポリゴンの位置
D3DXVECTOR3 g_posBlur;

//ポリゴンの向き
D3DXVECTOR3 g_rotBlur;

//ポリゴンのワールドマトリックス
D3DXMATRIX g_mtxWorldBlur;

//================================================
//初期化処理
//================================================
void InitBlur(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "テクスチャ/blur.jpg", &g_pTextureBlur);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBlur,
		NULL);

	VERTEX_3D*pVtx = NULL;

	//頂点バッファをロック
	g_pVtxBuffBlur->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(-(BLUR_SIZE / 2), 30.0f, +(BLUR_SIZE / 2));
	pVtx[1].pos = D3DXVECTOR3(+(BLUR_SIZE / 2), 30.0f, +(BLUR_SIZE / 2));
	pVtx[2].pos = D3DXVECTOR3(-(BLUR_SIZE / 2), 30.0f, -(BLUR_SIZE / 2));
	pVtx[3].pos = D3DXVECTOR3(+(BLUR_SIZE / 2), 30.0f, -(BLUR_SIZE / 2));

	//各頂点の法線の設定(※ベクトルの大きさは1にする必要がある)
	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	// 頂点カラーの設定
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 120);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 120);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 120);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 120);

	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファのアンロック
	g_pVtxBuffBlur->Unlock();
}

//================================================
//終了処理
//================================================
void UninitBlur(void)
{
	//テクスチャの開放
	if (g_pTextureBlur != NULL)
	{
		g_pTextureBlur->Release();
		g_pTextureBlur = NULL;
	}

	//頂点バッファの開放
	if (g_pVtxBuffBlur != NULL)
	{
		g_pVtxBuffBlur->Release();
		g_pVtxBuffBlur = NULL;
	}
}

//================================================
//更新処理
//================================================
void UpdateBlur(void)
{
}

//================================================
//描画処理
//================================================
void DrawBlur(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();//デバイスポインタ
	D3DXMATRIX mtxRot, mtxTrans;//行列計算用のマトリクス

								//ワールドマトリクスの初期化
	D3DXMatrixIdentity(&g_mtxWorldBlur);

	//向きを反転
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_rotBlur.y, g_rotBlur.x, g_rotBlur.z);
	D3DXMatrixMultiply(&g_mtxWorldBlur, &g_mtxWorldBlur, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, g_posBlur.x, g_posBlur.y, g_posBlur.z);
	D3DXMatrixMultiply(&g_mtxWorldBlur, &g_mtxWorldBlur, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldBlur);

	//頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffBlur, 0, sizeof(VERTEX_3D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_pTextureBlur);

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}