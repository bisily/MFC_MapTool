#pragma once

#include "ToolSingleTexture.h"
#include "ToolMultiTexture.h" 

class CToolTextureMgr
{
	DECLARE_SINGLETON(CToolTextureMgr)

private:
	map<wstring, CToolTexture*>			m_MapTexture;

public:
	HRESULT			InsertTexture(const wstring& wstrFilePath, const wstring& wstrObjKey, TEXTYPE eTexType, const wstring& wstrStateKey = L"", const int& iCnt = 0);

	const TEXINFO*	GetTexture(const wstring& wstrObjKey, const wstring& wstrStateKey = L"", const int& iCount = 0);

	void		Release();

private:
	CToolTextureMgr();
	~CToolTextureMgr();
};

