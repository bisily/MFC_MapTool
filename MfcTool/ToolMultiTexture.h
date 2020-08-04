#pragma once
#include "ToolTexture.h"
class CToolMultiTexture :
	public CToolTexture
{
public:
	CToolMultiTexture();
	virtual ~CToolMultiTexture();

	// CToolTexture��(��) ���� ��ӵ�
	virtual HRESULT InsertTexture(const wstring & wstrFilePath, const wstring & wstrStateKey = L"", const int & iCount = 0) override;
	virtual const TEXINFO * GetTexture(const wstring & wstrStateKey = L"", const int & iCount = 0) override;
	virtual void Release() override;

private:
	map<wstring, vector<TEXINFO*>>		m_MapMultiTexture;
};

