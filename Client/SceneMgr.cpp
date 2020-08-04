#include "stdafx.h"
#include "SceneMgr.h"

#include "Logo.h"
#include "Stage.h"
#include "Ending.h"

IMPLEMENT_SINGLETON(CSceneMgr)

CSceneMgr::CSceneMgr()
{
}


CSceneMgr::~CSceneMgr()
{
	Release();
}

HRESULT CSceneMgr::SetScene(SCENEID eScene)
{
	if (nullptr != m_pScene)
		Release();

	switch (eScene)
	{
	case SC_LOGO:
		m_pScene = new CLogo;
		break;
	case SC_STAGE:
		m_pScene = new CStage;
		break;

	case SC_ENDING:
		m_pScene = new CEnding;
		break;
	}

	if (FAILED(m_pScene->Initialize()))
	{
		ERR_MSG(L"Scene Init Failed");
		return E_FAIL;
	}

	return S_OK;
}

int CSceneMgr::Progress()
{
	if (nullptr != m_pScene)
		m_pScene->Progress();

	return 0;
}

void CSceneMgr::Render(HDC hDC)
{
	if (nullptr != m_pScene)
		m_pScene->Render(hDC);
}

void CSceneMgr::Release()
{
	Safe_Delete(m_pScene);
}

