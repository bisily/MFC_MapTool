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
	LPDIRECT3DTEXTURE9		pTexture;		// com ��ü
	D3DXIMAGE_INFO			tImgInfo;		// ���� �̹��� ������ �����صα� ���� ��ü

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
	D3DXVECTOR3	vCenter;	// ���� �߽�
	float		fRadius;	// ���� ������
	bool		bIsPicked;	// ������ �ƴ���, �ȵƴ��� �˻�

	tagSpher()
		: vCenter(0, 0, 0)
		, fRadius(0.f)
		, bIsPicked(false)
	{}

}SPHER;
