#include "stdafx.h"
#include "TextureMgr.h"

IMPLEMENT_SINGLETON(CToolTextureMgr)

CToolTextureMgr::CToolTextureMgr()
{
}


CToolTextureMgr::~CToolTextureMgr()
{
	Release();
}

HRESULT CToolTextureMgr::InsertTexture(const wstring & wstrFilePath, const wstring & wstrObjKey, TEXTYPE eTexType, const wstring & wstrStateKey, const int & iCnt)
{
	map<wstring, CToolTexture*>::iterator iter = m_MapTexture.find(wstrObjKey);

	if (iter == m_MapTexture.end())
	{
		CToolTexture*	pTexture = nullptr;

		switch (eTexType)
		{
		case TEX_SINGLE:
			pTexture = new CToolSingleTexture;
			break;
		case TEX_MULTI:
			pTexture = new CToolMultiTexture;
			break;
		}

		if (FAILED(pTexture->InsertTexture(wstrFilePath, wstrStateKey, iCnt)))
		{
			ERR_MSG(wstrObjKey.c_str());
			return E_FAIL;
		}

		// 이미지를 불러오고 맵에 넣어주는 코드
		m_MapTexture.insert(make_pair(wstrObjKey, pTexture));
	}
	else
	{
		if (eTexType == TEX_MULTI)
			iter->second->InsertTexture(wstrFilePath, wstrStateKey, iCnt);
	}


	return S_OK;
}

const TEXINFO * CToolTextureMgr::GetTexture(const wstring & wstrObjKey, const wstring & wstrStateKey, const int & iCount)
{
	auto	iter = m_MapTexture.find(wstrObjKey.c_str());

	if (iter == m_MapTexture.end())
	{
		return nullptr;
	}

	return iter->second->GetTexture(wstrStateKey, iCount);
	
}

void CToolTextureMgr::Release()
{
	for_each(m_MapTexture.begin(), m_MapTexture.end(), DeleteMap());
	m_MapTexture.clear();
}


