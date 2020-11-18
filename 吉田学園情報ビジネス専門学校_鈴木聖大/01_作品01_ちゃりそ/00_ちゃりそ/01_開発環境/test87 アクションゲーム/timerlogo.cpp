//================================================================
//
//DirectXシューティングゲーム
//Author:鈴木聖大
//
//================================================================

//****************************************************************
//インクルードファイル
//****************************************************************
#include "main.h"
#include "timerlogo.h"

//****************************************************************
// グローバル変数
//****************************************************************
//VERTEX_2D g_aVertex[NUM_VERTEX];					// 頂点情報格納
LPDIRECT3DTEXTURE9 g_pTextureTimerLogoBg = NULL;		// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTimerLogoBg = NULL;	// 頂点バッファへのポインタ

//****************************************************************
// 初期化処理
//****************************************************************
void InitTimerLogo(void)
{
	VERTEX_2D * pVtx;		// 頂点情報へのポインタ
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "テクスチャ/timer.png", &g_pTextureTimerLogoBg);	// 変数名が変わると変更

	// 頂点バッファ生成
	pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D)*NUM_VERTEX,	// バッファサイズ
		D3DUSAGE_WRITEONLY,				// (固定)
		FVF_VERTEX_2D,					// 頂点フォーマット
		D3DPOOL_MANAGED,				// (固定)
		&g_pVtxBuffTimerLogoBg,				// 変数名が変わると変更が必要
		NULL);

	// 頂点データの範囲をロックし、頂点バッファのポインタを取得
	g_pVtxBuffTimerLogoBg->Lock(0, 0, (void**)&pVtx, 0);	// この書式は変えないこと

	// 頂点座標の設定( Zの形に配置する)  / 四角形の頂点の位置
	pVtx[0].pos = D3DXVECTOR3((SCREEN_WIDTH / 2) - (TIMERLOGO_SIZE_X / 2)-1.5f, 25.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3((SCREEN_WIDTH / 2) + (TIMERLOGO_SIZE_X / 2)-1.5f, 25.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3((SCREEN_WIDTH / 2) - (TIMERLOGO_SIZE_X / 2)-1.5f, 25.0f + (TIMERLOGO_SIZE_Y / 2), 0.0f);
	pVtx[3].pos = D3DXVECTOR3((SCREEN_WIDTH / 2) + (TIMERLOGO_SIZE_X / 2)-1.5f, 25.0f + (TIMERLOGO_SIZE_Y / 2), 0.0f);

	// rhwの設定(値は1.0で固定)		/ あまり変えることはない
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// 頂点カラーの設定(0～255の数値で設定)	/ 全体の色
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 220);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 220);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 220);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 220);

	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// 頂点データをアンロックする
	g_pVtxBuffTimerLogoBg->Unlock();
}

//****************************************************************
// 終了処理
//****************************************************************
void UninitTimerLogo(void)
{
	// テクスチャの開放
	if (g_pTextureTimerLogoBg != NULL)
	{
		g_pTextureTimerLogoBg->Release();
		g_pTextureTimerLogoBg = NULL;
	}
	// 頂点バッファの開放
	if (g_pVtxBuffTimerLogoBg != NULL)
	{
		g_pVtxBuffTimerLogoBg->Release();
		g_pVtxBuffTimerLogoBg = NULL;
	}
}

//****************************************************************
// 更新処理
//****************************************************************
void UpdateTimerLogo(void)
{
}

//****************************************************************
// 描画処理
//****************************************************************
void DrawTimerLogo(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	// 頂点バッファをデバイスのデータストリームにバインド
	pDevice->SetStreamSource(0, g_pVtxBuffTimerLogoBg, 0, sizeof(VERTEX_2D));
	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);
	// テクスチャの設定
	pDevice->SetTexture(0, g_pTextureTimerLogoBg);
	// ポリゴンの描画
	pDevice->DrawPrimitive(
		D3DPT_TRIANGLESTRIP,		// プリミティブの種類
		0,
		NUM_POLYGON);				// プリミティブの数
}