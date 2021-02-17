//================================================================
//
// パーティクル処理 [particle.h]
// Author : Suzuki Mahiro
//
//================================================================
#ifndef _PARTICLE_H_
#define _PARTICLE_H_

//****************************************************************
//インクルードファイル
//****************************************************************
#include "scene2d.h"

//****************************************************************
//マクロ定義
//****************************************************************
#define PARTICLE_NONE (2)	//通常量
#define PARTICLE_MAX (12)	//最大量

//****************************************************************
//クラス定義
//****************************************************************
class CParticle :public CScene2D
{
public:
	CParticle();
	~CParticle();
	static CParticle *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move);
	static void Create(D3DXVECTOR3 pos, int nNum);
	static HRESULT Load(void);
	static void Unload(void);
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 move);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;	//テクスチャのポインタ
	D3DXVECTOR3 m_move;						//移動量
	float m_fGravity;						//重力
};

#endif