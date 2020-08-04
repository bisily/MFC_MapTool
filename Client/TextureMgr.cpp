#include "stdafx.h"
#include "TextureMgr.h"

IMPLEMENT_SINGLETON(CTextureMgr)

CTextureMgr::CTextureMgr()
{
}


CTextureMgr::~CTextureMgr()
{
	Release();
}

HRESULT CTextureMgr::InsertTexture(const wstring & wstrFilePath, const wstring & wstrObjKey, TEXTYPE eTexType, const wstring & wstrStateKey, const int & iCnt)
{
	map<wstring, CTexture*>::iterator iter = m_MapTexture.find(wstrObjKey);

	m_wstrFullPath = wstrFilePath;

	if (iter == m_MapTexture.end())
	{
		CTexture*	pTexture = nullptr;

		switch (eTexType)
		{
		case TEX_SINGLE:
			pTexture = new CSingleTexture;
			break;
		case TEX_MULTI:
			pTexture = new CMultiTexture;
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

const TEXINFO * CTextureMgr::GetTexture(const wstring & wstrObjKey, const wstring & wstrStateKey, const int & iCount)
{
	auto	iter = m_MapTexture.find(wstrObjKey.c_str());

	if (iter == m_MapTexture.end())
	{
		return nullptr;
	}

	return iter->second->GetTexture(wstrStateKey, iCount);
	
}

HRESULT CTextureMgr::ReadImgPath(const wstring & wstrImgPath)
{
	wifstream	LoadFile;
	LoadFile.open(wstrImgPath.c_str(), ios::in);

	TCHAR		szObjKey[MIN_STR] = L"";
	TCHAR		szStateKey[MIN_STR] = L"";
	TCHAR		szCount[MIN_STR] = L"";
	TCHAR		szImgPath[MAX_PATH] = L"";

	while (!LoadFile.eof())
	{
		LoadFile.getline(szObjKey, MIN_STR, '|');
		LoadFile.getline(szStateKey, MIN_STR, '|');
		LoadFile.getline(szCount, MIN_STR, '|');
		LoadFile.getline(szImgPath, MAX_PATH);

		int iCount = _ttoi(szCount);

		if (FAILED(InsertTexture(szImgPath, szObjKey, TEX_MULTI, szStateKey, iCount)))
		{
			return E_FAIL;
		}
	}

	LoadFile.close();

	return S_OK;
}

size_t CTextureMgr::GetImageCount(wstring wstrObjKey, wstring & wstrStateKey)
{
	auto		iter = m_MapTexture.find(wstrObjKey);

	if (iter == m_MapTexture.end())
	{
		return -1;
	}

	return dynamic_cast<CMultiTexture*>(iter->second)->GetImageCount(wstrStateKey);
}

void CTextureMgr::Release()
{
	for_each(m_MapTexture.begin(), m_MapTexture.end(), DeleteMap());
	m_MapTexture.clear();
}


