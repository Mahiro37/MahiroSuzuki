//=====================================================
//DirectXシューティングゲーム
//Author:鈴木聖大
//=====================================================
#include "enemy.h"
#include "main.h"
#include "explosion.h"
#include "bullet.h"

//=====================================================
//グローバル変数宣言
//=====================================================
LPDIRECT3DTEXTURE9 g_apTextureEnemy[MAX_TYPE_ENEMY] = {};	//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEnemy = NULL;				//頂点バッファへのポインタ
ENEMY g_aEnemy[MAX_ENEMY];									//敵の情報
int g_nDeleteCounter = 0;									//倒した敵の数
int g_nResultCounter = 0;									//リザルトに遷移するまでの時間

//=====================================================
//初期化処理
//=====================================================
void InitEnemy(void)
{
	int nCntEnemy;
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//敵の情報を初期化
	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		g_aEnemy[nCntEnemy].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEnemy[nCntEnemy].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEnemy[nCntEnemy].nType = 0;
		g_aEnemy[nCntEnemy].bUse = false;
		g_aEnemy[nCntEnemy].nLife = 0;
		g_aEnemy[nCntEnemy].nCounterState = 0;
		g_aEnemy[nCntEnemy].nCounterBullet = 0;
	}
	g_nDeleteCounter = 0;

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "Textures/enemy01.png",&g_apTextureEnemy[0]);

	// 頂点バッファ生成
	pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D)*NUM_VERTEX*MAX_ENEMY,	// バッファサイズ
		D3DUSAGE_WRITEONLY,				// (固定)
		FVF_VERTEX_2D,					// 頂点フォーマット
		D3DPOOL_MANAGED,				// (固定)
		&g_pVtxBuffEnemy,				// 変数名が変わると変更が必要
		NULL);

	VERTEX_2D * pVtx;		// 頂点情報へのポインタ

	// 頂点データの範囲をロックし、頂点バッファのポインタを取得
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);	// この書式は変えないこと

	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].bUse == false)//敵が未使用なら
		{
			// 頂点座標の設定( Zの形に配置する)  / 四角形の頂点の位置
			pVtx[0].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - (MAX_ENEMY_SIZE / 2), g_aEnemy[nCntEnemy].pos.y - (MAX_ENEMY_SIZE / 2), 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + (MAX_ENEMY_SIZE / 2), g_aEnemy[nCntEnemy].pos.y - (MAX_ENEMY_SIZE / 2), 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - (MAX_ENEMY_SIZE / 2), g_aEnemy[nCntEnemy].pos.y + (MAX_ENEMY_SIZE / 2), 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + (MAX_ENEMY_SIZE / 2), g_aEnemy[nCntEnemy].pos.y + (MAX_ENEMY_SIZE / 2), 0.0f);

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

			pVtx += 4;
		}
	}
	// 頂点データをアンロックする
	g_pVtxBuffEnemy->Unlock();

}

//=====================================================
//終了処理
//=====================================================
void UninitEnemy(void)
{
	// テクスチャの開放
	for (int nCntTex = 0; nCntTex < MAX_TYPE_ENEMY; nCntTex++)
	{
		if (g_apTextureEnemy[nCntTex] != NULL)
		{
			g_apTextureEnemy[nCntTex]->Release();
			g_apTextureEnemy[nCntTex] = NULL;
		}
	}

	// 頂点バッファの開放
	if (g_pVtxBuffEnemy != NULL)
	{
		g_pVtxBuffEnemy->Release();
		g_pVtxBuffEnemy = NULL;
	}
}

//=====================================================
// 更新処理
//=====================================================
void UpdateEnemy(void)
{
	VERTEX_2D * pVtx;		// 頂点情報へのポインタ

	// 頂点データの範囲をロック
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].bUse == true)//敵が使用中なら
		{
			g_aEnemy[nCntEnemy].pos += g_aEnemy[nCntEnemy].move;

			if (g_aEnemy[nCntEnemy].pos.x - (MAX_ENEMY_SIZE / 2) <= 0.0f)
			{
				g_aEnemy[nCntEnemy].move.x = 10.0f;
			}
			else if (g_aEnemy[nCntEnemy].pos.x + (MAX_ENEMY_SIZE / 2) >= SCREEN_WIDTH)
			{
				g_aEnemy[nCntEnemy].move.x = -10.0f;
			}

			// 頂点座標の設定( Zの形に配置する)
			pVtx[0].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - (MAX_ENEMY_SIZE / 2), g_aEnemy[nCntEnemy].pos.y - (MAX_ENEMY_SIZE / 2), 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + (MAX_ENEMY_SIZE / 2), g_aEnemy[nCntEnemy].pos.y - (MAX_ENEMY_SIZE / 2), 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - (MAX_ENEMY_SIZE / 2), g_aEnemy[nCntEnemy].pos.y + (MAX_ENEMY_SIZE / 2), 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + (MAX_ENEMY_SIZE / 2), g_aEnemy[nCntEnemy].pos.y + (MAX_ENEMY_SIZE / 2), 0.0f);

			g_aEnemy[nCntEnemy].nCounterBullet++;

			if (g_aEnemy[nCntEnemy].nCounterBullet == 50)
			{
				SetBullet(D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x, g_aEnemy[nCntEnemy].pos.y + (MAX_ENEMY_SIZE / 2), 0.0f), D3DXVECTOR3(-5.0f, 10.0f, 0.0f), BULLETTYPE_ENEMY, D3DXCOLOR(255, 0, 1, 255));
				SetBullet(D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x, g_aEnemy[nCntEnemy].pos.y + (MAX_ENEMY_SIZE / 2), 0.0f), D3DXVECTOR3(5.0f, 10.0f, 0.0f), BULLETTYPE_ENEMY, D3DXCOLOR(255, 0, 1, 255));
				g_aEnemy[nCntEnemy].nCounterBullet = 0;
			}

			switch (g_aEnemy[nCntEnemy].state)
			{
			case ENEMYSTATE_DAMAGE:

				// 頂点カラーの設定
				pVtx[0].col = D3DCOLOR_RGBA(255, 0, 0, 255);
				pVtx[1].col = D3DCOLOR_RGBA(255, 0, 0, 255);
				pVtx[2].col = D3DCOLOR_RGBA(255, 0, 0, 255);
				pVtx[3].col = D3DCOLOR_RGBA(255, 0, 0, 255);

				//int nDamageFinish = 100;

				g_aEnemy[nCntEnemy].nCounterState++;

				if (g_aEnemy[nCntEnemy].nCounterState == 10)
				{
					g_aEnemy[nCntEnemy].state = ENEMYSTATE_NOMAL;
					g_aEnemy[nCntEnemy].nCounterState = 0;
				}

				break;

			case ENEMYSTATE_NOMAL:

				// 頂点カラーの設定
				pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

				break;
			}
		
		}

		pVtx += 4;
	}

	// 頂点データをアンロック
	g_pVtxBuffEnemy->Unlock();
}

//=====================================================
// 描画処理
//=====================================================
void DrawEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	
	int nCntEnemy;

	// 頂点バッファをデバイスのデータストリームにバインド
	pDevice->SetStreamSource(0, g_pVtxBuffEnemy, 0, sizeof(VERTEX_2D));
	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);
	
	// ポリゴンの描画
	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].bUse == true)//敵が使用中なら描画
		{
			//テクスチャの設定
			pDevice->SetTexture(0, g_apTextureEnemy[g_aEnemy[nCntEnemy].nType]);

			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntEnemy*4 , NUM_POLYGON);
		}
	}
}

//=====================================================
//敵の取得
//=====================================================
ENEMY*GetEnemy(void)
{
	return&g_aEnemy[0];
}

//=====================================================
//敵の設定
//=====================================================
void SetEnemy(D3DXVECTOR3 pos, D3DXVECTOR3 move, int nType, int nLife)
{
	VERTEX_2D * pVtx;		// 頂点情報へのポインタ

	int nCntEnemy;

	// 頂点データの範囲をロックし、頂点バッファのポインタを取得
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);	// この書式は変えないこと

	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].bUse == false)
		{
			g_aEnemy[nCntEnemy].pos = pos;
			g_aEnemy[nCntEnemy].move = move;
			g_aEnemy[nCntEnemy].nType = nType;
			g_aEnemy[nCntEnemy].bUse = true;
			g_aEnemy[nCntEnemy].nLife = nLife;

			// 頂点座標の設定( Zの形に配置する)  / 四角形の頂点の位置
			pVtx[0].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - (MAX_ENEMY_SIZE / 2), g_aEnemy[nCntEnemy].pos.y - (MAX_ENEMY_SIZE / 2), 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + (MAX_ENEMY_SIZE / 2), g_aEnemy[nCntEnemy].pos.y - (MAX_ENEMY_SIZE / 2), 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - (MAX_ENEMY_SIZE / 2), g_aEnemy[nCntEnemy].pos.y + (MAX_ENEMY_SIZE / 2), 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + (MAX_ENEMY_SIZE / 2), g_aEnemy[nCntEnemy].pos.y + (MAX_ENEMY_SIZE / 2), 0.0f);
			
			break;
		}

		pVtx += 4;
	}

	// 頂点データをアンロックする
	g_pVtxBuffEnemy->Unlock();
}

//=====================================================
//ダメージ処理
//=====================================================
void HitEnemy(int nCntEnemy, int nDamage)
{
	VERTEX_2D*pVtx;//頂点情報のポインタ

	// 頂点データの範囲をロック
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	g_aEnemy[nCntEnemy].nLife -= nDamage;//敵の体力を減らす

	if (g_aEnemy[nCntEnemy].nLife <= 0)
	{
		g_aEnemy[nCntEnemy].bUse = false;

		//爆発生成
		SetExplosion(g_aEnemy[nCntEnemy].pos, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

		g_nDeleteCounter++;

		if (g_nDeleteCounter == MAX_ENEMY)
		{
			g_nDeleteCounter = 0;

			while (1)
			{
				g_nResultCounter++;

				if (g_nResultCounter == 10000)
				{
					SetMode(MODE_RESULT);

					break;
				}
			}
		}
	}
	else
	{
		//ダメージ状態へ
		g_aEnemy[nCntEnemy].state = ENEMYSTATE_DAMAGE;
	}

	// 頂点データをアンロック
	g_pVtxBuffEnemy->Unlock();
}