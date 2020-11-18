//================================================
//3Dゲーム制作
//Author:鈴木聖大
//================================================
#include "main.h"
#include "light.h"

//================================================
//グローバル変数
//================================================
D3DLIGHT9 g_light;//ライト情報

//================================================
//初期化処理
//================================================
void InitLight(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DXVECTOR3 vecDir;//ライト方向ベクトル
	D3DMATERIAL9 material;

	//ライトをクリアする
	ZeroMemory(&g_light, sizeof(D3DLIGHT9));
	ZeroMemory(&material, sizeof(D3DMATERIAL9));

	material.Ambient.r = 1.0f;
	material.Ambient.g = 1.0f;
	material.Ambient.b = 1.0f;
	material.Ambient.a = 1.0f;

	pDevice->SetMaterial(&material);
	pDevice->SetRenderState(D3DRS_AMBIENT, 0x44444444);

	//ライトの種類を設定
	g_light.Type = D3DLIGHT_DIRECTIONAL;

	//ライトの拡散光を設定
	g_light.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//ライトの方向を設定
	vecDir = D3DXVECTOR3(0.0f, -0.9f, -1.1f);
	D3DXVec3Normalize(&vecDir, &vecDir);//正規化する(大きさ1のベクトルにする必要がある)
	g_light.Direction = vecDir;

	//ライトを設定する
	pDevice->SetLight(0, &g_light);

	//ライトを有効にする
	pDevice->LightEnable(0, TRUE);
}