//================================================
//3Dゲーム制作
//Author:鈴木聖大
//================================================
#include "main.h"
#include "enemy.h"
#include "camera.h"
#include "input.h"
#include "shadow.h"
#include "bullet.h"
#include "game.h"
#include "effect.h"
#include "collision.h"

//=====================================================
//マクロ定義
//=====================================================
#define VALUE_MOVE (10.0f)//ポリゴンの横移動の速さ

//================================================
//グローバル変数
//================================================
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEnemy = NULL;		//頂点バッファへのポインタ
LPD3DXMESH g_pMeshEnemy = NULL;						//メッシュ情報へのポインタ
LPD3DXBUFFER g_pBuffMatEnemy = NULL;				//マテリアル情報へのポインタ
DWORD g_nNumMatEnemy = 0;							//マテリアル情報の数
D3DXMATRIX g_mtxWorldEnemy;							//ワールドマトリックス
Enemy g_apEnemy[MAX_ENEMY];							//敵の情報
int g_IndexEnemy = 0;
bool isGameClear;									//ゲームクリアの判定
bool isZakoDown;									//雑魚敵の全滅判定

//================================================
//初期化処理
//================================================
void InitEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//Xファイルの読み込み
	D3DXLoadMeshFromX("Xファイル/Enemy.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_pBuffMatEnemy, NULL, &g_nNumMatEnemy, &g_pMeshEnemy);

	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		g_apEnemy[nCntEnemy].bUse = false;
		g_apEnemy[nCntEnemy].isDown = false;
		g_apEnemy[nCntEnemy].nLife = 10;						//敵の体力
		g_apEnemy[nCntEnemy].pos = D3DXVECTOR3(0, 0, 0);		//初期位置
		g_apEnemy[nCntEnemy].posOld = D3DXVECTOR3(0, 0, 0);
		g_apEnemy[nCntEnemy].rot = D3DXVECTOR3(0, 0, 0);		//初期向き
		g_IndexEnemy = SetShadow(g_apEnemy[nCntEnemy].pos + D3DXVECTOR3(0.0f, 0.0f, 0.0f), g_apEnemy[nCntEnemy].rot);
		g_apEnemy[nCntEnemy].nCntBillboardEnemy = 0;
	}

	isGameClear = false;
	isZakoDown = false;
}

//================================================
//終了処理
//================================================
void UninitEnemy(void)
{
	//メッシュの破棄
	if (g_pMeshEnemy != NULL)
	{
		g_pMeshEnemy->Release();
		g_pMeshEnemy = NULL;
	}

	//マテリアルの破棄
	if (g_pBuffMatEnemy != NULL)
	{
		g_pBuffMatEnemy->Release();
		g_pBuffMatEnemy = NULL;
	}
}

//================================================
//更新処理
//================================================
void UpdateEnemy(void)
{
	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_apEnemy[nCntEnemy].bUse == true)
		{
			g_apEnemy[nCntEnemy].nCntBillboardEnemy++;

			//1F前の位置を記憶
			g_apEnemy[nCntEnemy].posOld = g_apEnemy[nCntEnemy].pos;

			if (g_apEnemy[nCntEnemy].nCntBillboardEnemy == 120)
			{
				SetBullet(D3DXVECTOR3(g_apEnemy[nCntEnemy].pos.x, g_apEnemy[nCntEnemy].pos.y, g_apEnemy[nCntEnemy].pos.z - 10), D3DXVECTOR3(BULLET_SIZE, BULLET_SIZE, BULLET_SIZE),
					D3DXVECTOR3(2.5f, 0.0f, 0.0f), D3DXVECTOR3(D3DXToRadian(90.0f), 0.0f, 0.0f), 75, BULLETTYPE_ENEMY1);
				SetBullet(D3DXVECTOR3(g_apEnemy[nCntEnemy].pos.x, g_apEnemy[nCntEnemy].pos.y, g_apEnemy[nCntEnemy].pos.z - 10), D3DXVECTOR3(BULLET_SIZE, BULLET_SIZE, BULLET_SIZE),
					D3DXVECTOR3(1.5f, 0.0f, 1.5f), D3DXVECTOR3(D3DXToRadian(90.0f), 0.0f, 0.0f), 75, BULLETTYPE_ENEMY2);
				SetBullet(D3DXVECTOR3(g_apEnemy[nCntEnemy].pos.x, g_apEnemy[nCntEnemy].pos.y, g_apEnemy[nCntEnemy].pos.z - 10), D3DXVECTOR3(BULLET_SIZE, BULLET_SIZE, BULLET_SIZE),
					D3DXVECTOR3(0.0f, 0.0f, 2.5f), D3DXVECTOR3(D3DXToRadian(90.0f), 0.0f, 0.0f), 75, BULLETTYPE_ENEMY1);
				SetBullet(D3DXVECTOR3(g_apEnemy[nCntEnemy].pos.x, g_apEnemy[nCntEnemy].pos.y, g_apEnemy[nCntEnemy].pos.z - 10), D3DXVECTOR3(BULLET_SIZE, BULLET_SIZE, BULLET_SIZE),
					D3DXVECTOR3(1.5f, 0.0f, -1.5f), D3DXVECTOR3(D3DXToRadian(90.0f), 0.0f, 0.0f), 75, BULLETTYPE_ENEMY2);
				SetBullet(D3DXVECTOR3(g_apEnemy[nCntEnemy].pos.x, g_apEnemy[nCntEnemy].pos.y, g_apEnemy[nCntEnemy].pos.z - 10), D3DXVECTOR3(BULLET_SIZE, BULLET_SIZE, BULLET_SIZE),
					D3DXVECTOR3(0.0f, 0.0f, -2.5f), D3DXVECTOR3(D3DXToRadian(90.0f), 0.0f, 0.0f), 75, BULLETTYPE_ENEMY1);
				SetBullet(D3DXVECTOR3(g_apEnemy[nCntEnemy].pos.x, g_apEnemy[nCntEnemy].pos.y, g_apEnemy[nCntEnemy].pos.z - 10), D3DXVECTOR3(BULLET_SIZE, BULLET_SIZE, BULLET_SIZE),
					D3DXVECTOR3(-1.5f, 0.0f, -1.5f), D3DXVECTOR3(D3DXToRadian(90.0f), 0.0f, 0.0f), 75, BULLETTYPE_ENEMY2);
				SetBullet(D3DXVECTOR3(g_apEnemy[nCntEnemy].pos.x, g_apEnemy[nCntEnemy].pos.y, g_apEnemy[nCntEnemy].pos.z - 10), D3DXVECTOR3(BULLET_SIZE, BULLET_SIZE, BULLET_SIZE),
					D3DXVECTOR3(-2.5f, 0.0f, 0.0f), D3DXVECTOR3(D3DXToRadian(90.0f), 0.0f, 0.0f), 75, BULLETTYPE_ENEMY1);
				SetBullet(D3DXVECTOR3(g_apEnemy[nCntEnemy].pos.x, g_apEnemy[nCntEnemy].pos.y, g_apEnemy[nCntEnemy].pos.z - 10), D3DXVECTOR3(BULLET_SIZE, BULLET_SIZE, BULLET_SIZE),
					D3DXVECTOR3(-1.5f, 0.0f, 1.5f), D3DXVECTOR3(D3DXToRadian(90.0f), 0.0f, 0.0f), 75, BULLETTYPE_ENEMY2);

				g_apEnemy[nCntEnemy].nCntBillboardEnemy = 0;
			}

			for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
			{
				if (g_apEnemy[nCntEnemy].isDown == false)
				{
					//プレイヤーの弾に当たった時
					if (CollisionBullet(&g_apEnemy[nCntEnemy].pos, &g_apEnemy[nCntEnemy].posOld, D3DXVECTOR3(ENEMY_SIZE, ENEMY_SIZE, ENEMY_SIZE), BULLETTYPE_PLAYER) == true)
					{
						HitEnemy(nCntEnemy, 1);//(誰に対して,何ダメージ与えるか)
					}
				}
			}
		}
	}
}

//================================================
//描画処理
//================================================
void DrawEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();//デバイスのポインタ
	D3DXMATRIX mtxRot, mtxTrans;
	D3DMATERIAL9 matDef;//現在のマテリアル保存用
	D3DXMATERIAL*pMat;//マテリアルデータへのポインタ

	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_apEnemy[nCntEnemy].bUse == true)
		{
			//ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_mtxWorldEnemy);

			//向きを反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_apEnemy[nCntEnemy].rot.y, g_apEnemy[nCntEnemy].rot.x, g_apEnemy[nCntEnemy].rot.z);
			D3DXMatrixMultiply(&g_mtxWorldEnemy, &g_mtxWorldEnemy, &mtxRot);

			//位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_apEnemy[nCntEnemy].pos.x, g_apEnemy[nCntEnemy].pos.y, g_apEnemy[nCntEnemy].pos.z);
			D3DXMatrixMultiply(&g_mtxWorldEnemy, &g_mtxWorldEnemy, &mtxTrans);

			//テクスチャの設定
			pDevice->SetTexture(0, NULL);

			//ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldEnemy);

			//現在のマテリアルを取得する
			pDevice->GetMaterial(&matDef);

			//マテリアルデータへのポインタを取得
			pMat = (D3DXMATERIAL*)g_pBuffMatEnemy->GetBufferPointer();
			for (int nCntMat = 0; nCntMat < (int)g_nNumMatEnemy; nCntMat++)
			{
				//マテリアルの設定
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);
				pMat[nCntMat].MatD3D.Ambient = pMat[nCntMat].MatD3D.Diffuse;

				//モデルパーツの描画
				g_pMeshEnemy->DrawSubset(nCntMat);
			}

			//保持していたマテリアルを戻す
			pDevice->SetMaterial(&matDef);
		}
	}
}

//=====================================================
//敵の取得
//=====================================================
Enemy*GetEnemy(void)
{
	int nCntEnemy;

	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		return&g_apEnemy[nCntEnemy];
	}
	return&g_apEnemy[nCntEnemy];
}

//=====================================================
//設定処理
//=====================================================
void SetEnemy(D3DXVECTOR3 pos, int nType, int number)
{
	for (number = 0; number < MAX_ENEMY; number++)
	{
		if (g_apEnemy[number].bUse == false)
		{
			g_apEnemy[number].pos = pos;
			g_apEnemy[number].nType = nType;
			g_apEnemy[number].bUse = true;

			break;
		}
	}
}

//=====================================================
//ダメージ処理
//=====================================================
void HitEnemy(int nCntEnemy, int nDamage)
{
	int Count = 0;

	g_apEnemy[nCntEnemy].nLife -= nDamage;//敵の体力を減らす

	if (g_apEnemy[nCntEnemy].nLife <= 0)
	{
 		g_apEnemy[nCntEnemy].bUse = false;
		g_apEnemy[nCntEnemy].isDown = true;
	}
	else
	{
	}

	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_apEnemy[nCntEnemy].bUse == false)
		{
			Count++;
			if (Count >= 8)
			{
				isZakoDown = true;
			}
		}

		if (isZakoDown == true)
		{
			if (Count == 9)
			{
				isGameClear = true;
				SetGameState(GAMESTATE_END);
			}
		}

	}
}

//=====================================================
// クリア判定処理
//=====================================================
bool IsGameClear()
{
	return isGameClear;
}

//=====================================================
// 雑魚的全滅判定処理
//=====================================================
bool IsZakoDown()
{
	return isZakoDown;
}


//=====================================================
// ブロックに横からあたったときの設定
//=====================================================
bool CollisionEnemy(D3DXVECTOR3* pPos, D3DXVECTOR3* pPosOld, D3DXVECTOR3 size)
{
	int nCntEnemy;					// ローカル変数
	bool isHit = false;

	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		// ブロックが使われたら
		if (g_apEnemy[nCntEnemy].bUse == true)
		{
			//当たり判定を計算
			if (WallCollision(pPos, pPosOld, size, &g_apEnemy[nCntEnemy].pos, g_apEnemy[nCntEnemy].size) == true)
			{
				isHit = true;
			}
		}
	}
	return isHit;
}