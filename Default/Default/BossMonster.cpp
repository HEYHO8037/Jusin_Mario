#include "stdafx.h"
#include "BossMonster.h"


CBossMonster::CBossMonster()
{
}


CBossMonster::~CBossMonster()
{
}

void CBossMonster::Initialize(void)
{
	m_tInfo.fCX = 200.f;
	m_tInfo.fCY = 200.f;

	m_tInfo.m_fSpeed = 10.f;
	m_tInfo.m_iHp = 1000;
	QueryPerformanceFrequency(&timer);
}

void CBossMonster::Release(void)
{
}

int CBossMonster::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;



	Update_Rect();

	return OBJ_NOEVENT;
}

void CBossMonster::Late_Update(void)
{


}

void CBossMonster::Render(HDC hDC)
{
	HBRUSH	brush;
	HGDIOBJ h_old_brush;

	brush = CreateSolidBrush(RGB(255, 128, 64));
	h_old_brush = SelectObject(hDC, brush);
	Ellipse(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
	
	SelectObject(hDC, h_old_brush);
	DeleteObject(brush);
}

void CBossMonster::SetPlayerInfo(const CObj * pPlayer)
{
	m_pPlayer = pPlayer;
}

void CBossMonster::PatternNormalShot()
{
	float fDeltaTime = 0.f;

	while (true)
	{
		QueryPerformanceCounter(&start);



		QueryPerformanceCounter(&end);

		fDeltaTime = (end.QuadPart - start.QuadPart) / (float)timer.QuadPart;

	}
}

void CBossMonster::PatternWideShot()
{
	float fDeltaTime = 0.f;

	while (true)
	{
		QueryPerformanceCounter(&start);



		QueryPerformanceCounter(&end);

		fDeltaTime = (end.QuadPart - start.QuadPart) / (float)timer.QuadPart;

	}

}

void CBossMonster::PatternMoveToPlayer()
{

}
