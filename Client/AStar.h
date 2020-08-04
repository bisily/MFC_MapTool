#pragma once

#include "Include.h"

class CAStar
{
	DECLARE_SINGLETON(CAStar)

public:
	void			AStarStart(const int& iStartIndex, const int& iGoalIndex);
	void			Release();
	void			MakeRoute();
	NODE*			MakeNode(int iIndex, NODE* pParent, const vector<TILE*>* pTile);
	void			AStarStartPos(const D3DXVECTOR3& vStartPos, const D3DXVECTOR3& vGoalPos);
	list<int>*		GetBestList() { return &m_BestList; }
	MOVEDIR			GetDir() { return m_eDir; }
	void			SetDir(MOVEDIR eDir) { m_eDir = eDir; }
	list<MOVEDIR>*		GetDirctionList() { return &m_Dirction; }

private:
	static  bool Compare(const NODE* pTemp, const NODE* pDest);
	bool	CheckList(const int& iIndex);
	bool	Picking(const D3DXVECTOR3& vPos, const TILE* pTile);
	int		GetTileIndex(const D3DXVECTOR3& vPos);

private:
	CAStar();
	~CAStar();

private:
	list<NODE*>			m_OpenList;
	list<NODE*>			m_CloseList;
	list<int>			m_BestList;
	list<MOVEDIR>		m_Dirction;

	MOVEDIR				m_eDir = MOVE_IDLE;
	int					m_iStartIndex = 0;
	int					m_iGoalIndex = 0;
};

