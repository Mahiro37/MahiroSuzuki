//================================================
//3Dゲーム制作
//Author:鈴木聖大
//================================================
#include "main.h"
#include "camera.h"
#include "input.h"
#include "player.h"

//================================================
//グローバル変数
//================================================
Camera g_camera;//カメラ情報

//================================================
//初期化処理
//================================================
void InitCamera(void)
{
	//カメラの位置・注視点・上方向を設定する
	g_camera.posV = D3DXVECTOR3(0.0f, 450.0f, -140.0f);
	g_camera.posR = D3DXVECTOR3(0.0f, 0.0f, -20.0f);
	g_camera.vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	//g_camera.rot.y = 0;
}

//================================================
//終了処理
//================================================
void UninitCamera(void)
{
}

//================================================
//更新処理
//================================================
void UpdateCamera(void)
{
	Player*pPlayer = GetPlayer();

	int CameraSpeed = 2.0f;//カメラの移動スピード

	g_camera.fDistance = sqrtf(powf(g_camera.posV.x - g_camera.posR.x, 2) + powf(g_camera.posV.z - g_camera.posR.z, 2));

	////注視点をモデルが向いている方向へ移動する
	//g_camera.posRDest = D3DXVECTOR3(pPlayer->pos.x + sinf(pPlayer->rot.y)*CAMERA_MOVE, pPlayer->pos.y, pPlayer->pos.z + 30.0f + cosf(pPlayer->rot.y)*CAMERA_MOVE);
	//g_camera.posVDest = D3DXVECTOR3(pPlayer->pos.x - sinf(D3DXToRadian(g_camera.rot.y))*g_camera.fDistance, pPlayer->pos.y + 100.0f, pPlayer->pos.z - 80.0f - cosf(D3DXToRadian(g_camera.rot.y)*g_camera.fDistance));
	//g_camera.posR += (g_camera.posRDest - g_camera.posR)*CAMERA_COEFFICIENT;//複数フレームで反映
	//g_camera.posV += (g_camera.posVDest - g_camera.posV)*CAMERA_COEFFICIENT;//複数フレームで反映
	
	//注視点の旋回
	//右回転
	//if (GetKeyboardPress(DIK_E))
	//{
	//	g_camera.rot.y += 2.0f;
	//	g_camera.posR.x = g_camera.posV.x + sinf(D3DXToRadian(g_camera.rot.y))*g_camera.fDistance;
	//	g_camera.posR.z = g_camera.posV.z + cosf(D3DXToRadian(g_camera.rot.y))*g_camera.fDistance;
	//}
	////左回転
	//if (GetKeyboardPress(DIK_Q))
	//{
	//	g_camera.rot.y -= 2.0f;
	//	g_camera.posR.x = g_camera.posV.x + sinf(D3DXToRadian(g_camera.rot.y))*g_camera.fDistance;
	//	g_camera.posR.z = g_camera.posV.z + cosf(D3DXToRadian(g_camera.rot.y))*g_camera.fDistance;
	//}

	////視点(カメラ視点)の移動
	////前移動
	//if (GetKeyboardPress(DIK_W))
	//{
	//	g_camera.posV.x += sinf(D3DXToRadian(g_camera.rot.y))*CameraSpeed;
	//	g_camera.posV.z += cosf(D3DXToRadian(g_camera.rot.y))*CameraSpeed;
	//	g_camera.posR.x = g_camera.posV.x + sinf(D3DXToRadian(g_camera.rot.y))*g_camera.fDistance;
	//	g_camera.posR.z = g_camera.posV.z + cosf(D3DXToRadian(g_camera.rot.y))*g_camera.fDistance;
	//}
	////後ろ移動
	//if (GetKeyboardPress(DIK_S))
	//{
	//	g_camera.posV.x -= sinf(D3DXToRadian(g_camera.rot.y))*CameraSpeed;
	//	g_camera.posV.z -= cosf(D3DXToRadian(g_camera.rot.y))*CameraSpeed;
	//	g_camera.posR.x = g_camera.posV.x + sinf(D3DXToRadian(g_camera.rot.y))*g_camera.fDistance;
	//	g_camera.posR.z = g_camera.posV.z + cosf(D3DXToRadian(g_camera.rot.y))*g_camera.fDistance;
	//}
	////右移動
	//if (GetKeyboardPress(DIK_D))
	//{
	//	g_camera.posV.x += sinf(D3DXToRadian(g_camera.rot.y + 90))*CameraSpeed;
	//	g_camera.posV.z += cosf(D3DXToRadian(g_camera.rot.y + 90))*CameraSpeed;
	//	g_camera.posR.x = g_camera.posV.x + sinf(D3DXToRadian(g_camera.rot.y))*g_camera.fDistance;
	//	g_camera.posR.z = g_camera.posV.z + cosf(D3DXToRadian(g_camera.rot.y))*g_camera.fDistance;
	//}
	////左移動
	//if (GetKeyboardPress(DIK_A))
	//{
	//	g_camera.posV.x += sinf(D3DXToRadian(g_camera.rot.y - 90))*CameraSpeed;
	//	g_camera.posV.z += cosf(D3DXToRadian(g_camera.rot.y - 90))*CameraSpeed;
	//	g_camera.posR.x = g_camera.posV.x + sinf(D3DXToRadian(g_camera.rot.y))*g_camera.fDistance;
	//	g_camera.posR.z = g_camera.posV.z + cosf(D3DXToRadian(g_camera.rot.y))*g_camera.fDistance;
	//}
	////上移動
	//if (GetKeyboardPress(DIK_R))
	//{
	//	g_camera.posV.y++;
	//}
	////下移動
	//if (GetKeyboardPress(DIK_F))
	//{
	//	g_camera.posV.y--;
	//}
}

//================================================
//設定処理
//================================================
void SetCamera(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();//デバイスのポインタ

	//ビューマトリックスの初期化
	D3DXMatrixIdentity(&g_camera.mtxView);

	//ビューマトリックスの作成
	D3DXMatrixLookAtLH(&g_camera.mtxView,
		&g_camera.posV,
		&g_camera.posR,
		&g_camera.vecU);

	//ビューマトリックスの設定
	pDevice->SetTransform(D3DTS_VIEW, &g_camera.mtxView);

	//プロジェクションマトリックスの初期化
	D3DXMatrixIdentity(&g_camera.mtxProjection);

	//プロジェクションマトリックスの作成
	D3DXMatrixPerspectiveFovLH(&g_camera.mtxProjection,
		D3DXToRadian(45.0f),
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,
		10.0f,
		550.0f);

	//プロジェクションマトリックスの設定
	pDevice->SetTransform(D3DTS_PROJECTION,
		&g_camera.mtxProjection);
}

Camera*GetCamera()
{
	return&g_camera;
}