#include "stdafx.h"
#include "ToolSingleTexture.h"


CToolSingleTexture::CToolSingleTexture()
{
}


CToolSingleTexture::~CToolSingleTexture()
{
	Release();
}

HRESULT CToolSingleTexture::InsertTexture(const wstring & wstrFilePath, const wstring & wstrStateKey, const int & iCount)
{
	m_pTexInfo = new TEXINFO;
	ZeroMemory(m_pTexInfo, sizeof(TEXINFO));

	// 텍스쳐를 불러드림
	if (FAILED(D3DXGetImageInfoFromFile(wstrFilePath.c_str(), &m_pTexInfo->tImgInfo)))
	{
		ERR_MSG(wstrFilePath.c_str());
		return E_FAIL;
	}

	if (FAILED(D3DXCreateTextureFromFileEx(CDevice::GetInstance()->GetDevice(), wstrFilePath.c_str(), m_pTexInfo->tImgInfo.Width, m_pTexInfo->tImgInfo.Height, m_pTexInfo->tImgInfo.MipLevels, 0, m_pTexInfo->tImgInfo.Format, D3DPOOL_MANAGED, D3DX_DEFAULT, D3DX_DEFAULT, NULL, &m_pTexInfo->tImgInfo, NULL, &m_pTexInfo->pTexture)))
	{
		ERR_MSG(L"Single Texture Image Load Failed");
		return E_FAIL;
	}

	return S_OK;
}

const TEXINFO * CToolSingleTexture::GetTexture(const wstring & wstrStateKey, const int & iCount)
{
	return m_pTexInfo;
}

void CToolSingleTexture::Release()
{
	// 제거 순서 ) 1. 컴 객체 해제, 2. 동적할당 해제
	m_pTexInfo->pTexture->Release();
	Safe_Delete(m_pTexInfo);
}
