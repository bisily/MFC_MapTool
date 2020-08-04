#pragma once

extern	HWND g_hWnd;

const	int		WINCX = 800;
const	int		WINCY = 600;

const	int		MAPSIZEX = 1450;
const	int		MAPSIZEY = 2450;

const	WORD	MIN_STR    = 64;
const	WORD	MIDDLE_STR = 128;
const	WORD	MAX_STR    = 256;

const	int		TILESIZEX = 50;
const	int		TILESIZEY = 50;

const	int		TILEX = 30;
const	int		TILEY = 100;


#define NO_COPY(CLASSNAME)							\
	private:										\
	CLASSNAME(const CLASSNAME&);					\
	CLASSNAME& operator = (const CLASSNAME&);		

#define DECLARE_SINGLETON(CLASSNAME)				\
	NO_COPY(CLASSNAME)								\
	private:										\
	static CLASSNAME*	m_pInstance;				\
	public:											\
	static CLASSNAME*	GetInstance( void );		\
	static void DestroyInstance( void );			

#define IMPLEMENT_SINGLETON(CLASSNAME)				\
	CLASSNAME*	CLASSNAME::m_pInstance = NULL;		\
	CLASSNAME*	CLASSNAME::GetInstance( void )	{	\
	if(NULL == m_pInstance) {						\
	m_pInstance = new CLASSNAME;					\
	}												\
	return m_pInstance;								\
	}												\
	void CLASSNAME::DestroyInstance( void ) {		\
	if(NULL != m_pInstance)	{						\
	delete m_pInstance;								\
	m_pInstance = NULL;								\
	}												\
	}

#define ERR_MSG(Message)		MessageBox(g_hWnd, Message, L"System Error", NULL)

#define GET_TIME				CTimeMgr::GetInstance()->GetTime()