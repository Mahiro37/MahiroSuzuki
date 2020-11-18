//=====================================================
//DirectXシューティングゲーム
//Author:鈴木聖大
//=====================================================
#include "main.h"
#include "borderlogo.h"
#include "input.h"
//#include "controller.h"

//=====================================================
// グローバル変数
//=====================================================
LPDIRECT3DTEXTURE9 g_pTexturePolygonBorderlogo = NULL;		// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPolygonBorderlogo = NULL;	// 頂点バッファへのポインタ
BORDERLOGO g_Borderlogo[MAX_BORDERLOGO];

//=============================================================================
// 初期化処理
//=============================================================================
void InitBorderlogo(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "テクスチャ/borderlogo.png", &g_pTexturePolygonBorderlogo);

	// 頂点バッファ生成
	pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D)*NUM_VERTEX,	// バッファサイズ
		D3DUSAGE_WRITEONLY,				// (固定)
		FVF_VERTEX_2D,					// 頂点フォーマット
		D3DPOOL_MANAGED,				// (固定)
		&g_pVtxBuffPolygonBorderlogo,		// 変数名が変わると変更が必要
		NULL);

	// 頂点情報へのポインタ
	VERTEX_2D * pVtx;

	// 頂点データの範囲をロックし、頂点バッファのポインタを取得
	g_pVtxBuffPolygonBorderlogo->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3((SCREEN_WIDTH / 2) - (BORDERLOGO_SIZE_X / 2), (SCREEN_HEIGHT / 2) - (BORDERLOGO_SIZE_Y / 2), 0.0f);
	pVtx[1].pos = D3DXVECTOR3((SCREEN_WIDTH / 2) + (BORDERLOGO_SIZE_X / 2), (SCREEN_HEIGHT / 2) - (BORDERLOGO_SIZE_Y / 2), 0.0f);
	pVtx[2].pos = D3DXVECTOR3((SCREEN_WIDTH / 2) - (BORDERLOGO_SIZE_X / 2), (SCREEN_HEIGHT / 2) + (BORDERLOGO_SIZE_Y / 2), 0.0f);
	pVtx[3].pos = D3DXVECTOR3((SCREEN_WIDTH / 2) + (BORDERLOGO_SIZE_X / 2), (SCREEN_HEIGHT / 2) + (BORDERLOGO_SIZE_Y / 2), 0.0f);

	// rhwの設定(値は1.0で固定)
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// 頂点カラーの設定
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 190);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 190);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 190);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 190);

	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// 頂点データをアンロックする
	g_pVtxBuffPolygonBorderlogo->Unlock();
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitBorderlogo(void)
{
	// テクスチャの開放
	if (g_pTexturePolygonBorderlogo != NULL)
	{
		g_pTexturePolygonBorderlogo->Release();
		g_pTexturePolygonBorderlogo = NULL;
	}

	// 頂点バッファの開放
	if (g_pVtxBuffPolygonBorderlogo != NULL)
	{
		g_pVtxBuffPolygonBorderlogo->Release();
		g_pVtxBuffPolygonBorderlogo = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateBorderlogo(void)
{
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawBorderlogo(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点バッファをデバイスのデータストリームにバインド
	pDevice->SetStreamSource(0, g_pVtxBuffPolygonBorderlogo, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_pTexturePolygonBorderlogo);

	// ポリゴンの描画
	pDevice->DrawPrimitive(
		D3DPT_TRIANGLESTRIP,		// プリミティブの種類
		0,
		NUM_POLYGON);				// プリミティブの数
}

//=============================================================================
// エフェクトの設定
//=============================================================================
void SetBorderlogo(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	int nCntBlock;				// ローカル変数

	for (nCntBlock = 0; nCntBlock < MAX_BORDERLOGO; nCntBlock++)
	{
		// ブロックが使われてないとき
		if (g_Borderlogo[nCntBlock].bUse == false)
		{
			g_Borderlogo[nCntBlock].pos = pos;
			g_Borderlogo[nCntBlock].size = size;
			g_Borderlogo[nCntBlock].bUse = true;
			break;
		}
	}
}