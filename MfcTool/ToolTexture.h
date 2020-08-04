#pragma once

#include "Include.h"

class CToolTexture
{
public:
	virtual HRESULT			InsertTexture(const wstring& wstrFilePath, const wstring& wstrStateKey = L"", const int& iCount = 0) PURE;
	virtual const TEXINFO*	GetTexture(const wstring& wstrStateKey = L"", const int& iCount = 0) PURE;
	virtual void			Release()PURE;

public:
	CToolTexture();
	virtual ~CToolTexture();
};

