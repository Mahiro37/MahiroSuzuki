//=============================================================================
//
// オブジェクト処理 [scene2d.h]
// Author : Suzuki Mahiro
//
//=============================================================================
#ifndef _SCENE2D_H_
#define _SCENE2D_H_

//*****************************************************************************
//ヘッダファイルのインクルード
//*****************************************************************************
#include "scene.h"

//*****************************************************************************
//構造体定義
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;	// 頂点座標
	float rhw;			// 座標
	D3DCOLOR col;		// 頂点カラー
	D3DXVECTOR2 tex;	// テクスチャ座標
}VERTEX_2D;

//*****************************************************************************
//クラス定義
//*****************************************************************************
class CScene2D :public CScene
{
public:
	//アニメーション条件の列挙型
	typedef enum
	{
		ANIMATION_REPEAT = 0,	//リピートする
		ANIMATION_UNREPEAT		//リピートしない
	}ANIMATION;

	//テクスチャを反転するかの列挙型
	typedef enum
	{
		NOT_INVERSION = 0,	//通常
		INVERSION			//左右反転
	}TEX;

	//回転の向きの列挙型
	typedef enum
	{
		ROTATION_RIGHT = 0,	//右回転
		ROTATION_LEFT		//左回転
	}ROTATION;

	//当たり判定の種類の列挙型
	typedef enum
	{
		RECTANGLE_AND_RECTANGLE = 0,	//矩形と矩形
		CIRCULAR_AND_CIRCULAR,			//円形と円形
		RECTANGLE_AND_CIRCLE,			//矩形と円形
	}COLLISION;

	CScene2D();
	virtual ~CScene2D();
	virtual HRESULT Init(void);
	virtual void Uninit(void);
	virtual void Update(void);
	virtual void Draw(void);

	void InitAnimation(float fCounterAnim, float fPatternAnim, float fLineAnim);
	void UpdateAnimation(ANIMATION AnimConditions, TEX texType);
	void Rotation(D3DXVECTOR3 pos, D3DXVECTOR3 size, ROTATION rotation);
	void SetSize(D3DXVECTOR3 size);
	void SetPos(D3DXVECTOR3 pos);
	void SetColor(D3DXCOLOR color);
	void BindTexture(LPDIRECT3DTEXTURE9 pTexture);	

	D3DXVECTOR3 GetPos(void);
	D3DXVECTOR3 GetSize(void);
	float GetRadian(void);
	TEX GetTexType(void);

private:
	D3DXVECTOR3 m_pos;						//位置
	D3DXVECTOR3 m_size;						//サイズ
	D3DXCOLOR m_color;						//色
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		//バッファのポインタ
	LPDIRECT3DTEXTURE9 m_pTexture;			//テクスチャのポインタ
	static LPDIRECT3DDEVICE9 m_pDevice;		//デバイスのポインタ
	int m_nCounterAnim;						//アニメーションの速さカウント
	int m_nPatternAnim;						//アニメーションの行数カウント
	int m_nCounterLine;						//アニメーションの列数カウント
	float m_fAnimationSpeed;				//アニメーションの速さ
	float m_fAnimationPattern;				//アニメーションの行数
	float m_fAnimationLine;					//アニメーションの列数
	float m_fRadian;						//角度
	TEX m_TexType;							//テクスチャの反転状態
};

#endif