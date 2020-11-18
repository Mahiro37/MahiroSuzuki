//================================================
//3Dゲーム制作
//Author:鈴木聖大
//================================================
#include "main.h"
#include "player.h"
#include "camera.h"
#include "input.h"
#include "shadow.h"
#include "bullet.h"
#include "wallblock.h"
#include "game.h"
#include "controller.h"
#include "damageblock.h"
#include "collision.h"
#include "enemy.h"
#include "barrier.h"

//================================================
//グローバル変数
//================================================
LPD3DXMESH g_pMeshPlayer = NULL;		//メッシュ情報へのポインタ
LPD3DXBUFFER g_pBuffMatPlayer = NULL;	//マテリアル情報へのポインタ
DWORD g_nNumMatPlayer = 0;				//マテリアル情報の数
Player g_aPlayer;						//自機の情報
D3DXMATRIX g_mtxWorldPlayer;			//ワールドマトリックス
int g_Index;
int g_nCntBulletPulse;					//連射の間隔
bool isGameOver;						//ゲームオーバーの判定
int g_nCntTime;

//================================================
//初期化処理
//================================================
void InitPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//Xファイルの読み込み
	D3DXLoadMeshFromX("Xファイル/player.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_pBuffMatPlayer, NULL, &g_nNumMatPlayer, &g_pMeshPlayer);

	g_aPlayer.pos = D3DXVECTOR3(0.0f, 0.4f, -30.0f);//初期位置
	g_aPlayer.posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_aPlayer.rot = D3DXVECTOR3(0, 0, 0);//初期向き
	isGameOver = false;
	g_nCntBulletPulse = 0;
	g_nCntTime = 0;

	for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
	{
		g_aPlayer.bUse = true;
		g_aPlayer.nLife = 3;
	}

	g_Index = SetShadow(g_aPlayer.pos + D3DXVECTOR3(0.0f, 0.0f, 0.0f), g_aPlayer.rot);
}

//================================================
//終了処理
//================================================
void UninitPlayer(void)
{
	//メッシュの破棄
	if (g_pMeshPlayer != NULL)
	{
		g_pMeshPlayer->Release();
		g_pMeshPlayer = NULL;
	}

	//マテリアルの破棄
	if (g_pBuffMatPlayer != NULL)
	{
		g_pBuffMatPlayer->Release();
		g_pBuffMatPlayer = NULL;
	}
}

//================================================
//更新処理
//================================================
void UpdatePlayer(void)
{
	float PlayerSpeed = 1.5f;//モデルの移動スピード

	for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
	{
		if (g_aPlayer.bUse == true)
		{
			//カメラ情報を取得する
			Camera*camera = GetCamera();

			//1F前の位置を記憶
			g_aPlayer.posOld = g_aPlayer.pos;
			//g_aPlayer.rotDest = g_aPlayer.rot;

			//コントローラーの情報を取得
			DIJOYSTATE2 Controller = GetController();

			if (Controller.lY != 0 || Controller.lX != 0)
			{
				float fAngle = atan2(Controller.lX, Controller.lY*-1.0f);//スティックの角度を求める、移動する方向の角度

				//スティックによるキャラの移動
				g_aPlayer.pos.x += sinf((camera->rot.y + fAngle)) * PlayerSpeed;
				g_aPlayer.pos.z += cosf((camera->rot.y + fAngle)) * PlayerSpeed;
			}

			if (Controller.lRz != 0 || Controller.lZ != 0)
			{
				float fPlayerAngle = atan2(Controller.lZ*-1.0f, Controller.lRz);//スティックの角度を求める、プレイヤーの角度

				//スティックによるキャラの向き変更
				g_aPlayer.rot.y = camera->rot.y + fPlayerAngle + D3DXToRadian(180);
			}

			////前後左右にモデルを移動させる
			//if (GetKeyboardPress(DIK_UP) || Controller.lY < 0)
			//{
			//	g_aPlayer.pos.x += sinf(D3DXToRadian(camera->rot.y))*PlayerSpeed;
			//	g_aPlayer.pos.z += cosf(D3DXToRadian(camera->rot.y))*PlayerSpeed;
			//}
			//if (GetKeyboardPress(DIK_DOWN) || Controller.lY > 0)
			//{
			//	g_aPlayer.pos.x -= sinf(D3DXToRadian(camera->rot.y))*PlayerSpeed;
			//	g_aPlayer.pos.z -= cosf(D3DXToRadian(camera->rot.y))*PlayerSpeed;
			//}
			//if (GetKeyboardPress(DIK_RIGHT) || Controller.lX > 0)
			//{
			//	g_aPlayer.pos.x += sinf(D3DXToRadian(camera->rot.y + 90))*PlayerSpeed;
			//	g_aPlayer.pos.z += cosf(D3DXToRadian(camera->rot.y + 90))*PlayerSpeed;

			//}
			//if (GetKeyboardPress(DIK_LEFT) || Controller.lX < 0)
			//{
			//	g_aPlayer.pos.x += sinf(D3DXToRadian(camera->rot.y - 90))*PlayerSpeed;
			//	g_aPlayer.pos.z += cosf(D3DXToRadian(camera->rot.y - 90))*PlayerSpeed;
			//}

			//前後左右にモデルを向かせる
			/*if (GetKeyboardPress(DIK_I) || Controller.lRz < 0)
			{
				g_aPlayer.rotDest.y = (g_aPlayer.rot.y);
			}
			if (GetKeyboardPress(DIK_K) || Controller.lRz > 0)
			{
				g_aPlayer.rotDest.y = (g_aPlayer.rot.y + D3DXToRadian(180));
			}
			if (GetKeyboardPress(DIK_L) || Controller.lZ > 0)
			{
				g_aPlayer.rotDest.y = (g_aPlayer.rot.y + D3DXToRadian(90));
			}
			if (GetKeyboardPress(DIK_J) || Controller.lZ < 0)
			{
				g_aPlayer.rotDest.y = (g_aPlayer.rot.y + D3DXToRadian(270));
			}*/

			//g_aPlayer.rot = (g_aPlayer.rotDest - g_aPlayer.rot)*0.2;


			//弾を放出する
			if (GetKeyboardTrigger(DIK_SPACE) || GetJoypadPress(5))
			{
				g_nCntBulletPulse++;

				if (g_nCntBulletPulse == 5)
				{
					SetBullet(D3DXVECTOR3(g_aPlayer.pos.x + sinf((g_aPlayer.rot.y)) * 5, g_aPlayer.pos.y, g_aPlayer.pos.z + cosf((g_aPlayer.rot.y)) * 5), D3DXVECTOR3(BULLET_SIZE, BULLET_SIZE, BULLET_SIZE),
						D3DXVECTOR3(sinf(g_aPlayer.rot.y) * 5, 0.0f, cosf(g_aPlayer.rot.y) * 5), D3DXVECTOR3(D3DXToRadian(90.0f), 0.0f, 0.0f), 75, BULLETTYPE_PLAYER);
					g_nCntBulletPulse = 0;
				}
			}

				//敵の弾に当たった時
				if (CollisionBullet(&g_aPlayer.pos, &g_aPlayer.posOld, D3DXVECTOR3(PLAYER_SIZE_X, PLAYER_SIZE_Y, PLAYER_SIZE_Z), BULLETTYPE_ENEMY1) == true)
				{
					HitPlayer(nCntPlayer, 1);//(誰に対して,何ダメージ与えるか)

				}

				//敵の弾に当たった時
				if (CollisionBullet(&g_aPlayer.pos, &g_aPlayer.posOld, D3DXVECTOR3(PLAYER_SIZE_X, PLAYER_SIZE_Y, PLAYER_SIZE_Z), BULLETTYPE_ENEMY2) == true)
				{
					HitPlayer(nCntPlayer, 1);//(誰に対して,何ダメージ与えるか)
				}
				
				//敵に当たった時
				if (CollisionEnemy(&g_aPlayer.pos, &g_aPlayer.posOld, D3DXVECTOR3(PLAYER_SIZE_X, PLAYER_SIZE_Y, PLAYER_SIZE_Z)) == true)
				{
					HitPlayer(nCntPlayer, 3);//(誰に対して,何ダメージ与えるか)
				}
			}

			for (int nCount = 0; nCount < MAX_BLOCK; nCount++)
			{
				if (RectangleCollision(&g_aPlayer.pos, &g_aPlayer.posOld, D3DXVECTOR3(PLAYER_SIZE_X, PLAYER_SIZE_Y, PLAYER_SIZE_Z),
					&GetBlock()[nCount].pos, GetBlock()[nCount].size) == true)
				{ //ブロックに当たった時
					g_aPlayer.pos = g_aPlayer.posOld;
				}
			}
			//CollisionBlock(&g_aPlayer.pos, &g_aPlayer.posOld, D3DXVECTOR3(PLAYER_SIZE_X, PLAYER_SIZE_Y, PLAYER_SIZE_Z));
			CollisionDamageblock(&g_aPlayer.pos, &g_aPlayer.posOld, D3DXVECTOR3(PLAYER_SIZE_X, PLAYER_SIZE_Y, PLAYER_SIZE_Z));
			CollisionBarrier(&g_aPlayer.pos, &g_aPlayer.posOld, D3DXVECTOR3(PLAYER_SIZE_X+25, PLAYER_SIZE_Y, PLAYER_SIZE_Z+30));

			SetPositionShadow(g_Index, g_aPlayer.pos, g_aPlayer.rot);
	}
}

//================================================
//描画処理
//================================================
void DrawPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();//デバイスのポインタ
	D3DXMATRIX mtxRot, mtxTrans;
	D3DMATERIAL9 matDef;//現在のマテリアル保存用
	D3DXMATERIAL*pMat;//マテリアルデータへのポインタ

	for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
	{
		if (g_aPlayer.bUse == true)
		{
			//ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_mtxWorldPlayer);

			//向きを反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aPlayer.rot.y, g_aPlayer.rot.x, g_aPlayer.rot.z);
			D3DXMatrixMultiply(&g_mtxWorldPlayer, &g_mtxWorldPlayer, &mtxRot);

			//位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_aPlayer.pos.x, g_aPlayer.pos.y, g_aPlayer.pos.z);
			D3DXMatrixMultiply(&g_mtxWorldPlayer, &g_mtxWorldPlayer, &mtxTrans);

			//テクスチャの設定
			pDevice->SetTexture(0, NULL);

			//ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldPlayer);

			//現在のマテリアルを取得する
			pDevice->GetMaterial(&matDef);

			//マテリアルデータへのポインタを取得
			pMat = (D3DXMATERIAL*)g_pBuffMatPlayer->GetBufferPointer();
			for (int nCntMat = 0; nCntMat < (int)g_nNumMatPlayer; nCntMat++)
			{
				//マテリアルの設定
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);
				pMat[nCntMat].MatD3D.Ambient = pMat[nCntMat].MatD3D.Diffuse;

				//モデルパーツの描画
				g_pMeshPlayer->DrawSubset(nCntMat);
			}

			//保持していたマテリアルを戻す
			pDevice->SetMaterial(&matDef);
		}
	}
}

//=====================================================
//敵の取得
//=====================================================
Player*GetPlayer(void)
{
	return&g_aPlayer;
}

//=====================================================
//ダメージ処理
//=====================================================
void HitPlayer(int nCntPlayer, int nDamage)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	g_aPlayer.nLife -= nDamage;//敵の体力を減らす

	if (g_aPlayer.nLife == 2)
	{
		D3DXLoadMeshFromX("Xファイル/Player damage1.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_pBuffMatPlayer, NULL, &g_nNumMatPlayer, &g_pMeshPlayer);
	}

	if (g_aPlayer.nLife == 1)
	{
		D3DXLoadMeshFromX("Xファイル/Player damage2.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_pBuffMatPlayer, NULL, &g_nNumMatPlayer, &g_pMeshPlayer);
	}

	if (g_aPlayer.nLife <= 0)
	{
		g_aPlayer.bUse = false;
		isGameOver = true;
		SetGameState(GAMESTATE_END);

		//SetExplosion(g_aEnemy[nCntEnemy].pos, D3DXCOLOR(1.0f, 0, 0, 0.5f));
	}
}

//=====================================================
// クリア判定処理
//=====================================================
bool IsGameOver()
{
	return isGameOver;
}