#pragma once

#include "Include.h"

class CMfcToolView;
class CBackGround
{
private:
	vector<TILE*>					m_vecTile;
	CMfcToolView*					m_pMainToolView = nullptr;
	vector<D3DXVECTOR2>				m_vecLine;
	vector<D3DXVECTOR2>::iterator	begin;

	/*vector<D3DXVECTOR3>				m_vecLine;
	vector<D3DXVECTOR3>::iterator	begin;*/

	float							m_fTileX;
	float							m_fTileY;
	

public:
	void	SetTestLine(D3DXVECTOR2 vPos) { m_vecLine.push_back(vPos); }
	vector<D3DXVECTOR2>*	GetVectorLine() { return &m_vecLine; }

	void	SetMainView(CMfcToolView* pMainView) { m_pMainToolView = pMainView; }
	vector<TILE*>*	GetvecTile() { return &m_vecTile; }


	void	TileChange(const D3DXVECTOR3& vPos, const BYTE& byDrawID, const int& iTileOpSion);
	int		GetTileIndex(const D3DXVECTOR3& vPos);
	bool	Picking(const D3DXVECTOR3& vPos, const int& iIndex);

	D3DXVECTOR3	GetIndexPos(const D3DXVECTOR3& vPos);

public:
	float		GetTileX() { return m_fTileX; }
	float		GetTileY() { return m_fTileY; }

public:
	HRESULT		Initialize();
	void		BackGroundRender();
	void		MiniViewRender();
	void		Release();


public:
	CBackGround();
	~CBackGround();
};

