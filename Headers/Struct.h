#pragma once

typedef struct tagInfo
{
	D3DXVECTOR3  vPos;
	D3DXVECTOR3  vDir;
	D3DXVECTOR3  vLook;

	D3DXMATRIX   matWorld;
}INFO;

typedef struct tagTexture
{
	LPDIRECT3DTEXTURE9		pTexture;		// com 객체
	D3DXIMAGE_INFO			tImgInfo;		// 실제 이미지 정보를 저장해두기 위한 객체

}TEXINFO;

typedef struct tagTile
{
	D3DXVECTOR3			vPos;
	D3DXVECTOR3			vSize;

	BYTE				byOption;
	BYTE				byDrawID;

}TILE;

typedef struct tagUnitData
{
	std::wstring			wstrName;
	int						iHp;
	int						iAttack;

}UNITDATA;

typedef struct tagTexturePath
{
	std::wstring		wstrObjKey;
	std::wstring		wstrStateKey;
	std::wstring		wstrPath;
	int					iCount;

	tagTexturePath()
		: wstrObjKey(L"")
		, wstrStateKey(L"")
		, wstrPath(L"")
		, iCount(0)
	{

	}
}IMGPATH;

typedef struct tagFrame
{
	float	fFrame;
	float	fCount;
	float	fMax;

	tagFrame() {}
	tagFrame(
	float	_fFrame,
	float	_fCount,
	float	_fMax)
		: fFrame(_fFrame), fCount(_fCount), fMax(_fMax)
	{
	}

}FRAME;

typedef struct tagAStarNode
{
	int				iIndex;
	float			fCost;
	//MOVEDIR			m_eDirction;
	tagAStarNode*	pParent;

}NODE;

typedef struct tagData
{
	int a = 0;
}DATA;


typedef struct tagSpher
{
	D3DXVECTOR3	vCenter;	// 구의 중심
	float		fRadius;	// 구의 반지름
	bool		bIsPicked;	// 선택이 됐는지, 안됐는지 검사

	tagSpher()
		: vCenter(0, 0, 0)
		, fRadius(0.f)
		, bIsPicked(false)
	{}

}SPHER;
