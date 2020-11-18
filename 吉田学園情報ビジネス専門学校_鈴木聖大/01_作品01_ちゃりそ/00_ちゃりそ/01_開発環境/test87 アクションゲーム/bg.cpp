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
#include "bg.h"

//****************************************************************
// グローバル変数
//****************************************************************
//VERTEX_2D g_aVertex[NUM_VERTEX];					// 頂点情報格納
LPDIRECT3DTEXTURE9 g_pTexturePolygonBg = NULL;		// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPolygonBg = NULL;	// 頂点バッファへのポインタ
int g_nCounterAnimBg;
int g_nPatternAnimBg;

//****************************************************************
// 初期化処理
//****************************************************************
void InitBg(void)
{
	VERTEX_2D * pVtx;		// 頂点情報へのポインタ
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "テクスチャ/bg1.png",&g_pTexturePolygonBg);	// 変数名が変わると変更

	// 頂点バッファ生成
	pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D)*NUM_VERTEX,	// バッファサイズ
		D3DUSAGE_WRITEONLY,				// (固定)
		FVF_VERTEX_2D,					// 頂点フォーマット
		D3DPOOL_MANAGED,				// (固定)
		&g_pVtxBuffPolygonBg,			// 変数名が変わると変更が必要
		NULL);

	// 頂点データの範囲をロック
	g_pVtxBuffPolygonBg->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(0.0f, -120.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, -120.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT - 120.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT - 120.0f, 0.0f);

	// rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// 頂点カラーの設定
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 180);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 180);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 180);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 180);

	// テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// 頂点データをアンロック
	g_pVtxBuffPolygonBg->Unlock();
}

//****************************************************************
// 終了処理
//****************************************************************
void UninitBg(void)
{
	// テクスチャの開放
	if (g_pTexturePolygonBg != NULL)
	{
		g_pTexturePolygonBg->Release();
		g_pTexturePolygonBg = NULL;
	}

	// 頂点バッファの開放
	if (g_pVtxBuffPolygonBg != NULL)
	{
		g_pVtxBuffPolygonBg->Release();
		g_pVtxBuffPolygonBg = NULL;
	}
}

//****************************************************************
// 更新処理
//****************************************************************
void UpdateBg(void)
{
	VERTEX_2D * pVtx;	// 頂点情報へのポインタ
	g_nCounterAnimBg++;	//カウンタ加算

	if (g_nCounterAnimBg == 1)//動きの速さ
	{
		g_nCounterAnimBg = 0;
		g_nPatternAnimBg++;

		if (g_nPatternAnimBg == 3333)//動かしたい画像の枚数
		{
			g_nPatternAnimBg = 0;
		}
	}
	  
	// 頂点データの範囲をロック
	g_pVtxBuffPolygonBg->Lock(0, 0, (void**)&pVtx, 0);

	// テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(g_nPatternAnimBg*-0.9997f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(g_nPatternAnimBg*-0.9997f+0.9997f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(g_nPatternAnimBg*-0.9997f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(g_nPatternAnimBg*-0.9997f+0.9997f, 1.0f);

	// 頂点データをアンロック
	g_pVtxBuffPolygonBg->Unlock();
}

//****************************************************************
// 描画処理
//****************************************************************
void DrawBg(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点バッファをデバイスのデータストリームにバインド
	pDevice->SetStreamSource(0, g_pVtxBuffPolygonBg, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_pTexturePolygonBg);

	// ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);	// プリミティブの種類 , 先頭の値 , プリミティブの数
}