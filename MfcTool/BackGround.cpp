#include "stdafx.h"
#include "BackGround.h"
#include "MfcToolView.h"

CBackGround::CBackGround()
{
}


CBackGround::~CBackGround()
{
	Release();
}

void CBackGround::TileChange(const D3DXVECTOR3 & vPos, const BYTE & byDrawID, const int & iTileOpSion)
{
	int		iIndex = GetTileIndex(vPos);

	if (-1 == iIndex)
		return;

	m_vecTile[iIndex]->byDrawID = byDrawID;
	m_vecTile[iIndex]->byOption = iTileOpSion;
}

int CBackGround::GetTileIndex(const D3DXVECTOR3 & vPos)
{
	for (size_t i = 0; i < m_vecTile.size(); ++i)
	{
		if (Picking(vPos, i))
		{
			return i;
		}
	}

	return -1;
}

bool CBackGround::Picking(const D3DXVECTOR3 & vPos, const int & iIndex)
{
	float		fGradient = (TILESIZEY / 2.f) / (TILESIZEX / 2.f);

	D3DXVECTOR3		vPoint[4] =
	{
		D3DXVECTOR3(m_vecTile[iIndex]->vPos.x, m_vecTile[iIndex]->vPos.y - TILESIZEY / 2.f, 0.f),
		D3DXVECTOR3(m_vecTile[iIndex]->vPos.x + TILESIZEX / 2.f, m_vecTile[iIndex]->vPos.y, 0.f),
		D3DXVECTOR3(m_vecTile[iIndex]->vPos.x, m_vecTile[iIndex]->vPos.y + TILESIZEY / 2.f, 0.f),
		D3DXVECTOR3(m_vecTile[iIndex]->vPos.x - TILESIZEX / 2.f, m_vecTile[iIndex]->vPos.y, 0.f)
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

D3DXVECTOR3 CBackGround::GetIndexPos(const D3DXVECTOR3& vPos)
{
	for (size_t i = 0; i < m_vecTile.size(); ++i)
	{
		if (Picking(vPos, i))
		{
			return D3DXVECTOR3(m_vecTile[i]->vPos.x, m_vecTile[i]->vPos.y, 0.f);
		}
	}

	return D3DXVECTOR3{-1.f, -1.f, 0.f};
}

HRESULT CBackGround::Initialize()
{
	m_vecTile.reserve(TILEX * TILEY);

	for (int i = 0; i < TILEY; ++i)
	{
		for (int j = 0; j < TILEX; ++j)
		{
			TILE*		pTile = new TILE;

			float	fX = j * TILESIZEX + ((i % 2) * (TILESIZEX / 2.f));
			float	fY = i * (TILESIZEY / 2.f);

			pTile->vPos = D3DXVECTOR3(fX, fY, 0.f);
			pTile->vSize = D3DXVECTOR3(float(TILESIZEX), float(TILESIZEY), 0.f);
			pTile->byOption = 0;
			pTile->byDrawID = 0;

			m_vecTile.push_back(pTile);
		}
	}

	return S_OK;
}

void CBackGround::BackGroundRender()
{
	D3DXMATRIX	matTrans, matTrans2, matTrans3;

	D3DXMatrixTranslation(&matTrans,
		float(-m_pMainToolView->GetScrollPos(0)),
		float(-m_pMainToolView->GetScrollPos(1)),
		0.f);

	CDevice::GetInstance()->GetSprite()->SetTransform(&matTrans);
	
	CDevice::GetInstance()->GetSprite()->Draw(CToolTextureMgr::GetInstance()->GetTexture(L"STAGE")->pTexture,
		NULL,
		NULL,
		NULL,
		D3DCOLOR_ARGB(255, 255, 255, 255));

	for (int i = 0; i < TILEY; ++i)
	{
		for (int j = 0; j < TILEX; ++j)
		{
			int	iIndex = i * TILEX + j;

			const TEXINFO*		pTexture = CToolTextureMgr::GetInstance()->
				GetTexture(L"TILE", L"Tile", m_vecTile[iIndex]->byDrawID);

			if (nullptr == pTexture)
				break;

			D3DXMatrixTranslation(&matTrans2,
				m_vecTile[iIndex]->vPos.x - m_pMainToolView->GetScrollPos(0),	// 0인 경우 x값 스크롤
				m_vecTile[iIndex]->vPos.y - m_pMainToolView->GetScrollPos(1),
				0.f);

			CDevice::GetInstance()->GetSprite()->SetTransform(&matTrans2);

			CDevice::GetInstance()->GetSprite()->Draw(pTexture->pTexture,
				NULL,
				&D3DXVECTOR3(25.f, 25.f, 0.f),
				NULL,
				D3DCOLOR_ARGB(255, 255, 255, 255));
		}
	}

}

void CBackGround::MiniViewRender()
{
	D3DXMATRIX	matWorld, matScale, matTrans;

	D3DXMatrixScaling(&matScale, 0.3f, 0.3f, 0.f);

	CDevice::GetInstance()->GetSprite()->SetTransform(&matScale);

	CDevice::GetInstance()->GetSprite()->Draw(CToolTextureMgr::GetInstance()->GetTexture(L"STAGE")->pTexture,
		NULL,
		NULL,
		NULL,
		D3DCOLOR_ARGB(255, 255, 255, 255));


	for (int i = 0; i < TILEY; ++i)
	{
		for (int j = 0; j < TILEX; ++j)
		{
			int	iIndex = i * TILEX + j;

			const TEXINFO*		pTexture = CToolTextureMgr::GetInstance()->
				GetTexture(L"TILE", L"Tile", m_vecTile[iIndex]->byDrawID);

			if (nullptr == pTexture)
				break;

			D3DXMatrixScaling(&matScale, 0.3f, 0.3f, 0.f);
			D3DXMatrixTranslation(&matTrans,
				m_vecTile[iIndex]->vPos.x * 0.3f,	// 0인 경우 x값 스크롤
				m_vecTile[iIndex]->vPos.y * 0.3f,
				0.f);

			matWorld = matScale * matTrans;

			CDevice::GetInstance()->GetSprite()->SetTransform(&matWorld);
			CDevice::GetInstance()->GetSprite()->Draw(pTexture->pTexture,
				NULL,
				&D3DXVECTOR3(65.f, 34.f, 0.f),
				NULL,
				D3DCOLOR_ARGB(255, 255, 255, 255));
		}
	}

}

void CBackGround::Release()
{
	for_each(
		m_vecTile.begin(),
		m_vecTile.end(),
		[](TILE*& Temp)
	{
		if (nullptr != Temp)
		{
			delete Temp;
			Temp = nullptr;
		}
	});
	m_vecTile.clear();
	vector<TILE*>().swap(m_vecTile);
}
