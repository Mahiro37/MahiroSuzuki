//================================================================
//
// エフェクト処理 [effect.h]
// Author : Suzuki Mahiro
//
//================================================================
#ifndef _EFFECT_H_
#define _EFFECT_H_

//****************************************************************
//インクルードファイル
//****************************************************************
#include "scene2d.h"
#include "sound.h"

//****************************************************************
//クラス定義
//****************************************************************
class CEffect :public CScene2D
{
public:
	//エフェクトのタイプ
	typedef enum
	{
		EFFECT_TYPE_NONE = 0,
		EFFECT_TYPE_GET_SCORE,			//スコア加算のアイテム取得
		EFFECT_TYPE_GET_SPEED_UP,		//スピードアップのアイテム取得
		EFFECT_TYPE_GET_TWIN_BULLET,	//ツイン弾のアイテム取得
		EFFECT_TYPE_GET_BARRIER,		//バリアのアイテム取得
		EFFECT_TYPE_BARRIER,			//バリア
		EFFECT_TYPE_CHARGE_SHOT,		//チャージショット
		EFFECT_TYPE_MAX
	}EFFECT_TYPE;

	CEffect();
	~CEffect();
	static CEffect *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, float fEffectSpeed, EFFECT_TYPE EffectType, ANIMATION Animation,CSound::SOUND_LABEL SoundLabel);
	static HRESULT Load(void);
	static void Unload(void);
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, float fEffectSpeed, EFFECT_TYPE EffectType, ANIMATION Animation);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetAnimation(ANIMATION Animation);

private:
	static LPDIRECT3DTEXTURE9 m_pTexture[EFFECT_TYPE_MAX];	//テクスチャのポインタ配列
	EFFECT_TYPE m_EffectType;								//エフェクトタイプ
	ANIMATION m_Animation;									//アニメーションをループするか
	D3DXVECTOR3 m_pos;										//位置
	D3DXVECTOR3 m_size;										//サイズ
	D3DXVECTOR3 m_SetSize;									//チャージショットエフェクトのサイズ変更用
	D3DXCOLOR m_color;										//色
	int m_nLifeCounter;										//チャージショットエフェクトのカウント
};

#endif