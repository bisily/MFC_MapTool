#include "stdafx.h"
#include "AStar.h"
#include "ObjMgr.h"
#include "Back.h"
#include "Player.h"

IMPLEMENT_SINGLETON(CAStar)

CAStar::CAStar()
{
}

CAStar::~CAStar()
{
	Release();
}

void CAStar::AStarStart(const int & iStartIndex, const int & iGoalIndex)
{
	if (iStartIndex == iGoalIndex)
	{
		m_eDir = MOVE_IDLE;
		return;
	}

	if (-1 == iGoalIndex)
	{
		m_eDir = MOVE_IDLE;
		return;
	}

	const vector<TILE*>*		pVecTile = CObjMgr::GetInstance()->GetTile();
	if (nullptr == pVecTile)
		return;

	if (1 == (*pVecTile)[iGoalIndex]->byOption)
	{
		m_eDir = MOVE_IDLE;
		return;
	}

	if (2 == (*pVecTile)[iGoalIndex]->byOption)
	{
		m_eDir = MOVE_IDLE;
		return;
	}

	Release();

	m_iStartIndex = iStartIndex;
	m_iGoalIndex = iGoalIndex;

	MakeRoute();

}

void CAStar::MakeRoute(void)
{
	NODE*	pParent = new NODE;

	pParent->pParent = nullptr;
	pParent->iIndex = m_iStartIndex;
	pParent->fCost = 0.f;

	m_CloseList.push_back(pParent);

	const vector<TILE*>*		pVecTile = CObjMgr::GetInstance()->GetTile();
	if (nullptr == pVecTile)
		return;

	NODE*		pNode = nullptr;
	int			iIndex = 0;


	while (true)
	{
		// 위로 이동
		iIndex = pParent->iIndex - TILEX * 2;

		if (pParent->iIndex >= TILEX * 2 &&
			(*pVecTile)[iIndex]->byOption == 0 &&
			CheckList(iIndex))
		{
			m_eDir = MOVE_U;

			pNode = MakeNode(iIndex, pParent, pVecTile);
			m_OpenList.push_back(pNode);

			m_Dirction.push_back(MOVE_U);

		}

		// 아래로 이동
		iIndex = pParent->iIndex + TILEX * 2;

		if (pParent->iIndex < (TILEX * TILEY) - (TILEX * 2) &&
			(*pVecTile)[iIndex]->byOption == 0 &&
			CheckList(iIndex))
		{
			m_eDir = MOVE_B;

			pNode = MakeNode(iIndex, pParent, pVecTile);
			m_OpenList.push_back(pNode);

			m_Dirction.push_back(MOVE_B);
		}

		// 왼쪽 이동
		iIndex = pParent->iIndex - 1;

		if (pParent->iIndex % TILEX != 0 &&
			(*pVecTile)[iIndex]->byOption == 0 &&
			CheckList(iIndex))
		{
			m_eDir = MOVE_L;

			pNode = MakeNode(iIndex, pParent, pVecTile);
			m_OpenList.push_back(pNode);

			m_Dirction.push_back(MOVE_L);

		}

		// 오른쪽 이동
		iIndex = pParent->iIndex + 1;

		if (pParent->iIndex % TILEX != TILEX - 1 &&
			(*pVecTile)[iIndex]->byOption == 0 &&
			CheckList(iIndex))
		{
			m_eDir = MOVE_R;

			pNode = MakeNode(iIndex, pParent, pVecTile);
			m_OpenList.push_back(pNode);

			m_Dirction.push_back(MOVE_R);
		}

		// 오른쪽 위 이동
		iIndex = pParent->iIndex - (TILEX - (pParent->iIndex / TILEX) % 2);

		if (pParent->iIndex >= TILEX						 &&		// 위 예외처리
			pParent->iIndex % (TILEX * 2) != (TILEX * 2) - 1 &&		// 오른쪽 예외처리
			(*pVecTile)[iIndex]->byOption == 0 &&
			CheckList(iIndex))
		{
			m_eDir = MOVE_RU;

			pNode = MakeNode(iIndex, pParent, pVecTile);
			m_OpenList.push_back(pNode);

			m_Dirction.push_back(MOVE_RU);
		}

		// 오른쪽 아래 이동
		iIndex = pParent->iIndex + (TILEX + (pParent->iIndex / TILEX) % 2);

		if (pParent->iIndex < TILEX * TILEY - TILEX			 &&		// 아래 예외처리
			pParent->iIndex % (TILEX * 2) != (TILEX * 2) - 1 &&		// 오른쪽 예외처리
			(*pVecTile)[iIndex]->byOption == 0 &&
			CheckList(iIndex))
		{
			m_eDir = MOVE_RB;
		
			pNode = MakeNode(iIndex, pParent, pVecTile);
			m_OpenList.push_back(pNode);

			m_Dirction.push_back(MOVE_RB);
		}

		// 왼 아래 이동
		iIndex = pParent->iIndex + (TILEX + (pParent->iIndex / TILEX) % 2) - 1;

		if (pParent->iIndex < TILEX * TILEY - TILEX			 &&		// 아래 예외처리
			pParent->iIndex % (TILEX * 2) != 0 &&					// 왼쪽 예외처리
			(*pVecTile)[iIndex]->byOption == 0 &&
			CheckList(iIndex))
		{
			m_eDir = MOVE_LB;

			pNode = MakeNode(iIndex, pParent, pVecTile);
			m_OpenList.push_back(pNode);

			m_Dirction.push_back(MOVE_LB);
		}

		// 왼 위 이동
		iIndex = pParent->iIndex - (TILEX + (pParent->iIndex / TILEX + 1) % 2);

		if (pParent->iIndex >= TILEX		  &&					// 아래 예외처리
			pParent->iIndex % (TILEX * 2) != 0 &&					// 왼쪽 예외처리
			(*pVecTile)[iIndex]->byOption == 0 &&
			CheckList(iIndex))
		{
			m_eDir = MOVE_LU;

			pNode = MakeNode(iIndex, pParent, pVecTile);
			m_OpenList.push_back(pNode);

			m_Dirction.push_back(MOVE_LU);
		}

		m_OpenList.sort(Compare);

		auto	iter = m_OpenList.begin();
		pParent = *iter;

		m_CloseList.push_back(*iter);
		m_OpenList.erase(iter);

		if (m_iGoalIndex == pParent->iIndex)
		{
			while (true)
			{
				m_BestList.push_back(pParent->iIndex);
				pParent = pParent->pParent;

				if (m_iStartIndex == pParent->iIndex)
					break;
			}
			m_BestList.reverse();
			m_Dirction.reverse();
			break;
		}

	}


}

NODE * CAStar::MakeNode(int iIndex, NODE * pParent, const vector<TILE*>* pTile)
{
	NODE*		pNode = new NODE;

	pNode->iIndex = iIndex;
	pNode->pParent = pParent;

	D3DXVECTOR3		vDistance = (*pTile)[iIndex]->vPos - (*pTile)[pParent->iIndex]->vPos;
	float	fPCost = D3DXVec3Length(&vDistance);

	vDistance = (*pTile)[iIndex]->vPos - (*pTile)[m_iGoalIndex]->vPos;
	float	fGCost = D3DXVec3Length(&vDistance);

	pNode->fCost = fPCost + fGCost;

	return pNode;
}

void CAStar::AStarStartPos(const D3DXVECTOR3 & vStartPos, const D3DXVECTOR3 & vGoalPos)
{
	m_iStartIndex = GetTileIndex(vStartPos);
	m_iGoalIndex = GetTileIndex(vGoalPos);

	 
	AStarStart(m_iStartIndex, m_iGoalIndex);
}

bool CAStar::CheckList(const int & iIndex)
{
	for (auto& i : m_OpenList)
	{
		if (iIndex == i->iIndex)
			return false;
	}

	for (auto& i : m_CloseList)
	{
		if (iIndex == i->iIndex)
			return false;
	}

	return true;
}

bool CAStar::Picking(const D3DXVECTOR3 & vPos, const TILE * pTile)
{
	float		fGradient = (TILESIZEY / 2.f) / (TILESIZEX / 2.f);

	D3DXVECTOR3		vPoint[4] =
	{
		D3DXVECTOR3(pTile->vPos.x, pTile->vPos.y - TILESIZEY / 2.f, 0.f),
		D3DXVECTOR3(pTile->vPos.x + TILESIZEX / 2.f, pTile->vPos.y, 0.f),
		D3DXVECTOR3(pTile->vPos.x, pTile->vPos.y + TILESIZEY / 2.f, 0.f),
		D3DXVECTOR3(pTile->vPos.x - TILESIZEX / 2.f, pTile->vPos.y, 0.f)
	};

	D3DXVECTOR3		vDirection[4] = {

		vPoint[1] - vPoint[0],
		vPoint[2] - vPoint[1],
		vPoint[3] - vPoint[2],
		vPoint[0] - vPoint[3]

	};

	D3DXVECTOR3		vNormal[4] = {

		D3DXVECTOR3(vDirection[0].y, -vDirection[0].x, 0.f),
		D3DXVECTOR3(vDirection[1].y, -vDirection[1].x, 0.f),
		D3DXVECTOR3(vDirection[2].y, -vDirection[2].x, 0.f),
		D3DXVECTOR3(vDirection[3].y, -vDirection[3].x, 0.f)
	};

	for (int i = 0; i < 4; ++i)
		D3DXVec3Normalize(&vNormal[i], &vNormal[i]);

	for (int i = 0; i < 4; ++i)
	{
		D3DXVECTOR3		vDestDir = vPos - vPoint[i];
		D3DXVec3Normalize(&vDestDir, &vDestDir);

		float	fDotResult = D3DXVec3Dot(&vDestDir, &vNormal[i]);

		if (fDotResult > 0.f)
			return false;
	}

	return true;
}

int CAStar::GetTileIndex(const D3DXVECTOR3 & vPos)
{
	const vector<TILE*>*		pVecTile = CObjMgr::GetInstance()->GetTile();

	for (size_t i = 0; i < pVecTile->size(); ++i)
	{
		if (Picking(vPos, (*pVecTile)[i]))
		{
			return i;
		}
	}

	return -1;
}

bool CAStar::Compare(const NODE * pTemp, const NODE * pDest)
{
	return pTemp->fCost < pDest->fCost;
}

void CAStar::Release(void)
{
	for_each(m_OpenList.begin(), m_OpenList.end(), DeleteOBJ());
	m_OpenList.clear();

	for_each(m_CloseList.begin(), m_CloseList.end(), DeleteOBJ());
	m_CloseList.clear();

	m_BestList.clear();
}