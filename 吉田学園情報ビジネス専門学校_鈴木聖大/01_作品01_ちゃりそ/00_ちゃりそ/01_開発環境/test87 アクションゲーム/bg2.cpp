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
#include "bg2.h"

//****************************************************************
// グローバル変数
//****************************************************************
//VERTEX_2D g_aVertex[NUM_VERTEX];					// 頂点情報格納
LPDIRECT3DTEXTURE9 g_pTexturePolygonBg2 = NULL;		// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPolygonBg2 = NULL;	// 頂点バッファへのポインタ
int g_nCounterAnimBg2;
int g_nPatternAnimBg2;

//****************************************************************
// 初期化処理
//****************************************************************
void InitBg2(void)
{
	VERTEX_2D * pVtx;		// 頂点情報へのポインタ
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "テクスチャ/bg2.png", &g_pTexturePolygonBg2);	// 変数名が変わると変更

																				// 頂点バッファ生成
	pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D)*NUM_VERTEX,	// バッファサイズ
		D3DUSAGE_WRITEONLY,				// (固定)
		FVF_VERTEX_2D,					// 頂点フォーマット
		D3DPOOL_MANAGED,				// (固定)
		&g_pVtxBuffPolygonBg2,				// 変数名が変わると変更が必要
		NULL);

	// 頂点データの範囲をロックし、頂点バッファのポインタを取得
	g_pVtxBuffPolygonBg2->Lock(0, 0, (void**)&pVtx, 0);	// この書式は変えないこと

	// 頂点座標の設定( Zの形に配置する)  / 四角形の頂点の位置
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);
	// rhwの設定(値は1.0で固定)		/ あまり変えることはない
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;
	// 頂点カラーの設定(0～255の数値で設定)	/ 全体の色
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);	// 左上頂点の色	透明度255
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);	// 右上頂点の色	透明度255
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);	// 左下頂点の色	透明度255
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);	// 右上頂点の色	透明度255
														// テクスチャ座標の設定		画面に対しての分割数
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// 頂点データをアンロックする
	g_pVtxBuffPolygonBg2->Unlock();
}

//****************************************************************
// 終了処理
//****************************************************************
void UninitBg2(void)
{
	// テクスチャの開放
	if (g_pTexturePolygonBg2 != NULL)
	{
		g_pTexturePolygonBg2->Release();
		g_pTexturePolygonBg2 = NULL;
	}
	// 頂点バッファの開放
	if (g_pVtxBuffPolygonBg2 != NULL)
	{
		g_pVtxBuffPolygonBg2->Release();
		g_pVtxBuffPolygonBg2 = NULL;
	}
}

//****************************************************************
// 更新処理
//****************************************************************
void UpdateBg2(void)
{
	VERTEX_2D * pVtx;		// 頂点情報へのポインタ
	g_nCounterAnimBg2++;//カウンタ加算

	if (g_nCounterAnimBg2 == 1)//動きの速さ
	{
		g_nCounterAnimBg2 = 0;
		g_nPatternAnimBg2++;

		if (g_nPatternAnimBg2 == 500)//動かしたい画像の枚数
		{
			g_nPatternAnimBg2 = 0;
		}
	}

	// 頂点データの範囲をロックし、頂点バッファのポインタを取得
	g_pVtxBuffPolygonBg2->Lock(0, 0, (void**)&pVtx, 0);	// この書式は変えないこと

	// テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(g_nPatternAnimBg2*-0.996f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(g_nPatternAnimBg2*-0.996f + 0.996f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(g_nPatternAnimBg2*-0.996f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(g_nPatternAnimBg2*-0.996f + 0.996f, 1.0f);

	// 頂点データをアンロックする
	g_pVtxBuffPolygonBg2->Unlock();
}

//****************************************************************
// 描画処理
//****************************************************************
void DrawBg2(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	// 頂点バッファをデバイスのデータストリームにバインド
	pDevice->SetStreamSource(0, g_pVtxBuffPolygonBg2, 0, sizeof(VERTEX_2D));
	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);
	// テクスチャの設定
	pDevice->SetTexture(0, g_pTexturePolygonBg2);
	// ポリゴンの描画
	pDevice->DrawPrimitive(
		D3DPT_TRIANGLESTRIP,			// プリミティブの種類
		0,
		NUM_POLYGON);				// プリミティブの数
}