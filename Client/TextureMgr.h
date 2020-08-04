#pragma once

#include "SingleTexture.h"
#include "MultiTexture.h" 

class CTextureMgr
{
	DECLARE_SINGLETON(CTextureMgr)

private:
	map<wstring, CTexture*>			m_MapTexture;
	wstring							m_wstrFullPath;

public:
	HRESULT			InsertTexture(const wstring& wstrFilePath, const wstring& wstrObjKey, TEXTYPE eTexType, const wstring& wstrStateKey = L"", const int& iCnt = 0);

	const TEXINFO*	GetTexture(const wstring& wstrObjKey, const wstring& wstrStateKey = L"", const int& iCount = 0);

	HRESULT		ReadImgPath(const wstring& wstrImgPath);
	size_t		GetImageCount(wstring wstrObjKey, wstring& wstrStateKey);
	void		SetString(const wstring& wstrPath) { m_wstrFullPath = wstrPath; }
	const wstring&		GetFilePath() { return m_wstrFullPath; }
	void		Release();

private:
	CTextureMgr();
	~CTextureMgr();
};

