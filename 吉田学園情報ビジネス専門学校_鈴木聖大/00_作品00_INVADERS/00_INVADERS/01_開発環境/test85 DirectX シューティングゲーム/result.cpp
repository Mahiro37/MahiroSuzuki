//=====================================================
//DirectXシューティングゲーム
//Author:鈴木聖大
//=====================================================
#include "main.h"
#include "Result.h"
#include "input.h"
#include "player.h"

//=====================================================
// グローバル変数
//=====================================================
//VERTEX_2D g_aVertex[NUM_VERTEX];						// 頂点情報格納
LPDIRECT3DTEXTURE9 g_pTexturePolygonResult = NULL;		// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPolygonResult = NULL;	// 頂点バッファへのポインタ

//=============================================================================
// 初期化処理
//=============================================================================
void InitResult(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	PLAYER *pPlayer = GetPlayer();

	// テクスチャの読み込み
	if (pPlayer->bUse == true)
	{
		D3DXCreateTextureFromFile(pDevice, "Textures/gameclear.png", &g_pTexturePolygonResult);
	}
	else
	{
		D3DXCreateTextureFromFile(pDevice, "Textures/gameover.png", &g_pTexturePolygonResult);
	}

	// 頂点バッファ生成
	pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D)*NUM_VERTEX,	// バッファサイズ
		D3DUSAGE_WRITEONLY,				// (固定)
		FVF_VERTEX_2D,					// 頂点フォーマット
		D3DPOOL_MANAGED,				// (固定)
		&g_pVtxBuffPolygonResult,		// 変数名が変わると変更が必要
		NULL);

	VERTEX_2D * pVtx;

	// 頂点データの範囲をロック
	g_pVtxBuffPolygonResult->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(1280.0f, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, 720.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(1280.0f, 720.0f, 0.0f);

	// rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// 頂点カラーの設定
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	// テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// 頂点データをアンロック
	g_pVtxBuffPolygonResult->Unlock();
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitResult(void)
{
	// テクスチャの開放
	if (g_pTexturePolygonResult != NULL)
	{
		g_pTexturePolygonResult->Release();
		g_pTexturePolygonResult = NULL;
	}
	// 頂点バッファの開放
	if (g_pVtxBuffPolygonResult != NULL)
	{
		g_pVtxBuffPolygonResult->Release();
		g_pVtxBuffPolygonResult = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateResult(void)
{
	if (GetKeyboardTrigger(DIK_RETURN))
	{
		SetMode(MODE_TITLE);
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawResult(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点バッファをデバイスのデータストリームにバインド
	pDevice->SetStreamSource(0, g_pVtxBuffPolygonResult, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_pTexturePolygonResult);

	// ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);
}