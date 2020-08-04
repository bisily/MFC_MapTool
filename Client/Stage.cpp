#include "stdafx.h"
#include "Stage.h"
#include "ObjMgr.h"

CStage::CStage()
{
}


CStage::~CStage()
{
	Release();
}

HRESULT CStage::Initialize()
{
	CSoundMgr::GetInstance()->PlayBGM(L"espera.wav");

	m_pBack = new CBack;
	if (FAILED(m_pBack->Initialize()))
	{
		ERR_MSG(L"Back Initialize Failed");
		return E_FAIL;
	}

	return S_OK;
}

int CStage::Progress()
{
	int iResult = 0;

	m_pBack->Progress();
	iResult = CObjMgr::GetInstance()->Progress();

	return 0;
}

void CStage::Render(HDC hDC)
{
	m_pBack->Render(hDC);
	CObjMgr::GetInstance()->Render(hDC);
}

void CStage::Release()
{
	Safe_Delete(m_pBack);
}
