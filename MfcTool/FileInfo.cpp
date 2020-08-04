#include "stdafx.h"
#include "FileInfo.h"

CFileInfo::CFileInfo()
{
}


CFileInfo::~CFileInfo()
{
}

wstring CFileInfo::ConvertRelativePath(wstring wstrFullPath)
{
	TCHAR		szRelativePath[MAX_PATH] = L"";
	TCHAR		szDirPath[MAX_PATH] = L"";

	GetCurrentDirectory(sizeof(szDirPath), szDirPath);

	PathRelativePathTo((LPWSTR)szRelativePath, szDirPath, FILE_ATTRIBUTE_DIRECTORY, wstrFullPath.c_str(), FILE_ATTRIBUTE_NORMAL);

	return szRelativePath;
}

void CFileInfo::DirInfoExtraction(const wstring & wstrPath, list<IMGPATH*>& rPathInfoList)
{
	CFileFind		Find;
	Find.FindFile(wstrPath.c_str());

	int iContiue = 1;

	while (iContiue)
	{
		iContiue = Find.FindNextFile();

		if (Find.IsDots())
			continue;

		if (Find.IsDirectory())
		{
			DirInfoExtraction(wstring(Find.GetFilePath() + L"\\*.*"), rPathInfoList);
		}
		else
		{
			if (Find.IsSystem())
			{
				continue;
			}

			IMGPATH*	pImgPath = new IMGPATH;

			TCHAR		szPathBuf[MAX_PATH] = L"";
			lstrcpy(szPathBuf, Find.GetFilePath().operator LPCWSTR());
			PathRemoveFileSpec(szPathBuf);
			pImgPath->iCount = DirFileCount(szPathBuf);

			wstring wstrTextureName = Find.GetFileTitle().operator LPCWSTR();

			wstrTextureName = wstrTextureName.substr(0, wstrTextureName.size() - 1) + L"%d.png";

			//////////////////////////////////////////

			TCHAR	szBuf[MAX_PATH] = L"";
			lstrcpy(szBuf, (LPWSTR)Find.GetFilePath().operator LPCWSTR());

			PathRemoveFileSpec(szBuf);

			PathCombine(szBuf, szBuf, (LPWSTR)wstrTextureName.c_str());

			pImgPath->wstrPath = ConvertRelativePath(szBuf);

			PathRemoveFileSpec(szBuf);

			pImgPath->wstrStateKey = PathFindFileName(szBuf);

			PathRemoveFileSpec(szBuf);

			pImgPath->wstrObjKey = PathFindFileName(szBuf);

			rPathInfoList.push_back(pImgPath);

			Find.FindFile(Find.GetFilePath());
			Find.FindNextFile();
		}
	}

}

int CFileInfo::DirFileCount(const wstring & wstrPath)
{
	wstring		wstrTemp = wstrPath + L"\\*.png";

	CFileFind	Find;
	Find.FindFile(wstrTemp.c_str());

	int iContinue = 1;
	int iFileCount = 0;
	
	while (iContinue)
	{
		iContinue = Find.FindNextFile();

		if (!Find.IsDirectory())
			++iFileCount;
	}

	return iFileCount;
}
