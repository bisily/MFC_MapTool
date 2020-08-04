#pragma once

template<typename T>
static void Safe_Delete(T& Temp)
{
	if (nullptr != Temp)
	{
		delete Temp;
		Temp = nullptr;
	}
}

struct DeleteMap
{
	template<typename T>
	void operator()(T& Temp)
	{
		if (Temp.second)
		{
			delete Temp.second;
			Temp.second = nullptr;
		}
	}
};

struct DeleteOBJ
{
	template<typename T>
	void operator()(T& Temp)
	{
		if (Temp)
		{
			delete Temp;
			Temp = nullptr;
		}
	}
};

static D3DXVECTOR3	GetMouse(void)
{
	POINT		Pt;

	GetCursorPos(&Pt);
	ScreenToClient(g_hWnd, &Pt);

	return D3DXVECTOR3(float(Pt.x), float(Pt.y), 0.f);
}

template <typename T>
bool LessY(T dst, T src)
{
	return dst->GetInfo()->vPos.y < src->GetInfo()->vPos.y;
}
