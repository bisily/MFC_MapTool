#include "stdafx.h"
#include "MultiTexture.h"

CMultiTexture::CMultiTexture()
{
}


CMultiTexture::~CMultiTexture()
{
	Release();
}

HRESULT CMultiTexture::InsertTexture(const wstring & wstrFilePath, const wstring & wstrStateKey, const int & iCount)
{
	TCHAR		szPath[MAX_PATH] = L"";

	vector<TEXINFO*>		vecTexture;

	for (int i = 0; i < iCount; ++i)
	{
		wsprintf(szPath, wstrFilePath.c_str(), i);

		TEXINFO*		pTexInfo = new TEXINFO;
		ZeroMemory(pTexInfo, sizeof(TEXINFO));

		if (FAILED(D3DXGetImageInfoFromFile(
			szPath,			
			&pTexInfo->tImgInfo)))   
		{
			ERR_MSG(szPath);
			return E_FAIL;
		}

		if (FAILED(D3DXCreateTextureFromFileEx(
			CDevice::GetInstance()->GetDevice(),
			szPath,
			pTexInfo->tImgInfo.Width,
			pTexInfo->tImgInfo.Height,
			pTexInfo->tImgInfo.MipLevels,
			0,								
			pTexInfo->tImgInfo.Format,		
			D3DPOOL_MANAGED,				
			D3DX_DEFAULT,					
			D3DX_DEFAULT,					
			NULL,							
			&pTexInfo->tImgInfo,
			NULL,							
			&pTexInfo->pTexture)))
		{
			ERR_MSG(L"Multi Texture Image Load Failed");
			return E_FAIL;
		}

		vecTexture.push_back(pTexInfo);
	}

	m_MapMultiTexture.insert(make_pair(wstrStateKey, vecTexture));


	return S_OK;
}

const TEXINFO * CMultiTexture::GetTexture(const wstring & wstrStateKey, const int & iCount)
{
	auto		iter = m_MapMultiTexture.find(wstrStateKey);

	if (iter == m_MapMultiTexture.end())
		return nullptr;

	return iter->second[iCount];
}

size_t CMultiTexture::GetImageCount(wstring & wstrStateKey)
{
	auto		iter = m_MapMultiTexture.find(wstrStateKey);

	if (iter == m_MapMultiTexture.end())
		return -1;

	return iter->second.size();
}

void CMultiTexture::Release()
{
	//for (map<wstring, vector<TEXINFO*>>::iterator mapiter = m_MapMultiTexture.begin();
	//	mapiter != m_MapMultiTexture.end(); ++mapiter)
	//{
	//	for (size_t i = 0; i < mapiter->second.size(); ++i)
	//	{
	//		mapiter->second[i]->pTexture->Release();
	//		::Safe_Delete(mapiter->second[i]);
	//	}
	//	mapiter->second.clear();
	//}
	//m_MapMultiTexture.clear();

	for (auto mapIter : m_MapMultiTexture)
	{	

		for_each(mapIter.second.begin(), mapIter.second.end(), 
		[](TEXINFO*& Temp)
		{
			Temp->pTexture->Release();
			
			if (Temp)
			{
				delete Temp;
				Temp = nullptr;
			}
		});
		mapIter.second.clear();
	}
	
	m_MapMultiTexture.clear();
}
