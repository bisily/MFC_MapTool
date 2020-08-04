// MapDialog.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "MfcTool.h"
#include "MapDialog.h"
#include "afxdialogex.h"
#include "MainFrm.h"
#include "MfcToolView.h"
#include "FileInfo.h"
#include "Building.h"

// CMapDialog 대화 상자입니다.

IMPLEMENT_DYNAMIC(CMapDialog, CDialog)

CMapDialog::CMapDialog(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_MAPDIALOG, pParent)
	, m_TileOption{}
{

}

CMapDialog::~CMapDialog()
{
	for (auto i : m_MapPngImage)
	{
		i.second->Destroy();
		Safe_Delete(i.second);
	}
	m_MapPngImage.clear();

}

void CMapDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_RADIO1, m_TileOption[0]);
	DDX_Control(pDX, IDC_RADIO2, m_TileOption[1]);
	DDX_Control(pDX, IDC_RADIO3, m_TileOption[2]);
	DDX_Control(pDX, IDC_PICTURE, m_Picture);
	DDX_Control(pDX, IDC_LIST1, m_StructList);
	DDX_Control(pDX, IDC_PICTURE_STRUCT, m_Picture_Struct);

	if (m_bStart)
	{
		m_TileOption[0].SetCheck(TRUE);
		m_bStart = false;

		CImage image;

		image.Load(L"../Texture/Map/Tile/Tile0.png");

		CBitmap bitmap;
		bitmap.Attach(image.Detach());

		m_Picture.SetBitmap(bitmap);
	}
	DDX_Control(pDX, IDC_LIST5, m_AddList);
}

BEGIN_MESSAGE_MAP(CMapDialog, CDialog)
	ON_BN_CLICKED(IDC_RADIO1, &CMapDialog::OnSelectRadio)
	ON_BN_CLICKED(IDC_RADIO2, &CMapDialog::OnSelectRadio2)
	ON_BN_CLICKED(IDC_RADIO3, &CMapDialog::OnSelectRadio3)
	ON_BN_CLICKED(IDC_BUTTON2, &CMapDialog::OnAddObj)
	ON_BN_CLICKED(IDC_BUTTON4, &CMapDialog::OnDeleteObj)
	ON_WM_DROPFILES()
	ON_LBN_SELCHANGE(IDC_LIST1, &CMapDialog::OnList)
	ON_BN_CLICKED(IDC_BUTTON1, &CMapDialog::OnTileSave)
	ON_BN_CLICKED(IDC_BUTTON3, &CMapDialog::OnTileLoad)
	ON_BN_CLICKED(IDC_BUTTON5, &CMapDialog::OnSaveObject)
	ON_BN_CLICKED(IDC_BUTTON6, &CMapDialog::OnLoadObject)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BUTTON7, &CMapDialog::OnDelete)
	ON_BN_CLICKED(IDC_BUTTON15, &CMapDialog::OnListObjDelete)
END_MESSAGE_MAP()


// CMapDialog 메시지 처리기입니다.
void CMapDialog::OnSelectRadio()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	UpdateData(TRUE);

	CImage image;
	image.Load(L"../Texture/Map/Tile/Tile0.png");

	CBitmap bitmap;
	bitmap.Attach(image.Detach());

	m_Picture.SetBitmap(bitmap);

	UpdateData(FALSE);

	((CMainFrame*)AfxGetMainWnd())->GetToolView()->SetDrawID(0);
	((CMainFrame*)AfxGetMainWnd())->GetToolView()->SetTileOption(0);

}

void CMapDialog::OnSelectRadio2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	UpdateData(TRUE);

	CImage image;
	image.Load(L"../Texture/Map/Tile/Tile1.png");

	CBitmap bitmap;
	bitmap.Attach(image.Detach());

	m_Picture.SetBitmap(bitmap);
	
	UpdateData(FALSE);

	((CMainFrame*)AfxGetMainWnd())->GetToolView()->SetDrawID(1);
	((CMainFrame*)AfxGetMainWnd())->GetToolView()->SetTileOption(1);

}

void CMapDialog::OnSelectRadio3()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	UpdateData(TRUE);

	CImage image;
	image.Load(L"../Texture/Map/Tile/Tile2.png");

	CBitmap bitmap;
	bitmap.Attach(image.Detach());

	m_Picture.SetBitmap(bitmap);

	UpdateData(FALSE);
	
	((CMainFrame*)AfxGetMainWnd())->GetToolView()->SetDrawID(2);
	((CMainFrame*)AfxGetMainWnd())->GetToolView()->SetTileOption(2);

}

void CMapDialog::OnTileSave()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	CFileDialog Dlg(FALSE, L"dat", L"*.dat", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, L"*.dat", this);

	if (Dlg.DoModal() == IDCANCEL)
	{
		return;
	}

	TCHAR	szDirPath[MAX_PATH]{};

	// 프로젝트 proj 파일이 있는 경로를 가져옮
	GetCurrentDirectory(sizeof(szDirPath), szDirPath);
	
	// 현재 문자열을 세팅해줌
	SetCurrentDirectory(szDirPath);

	// / 문자까지 문자열을 삭제해줌
	PathRemoveFileSpec(szDirPath);
	
	// 문자열 붙이기
	lstrcat(szDirPath, L"\\Data");

	// 디렉토리 변경을 불허한다.
	Dlg.m_ofn.lpstrInitialDir = szDirPath;

	HANDLE	hFile = CreateFile(Dlg.GetPathName(),
		GENERIC_WRITE,
		0,
		NULL,
		CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		NULL);

	DWORD		dwByte = 0;

	CBackGround*	pBack = ((CMainFrame*)AfxGetMainWnd())->GetToolView()->GetBackGround();

	if (nullptr == pBack)
	{
		return;
	}

	const vector<TILE*>* pVecTile = pBack->GetvecTile();

	if (nullptr == pVecTile)
	{
		return;
	}

	for (size_t i = 0; i < pVecTile->size(); ++i)
	{
		WriteFile(hFile, (*pVecTile)[i], sizeof(TILE), &dwByte, NULL);
	}

	CloseHandle(hFile);
}

void CMapDialog::OnTileLoad()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	UpdateData(TRUE);

	CFileDialog	Dlg(TRUE, L"dat", L"*.dat",OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, L"*.dat", this);

	if (Dlg.DoModal() == IDCANCEL)
		return;

	CBackGround*	pBack = ((CMainFrame*)AfxGetMainWnd())->GetToolView()->GetBackGround();
	
	if (nullptr == pBack)
	{
		return;
	}

	for_each(pBack->GetvecTile()->begin(), pBack->GetvecTile()->end(), [](TILE*& Temp)
	{
		if (nullptr != Temp)
		{
			delete Temp;
			Temp = nullptr;
		}
	});
	pBack->GetvecTile()->clear();

	TCHAR		szDirPath[MAX_PATH]{};

	GetCurrentDirectory(sizeof(szDirPath), szDirPath);
	// 현재 디렉토리 경로를 얻어옴(vcproj 파일이 있는 디렉토리)

	SetCurrentDirectory(szDirPath);
	// 응용 프로그램의 현재 작업 디렉토리를 지정된 디렉토리로 설정해주는 함수


	PathRemoveFileSpec(szDirPath);
	// 마지막 경로를 잘라내고 남는 경로를 저장해주는 함수

	lstrcat(szDirPath, L"\\Data");

	Dlg.m_ofn.lpstrInitialDir = szDirPath;
	
	HANDLE	hFile = CreateFile(Dlg.GetPathName(), GENERIC_READ, 0, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	DWORD	dwByte = 0;

	while (true)
	{
		TILE*		pTile = new TILE;
		ReadFile(hFile, pTile, sizeof(TILE), &dwByte, NULL);
		
		if (dwByte == 0)
		{
			Safe_Delete(pTile);
			break;
		}

		pBack->GetvecTile()->push_back(pTile);
	}

	CloseHandle(hFile);

	UpdateData(FALSE);

	((CMainFrame*)AfxGetMainWnd())->GetToolView()->PostMessageW(WM_PAINT);
}

void CMapDialog::OnDropFiles(HDROP hDropInfo)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	UpdateData(TRUE);

	int iFileNumer = DragQueryFile(hDropInfo, -1, NULL, 0);

	if (0 > iFileNumer)
	{
		return;
	}

	TCHAR	szFullPath[MAX_PATH] = L"";

	CFileInfo	FileInfo;

	for (int i = 0; i < iFileNumer; ++i)
	{
		// 2번째 인자에 -1이 아닌 0 ~ N 까지
		// 들어오면 그 인덱스에 해당하는 파일명과 데이터를 버퍼에 담아줌
		DragQueryFile(hDropInfo, i, (LPWSTR)szFullPath, MAX_PATH);

		wstring wstrRelativePath = FileInfo.ConvertRelativePath(szFullPath);

		CString strImageName;
		// 제일 뒤에 파일명만 남겨줌
		strImageName = PathFindFileName(wstrRelativePath.c_str());

		// 확장자 명을 제거
		PathRemoveExtension((LPWSTR)strImageName.operator LPCWSTR());

		auto iter = m_MapPngImage.find(strImageName);

		if (iter == m_MapPngImage.end())
		{
			CImage*		pPngImage = new CImage;
			pPngImage->Load(wstrRelativePath.c_str());

			m_MapPngImage.insert(make_pair(strImageName, pPngImage));
			m_StructList.InsertString(-1, strImageName);
		}


		/*FileInfo.DirInfoExtraction(szFullPath, m_PathList);

		wstring		wstrCombine = L"";
		TCHAR		szBuf[MIN_STR] = L"";

		for (auto& i : m_PathList)
		{
		_itow_s(i->iCount, szBuf, 10);

		wstrCombine = i->wstrObjKey + L'|' + i->wstrStateKey + L'|';
		wstrCombine += szBuf;
		wstrCombine += L'|' + i->wstrPath;

		m_StructList.AddString(wstrCombine.c_str());
		}*/
	}

	HorizontalScroll();
	UpdateData(FALSE);

	CDialog::OnDropFiles(hDropInfo);
}

void CMapDialog::OnAddObj()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	UpdateData(TRUE);

	CString		strSelectName;
	
	int	iSelectIndex = m_StructList.GetCurSel();

	if (0 > iSelectIndex)
	{
		return;
	}
	
	m_StructList.GetText(iSelectIndex, strSelectName);

	auto iter = m_MapPngImage.find(strSelectName);

	if (iter == m_MapPngImage.end())
	{
		return;
	}

	// 먼저 Map과 Obj키 값을 지워준다
	((CMainFrame*)AfxGetMainWnd())->GetToolView()->GetMapPngImage().clear();
	((CMainFrame*)AfxGetMainWnd())->GetToolView()->SetObjkey(L"");
	
	CString tempKey, szName;
	int retval = 0;

	retval = strSelectName.Find('_');
	szName = strSelectName.Left(retval);
	tempKey = strSelectName.Mid(retval + 1);

	if (!lstrcmp(szName, L"Drum"))
	{
		// 맵과 Obj키 값을 세팅 해준다
		((CMainFrame*)AfxGetMainWnd())->GetToolView()->GetMapPngImage().insert(make_pair(strSelectName, iter->second));
		((CMainFrame*)AfxGetMainWnd())->GetToolView()->SetObjkey(L"DRUM");
		((CMainFrame*)AfxGetMainWnd())->GetToolView()->SetObjkey(L"ACTIVEOBJECT");
	}
	else if (!lstrcmp(szName, L"Generator"))
	{
		// 맵과 Obj키 값을 세팅 해준다
		((CMainFrame*)AfxGetMainWnd())->GetToolView()->GetMapPngImage().insert(make_pair(strSelectName, iter->second));
		((CMainFrame*)AfxGetMainWnd())->GetToolView()->SetObjkey(L"GENERATOR");
		((CMainFrame*)AfxGetMainWnd())->GetToolView()->SetObjkey(L"ACTIVEOBJECT");
	}
	else
	{
		// 맵과 Obj키 값을 세팅 해준다
		((CMainFrame*)AfxGetMainWnd())->GetToolView()->GetMapPngImage().insert(make_pair(strSelectName, iter->second));
		((CMainFrame*)AfxGetMainWnd())->GetToolView()->SetObjkey(L"BUILDING");
	}

	UpdateData(FALSE);

	((CMainFrame*)AfxGetMainWnd())->GetToolView()->PostMessageW(WM_PAINT);
}

void CMapDialog::OnDeleteObj()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	((CMainFrame*)AfxGetMainWnd())->GetToolView()->GetMapPngImage().clear();
	((CMainFrame*)AfxGetMainWnd())->GetToolView()->PostMessageW(WM_PAINT);
}

void CMapDialog::OnList()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	UpdateData(TRUE);

	CString		strSelectName;

	int			iSelectIndex = m_StructList.GetCurSel();

	if (0 > iSelectIndex)
	{
		return;
	}

	m_StructList.GetText(iSelectIndex, strSelectName);

	auto iter = m_MapPngImage.find(strSelectName);

	if (iter == m_MapPngImage.end())
	{
		return;
	}

	m_Picture_Struct.SetBitmap(*iter->second);
	UpdateData(FALSE);
}

void CMapDialog::OnSaveObject()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	CFileDialog Dlg(FALSE, L"dat", L"*.dat", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, L"*.dat", this);

	if (Dlg.DoModal() == IDCANCEL)
	{
		return;
	}

	TCHAR	szDirPath[MAX_PATH]{};

	GetCurrentDirectory(sizeof(szDirPath), szDirPath);
	// 현재 디렉토리 경로를 얻어옴(vcproj 파일이 있는 디렉토리)
	SetCurrentDirectory(szDirPath);
	// 응용 프로그램의 현재 작업 디렉토리를 지정된 디렉토리로 설정해주는 함수
	PathRemoveFileSpec(szDirPath);
	// 마지막 경로를 잘라내고 남는 경로를 저장해주는 함수
	lstrcat(szDirPath, L"\\Data");

	Dlg.m_ofn.lpstrInitialDir = szDirPath;


	DWORD		dwByte = 0;
	
	list<CObj*> pBuildingList = CObjMgr::GetInstance()->GetBuildingObjList();

	HANDLE	hFile = CreateFile(Dlg.GetPathName(), GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	for (auto list : pBuildingList)
	{
		WriteFile(hFile, &list->GetInfo()->vPos, sizeof(D3DXVECTOR3), &dwByte, NULL);

		TCHAR szBuffer_1[MIN_STR];
		
		lstrcpy(szBuffer_1, list->GetStateKey().c_str());
		lstrcat(szBuffer_1, L"_");
		lstrcat(szBuffer_1, list->GetCount().c_str());

		WriteFile(hFile, szBuffer_1, MIN_STR, &dwByte, NULL);
	}

	list<CObj*> pActiveObjList = CObjMgr::GetInstance()->GetActiveObjList();

	if (!pActiveObjList.empty())
	{	
		for (auto list : pActiveObjList)
		{
			WriteFile(hFile, &list->GetInfo()->vPos, sizeof(D3DXVECTOR3), &dwByte, NULL);

			TCHAR szBuffer_1[MIN_STR];

			lstrcpy(szBuffer_1, list->GetStateKey().c_str());
			lstrcat(szBuffer_1, L"_");
			lstrcat(szBuffer_1, list->GetCount().c_str());

			WriteFile(hFile, szBuffer_1, MIN_STR, &dwByte, NULL);
		}
	}

	CloseHandle(hFile);
}

void CMapDialog::OnLoadObject()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	UpdateData(TRUE);

	CFileDialog Dlg(TRUE, L"dat", L"*.dat", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, L"*.dat", this);

	// 모달 : 다른 창으로 넘어 갈 수 없고 발생시킨 다이얼로그와 대화를 끝내야 다른 작업을 할 수 있는 다이얼로그
	if (Dlg.DoModal() == IDCANCEL)
	{
		return;
	}

	TCHAR		szDirPath[MAX_PATH]{};
	GetCurrentDirectory(sizeof(szDirPath), szDirPath);
	SetCurrentDirectory(szDirPath);
	PathRemoveFileSpec(szDirPath);

	lstrcat(szDirPath, L"\\Data");
	Dlg.m_ofn.lpstrInitialDir = szDirPath;

	Release();
	m_StructList.ResetContent();

	HANDLE	hFile = CreateFile(Dlg.GetPathName(), GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	DWORD	dwByte = 0;
	bool	bData = false;
	TCHAR	szBuffer[MIN_STR] = L"";
	D3DXVECTOR3 vPos;
	
	while (true)
	{
		ReadFile(hFile, vPos, sizeof(D3DXVECTOR3), &dwByte, NULL);
	
		ReadFile(hFile, szBuffer, MIN_STR, &dwByte, NULL);

		if (dwByte == 0)
		{
			break;
		}
		
		if (lstrcmp(szBuffer, L"Drum_0") && lstrcmp(szBuffer, L"Generator_0") && lstrcmp(szBuffer, L"Generator_1"))
		{
			m_AddList.AddString(szBuffer);
			CObjMgr::GetInstance()->AddObject(CObjFactory<CBuilding>::CreateObj(vPos, szBuffer), OBJ_BUILDING);
		}
		else
		{
			m_AddList.AddString(szBuffer);
			CObjMgr::GetInstance()->AddObject(CObjFactory<CBuilding>::CreateObj(vPos, szBuffer), OBJ_ACTIVE);
		}

	}

	CloseHandle(hFile);

	UpdateData(FALSE);

	((CMainFrame*)AfxGetMainWnd())->GetToolView()->PostMessageW(WM_PAINT);

}

void CMapDialog::Release()
{
	for_each(m_MapPngImage.begin(), m_MapPngImage.end(), DeleteMap());
	m_MapPngImage.clear();
}

void CMapDialog::HorizontalScroll()
{
	CString		strName;
	CSize		csize;

	int			iDCX = 0;

	CDC*		pDC = m_StructList.GetDC();

	for (int i = 0; i < m_StructList.GetCount(); ++i)
	{
		m_StructList.GetText(i, strName);

		csize = pDC->GetTextExtent(strName);

		if (csize.cx > iDCX)
		{
			iDCX = csize.cx;
		}
	}
	m_StructList.ReleaseDC(pDC);

	if (m_StructList.GetHorizontalExtent() < iDCX)
	{
		m_StructList.SetHorizontalExtent(iDCX);
	}
}

void CMapDialog::OnDestroy()
{
	CDialog::OnDestroy();

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
}

void CMapDialog::OnDelete()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	UpdateData(TRUE);

	CString		strSelectName;

	int	iSelectIndex = m_StructList.GetCurSel();

	if (0 > iSelectIndex)
	{
		return;
	}

	m_StructList.GetText(iSelectIndex, strSelectName);
	auto iter = m_MapPngImage.find(strSelectName);

	if (iter == m_MapPngImage.end())
	{
		return;
	}

	Safe_Delete(iter->second);
	m_MapPngImage.erase(strSelectName);

	m_StructList.DeleteString(iSelectIndex);

	UpdateData(FALSE);

}

void CMapDialog::OnListObjDelete()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	UpdateData(TRUE);

	int iCur = m_AddList.GetCurSel();
	
	if (0 > iCur)
	{
		return;
	}

	list<CObj*>::iterator begin = CObjMgr::GetInstance()->GetBuildingObjList().begin();

	for (int i = 0; i < iCur; ++i)
	{
		++begin;
	}

	Safe_Delete(*begin);

	CObjMgr::GetInstance()->GetBuildingObjList().erase(begin);

	m_AddList.DeleteString(iCur);

	UpdateData(FALSE);

	((CMainFrame*)AfxGetMainWnd())->GetToolView()->PostMessageW(WM_PAINT);

}
