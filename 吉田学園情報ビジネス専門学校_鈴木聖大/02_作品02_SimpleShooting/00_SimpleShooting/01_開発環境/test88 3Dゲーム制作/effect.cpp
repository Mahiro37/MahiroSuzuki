//=====================================================
//DirectXシューティングゲーム
//Author:鈴木聖大
//=====================================================
#include "main.h"
#include "effect.h"
#include "input.h"

//=====================================================
// グローバル変数
//=====================================================
LPDIRECT3DTEXTURE9 g_pTextureEffect = NULL;		// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEffect = NULL;	// 頂点バッファへのポインタ
int g_nCounterAnim;			// アニメーションカウンター
int g_nPatternAnim;			// アニメーションパターンNo.
int g_aNumPlayer; 
EFFECT g_Effect[MAX_EFFECT];

//=============================================================================
// 初期化処理
//=============================================================================
void InitEffect(void)
{
	int nCntEffect = 0;

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	g_Effect[nCntEffect].bUse = true;

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "テクスチャ/barriereffect.png", &g_pTextureEffect);
	//D3DXCreateTextureFromFile(pDevice, "テクスチャ/player.png", &g_pTextureEffect);

	// 頂点バッファ生成
	pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D)*NUM_VERTEX,	// バッファサイズ
		D3DUSAGE_WRITEONLY,				// (固定)
		FVF_VERTEX_2D,					// 頂点フォーマット
		D3DPOOL_MANAGED,				// (固定)
		&g_pVtxBuffEffect,		// 変数名が変わると変更が必要
		NULL);

	// 頂点情報へのポインタ
	VERTEX_2D * pVtx;

	// 頂点データの範囲をロックし、頂点バッファのポインタを取得
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3((SCREEN_WIDTH / 2) - (EFFECT_SIZE_X / 2), (SCREEN_HEIGHT / 2) + (EFFECT_SIZE_Y / 2) - 80.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3((SCREEN_WIDTH / 2) + (EFFECT_SIZE_X / 2), (SCREEN_HEIGHT / 2) + (EFFECT_SIZE_Y / 2) - 80.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3((SCREEN_WIDTH / 2) - (EFFECT_SIZE_X / 2), (SCREEN_HEIGHT / 2) - (EFFECT_SIZE_Y / 2) - 80.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3((SCREEN_WIDTH / 2) + (EFFECT_SIZE_X / 2), (SCREEN_HEIGHT / 2) - (EFFECT_SIZE_Y / 2) - 80.0f, 0.0f);

	// rhwの設定(値は1.0で固定)
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// 頂点カラーの設定
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	g_Effect[nCntEffect].pos = D3DXVECTOR3(EFFECT_POS_X, EFFECT_POS_Y, 0.0f);

	// 頂点データをアンロックする
	g_pVtxBuffEffect->Unlock();
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitEffect(void)
{
	// テクスチャの開放
	if (g_pTextureEffect != NULL)
	{
		g_pTextureEffect->Release();
		g_pTextureEffect = NULL;
	}

	// 頂点バッファの開放
	if (g_pVtxBuffEffect != NULL)
	{
		g_pVtxBuffEffect->Release();
		g_pVtxBuffEffect = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateEffect(void)
{
	// 頂点情報へのポインタ
	VERTEX_2D *pVtx;

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	int nCntEffect = 0;

	g_nCounterAnim++;				// カウンター加算

	if (g_nCounterAnim == 4)		// 8fpsで次のアニメーション	＝ アニメーションの速さ
	{
		g_nCounterAnim = 0;			// カウンターを初期値に戻す
		g_nPatternAnim++;

		if (g_nPatternAnim == 10)	// 動かしたい画像の枚数
		{
			g_nPatternAnim = 0;		// カウンターを初期地に戻す
		}
	}

	// 頂点バッファのロック
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	// テクスチャ座標を更新
	pVtx[0].tex = D3DXVECTOR2(g_nPatternAnim * 0.1f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(g_nPatternAnim * 0.1f + 0.1f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(g_nPatternAnim * 0.1f, -1.0f);
	pVtx[3].tex = D3DXVECTOR2(g_nPatternAnim * 0.1f + 0.1f, -1.0f);

	// 頂点座標の更新
	pVtx[0].pos = D3DXVECTOR3((SCREEN_WIDTH / 2) - (EFFECT_POS_X / 2), (SCREEN_HEIGHT / 2) + (EFFECT_POS_Y / 2) - 80.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3((SCREEN_WIDTH / 2) + (EFFECT_POS_X / 2), (SCREEN_HEIGHT / 2) + (EFFECT_POS_Y / 2) - 80.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3((SCREEN_WIDTH / 2) - (EFFECT_POS_X / 2), (SCREEN_HEIGHT / 2) - (EFFECT_POS_Y / 2) - 80.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3((SCREEN_WIDTH / 2) + (EFFECT_POS_X / 2), (SCREEN_HEIGHT / 2) - (EFFECT_POS_Y / 2) - 80.0f, 0.0f);

	//pVtx += 4;

	// 頂点バッファをアンロック
	g_pVtxBuffEffect->Unlock();

}

//=============================================================================
// 描画処理
//=============================================================================
void DrawEffect(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点バッファをデバイスのデータストリームにバインド
	pDevice->SetStreamSource(0, g_pVtxBuffEffect, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_pTextureEffect);

	// ポリゴンの描画
	pDevice->DrawPrimitive(
		D3DPT_TRIANGLESTRIP,		// プリミティブの種類
		0,
		NUM_POLYGON);				// プリミティブの数
}

////=============================================================================
//// エフェクトの設定
////=============================================================================
//void SetEffect(D3DXVECTOR3 pos, D3DXVECTOR3 size)
//{
//	int nCntBlock;				// ローカル変数
//
//	for (nCntBlock = 0; nCntBlock < MAX_EFFECT; nCntBlock++)
//	{
//		// ブロックが使われてないとき
//		if (g_Effect[nCntBlock].bUse == false)
//		{
//			g_Effect[nCntBlock].pos = pos;
//			g_Effect[nCntBlock].size = size;
//			g_Effect[nCntBlock].bUse = true;
//			break;
//		}
//	}
//}