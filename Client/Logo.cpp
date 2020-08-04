#include "stdafx.h"
#include "Logo.h"
#include "SceneMgr.h"

CLogo::CLogo()
{
}


CLogo::~CLogo()
{
	Release();
}

unsigned int __stdcall ImgLoadThreadFunc(void* pArg)
{
	CLogo*			pLogo = (CLogo*)pArg;

	EnterCriticalSection(&pLogo->GetCrt());

	if (FAILED(CObjMgr::GetInstance()->Initialize()))
	{
		ERR_MSG(L"Client Object Load Failed");
		return E_FAIL;
	}

	///////////////////////////////////////////////////////////////////////////////
	////////////////////////////	Object	/////////////////////////////////////// 

	// Box
	if (FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Map/Struct/Box/Box_%d.png", L"BOX", TEX_MULTI, L"Box", 3)))
	{
		return E_FAIL;
	}

	// Building
	if (FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Map/Struct/Building/Building_%d.png", L"BUILDING", TEX_MULTI, L"Building", 8)))
	{
		return E_FAIL;
	}

	// Stone
	if (FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Map/Struct/Stone/Stone_%d.png", L"STONE", TEX_MULTI, L"Stone", 4)))
	{
		return E_FAIL;
	}

	// Tree
	if (FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Map/Struct/Tree/Tree_%d.png", L"TREE", TEX_MULTI, L"Tree", 2)))
	{
		return E_FAIL;
	}

	if (FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Map/Tile/Tile%d.png", L"TILE", TEX_MULTI, L"Tile", 3)))
	{
		return E_FAIL;
	}

	if (FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/InterFace/View.png", L"VIEW", TEX_SINGLE)))
	{
		return E_FAIL;
	}

	if (FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Cursor/Cursor.png", L"CURSOR", TEX_MULTI, L"Cursor", 1)))
	{
		return E_FAIL;
	}

	if (FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Activeobject/Drum/Drum_%d.png", L"DRUM", TEX_MULTI, L"Drum", 1)))
	{
		return E_FAIL;
	}

	// Generator
	if (FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Activeobject/Generator/Generator_%d.png", L"GENERATOR", TEX_MULTI, L"Generator", 2)))
	{
		return E_FAIL;
	}

	if (FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Map/Stage0.png", L"STAGE0", TEX_SINGLE,
		L"Stage0")))
	{
		ERR_MSG(L"Client Stage Map Load Failed");
		return E_FAIL;
	}

	if (FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Ending/Ending.png", L"ENDING", TEX_SINGLE,
		L"Ending")))
	{
		ERR_MSG(L"Client Ending Load Failed");
		return E_FAIL;
	}

	if (FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Item/GunCursor.png", L"GUN", TEX_SINGLE)))
	{
		ERR_MSG(L"GUN Image Load Failed");
		return E_FAIL;
	}

	if (FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Item/KnifeCursor.png", L"KNIFE", TEX_SINGLE)))
	{
		ERR_MSG(L"KNIFE Image Load Failed");
		return E_FAIL;
	}

	if (FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Hand/Hand_%d.png", L"HAND", TEX_MULTI, L"Hand", 2)))
	{
		ERR_MSG(L"HAND Image Load Failed");
		return E_FAIL;
	}

	// Car
	if (FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/ActiveObject/CarU/CarU.png", L"CAR", TEX_MULTI, L"CarU", 1)))
	{
		ERR_MSG(L"CAR Image Load Failed");
		return E_FAIL;
	}

	if (FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/ActiveObject/CarRU/CarRU.png", L"CAR", TEX_MULTI, L"CarRU", 1)))
	{
		ERR_MSG(L"CAR Image Load Failed");
		return E_FAIL;
	}

	if (FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/ActiveObject/CarR/CarR.png", L"CAR", TEX_MULTI, L"CarR", 1)))
	{
		ERR_MSG(L"CAR Image Load Failed");
		return E_FAIL;
	}

	if (FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/ActiveObject/CarRB/CarRB.png", L"CAR", TEX_MULTI, L"CarRB", 1)))
	{
		ERR_MSG(L"CAR Image Load Failed");
		return E_FAIL;
	}

	if (FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/ActiveObject/CarB/CarB.png", L"CAR", TEX_MULTI, L"CarB", 1)))
	{
		ERR_MSG(L"CAR Image Load Failed");
		return E_FAIL;
	}

	// 보트
	if (FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/ActiveObject/BoatU/BoatU_%d.png", L"BOAT", TEX_MULTI, L"BoatU", 1)))
	{
		ERR_MSG(L"BOAT Image Load Failed");
		return E_FAIL;
	}

	if (FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/ActiveObject/BoatLU/BoatLU_%d.png", L"BOAT", TEX_MULTI, L"BoatLU", 1)))
	{
		ERR_MSG(L"BOAT Image Load Failed");
		return E_FAIL;
	}

	if (FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/ActiveObject/BoatL/BoatL_%d.png", L"BOAT", TEX_MULTI, L"BoatL", 1)))
	{
		ERR_MSG(L"BOAT Image Load Failed");
		return E_FAIL;
	}

	if (FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/ActiveObject/BoatLB/BoatLB_%d.png", L"BOAT", TEX_MULTI, L"BoatLB", 1)))
	{
		ERR_MSG(L"BOAT Image Load Failed");
		return E_FAIL;
	}

	if (FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/ActiveObject/BoatB/BoatB_%d.png", L"BOAT", TEX_MULTI, L"BoatB", 1)))
	{
		ERR_MSG(L"BOAT Image Load Failed");
		return E_FAIL;
	}

	if (FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/ActiveObject/BoatRB/BoatRB_%d.png", L"BOAT", TEX_MULTI, L"BoatRB", 1)))
	{
		ERR_MSG(L"BOAT Image Load Failed");
		return E_FAIL;
	}

	if (FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/ActiveObject/BoatR/BoatR_%d.png", L"BOAT", TEX_MULTI, L"BoatR", 1)))
	{
		ERR_MSG(L"BOAT Image Load Failed");
		return E_FAIL;
	}

	if (FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/ActiveObject/BoatRU/BoatRU_%d.png", L"BOAT", TEX_MULTI, L"BoatRU", 1)))
	{
		ERR_MSG(L"BOAT Image Load Failed");
		return E_FAIL;
	}

	if (FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Item/SniperRifle_%d.png", L"SNIPERRIFLE", TEX_MULTI, L"SniperRifle", 1)))
	{
		ERR_MSG(L"SNIPERRIFLE Image Load Failed");
		return E_FAIL;
	}

	if (FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Take/Take_%d.png", L"TAKE", TEX_MULTI, L"Take", 2)))
	{
		ERR_MSG(L"TAKE Image Load Failed");
		return E_FAIL;
	}
	
	if (FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Sniping/Sniping_%d.png", L"SNIPING", TEX_MULTI, L"Sniping", 1)))
	{
		ERR_MSG(L"SNIPING Image Load Failed");
		return E_FAIL;
	}

	///////////////////////////////////////////////////////////////////////////////
	////////////////////////////	Effect	/////////////////////////////////////// 

	if (FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/EFFECT/Explosion/Explosion_%d.png", L"EFFECT", TEX_MULTI, L"Explosion", 10)))
	{
		return E_FAIL;
	}

	if (FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/EFFECT/Shoot/Shoot_%d.png", L"EFFECT", TEX_MULTI, L"Shoot", 5)))
	{
		return E_FAIL;
	}

	if (FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/EFFECT/Bomb/Bomb_%d.png", L"EFFECT", TEX_MULTI, L"Bomb", 3)))
	{
		return E_FAIL;
	}

	if (FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/EFFECT/FireL/FireL_%d.png", L"EFFECT", TEX_MULTI, L"FireL", 3)))
	{
		return E_FAIL;
	}

	if (FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/EFFECT/FireLB/FireLB_%d.png", L"EFFECT", TEX_MULTI, L"FireLB", 3)))
	{
		return E_FAIL;
	}

	if (FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/EFFECT/FireLU/FireLU_%d.png", L"EFFECT", TEX_MULTI, L"FireLU", 3)))
	{
		return E_FAIL;
	}

	if (FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/EFFECT/FireB/FireB_%d.png", L"EFFECT", TEX_MULTI, L"FireB", 3)))
	{
		return E_FAIL;
	}

	if (FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/EFFECT/FireR/FireR_%d.png", L"EFFECT", TEX_MULTI, L"FireR", 3)))
	{
		return E_FAIL;
	}

	if (FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/EFFECT/FireRB/FireRB_%d.png", L"EFFECT", TEX_MULTI, L"FireRB", 3)))
	{
		return E_FAIL;
	}

	if (FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/EFFECT/FireRU/FireRU_%d.png", L"EFFECT", TEX_MULTI, L"FireRU", 3)))
	{
		return E_FAIL;
	}

	if (FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/EFFECT/FireU/FireU_%d.png", L"EFFECT", TEX_MULTI, L"FireU", 3)))
	{
		return E_FAIL;
	}

	if (FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/EFFECT/Splash/Splash_%d.png", L"EFFECT", TEX_MULTI, L"Splash", 4)))
	{
		return E_FAIL;
	}

	if (FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/EFFECT/DeadEffect/DeadEffect_%d.png", L"EFFECT", TEX_MULTI, L"DeadEffect", 3)))
	{
		return E_FAIL;
	}

	if (FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/EFFECT/BigExPlosion/BigExPlosion_%d.png", L"EFFECT", TEX_MULTI, L"BigExplosion", 24)))
	{
		return E_FAIL;
	}

	if (FAILED(CTextureMgr::GetInstance()->ReadImgPath(L"../Data/ImgPath.txt")))
	{
		return E_FAIL;
	}

	CTextureMgr::GetInstance()->SetString(L"Press Enter Key");

	LeaveCriticalSection(&pLogo->GetCrt());
	_endthreadex(0);

	return 0;
}


HRESULT CLogo::Initialize()
{
	InitializeCriticalSection(&m_Crt);
	m_hThread = (HANDLE)_beginthreadex(0, 0, ImgLoadThreadFunc, this, 0, 0);


	if (FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Logo.png", L"LOGO", TEX_SINGLE)))
	{
		return E_FAIL;
	}

	return S_OK;
}

int CLogo::Progress()
{
	if (KEY_DOWN(VK_RETURN))
	{
		WaitForSingleObject(m_hThread, INFINITE);
		CloseHandle(m_hThread);

		DeleteCriticalSection(&m_Crt);

		CSceneMgr::GetInstance()->SetScene(SC_STAGE);
		return 0;
	}

	return 0;
}

void CLogo::Render(HDC hDC)
{
	const TEXINFO*		pTexture = CTextureMgr::GetInstance()->GetTexture(L"LOGO");

	if (nullptr == pTexture)
		return;

	float fX = pTexture->tImgInfo.Width / 2.f;
	float fY = pTexture->tImgInfo.Height / 2.f;

	D3DXMATRIX		matTrans;
	D3DXMatrixTranslation(&matTrans, WINCX / 2.f, WINCY / 2.f, 0.f);

	// 로고 이미지 출력
	CDevice::GetInstance()->GetSprite()->SetTransform(&matTrans);
	CDevice::GetInstance()->GetSprite()->Draw(pTexture->pTexture,
		NULL,
		&D3DXVECTOR3(fX, fY, 0.f),
		NULL,
		D3DCOLOR_ARGB(255, 255, 255, 255));

	// 파일 경로 출력
	D3DXMatrixTranslation(&matTrans, 50.f, 500.f, 0.f);
	CDevice::GetInstance()->GetSprite()->SetTransform(&matTrans);
	CDevice::GetInstance()->GetFont()->DrawTextW(CDevice::GetInstance()->GetSprite(),
		CTextureMgr::GetInstance()->GetFilePath().c_str(),
		CTextureMgr::GetInstance()->GetFilePath().size(),
		nullptr, 
		0, 
		D3DCOLOR_ARGB(255, 255, 255, 255));
}

void CLogo::Release()
{
}
