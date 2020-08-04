#include "stdafx.h"
#include "Back.h"
#include "Car.h"

CBack::CBack()
{
}


CBack::~CBack()
{
	Release();
}

HRESULT CBack::Initialize(void)
{
	LoadTile(L"../Data/Map.dat");
	

	m_iTileRenderX = WINCX / TILESIZEX + 1;
	m_iTileRenderY = WINCY / (TILESIZEY / 2) + 1;

	m_eLayer = RENDER_BACK;

	return S_OK;
}

int CBack::Progress(void)
{
	D3DXVECTOR3	vMouse = GetMouse();

	// 클리어 조건이 만족하지 않은 경우
	if (CObjMgr::GetInstance()->GetClaerContion())
	{
		CObj* pCar = CObjMgr::GetInstance()->FindObj(OBJ_ACTIVE, L"CAR");

		// Car가 Player의 주소값을 가지고 있지 않을 경우
		/*if (nullptr != dynamic_cast<CCar*>(pCar)->GetTargetInfo())
		{
			if (WINCX / 2 < pCar->GetInfo()->vPos.x - pCar->GetScroll().x)
			{
				m_vScroll.x += CScrollMgr::GetInstance()->GetScrollX() * GET_TIME;
			}
			
			if (WINCY / 2 < pCar->GetInfo()->vPos.y - pCar->GetScroll().y)
			{
				m_vScroll.y += CScrollMgr::GetInstance()->GetScrollY() * GET_TIME;
			}
		}*/
		if (nullptr != dynamic_cast<CCar*>(pCar)->GetTargetInfo())
		{
			if ((WINCX / 2) > pCar->GetInfo()->vPos.x + m_vScroll.x &&  -5 > m_vScroll.x)
			{
				m_vScroll.x += pCar->GetSpeed() * GET_TIME;
			}

			if ((WINCX / 2)  <  pCar->GetInfo()->vPos.x + m_vScroll.x && WINCX - (WINCY / 4) > -(m_vScroll.x))
			{
				m_vScroll.x -= pCar->GetSpeed() * GET_TIME;
			}

			if ((WINCY / 2) >  pCar->GetInfo()->vPos.y + m_vScroll.y && 0 > m_vScroll.y)
			{
				m_vScroll.y += pCar->GetSpeed() * GET_TIME;
			}

			if ((WINCY / 2) <  pCar->GetInfo()->vPos.y + m_vScroll.y && WINCY * 3 > -(m_vScroll.y))
			{
				m_vScroll.y -= pCar->GetSpeed() * GET_TIME;
			}
		}
		else
		{
			// 좌
			if (0 > vMouse.x && -5 > m_vScroll.x)
			{
				m_vScroll.x += 300.f * GET_TIME;
			}

			// 우
			// 800 + 400 + 200 = 1400 < mouse.x 
			// 오른쪽 오프셋 550
			if (WINCX - 10 < vMouse.x && WINCX - (WINCY / 4) > -(m_vScroll.x))
			{
				m_vScroll.x -= 300.f * GET_TIME;
			}

			// 상
			if (0 > vMouse.y && 0 > m_vScroll.y)
			{
				m_vScroll.y += 300.f * GET_TIME;
			}

			// 하
			// 1800 + 400 < mouse.y
			// 아래쪽 오프셋 1800
			if (WINCY - 50 < vMouse.y && WINCY * 3 > -(m_vScroll.y))
			{
				m_vScroll.y -= 300.f * GET_TIME;
			}
		}
	}
	else
	{
		// 좌
		if (0 > vMouse.x && -5 > m_vScroll.x)
		{
			m_vScroll.x += 300.f * GET_TIME;
		}

		// 우
		// 800 + 400 + 200 = 1400 < mouse.x 
		// 오른쪽 오프셋 550
		if (WINCX - 10 < vMouse.x && WINCX - (WINCY / 4) > -(m_vScroll.x))
		{
			m_vScroll.x -= 300.f * GET_TIME;
		}

		// 상
		if (0 > vMouse.y && 0 > m_vScroll.y)
		{
			m_vScroll.y += 300.f * GET_TIME;
		}

		// 하
		// 1800 + 400 < mouse.y
		// 아래쪽 오프셋 1800
		if (WINCY - 50 < vMouse.y && WINCY * 3 > -(m_vScroll.y))
		{
			m_vScroll.y -= 300.f * GET_TIME;
		}
	}

	return 0;
}

void CBack::Render(HDC hDC)
{
	D3DXMATRIX	matTrans, matTrans2;

	D3DXMatrixTranslation(&matTrans,
		m_vScroll.x, m_vScroll.y, 0.f);

	CDevice::GetInstance()->GetSprite()->SetTransform(&matTrans);

	const TEXINFO* pTextureMgr = CTextureMgr::GetInstance()->GetTexture(L"STAGE0");

	if (nullptr == pTextureMgr)
		return;

	CDevice::GetInstance()->GetSprite()->Draw(pTextureMgr->pTexture,
		NULL,
		NULL,
		NULL,
		D3DCOLOR_ARGB(255, 255, 255, 255));

	if (KEY_PRESSING('A'))
	{
		for (int i = 0; i < m_iTileRenderY; ++i)
		{
			for (int j = 0; j < m_iTileRenderX; ++j)
			{
				int		iCullX = int(-m_vScroll.x) / TILESIZEX;
				int		iCullY = int(-m_vScroll.y * 2) / TILESIZEY;

				int	iIndex = (i + iCullY) * TILEX + (j + iCullX);

				if (iIndex < 0 || iIndex >= TILEX * TILEY)
					continue;

				const TEXINFO*		pTexture = CTextureMgr::GetInstance()->
					GetTexture(L"TILE", L"Tile", m_vecTile[iIndex]->byDrawID);

				if (nullptr == pTexture)
					break;

				D3DXMatrixTranslation(&matTrans,
					m_vecTile[iIndex]->vPos.x + m_vScroll.x,	// 0인 경우 x값 스크롤
					m_vecTile[iIndex]->vPos.y + m_vScroll.y,
					0.f);

				CDevice::GetInstance()->GetSprite()->SetTransform(&matTrans);

				CDevice::GetInstance()->GetSprite()->Draw(pTexture->pTexture,
					NULL,
					&D3DXVECTOR3(25.f, 25.f, 0.f),
					NULL,
					D3DCOLOR_ARGB(255, 255, 255, 255));
			}
		}
	}

}

void CBack::Release(void)
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

void CBack::LoadTile(const wstring & wstrPath)
{
	HANDLE hFile = CreateFile(wstrPath.c_str(), GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	DWORD	dwByte = 0;

	while (true)
	{
		TILE*	pTile = new TILE;

		ReadFile(hFile, pTile, sizeof(TILE), &dwByte, NULL);

		if (0 == dwByte)
		{
			Safe_Delete(pTile);
			break;
		}
		m_vecTile.push_back(pTile);
	}

	CloseHandle(hFile);
}
