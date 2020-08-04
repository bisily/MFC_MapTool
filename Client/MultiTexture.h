#pragma once

#include "Texture.h"

class CMultiTexture :
	public CTexture
{
public:
	CMultiTexture();
	virtual ~CMultiTexture();

public:
	// CTexture��(��) ���� ��ӵ�
	virtual HRESULT InsertTexture(const wstring & wstrFilePath, const wstring & wstrStateKey = L"", const int & iCount = 0) override;
	virtual const TEXINFO * GetTexture(const wstring & wstrStateKey = L"", const int & iCount = 0) override;
	virtual void Release() override;
	size_t	GetImageCount(wstring& wstrStateKey);

private:
	map<wstring, vector<TEXINFO*>>			m_MapMultiTexture;
};

